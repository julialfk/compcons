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
void type_error(node_st *node, enum Type given_type)
{
    char *given = (char *)malloc(6 * sizeof(char));
    given = type_string(given_type, given);

    printf("Error: incorrect data type (%s) (%d:%d).\n",
            given, NODE_BLINE(node), NODE_BCOL(node));
    free(given);
}

void TCinit()
{
    struct data_tc *data = DATA_TC_GET();
    data->for_counter = NULL;
    data->current_type = CT_NULL;
    data->bool_return = false;
    return;
}
void TCfini() { return; }

/**
 * @fn TCfundef
 */
node_st *TCfundef(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();
    printf("\n%s:\n", FUNDEF_NAME(node));
    TRAVparams(node);
    data->current_type = CT_NULL;
    TRAVbody(node);
    if (!data->bool_return) {
        data->current_type = CT_void;
    }
    if (data->current_type != FUNDEF_TYPE(node)) {
        type_error(data->return_node, data->current_type);
    }
    char *tmp = (char *)malloc(6 * sizeof(char));
    printf("\n%s return = %s\n", FUNDEF_NAME(node),
                                    type_string(data->current_type, tmp));
    free(tmp);

    data->bool_return = false;
    data->current_type = CT_NULL;
    return node;
}

/**
 * @fn TCfor
 */
node_st *TCfor(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();
    printf("\nfor init:\n");
    data->current_type = CT_NULL;
    TRAVstart_expr(node);
    if (data->current_type != CT_int) {
        type_error(FOR_START_EXPR(node), data->current_type);
    }

    printf("\nstop:\n");
    data->current_type = CT_NULL;
    TRAVstop(node);
    if (data->current_type != CT_int) {
        type_error(FOR_STOP(node), data->current_type);
    }

    printf("\nstep:\n");
    if (FOR_STEP(node)) {
        data->current_type = CT_NULL;
        TRAVstep(node);
        if (data->current_type != CT_int) {
            type_error(FOR_STEP(node), data->current_type);
        }
    }

    printf("\nblock:\n");
    if (FOR_BLOCK(node)) {
        data->current_type = CT_NULL;
        TRAVblock(node);
    }

    printf("\n");
    data->current_type = CT_NULL;
    return node;
}

/**
 * @fn TCcast
 */
node_st *TCcast(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();
    char *tmp = (char *)malloc(6 * sizeof(char));
    printf("\ncast: %s\n", type_string(CAST_TYPE(node), tmp));
    free(tmp);

    data->current_type = CT_NULL;
    TRAVexpr(node);
    if (data->current_type != CT_int && data->current_type != CT_float
        && data->current_type != CT_bool) {
        type_error(CAST_EXPR(node), data->current_type);
        printf("Unable to cast this data type.\n");
    }
    data->current_type = CAST_TYPE(node);
    return node;
}

/**
 * @fn TCbool
 */
node_st *TCbool(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();
    if (BOOL_VAL(node) == true) {
        printf("true\n");
    }
    else {
        printf("false\n");
    }
    data->current_type = CT_bool;
    return node;
}

/**
 * @fn TCbinop
 */
node_st *TCbinop(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();

    printf("\nbinop left:\n");
    data->current_type = CT_NULL;
    TRAVleft(node);
    enum Type type_left = data->current_type;
    printf("\nbinop right:\n");
    data->current_type = CT_NULL;
    TRAVright(node);
    enum Type type_right = data->current_type;

    char *tmp_left = (char *)malloc(6 * sizeof(char));
    char *tmp_right = (char *)malloc(6 * sizeof(char));
    printf("\n%s binop %s\n",
                type_string(type_left, tmp_left),
                type_string(type_right, tmp_right));
    free(tmp_left);
    free(tmp_right);

    if (BINOP_OP(node) == BO_and || BINOP_OP(node) == BO_or) {
        if (type_left != CT_bool) {
            type_error(BINOP_LEFT(node), type_left);
        }
        if (type_right != CT_bool) {
            type_error(BINOP_RIGHT(node), type_right);
        }
        data->current_type = CT_bool;
    }
    else if (type_left != type_right) {
        bool right_numerical = type_right == CT_int || type_right == CT_float;
        bool left_numerical = type_left == CT_int || type_left == CT_float;

        if (!left_numerical) {
            type_error(BINOP_LEFT(node), type_left);
            if (!right_numerical) {
                type_error(BINOP_RIGHT(node), type_right);
                data->current_type = CT_NULL;
            }
            else {
                data->current_type = type_right;
            }
        }
        // Either right is not numerical or it does not have the same numerical
        // type as left. In both cases, an error for right will be raised.
        else {
            type_error(BINOP_RIGHT(node), type_right);
            data->current_type = type_left;
        }
    }

    return node;
}

/**
 * @fn TCassign
 */
