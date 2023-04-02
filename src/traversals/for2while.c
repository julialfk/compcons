/**
 * @file
 *
 * Traversal: ForToWhile
 * UID      : FTW
 *
 *
 */

#include <stdio.h>
#include <string.h>

#include "ccn/ccn.h"
#include "ccngen/ast.h"
#include "ccngen/enum.h"
#include "ccngen/trav.h"
#include "palm/ctinfo.h"
#include "palm/str.h"


int digit_counter(int digit) {
    int count = 0;
    do {
        digit /= 10;
        ++count;
    } while (digit != 0);
    return count;
}

void FTWinit()
{
    struct data_ftw *data = DATA_FTW_GET();
    data->cur_function = NULL;
    data->last_vardecl = NULL;
    data->last_ste = NULL;
    data->last_stmts = NULL;
    data->head_new = NULL;
    data->tail_new = NULL;
    data->insert = NULL;
    data->counter = 1;
}
void FTWfini() { return; }

/**
 * @fn FTWfundef
 */
node_st *FTWfundef(node_st *node)
{
    struct data_ftw *data = DATA_FTW_GET();
    data->cur_function = node;
    TRAVnext(FUNDEF_SYMTABLE(node));
    TRAVbody(node);
    return node;
}

/**
 * @fn FTWfunbody
 */
node_st *FTWfunbody(node_st *node)
{
    struct data_ftw *data = DATA_FTW_GET();
    if (FUNBODY_STMTS(node)) {
        // Find the last vardecl.
        TRAVdecls(node);

        node_st *old_stmt = FUNBODY_STMTS(node);
        if (NODE_TYPE(STMTS_STMT(old_stmt)) == NT_FOR) {
            node_st *old_next = STMTS_NEXT(old_stmt);
            TRAVstmt(old_stmt);
            FUNBODY_STMTS(node) = data->head_new;
            STMTS_NEXT(data->tail_new) = CCNcopy(old_next);
            CCNfree(old_stmt);
        }
        TRAVstmts(node);
    }
    return node;
}

/**
 * @fn FTWvardecl
 */
node_st *FTWvardecl(node_st *node)
{
    struct data_ftw *data = DATA_FTW_GET();
    if (!VARDECL_NEXT(node)) {
        data->last_vardecl = node;
    }
    else {
        TRAVnext(node);
    }
    return node;
}


/**
 * @fn FTWstmts
 */
node_st *FTWstmts(node_st *node)
{
    struct data_ftw *data = DATA_FTW_GET();

    TRAVstmt(node);
    if (STMTS_NEXT(node)) {
        node_st *old_stmt = STMTS_NEXT(node);
        if (NODE_TYPE(STMTS_STMT(old_stmt)) == NT_FOR) {
            node_st *old_next = STMTS_NEXT(old_stmt);
            TRAVstmt(old_stmt);

            STMTS_NEXT(node) = data->head_new;
            STMTS_NEXT(data->tail_new) = CCNcopy(old_next);
            CCNfree(old_stmt);
        }
        TRAVnext(node);
    }

    return node;
}

/**
 * @fn FTWfor
 */
