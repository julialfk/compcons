/**
 * @file
 *
 * This file contains the code for the LookupTables traversal.
 * The traversal has the uid: LT
 *
 * @brief This module implements a traversal of the abstract syntax tree that
 * counts the occurences of all variable names and prints them at the end of
 * the traversal.
 */

#include <stdio.h>
#include <string.h>

#include "ccn/ccn.h"
#include "ccngen/ast.h"
#include "ccngen/trav_data.h"


void LTinit()
{
    struct data_lt *data = DATA_LT_GET();
    data->id_table = HTnew_String(10);
    data->first_stmts = false;
}

void LTfini()
{
    struct data_lt *data = DATA_LT_GET();
    HTdelete(data->id_table);
}

/**
 * Print an entry from id_table and free the value of the entry.
 */
void *LTprint(void *key, void *value)
{
    printf("%s\t %d\n", (char *)key, *((int *)value));
    free(value);
    return NULL;
}

/**
 * @fn LTstmts
 */
node_st *LTstmts(node_st *node)
{
    TRAVchildren(node);
    struct data_lt *data = DATA_LT_GET();
    if (!data->first_stmts) {
        data->first_stmts = true;
        printf("Variables:\n");
        HTmapWithKey(data->id_table, LTprint);
        printf("\n");
    }
    return node;
}

/**
 * @fn LTvar
 */
node_st *LTvar(node_st *node)
{
    struct data_lt *data = DATA_LT_GET();

    char *name = VAR_NAME(node);
    int *counter = HTlookup(data->id_table, name);

    if (!counter) {
        counter = (int *)malloc(sizeof(int));
        *counter = 1;
        HTinsert(data->id_table, name, counter);
    }
    else {
        (*counter)++;
    }

    return node;
}

/**
 * @fn LTvarlet
 */
node_st *LTvarlet(node_st *node)
{
    struct data_lt *data = DATA_LT_GET();

    char *name = VARLET_NAME(node);
    int *counter = HTlookup(data->id_table, name);

    if (!counter) {
        counter = (int *)malloc(sizeof(int));
        *counter = 1;
        HTinsert(data->id_table, name, counter);
    }
    else {
        (*counter)++;
    }

    return node;
}

