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

    data->head_for_decls = start_decl;

    // CCNfree(node);

    // STMTS_NEXT(data->parent_for_stmt) = while_loop;
    
    return node;
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
    return node;
}

/**
 * @fn FTWste
 */
node_st *FTWste(node_st *node)
{
    TRAVchildren(node);
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
    TRAVchildren(node);
    return node;
}

/**
 * @fn FTWstmts
 */
node_st *FTWstmts(node_st *node)
{
    TRAVchildren(node);
    return node;
}
