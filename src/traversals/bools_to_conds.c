/**
 * @file
 *
 * Traversal: BoolopsToCondops
 * UID      : BTC
 *
 *
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"

/**
 * @fn BTCbinop
 */
node_st *BTCbinop(node_st *node)
{
    if (BINOP_OP(node) == BO_and) {
        node_st *cond = ASTboolbinop(CCNcopy(BINOP_LEFT(node)), CCNcopy(BINOP_RIGHT(node)), BOO_and);
        node_st **node_ptr = &node;
        CCNfree(node);
        *node_ptr = cond;
    }
    else if (BINOP_OP(node) == BO_or) {
        node_st *cond = ASTboolbinop(CCNcopy(BINOP_LEFT(node)), CCNcopy(BINOP_RIGHT(node)), BOO_or);
        node_st **node_ptr = &node;
        CCNfree(node);
        *node_ptr = cond;
    }
    return node;
}

/**
 * @fn BTCmonop
 */
node_st *BTCmonop(node_st *node)
{
    if (MONOP_OP(node) == MO_not) {
        node_st *cond = ASTboolmonop(CCNcopy(MONOP_OPERAND(node)), MOO_not);
        node_st **node_ptr = &node;
        CCNfree(node);
        *node_ptr = cond;
    }
    return node;
}

