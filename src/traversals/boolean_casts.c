/**
 * @file
 *
 * Traversal: BooleanCasts
 * UID      : BC
 *
 *
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"

void BCinit() {
    struct data_bc *data = DATA_BC_GET();
    data->expr_type;
    return;
}

void BCfini() { return; }

/**
 * @fn BCcast
 */
node_st *BCcast(node_st *node)
{
    struct data_bc *data = DATA_BC_GET();
    data->expr_type = CAST_TYPE(node);
    TRAVexpr(node);

    if (CAST_TYPE(node) == CT_bool) {
        if (data->expr_type == CT_float) {
            node_st *new_node = ASTbinop(CCNcopy(CAST_EXPR(node)), ASTfloat(0.0), BO_ne);
            node_st **node_ptr = &node;
            CCNfree(node);
            *node_ptr = new_node;
        }
        else if (data->expr_type == CT_int) {
            node_st *new_node = ASTbinop(CCNcopy(CAST_EXPR(node)), ASTnum(0), BO_ne);
            node_st **node_ptr = &node;
            CCNfree(node);
            *node_ptr = new_node;
        }
    }
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
 * @fn BCboolbinop
 */
node_st *BCboolbinop(node_st *node)
{
    struct data_bc *data = DATA_BC_GET();
    data->expr_type = CT_bool;
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
 * @fn BCboolmonop
 */
node_st *BCboolmonop(node_st *node)
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
