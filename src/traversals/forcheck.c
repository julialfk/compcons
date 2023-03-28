/**
 * @file
 *
 * Traversal: ForCheck
 * UID      : FC
 *
 *
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"


void FCinit()
{
    struct data_fc *data = DATA_FC_GET();
    data->for_loops = 0;
    data->current_scope = NULL;
    data->var_name = "";
}
void FCfini() { return; }

/**
 * @fn FCfor
 */
node_st *FCfor(node_st *node)
{
    struct data_fc *data = DATA_FC_GET();


    data->for_loops++;
    data->current_scope = FOR_SYMTABLE(node);
    TRAVblock(node);

    data->current_scope = SYMTABLE_PARENT(data->current_scope);
    data->for_loops--;
    return node;
}

/**
 * @fn FCvarlet
 */
node_st *FCvarlet(node_st *node)
{
    struct data_fc *data = DATA_FC_GET();
    node_st *cur_table = data->current_scope;
    for (int i = data->for_loops; i > 0; i--) {
        char *cur_start = STE_NAME(SYMTABLE_NEXT(cur_table));
        if (!strcmp(cur_start, VARLET_NAME(node))) {
            printf("Error (%d:%d): start variable '%s' cannot be reassigned "
                   "within for loop.\n",
                   NODE_BLINE(node), NODE_BCOL(node), VARLET_NAME(node));
        }
    }
    return node;
}

/**
 * @fn FCste
 */
node_st *FCste(node_st *node)
{
    return node;
}
