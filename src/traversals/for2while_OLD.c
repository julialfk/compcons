/**
 * @file
 *
 * Traversal: ForToWhile
 * UID      : FTW
 *
 *
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"

static char *copy_entry_name(char *original) {
    char *entry_name_cpy = (char *)malloc(sizeof(char)
                                        * (strlen(original) + 1));
    strcpy(entry_name_cpy, original);
    return entry_name_cpy;
}

int digit_counter(int digit) {
    int count = 0;
    do {
    digit /= 10;
    ++count;
  } while (digit != 0);
  return count;
}

void FTWinit() {
    struct data_ftw *data = DATA_FTW_GET();
    data->index_counter = 0;
    data->for_funbody = NULL;
    data->head_for_decls = NULL;
    data->tail_funbody_decls = NULL;
    data->parent_for_stmt = NULL;
    data->ste_index = NULL;
    data->tail_for_assigns = NULL;
    data->head_for_assigns = NULL;
    data->last_ste = NULL;
    data->last_block_stmts = NULL;
    return;
}
void FTWfini() { return; }

/**
 * @fn FTWfor
 */
node_st *FTWfor(node_st *node)
{
    TRAVblock(node);

    struct data_ftw *data = DATA_FTW_GET();

    // create the decls for the for loop
    data->index_counter++;
    char *start_name = malloc(sizeof(char) * (strlen("_start_") + digit_counter(data->index_counter) + 1));
    sprintf(start_name, "_start_%d", data->index_counter);
    data->index_counter++;
    char *stop_name = malloc(sizeof(char) * (strlen("_stop_") + digit_counter(data->index_counter) + 1));
    sprintf(stop_name, "_stop_%d", data->index_counter);
    data->index_counter++;
    char *step_name = malloc(sizeof(char) * (strlen("_step_") + digit_counter(data->index_counter) + 1));
    sprintf(step_name, "_step_%d", data->index_counter);
    node_st *step_next;
    if (data->head_for_decls == NULL) {
        step_next = NULL;
    }
    else {
        step_next = data->head_for_decls;
    }
    node_st *step_decl = ASTvardecl(NULL, NULL, step_next, step_name, CT_int);
    node_st *stop_decl = ASTvardecl(NULL, NULL, step_decl, stop_name, CT_int);
    node_st *start_decl = ASTvardecl(NULL, NULL, stop_decl, start_name, CT_int);
    
    // // assign the values to the decls
    node_st *step_ste = ASTste(NULL, copy_entry_name(step_name), CT_int, false, 0, NULL, SYMTABLE_NEST_LVL(data->current_scope), data->ste_index);
    data->ste_index++;
    node_st *step_varlet = ASTvarlet(NULL, copy_entry_name(VARDECL_NAME(step_decl)), step_ste);
    node_st *step_assign = ASTassign(step_varlet, CCNcopy(FOR_STEP(node)));
    node_st *step_stmts = ASTstmts(step_assign, NULL);
    node_st *step_expr = ASTvar(NULL, copy_entry_name(VARDECL_NAME(step_decl)), step_ste);

    node_st *stop_ste = ASTste(step_ste, copy_entry_name(stop_name), CT_int, false, 0, NULL, SYMTABLE_NEST_LVL(data->current_scope), data->ste_index);
    data->ste_index++;
    node_st *stop_varlet = ASTvarlet(NULL, copy_entry_name(VARDECL_NAME(stop_decl)), stop_ste);
    node_st *stop_assign = ASTassign(stop_varlet, CCNcopy(FOR_STOP(node)));
    node_st *stop_stmts = ASTstmts(stop_assign, step_stmts);
    node_st *stop_expr = ASTvar(NULL, copy_entry_name(VARDECL_NAME(stop_decl)), stop_ste);

    node_st *start_ste = ASTste(stop_ste, copy_entry_name(start_name), CT_int, false, 0, NULL, SYMTABLE_NEST_LVL(data->current_scope), data->ste_index);
    data->ste_index++;
    node_st *start_varlet = ASTvarlet(NULL, copy_entry_name(VARDECL_NAME(start_decl)), start_ste);
    node_st *start_assign = ASTassign(start_varlet, CCNcopy(FOR_START_EXPR(node)));
    node_st *start_stmts = ASTstmts(start_assign, stop_stmts);
    node_st *start_expr = ASTvar(NULL, copy_entry_name(VARDECL_NAME(start_decl)), start_ste);
    STE_NEXT(data->last_ste) = start_ste;
    data->last_ste = step_ste;

    node_st *pred = ASTbinop(step_expr, ASTnum(0, NULL), BO_gt, CT_bool);
    node_st *then_ = ASTbinop(start_expr, stop_expr, BO_lt, CT_bool);
    node_st *else_ = ASTbinop(CCNcopy(start_expr), CCNcopy(stop_expr), BO_gt, CT_bool);
    node_st *while_cond = ASTternary(pred, then_, else_);
    node_st *while_loop = ASTwhile(while_cond, CCNcopy(FOR_BLOCK(node)));
    TRAVblock(while_loop);
    node_st *while_stmts = ASTstmts(while_loop, NULL);
    STMTS_NEXT(step_stmts) = while_stmts;
    data->head_for_assigns = start_stmts;
    data->tail_for_assigns = while_stmts;

    node_st *step_binop = ASTbinop(start_expr, step_expr, BO_add, CT_int);
    node_st *increment = ASTassign(start_varlet, step_binop);
    node_st *increment_stmts = ASTstmts(increment, NULL);
    STMTS_NEXT(data->last_block_stmts) = increment_stmts;
    data->last_block_stmts = increment_stmts;

    // STMTS_STMT(STMTS_NEXT(data->parent_for_stmt)) = start_stmts;
    // STMTS_NEXT(step_stmts) =  while_stmts;

    data->head_for_decls = start_decl;

    CCNfree(node);

    // STMTS_NEXT(data->parent_for_stmt) = while_loop;
    
    return while_loop;
}
/**
 * @fn FTWfundef
 */
