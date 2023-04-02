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
        node_st *ternary = ASTternary(CCNcopy(BINOP_LEFT(node)),
                            ASTbool(true),
                            CCNcopy(BINOP_RIGHT(node)),
                            CT_bool);
        node_st **node_ptr = &node;
        CCNfree(node);
        *node_ptr = ternary;
    }
    else if (BINOP_OP(node) == BO_and) {
        node_st *ternary = ASTternary(CCNcopy(BINOP_LEFT(node)),
                            CCNcopy(BINOP_RIGHT(node)),
                            ASTbool(false),
                            CT_bool);
        node_st **node_ptr = &node;
        CCNfree(node);
        *node_ptr = ternary;
    }

    return node;
}

// a || b;

// pred: a
// then: true
// else: b

// --------------------

// a && b;

// pred: a
// then: b
// else: false