node_st *FTWfor(node_st *node)
{
    struct data_ftw *data = DATA_FTW_GET();

    // Extend the list of vardecls.
    char *start_name = (char *)malloc(sizeof(char) * (strlen(FOR_VAR(node))
                                        + digit_counter(data->counter) + 3));
    sprintf(start_name, "_%s_%d", FOR_VAR(node), (data->counter)++);

    char *stop_name = (char *)malloc(sizeof(char)
                                        * (digit_counter(data->counter) + 8));
    sprintf(stop_name, "_stop_%d_", (data->counter)++);

    char *step_name = (char *)malloc(sizeof(char)
                                        * (digit_counter(data->counter) + 8));
    sprintf(step_name, "_step_%d_", (data->counter)++);

    node_st *step_vardecl = ASTvardecl(NULL, NULL, NULL, step_name, CT_int);
    node_st *stop_vardecl = ASTvardecl(NULL, NULL, step_vardecl,
                                        stop_name, CT_int);
    node_st *start_vardecl = ASTvardecl(NULL, NULL, stop_vardecl,
                                        start_name, CT_int);
    if (data->last_vardecl) {
        VARDECL_NEXT(data->last_vardecl) = start_vardecl;
    }
    else {
        FUNBODY_DECLS(FUNDEF_BODY(data->cur_function)) = start_vardecl;
    }
    data->last_vardecl = step_vardecl;

    // Extend the symboltable.
    node_st *symtable = FUNDEF_SYMTABLE(data->cur_function);

    node_st *start_ste = ASTste(NULL, STRcpy(start_name), CT_int, false, 0,
                                    NULL, SYMTABLE_NEST_LVL(symtable),
                                    SYMTABLE_NEXT_INDEX(symtable)++,
                                    false, false);
    node_st *stop_ste = ASTste(NULL, STRcpy(stop_name), CT_int, false, 0,
                                    NULL, SYMTABLE_NEST_LVL(symtable),
                                    SYMTABLE_NEXT_INDEX(symtable)++,
                                    false, false);
    node_st *step_ste = ASTste(NULL, STRcpy(step_name), CT_int, false, 0,
                                    NULL, SYMTABLE_NEST_LVL(symtable),
                                    SYMTABLE_NEXT_INDEX(symtable)++,
                                    false, false);

    STE_NEXT(start_ste) = stop_ste;
    STE_NEXT(stop_ste) = step_ste;

    if (data->last_ste) {
        STE_NEXT(data->last_ste) = start_ste;
    }
    else {
        SYMTABLE_NEXT(symtable) = start_ste;
    }
    data->last_ste = step_ste;

    // Create initializing assign nodes.
    node_st *start_varlet = ASTvarlet(NULL, STRcpy(start_name), start_ste);
    node_st *stop_varlet = ASTvarlet(NULL, STRcpy(stop_name), stop_ste);
    node_st *step_varlet = ASTvarlet(NULL, STRcpy(step_name), step_ste);

    node_st *start_assign = ASTassign(start_varlet,
                                            CCNcopy(FOR_START_EXPR(node)));
    node_st *stop_assign = ASTassign(stop_varlet, CCNcopy(FOR_STOP(node)));
    node_st *step_assign;
    if (FOR_STEP(node)) {
        step_assign = ASTassign(step_varlet, CCNcopy(FOR_STEP(node)));
    }
    else {
        step_assign = ASTassign(step_varlet, ASTnum(1, NULL));
    }

    // Create Ternary node.
    node_st *start_var = ASTvar(NULL, STRcpy(start_name), start_ste);
    node_st *stop_var = ASTvar(NULL, STRcpy(stop_name), stop_ste);
    node_st *step_var = ASTvar(NULL, STRcpy(step_name), step_ste);

    node_st *pred = ASTbinop(step_var, ASTnum(0, NULL), BO_gt, CT_bool);
    node_st *then_ = ASTbinop(start_var, stop_var, BO_lt, CT_bool);
    node_st *else_ = ASTbinop(CCNcopy(start_var), CCNcopy(stop_var),
                                BO_gt, CT_bool);

    node_st *cond = ASTternary(pred, then_, else_, CT_bool);

    // Extend the block with the increment assignment.
    if (FOR_BLOCK(node)) {
        node_st *old_stmt = FOR_BLOCK(node);
        if (NODE_TYPE(STMTS_STMT(old_stmt)) == NT_FOR) {
            node_st *old_next = STMTS_NEXT(old_stmt);
            TRAVstmt(old_stmt);
            FOR_BLOCK(node) = data->head_new;
            STMTS_NEXT(data->tail_new) = old_next;
            CCNfree(old_stmt);
        }
    }

    node_st *increment = ASTbinop(CCNcopy(start_var), CCNcopy(step_var),
                                    BO_add, CT_int);
    node_st *increment_assign = ASTassign(CCNcopy(start_varlet), increment);
    node_st *increment_stmts = ASTstmts(increment_assign, NULL);

    node_st *last_stmts = FOR_BLOCK(node);
    if (last_stmts) {
        while (STMTS_NEXT(last_stmts)) {
            last_stmts = STMTS_NEXT(last_stmts);
        }
        STMTS_NEXT(last_stmts) = increment_stmts;
    }
    else {
        FOR_BLOCK(node) = increment_stmts;
    }

    // Create While stmt.
    node_st *while_node = ASTwhile(cond, CCNcopy(FOR_BLOCK(node)));
    node_st *while_stmts = ASTstmts(while_node, NULL);
    node_st *step_stmts = ASTstmts(step_assign, while_stmts);
    node_st *stop_stmts = ASTstmts(stop_assign, step_stmts);
    node_st *start_stmts = ASTstmts(start_assign, stop_stmts);

    data->head_new = start_stmts;
    data->tail_new = while_stmts;

    return node;
}

/**
 * @fn FTWste
 */
node_st *FTWste(node_st *node)
{
    struct data_ftw *data = DATA_FTW_GET();
    if (!STE_NEXT(node)) {
        data->last_ste = node;
    }
    else {
        TRAVnext(node);
    }
    return node;
}
