/**
 * @file
 *
 * Traversal: TypeChecking
 * UID      : TC
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
    }

    return type;
}

/* Create a string from a given Type.
 *
 * type: the data type enum
 * str : the char pointer to store the string into
 */
char *type_string(enum Type type, char *str) {
    char *tmp = NULL;
    switch (type) {
    case CT_bool:
      tmp = "bool";
      break;
    case CT_int:
      tmp = "int";
      break;
    case CT_float:
      tmp = "float";
      break;
    case CT_void:
      tmp = "void";
      break;
    case CT_NULL:
      tmp = "UNDEF";
      break;
    }

    strcpy(str, tmp);
    return str;
}

/* Print an error message for an incorrect data type.
 *
 * node       : the node pointer to the incorrect data type
 * given_type : the actual data type enum of the data type
 */
void type_error(node_st *node, enum Type expected_type, enum Type given_type)
{
    char *given = (char *)malloc(6 * sizeof(char));
    char *expected = (char *)malloc(13 * sizeof(char));
    expected = type_string(expected_type, expected);
    if (!strcmp(expected, "UNDEF")) {
        strcpy(expected, "int or float");
    }

    CTI(CTI_ERROR, false,
            "Error (%d:%d): type mismatch: expected type %s, got %s.",
            NODE_BLINE(node), NODE_BCOL(node),
            expected, type_string(given_type, given));
    CCNerrorAction();
    free(given);
    free(expected);
}

void TCinit()
{
    struct data_tc *data = DATA_TC_GET();
    data->for_counter = NULL;
    return;
}
void TCfini() { return; }

/**
 * @fn TCfundef
 */
node_st *TCfundef(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();
    TRAVparams(node);
    data->return_type = FUNDEF_TYPE(node);
    TRAVbody(node);
    return node;
}

/**
 * @fn TCfor
 */
node_st *TCfor(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();

    TRAVstart_expr(node);
    enum Type type = get_type(FOR_START_EXPR(node));
    if (type != CT_int) {
        type_error(FOR_START_EXPR(node), CT_int, type);
    }

    TRAVstop(node);
    type = get_type(FOR_STOP(node));
    if (type != CT_int) {
        type_error(FOR_STOP(node), CT_int, type);
    }

    if (FOR_STEP(node)) {
        TRAVstep(node);
        type = get_type(FOR_STEP(node));
        if (type != CT_int) {
            type_error(FOR_STEP(node), CT_int, type);
        }
    }

    TRAVblock(node);
    return node;
}

/**
 * @fn TCcast
 */
node_st *TCcast(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();

    if (CAST_TYPE(node) == CT_void) {
        CTI(CTI_ERROR, false, "Error (%d:%d): cast type cannot be void.",
                NODE_BLINE(node), NODE_BCOL(node));
        CCNerrorAction();
    }

    TRAVexpr(node);
    enum Type type = get_type(CAST_EXPR(node));
    if (type == CT_void) {
        CTI(CTI_ERROR, false,
                "Error (%d:%d): typecast cannot be applied to type void, "
                "only to bool or int or float",
                NODE_BLINE(CAST_EXPR(node)), NODE_BCOL(CAST_EXPR(node)));
        CCNerrorAction();
    }
    return node;
}

/**
 * @fn TCbool
 */
node_st *TCbool(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();
    return node;
}

/**
 * @fn TCbinop
 */
node_st *TCbinop(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();

    TRAVleft(node);
    enum Type type_left = get_type(BINOP_LEFT(node));
    TRAVright(node);
    enum Type type_right = get_type(BINOP_RIGHT(node));

    if (BINOP_OP(node) == BO_and || BINOP_OP(node) == BO_or) {
        if (type_left != CT_bool) {
            type_error(BINOP_LEFT(node), CT_bool, type_left);
        }
        if (type_right != CT_bool) {
            type_error(BINOP_RIGHT(node), CT_bool, type_right);
        }
        BINOP_EXPR_TYPE(node) = CT_bool;
    }
    else if (BINOP_OP(node) == BO_mod) {
        if (type_left != CT_int) {
            type_error(BINOP_LEFT(node), CT_int, type_left);
        }
        if (type_right != CT_int) {
            type_error(BINOP_RIGHT(node), CT_int, type_right);
        }
        BINOP_EXPR_TYPE(node) = CT_int;
    }
    else if (type_left != type_right) {
        bool right_numerical = type_right == CT_int || type_right == CT_float;
        bool left_numerical = type_left == CT_int || type_left == CT_float;

        if (!left_numerical) {
            type_error(BINOP_LEFT(node), CT_NULL, type_left);
            if (!right_numerical) {
                type_error(BINOP_RIGHT(node), CT_NULL, type_right);
                BINOP_EXPR_TYPE(node) = CT_NULL;
            }
            else {
                BINOP_EXPR_TYPE(node) = type_right;
            }
        }
        // Either right is not numerical or it does not have the same numerical
        // type as left. In both cases, an error for right will be raised.
        else {
            type_error(BINOP_RIGHT(node), type_left, type_right);
            BINOP_EXPR_TYPE(node) = type_left;
        }
    }
    else {
        BINOP_EXPR_TYPE(node) = type_left;
    }

    if (BINOP_OP(node) == BO_lt || BINOP_OP(node) == BO_le
        || BINOP_OP(node) == BO_gt || BINOP_OP(node) == BO_ge
        || BINOP_OP(node) == BO_eq || BINOP_OP(node) == BO_ne) {
        BINOP_EXPR_TYPE(node) = CT_bool;
    }
    return node;
}