node_st *TCassign(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();
    printf("\nlefthand side expr:\n");
    data->current_type = CT_NULL;
    TRAVexpr(node);

    char *tmp1 = (char *)malloc(6 * sizeof(char));
    char *tmp2 = (char *)malloc(6 * sizeof(char));
    printf("\n%s: expected = %s, actual = %s\n", VARLET_NAME(ASSIGN_LET(node)),
                    type_string(STE_TYPE(VARLET_STE(ASSIGN_LET(node))), tmp1),
                    type_string(data->current_type, tmp2));
    free(tmp1);
    free(tmp2);

    node_st *varlet = ASSIGN_LET(node);
    node_st *ste = VAR_STE(varlet);

    enum Type varlet_type = STE_TYPE(VAR_STE(ASSIGN_LET(node)));
    if (varlet_type != data->current_type) {
        char *expected = (char *)malloc(6 * sizeof(char));
        char *given = (char *)malloc(6 * sizeof(char));
        expected = type_string(varlet_type, expected);
        given = type_string(data->current_type, given);

        printf("Error: incorrect data type for variable %s(%d:%d). "
                "Expected %s, %s given.\n",
                VARLET_NAME(ASSIGN_LET(node)), NODE_BLINE(ASSIGN_LET(node)),
                NODE_BCOL(ASSIGN_LET(node)), expected, given);
        free(expected);
        free(given);
    }
    data->current_type = CT_NULL;
    return node;
}

/**
 * @fn TCfloat
 */
node_st *TCfloat(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();
    printf("%f\n", FLOAT_VAL(node));
    data->current_type = CT_float;
    return node;
}

/**
 * @fn TCfuncall
 */
node_st *TCfuncall(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();

    printf("\nFunction call: %s\n", FUNCALL_NAME(node));
    node_st *arg = FUNCALL_ARGS(node);
    node_st *param = STE_FIRST_PARAM(FUNCALL_STE(node));
    for (int i = STE_ARITY(FUNCALL_STE(node)); i > 0; i--) {
        if (!arg) {
            printf("Error: not enough arguments for function %s(%d:%d).\n",
                    FUNCALL_NAME(node), NODE_BLINE(node), NODE_BCOL(node));
            break;
        }

        data->current_type = CT_NULL;
        TRAVexpr(arg);
        if (data->current_type != STE_TYPE(param)) {
            type_error(EXPRS_EXPR(arg), data->current_type);
        }

        char *tmp = (char *)malloc(6 * sizeof(char));
        printf("param: %s\n", type_string(data->current_type, tmp));
        free(tmp);

        param = STE_NEXT(param);
        arg = EXPRS_NEXT(arg);
    }

    if (arg) {
        printf("Error: too many arguments for function %s(%d:%d).\n",
                FUNCALL_NAME(node), NODE_BLINE(node), NODE_BCOL(node));
    }

    data->current_type = STE_TYPE(FUNCALL_STE(node));
    return node;
}

/**
 * @fn TCifelse
 */
node_st *TCifelse(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();
    data->current_type = CT_NULL;
    TRAVcond(node);
    if (data->current_type != CT_bool) {
        type_error(IFELSE_COND(node), data->current_type);
    }

    char *tmp = (char *)malloc(6 * sizeof(char));
    printf("\nif (cond: %s)\n", type_string(data->current_type, tmp));
    free(tmp);

    printf("\nthen:\n");
    data->current_type = CT_NULL;
    TRAVthen(node);
    printf("\nelse:\n");
    data->current_type = CT_NULL;
    TRAVelse_block(node);

    data->current_type = CT_NULL;
    return node;
}

/**
 * @fn TCnum
 */
node_st *TCnum(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();
    printf("%d\n", NUM_VAL(node));
    data->current_type = CT_int;
    return node;
}

/**
 * @fn TCmonop
 */
node_st *TCmonop(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();
    data->current_type = CT_NULL;
    TRAVoperand(node);
    char *tmp = (char *)malloc(6 * sizeof(char));

    // Check if the operand has the correct type for the operator and update
    // the current type to the expected type.
    if (MONOP_OP(node) == MO_not) {
        if (data->current_type != CT_bool){
            type_error(MONOP_OPERAND(node), data->current_type);
            data->current_type = CT_bool;
        }
        printf("! %s\n", type_string(data->current_type, tmp));
    }
    else if (MONOP_OP(node) == MO_neg) {
        if (data->current_type != CT_int && data->current_type != CT_float) {
            type_error(MONOP_OPERAND(node), data->current_type);
            data->current_type = CT_NULL;
        }
        printf("- %s\n", type_string(data->current_type, tmp));
    }
    free(tmp);

    return node;
}

/**
 * @fn TCparam
 */
node_st *TCparam(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();
    printf("%s, ", PARAM_NAME(node));
    if (PARAM_TYPE(node) == CT_void) {
        printf("Error: function parameter (%s) cannot be void (%d:%d).\n",
                PARAM_NAME(node), NODE_BLINE(node), NODE_BCOL(node));
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
    data->current_type = STE_TYPE(VAR_STE(node));

    char *tmp = (char *)malloc(6 * sizeof(char));
    printf("%s: %s\n", VAR_NAME(node), type_string(data->current_type, tmp));
    free(tmp);

    return node;
}

/**
 * @fn TCreturn
 */
node_st *TCreturn(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();
    printf("\nreturn:\n");
    if (RETURN_EXPR(node)) {
        data->current_type = CT_NULL;
        TRAVexpr(node);
    }
    else {
        data->current_type = CT_void;
    }

    data->bool_return = true;
    return node;
}

