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

/* Return the resulting type of an expression
 *
 * expr: the expression
 */
static enum Type get_type(node_st *expr) {
    enum Type type;
    switch (NODE_TYPE(expr)) {
      case NT_CAST:
        type = CAST_TYPE(expr);
        break;
      case NT_FUNCALL:
        type = STE_TYPE(FUNCALL_STE(expr));
        break;
      case NT_VAR:
        type = STE_TYPE(VAR_STE(expr));
        break;
      case NT_NUM:
        type = CT_int;
        break;
      case NT_FLOAT:
        type = CT_float;
        break;
      case NT_BOOL:
        type = CT_bool;
        break;
      case NT_BINOP:
        type = BINOP_EXPR_TYPE(expr);
        break;
      case NT_MONOP:
        type = MONOP_EXPR_TYPE(expr);
        break;
      case NT_TERNARY:
        type = TERNARY_EXPR_TYPE(expr);
    }

    return type;
}

/**
 * @fn BCcast
 */
node_st *BCcast(node_st *node)
{
    TRAVexpr(node);
    if (CAST_TYPE(node) == CT_bool) {
        if (get_type(CAST_EXPR(node)) == CT_float) {
            node_st *new_node = ASTbinop(CCNcopy(CAST_EXPR(node)),
                                            ASTfloat(0.0, NULL), BO_ne,
                                            CT_float);
            node_st **node_ptr = &node;
            CCNfree(node);
            *node_ptr = new_node;
        }
        else if (get_type(CAST_EXPR(node)) == CT_int) {
            node_st *new_node = ASTbinop(CCNcopy(CAST_EXPR(node)),
                                            ASTnum(0, NULL), BO_ne, CT_int);
            node_st **node_ptr = &node;
            CCNfree(node);
            *node_ptr = new_node;
        }
    }
    else if (get_type(CAST_EXPR(node)) == CT_bool) {
        node_st *then_;
        node_st *else_;
        if (CAST_TYPE(node) == CT_float) {
            then_ = ASTfloat(1.0, CT_float);
            else_ = ASTfloat(0.0, CT_float);
        }
        else if (CAST_TYPE(node) == CT_int) {
            then_ = ASTnum(1, CT_int);
            else_ = ASTnum(0, CT_int);
        }
        node_st *ternary = ASTternary(CCNcopy(CAST_EXPR(node)), then_, else_,
                                        CAST_TYPE(node));
        node_st **node_ptr = &node;
        CCNfree(node);
        *node_ptr = ternary;
    }

    return node;
}
