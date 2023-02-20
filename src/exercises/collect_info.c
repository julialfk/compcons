/**
 * @file
 *
 * This file contains the code for the CollectInfo traversal.
 * The traversal has the uid: CI
 *
 * @brief This module implements a traversal of the abstract syntax tree that
 * counts the occurences of the five arithmetic operators.
 */

#include <stdio.h>

#include "ccn/ccn.h"
#include "ccngen/ast.h"
#include "ccngen/trav_data.h"
#include "palm/dbug.h"


void CIinit() { return; }
void CIfini() { return; }


/**
 * @fn CImodule
 */
node_st *CImodule(node_st *node)
{
    TRAVchildren(node);
    struct data_ci *data = DATA_CI_GET();
    MODULE_PLUS(node) = data->plus;
    MODULE_MINUS(node) = data->minus;
    MODULE_MUL(node) = data->mul;
    MODULE_DIV(node) = data->div;
    MODULE_MOD(node) = data->mod;
    return node;
}

/**
 * @fn CIbinop
 */
node_st *CIbinop(node_st *node)
{
    TRAVchildren(node);
    struct data_ci *data = DATA_CI_GET();

    switch (BINOP_TYPE(node)) {
    case BO_add:
        data->plus += 1;
        break;
    case BO_sub:
        data->minus += 1;
        break;
    case BO_mul:
        data->mul += 1;
        break;
    case BO_div:
        data->div += 1;
        break;
    case BO_mod:
        data->mod += 1;
        break;
    case BO_NULL:
        DBUG_ASSERT(false, "unknown binop detected!");
    }

    return node;
}

