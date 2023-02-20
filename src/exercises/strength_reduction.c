/**
 * @file
 *
 * This file contains the code for the StrengthReduction traversal.
 * The traversal has the uid: SR
 *
 * @brief This module implements a traversal of the abstract syntax tree that
 * replaces multiplication operations with equivalent addition operations.
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"

/**
 * @fn SRbinop
 */
node_st *SRbinop(node_st *node)
{
    node_st *new = NULL;

    if (BINOP_TYPE( node) == BO_mul) {
        if (NODE_TYPE( BINOP_LEFT( node)) == NT_NUM
        && (NODE_TYPE( BINOP_RIGHT( node)) == NT_NUM
        || NODE_TYPE( BINOP_RIGHT( node)) == NT_VAR)
        && NUM_VAL( BINOP_LEFT( node)) > 1) {
            new = ASTbinop(CCNcopy(BINOP_RIGHT( node)), CCNcopy(BINOP_RIGHT( node)), BO_add);
            for (int n = 2; n < NUM_VAL( BINOP_LEFT( node)); n++) {
                new = ASTbinop(CCNcopy(BINOP_RIGHT( node)), new, BO_add);
            }
            node = CCNfree(node);
            node = new;
        } else if (NODE_TYPE( BINOP_LEFT( node)) == NT_VAR
        && NODE_TYPE( BINOP_RIGHT( node)) == NT_NUM
        && NUM_VAL( BINOP_RIGHT( node)) > 1) {
            new = ASTbinop(CCNcopy(BINOP_LEFT( node)), CCNcopy(BINOP_LEFT( node)), BO_add);
            for (int n = 2; n < NUM_VAL( BINOP_RIGHT( node)); n++) {
                new = ASTbinop(CCNcopy(BINOP_LEFT( node)), new, BO_add);
            }
            node = CCNfree(node);
            node = new;
        }
    }
    return node;
}

