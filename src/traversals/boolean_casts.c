/**
 * @file
 *
 * Traversal: BooleanCasts
 * UID      : BC
 *
 *
 */

#include <stdio.h>
#include <string.h>

#include "ccn/ccn.h"
#include "ccngen/ast.h"
#include "ccngen/enum.h"
#include "ccngen/trav.h"


void BCinit() { return; }
void BCfini() { return; }


/**
 * @fn BCcast
 */
node_st *BCcast(node_st *node)
{
    struct data_bc *data = DATA_BC_GET();
    TRAVexpr(node);
    if (CAST_TYPE(node) == CT_bool) {
        if (data->expr_type == CT_float) {
            node_st *new_node = ASTbinop(CCNcopy(CAST_EXPR(node)), ASTfloat(0.0, NULL), BO_ne, CT_float);
            node_st **node_ptr = &node;
            CCNfree(node);
            *node_ptr = new_node;
        }
        else if (data->expr_type == CT_int) {
            node_st *new_node = ASTbinop(CCNcopy(CAST_EXPR(node)), ASTnum(0, NULL), BO_ne, CT_int);
            node_st **node_ptr = &node;
            CCNfree(node);
            *node_ptr = new_node;
        }
    }

    else {
        if (data->expr_type == CT_bool){
            node_st *pred = ASTbinop(CCNcopy(CAST_EXPR(node)), ASTbool(true), BO_eq, CT_int);
            node_st *then_;
            node_st *else_;
            if (CAST_TYPE(node) == CT_float) {
                then_ = ASTfloat(1.0, NULL);
                else_ = ASTfloat(0.0, NULL);
                BINOP_EXPR_TYPE(pred) = CT_float;
            }
            else if (CAST_TYPE(node) == CT_int) {
                then_ = ASTnum(1, NULL);
                else_ = ASTnum(0, NULL);
            }
            node_st *ternary = ASTternary(pred, then_, else_);
            node_st **node_ptr = &node;
            CCNfree(node);
            *node_ptr = ternary;
        }
    }

    data->expr_type = CAST_TYPE(node);

    return node;
}

/**
 * @fn BCbinop
 */
node_st *BCbinop(node_st *node)
{
    TRAVleft(node);
    return node;
}

/**
 * @fn BCbool
 */
node_st *BCbool(node_st *node)
{
    struct data_bc *data = DATA_BC_GET();
    data->expr_type = CT_bool;
    return node;
}

/**
 * @fn BCfuncall
 */
node_st *BCfuncall(node_st *node)
{
    struct data_bc *data = DATA_BC_GET();
    data->expr_type = STE_TYPE(FUNCALL_STE(node));
    return node;
}

/**
 * @fn BCfloat
 */
node_st *BCfloat(node_st *node)
{
    struct data_bc *data = DATA_BC_GET();
    data->expr_type = CT_float;
    return node;
}

/**
 * @fn BCvar
 */
node_st *BCvar(node_st *node)
{
    struct data_bc *data = DATA_BC_GET();
    data->expr_type = STE_TYPE(VAR_STE(node));
    return node;
}

/**
 * @fn BCmonop
 */
node_st *BCmonop(node_st *node)
{
    TRAVoperand(node);
    return node;
}

/**
 * @fn BCnum
 */
node_st *BCnum(node_st *node)
{
    struct data_bc *data = DATA_BC_GET();
    data->expr_type = CT_int;
    return node;
}
