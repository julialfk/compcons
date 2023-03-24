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

/* Print an error message for an incorrect operand.
 *
 * node       : the node pointer to the incorrect operand
 * given_type : the actual data type enum of the operand
 */
void type_error(node_st *node, enum Type given_type)
{
    char *given = (char *)malloc(6 * sizeof(cahar));
    given = type_string(given_type, given);

    printf("Error: incorrect data type (%s) (%d:%d).",
            given, NODE_BLINE(node), NODE_BCOL(node));
    free(given);
}

void TCinit()
{
    struct data_tc *data = DATA_TC_GET();
    data->for_counter = NULL;
    data->current_type = CT_NULL;
    return;
}
void TCfini() { return; }

/**
 * @fn TCprogram
 */
node_st *TCprogram(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();
    return node;
}

/**
 * @fn TCfundef
 */
node_st *TCfundef(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();
    return node;
}

/**
 * @fn TCfor
 */
node_st *TCfor(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();
    return node;
}

/**
 * @fn TCcast
 */
node_st *TCcast(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();
    TRAVexpr(node);
    if (data->current_type != CT_int && data->current_type != CT_float
        && data->current_type != CT_bool) {
        type_error(CAST_EXPR(node), data->current_type) {

        }
    }
    return node;
}

/**
 * @fn TCbool
 */
node_st *TCbool(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();
    data->current_type = CT_bool;
    return node;
}

/**
 * @fn TCbinop
 */
node_st *TCbinop(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();

    TRAVleft(node);
    enum Type type_left = data->current_type;
    data->current_type = CT_NULL;
    TRAVright(node);
    enum Type type_right = data->current_type;

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
        bool right_numerical = type_right == CT_num || type_right == CT_float;
        bool left_numerical = type_left == CT_num || type_left == CT_float;

        if (!left_numerical) {
            type_error(BINOP_LEFT(node), type_left);
            if (!right_numerical) {
                type_error(BINOP_RIGHT(node), type_right);
                data->current_type = CT_num;
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
    TRAVexpr(node);

    enum Type varlet_type = STE_TYPE(VAR_STE(ASSIGN_LET(node)));
    if (varlet_type != data->current_type) {
        char *expected = (char *)malloc(6 * sizeof(char));
        char *given = (char *)malloc(6 * sizeof(char));
        expected = type_string(varlet_type, expected);
        given = type_string(data->current_type, given);

        printf("Error: incorrect data type %s(%d:%d). "
                "Expected %s, %s given.",
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
    data->current_type = CT_float;
    return node;
}

/**
 * @fn TCfuncall
 */
node_st *TCfuncall(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();
    data->current_type = STE_TYPE(FUNCALL_STE(node));
    return node;
}

/**
 * @fn TCifelse
 */
node_st *TCifelse(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();
    return node;
}

/**
 * @fn TCnum
 */
node_st *TCnum(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();
    data->current_type = CT_int;
    return node;
}

/**
 * @fn TCmonop
 */
node_st *TCmonop(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();
    TRAVoperand(node);

    // Check if the operand has the correct type for the operator and update
    // the current type to the expected type.
    if (MONOP_OP(node) == MO_not) {
        if (data->current_type != CT_bool){
            type_error(MONOP_OPERAND(node), data->current_type);
        }
        data->current_type = CT_bool;
    }
    else if (MONOP_OP(node) == MO_neg) {
        if (data->current_type != CT_num || data->current_type != CT_float) {
            type_error(MONOP_OPERAND(node), data->current_type);
        }
        data->current_type = CT_bool;
    }
    return node;
}

/**
 * @fn TCvar
 */
node_st *TCvar(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();
    data->current_type = STE_TYPE(VAR_STE(node));
    return node;
}

/**
 * @fn TCreturn
 */
node_st *TCreturn(node_st *node)
{
    struct data_tc *data = DATA_TC_GET();
    TRAVexpr(node)
    return node;
}

