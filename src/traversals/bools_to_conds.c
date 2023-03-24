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
        // extract the memory adress of the node
        node_st **node_ptr = &node;
        // free the old node
        CCNfree(node);
        // and replace the node with the new one
        *node_ptr = cond;
    }
    else if (BINOP_OP(node) == BO_or) {
        node_st *cond = ASTboolbinop(CCNcopy(BINOP_LEFT(node)), CCNcopy(BINOP_RIGHT(node)), BOO_or);
        // extract the memory adress of the node
        node_st **node_ptr = &node;
        // free the old node
        CCNfree(node);
        // and replace the node with the new one
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
        // extract the memory adress of the node
        node_st **node_ptr = &node;
        // free the old node
        CCNfree(node);
        // and replace the node with the new one
        *node_ptr = cond;
    }
    return node;
}

