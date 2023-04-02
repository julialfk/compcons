/**
 * @file
 *
 * Traversal: BoolopsToCondops
 * UID      : BTC
 *
 *
 */

#include <stdio.h>
#include <string.h>

#include "ccn/ccn.h"
#include "ccngen/ast.h"
#include "ccngen/enum.h"
#include "ccngen/trav.h"

/**
 * @fn BTCbinop
 */
node_st *BTCbinop(node_st *node)
{
    TRAVchildren(node);
    if (BINOP_OP(node) == BO_or) {
        node_st *pred = ASTbinop(CCNcopy(BINOP_LEFT(node)), ASTbool(true), BO_eq, CT_bool);
        node_st *then = ASTbool(true);
        node_st *els = ASTbinop(CCNcopy(BINOP_RIGHT(node)), ASTbool(true), BO_eq, CT_bool);
        node_st *ternary = ASTternary(pred, then, els, CT_bool);
        node_st **node_ptr = &node;
        CCNfree(node);
        *node_ptr = ternary;
    }
    else if (BINOP_OP(node) == BO_and) {
        node_st *pred = ASTbinop(CCNcopy(BINOP_LEFT(node)), ASTbool(false), BO_eq, CT_bool);
        node_st *then = ASTbool(false);
        node_st *els = ASTbinop(CCNcopy(BINOP_RIGHT(node)), ASTbool(true), BO_eq, CT_bool);
        node_st *ternary = ASTternary(pred, then, els, CT_bool);
        node_st **node_ptr = &node;
        CCNfree(node);
        *node_ptr = ternary;
    }

    return node;
}

// a || b;

// pred: een binop met a == true
// then: een constante met true
// else: een binop met b == true

// --------------------

// a && b;

// pred: een binop met a == false
// then: een constante met false
// else: een binop met b == true