/**
 * @fn TCassign
 */
node_st *TCassign(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();
    TRAVexpr(node);

    enum Type type = get_type(ASSIGN_EXPR(node));
    enum Type varlet_type = STE_TYPE(VAR_STE(ASSIGN_LET(node)));
    if (varlet_type != type) {
        char *expected = (char *)malloc(6 * sizeof(char));
        char *got = (char *)malloc(6 * sizeof(char));
        CTI(CTI_ERROR, false,
                "Error (%d:%d): incorrect data type for variable \"%s\". "
                "Expected %s, got %s.",
                NODE_BLINE(ASSIGN_LET(node)), NODE_BCOL(ASSIGN_LET(node)),
                VARLET_NAME(ASSIGN_LET(node)),
                type_string(varlet_type, expected), type_string(type, got));
        CCNerrorAction();
        free(expected);
        free(got);
    }
    return node;
}

/**
 * @fn TCfloat
 */
node_st *TCfloat(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();
    return node;
}

/**
 * @fn TCfuncall
 */
node_st *TCfuncall(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();

    node_st *arg = FUNCALL_ARGS(node);
    node_st *param = STE_FIRST_PARAM(FUNCALL_STE(node));
    int arity = STE_ARITY(FUNCALL_STE(node));
    enum Type type;
    for (int i = arity; i > 0; i--) {
        if (!arg) {
            CTI(CTI_ERROR, false,
                    "Error (%d:%d): function \"%s\" expects %d arguments.",
                    NODE_BLINE(node), NODE_BCOL(node), FUNCALL_NAME(node),
                    arity);
            CCNerrorAction();
            break;
        }

        TRAVexpr(arg);
        type = get_type(EXPRS_EXPR(arg));
        if (type != STE_TYPE(param) && STE_TYPE(param) != CT_void) {
            type_error(EXPRS_EXPR(arg), STE_TYPE(param), type);
        }

        param = STE_NEXT(param);
        arg = EXPRS_NEXT(arg);
    }

    if (arg) {
        CTI(CTI_ERROR, false,
                "Error (%d:%d): function \"%s\" expects %d arguments.",
                NODE_BLINE(node), NODE_BCOL(node), FUNCALL_NAME(node), arity);
        CCNerrorAction();
    }

    return node;
}

/**
 * @fn TCifelse
 */
node_st *TCifelse(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();

    TRAVcond(node);
    enum Type type = get_type(IFELSE_COND(node));
    if (type != CT_bool) {
        type_error(IFELSE_COND(node), CT_bool, type);
    }

    TRAVthen(node);
    TRAVelse_block(node);

    return node;
}

/**
 * @fn TCnum
 */
node_st *TCnum(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();
    return node;
}

/**
 * @fn TCmonop
 */
node_st *TCmonop(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();
    TRAVoperand(node);

    // Check if the operand has the correct type for the operator.
    enum Type type = get_type(MONOP_OPERAND(node));
    if (MONOP_OP(node) == MO_not) {
        if (type != CT_bool){
            type_error(MONOP_OPERAND(node), CT_bool, type);
        }
        MONOP_EXPR_TYPE(node) = CT_bool;
    }
    else if (type != CT_int && type != CT_float) {
        type_error(MONOP_OPERAND(node), CT_NULL, type);
        MONOP_EXPR_TYPE(node) = CT_NULL;
    }
    else {
        MONOP_EXPR_TYPE(node) = type;
    }

    return node;
}

/**
 * @fn TCparam
 */
node_st *TCparam(node_st *node)
{
    if (PARAM_TYPE(node) == CT_void) {
        CTI(CTI_ERROR, false,
                "Error (%d:%d): function parameter \"%s\" cannot be void.",
                NODE_BLINE(node), NODE_BCOL(node), PARAM_NAME(node));
        CCNerrorAction();
    }
    TRAVnext(node);
    return node;
}

/**
 * @fn TCvar
 */
node_st *TCvar(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();
    return node;
}

/**
 * @fn TCreturn
 */
node_st *TCreturn(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();
    enum Type type;
    if (RETURN_EXPR(node)) {
        TRAVexpr(node);
        type = get_type(RETURN_EXPR(node));
    }
    else {
        type = CT_void;
    }

    if (data->return_type == CT_void && type != CT_void) {
        CTI(CTI_ERROR, false,
                "Error (%d:%d): void function should not have a return value",
                NODE_BLINE(RETURN_EXPR(node)), NODE_BCOL(RETURN_EXPR(node)));
    }
    else if (data->return_type != type) {
        char *expected = (char *)malloc(6 * sizeof(char));
        char *got = (char *)malloc(6 * sizeof(char));
        CTI(CTI_ERROR, false,
                "Error (%d:%d): expected return value of type %s, got %s",
                NODE_BLINE(node), NODE_BCOL(node),
                type_string(data->return_type, expected),
                type_string(type, got));
        free(expected);
        free(got);
    }

    return node;
}