node_st *FTWfundef(node_st *node)
{
    struct data_ftw *data = DATA_FTW_GET();
    data->current_scope = FUNDEF_SYMTABLE(node);
    TRAVsymtable(node);
    TRAVbody(node);
    data->current_scope = SYMTABLE_PARENT(node);
    return node;
}

/**
 * @fn FTWfunbody
 */
node_st *FTWfunbody(node_st *node)
{
    struct data_ftw *data = DATA_FTW_GET();
    data->for_funbody = node;
    TRAVdecls(node);
    TRAVstmts(node);
    if (data->head_for_decls != NULL) {
        VARDECL_NEXT(data->tail_funbody_decls) = data->head_for_decls;
        data->head_for_decls = NULL;
    }
    // if (data->head_for_assigns != NULL) {
    //     STMTS_NEXT(data->parent_for_stmt) = data->head_for_assigns;
    //     data->head_for_assigns = NULL;
    // }
    return node;
}

/**
 * @fn FTWste
 */
node_st *FTWste(node_st *node)
{
    struct data_ftw *data = DATA_FTW_GET();
    if (STE_NEXT(node) == NULL) {
        data->index_counter = STE_INDEX(node);
        data->last_ste = node;
    }
    else {
        TRAVnext(node);
    }
    return node;
}

/**
 * @fn FTWvardecl
 */
node_st *FTWvardecl(node_st *node)
{
    TRAVnext(node);
    if (VARDECL_NEXT(node) == NULL) {
        struct data_ftw *data = DATA_FTW_GET();
        data->tail_funbody_decls = node;
    }
    return node;
}

/**
 * @fn FTWprogram
 */
node_st *FTWprogram(node_st *node)
{
    struct data_ftw *data = DATA_FTW_GET();
    data->current_scope = PROGRAM_GLOBAL(node);
    TRAVchildren(node);
    return node;
}

/**
 * @fn FTWstmts
 */
node_st *FTWstmts(node_st *node)
{
    struct data_ftw *data = DATA_FTW_GET();
    if (STMTS_NEXT(node) == NULL) {
        data->last_block_stmts = node;
    }
    if ((STMTS_NEXT(node) != NULL) && (NODE_TYPE(STMTS_STMT(STMTS_NEXT(node))) == NT_FOR)) {
        data->parent_for_stmt = node;
        TRAVchildren(node);
        node_st *old_next = STMTS_NEXT(STMTS_NEXT(node));
        STMTS_NEXT(node) = data->head_for_assigns;
        STMTS_NEXT(data->tail_for_assigns) = old_next;
    }
    else {
       TRAVchildren(node);
    }
    
    return node;
}
