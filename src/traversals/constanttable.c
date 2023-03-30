/**
 * @file
 *
 * Traversal: ConstantTable
 * UID      : CST
 *
 *
 */

#include <stdio.h>
#include <string.h>

#include "ccn/ccn.h"
#include "ccngen/ast.h"
#include "ccngen/enum.h"
#include "ccngen/trav.h"

void CSTinit()
{
    struct data_cst *data = DATA_CST_GET();
    data->index = 0;
    data->tail = NULL;
    data->program = NULL;
    data->cur_const = NULL;
    data->cur_type = CT_NULL;
}
void CSTfini() { return; }

void insert_cte(struct data_cst *data, node_st *new_entry) {
    if (data->tail == NULL) {
        PROGRAM_CONSTANTS(data->program) = new_entry;
    }
    else {
        CTE_NEXT(data->tail) = new_entry;
    }
    data->tail = new_entry;
    data->index++;
}

/**
 * @fn CSTprogram
 */
node_st *CSTprogram(node_st *node)
{
    struct data_cst *data = DATA_CST_GET();
    data->program = node;
    TRAVdecls(node);
    return node;
}

/**
 * @fn CSTnum
 */
node_st *CSTnum(node_st *node)
{
    struct data_cst *data = DATA_CST_GET();
    // printf("num: %d\n", NUM_VAL(node));
    if (NUM_VAL(node) != 1 && NUM_VAL(node) != 0 && NUM_VAL(node) != -1) {
        data->cur_const = node;
        data->cur_type = CT_int;
        TRAVconstants(data->program);
        if (!NUM_CTE(node)) {
            node_st *new_entry = ASTcte(NULL, data->index,
                                        CT_int, NUM_VAL(node), 0.0);
            insert_cte(data, new_entry);
            NUM_CTE(node) = new_entry;
        }
        data->cur_const = NULL;
        data->cur_type = CT_NULL;
    }
    return node;
}

/**
 * @fn CSTfloat
 */
node_st *CSTfloat(node_st *node)
{
    struct data_cst *data = DATA_CST_GET();
    if (FLOAT_VAL(node) != 1.0 && FLOAT_VAL(node) != 0.0) {
        data->cur_const = node;
        data->cur_type = CT_float;
        TRAVconstants(data->program);
        if (!FLOAT_CTE(node)) {
            node_st *new_entry = ASTcte(NULL, data->index,
                                        CT_float, FLOAT_VAL(node), 0.0);
            insert_cte(data, new_entry);
            FLOAT_CTE(node) = new_entry;
        }
        data->cur_const = NULL;
        data->cur_type = CT_NULL;
    }
    return node;
}

/**
 * @fn CSTcte
 */
node_st *CSTcte(node_st *node)
{
    struct data_cst *data = DATA_CST_GET();
    bool correct_type = data->cur_type == CTE_TYPE(node);
    if (correct_type && CTE_TYPE(node) == CT_int
        && NUM_VAL(data->cur_const) == CTE_INT_VAL(node)) {
        NUM_CTE(data->cur_const) = node;
    }
    else if (correct_type && CTE_TYPE(node) == CT_float
             && FLOAT_VAL(data->cur_const) == CTE_FLOAT_VAL(node)) {
        FLOAT_CTE(data->cur_const) = node;
    }
    else {
        TRAVnext(node);
    }
    return node;
}
