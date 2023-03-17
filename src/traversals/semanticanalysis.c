/**
 * @file
 *
 * Traversal: SemanticAnalysis
 * UID      : SA
 *
 *
 */

#include <stdio.h>
#include <string.h>

#include "ccn/ccn.h"
#include "ccngen/ast.h"
#include "ccngen/enum.h"
#include "ccngen/trav.h"


/* Append the new Ste node to the end of the symbol table.
*/
void insert_ste(struct data_sa *data, node_st *new_entry) {
    if (SYMTABLE_TAIL(data->current_scope) == NULL) {
        // printf("tail = symtable\n");
        SYMTABLE_NEXT(data->current_scope) = new_entry;
    }
    else {
        // printf("tail = %s\n", STE_NAME(cur_table_data->tail));
        STE_NEXT(SYMTABLE_TAIL(data->current_scope)) = new_entry;
    }
    SYMTABLE_TAIL(data->current_scope) = new_entry;
}


void search_ste(struct data_sa *data) {
    node_st *cur_table = data->current_scope;
    do {
        TRAVnext(cur_table);
        cur_table = SYMTABLE_PARENT(data->current_scope);
        // printf("searching: ")
    }
    while (!data->link_ste && cur_table);
}

void SAinit()
{
    struct data_sa *data = DATA_SA_GET();
    data->current_scope = NULL;
    data->entry_name = "";
    data->link_ste = NULL;
    data->function_ste = NULL;
}
void SAfini()
{
    struct data_sa *data = DATA_SA_GET();
}


/**
 * @fn SAprogram
 */
node_st *SAprogram(node_st *node)
{
    struct data_sa *data = DATA_SA_GET();
    data->nest_lvl = 0;

    node_st *global_symtable = ASTsymtable(NULL, data->nest_lvl, NULL, NULL);
    printf("%ld\n", global_symtable);
    PROGRAM_GLOBAL(node) = global_symtable;
    data->current_scope = global_symtable;
    // printf("%ld\n", data->current_scope);

    TRAVdecls(node);

    return node;
}

/**
 * @fn SAglobdef
 */
node_st *SAglobdef(node_st *node)
{
    if (GLOBDEF_TYPE(node) == CT_void) {
        printf("Error: %s(%d:%d-%d) has invalid void type.",
                    GLOBDEF_NAME(node), NODE_BLINE(node),
                    NODE_BCOL(node), NODE_ECOL(node));

        return node;
    }

    struct data_sa *data = DATA_SA_GET();
    // Check if already in table
    data->link_ste = NULL;
    data->entry_name = GLOBDEF_NAME(node);
    // printf("in globdef: %s\n", data->entry_name);
    TRAVnext(data->current_scope);

    if (!data->link_ste) {
        node_st *new_entry = ASTste(NULL,  data->entry_name,
                                    GLOBDEF_TYPE(node), 0, data->nest_lvl);
        insert_ste(data, new_entry);
    }
    else {
        // Could add where it has been declared before.
        printf("Warning: %s(%d:%d-%d) already declared.",
                    GLOBDEF_NAME(node), NODE_BLINE(node),
                    NODE_BCOL(node), NODE_ECOL(node));
    }

    data->link_ste = NULL;
    return node;
}

/**
 * @fn SAglobdecl
 */
node_st *SAglobdecl(node_st *node)
{
    if (GLOBDECL_TYPE(node) == CT_void) {
        printf("Error: %s(%d:%d-%d) has invalid void type.",
                    GLOBDECL_NAME(node), NODE_BLINE(node),
                    NODE_BCOL(node), NODE_ECOL(node));

        return node;
    }

    struct data_sa *data = DATA_SA_GET();
    data->link_ste = NULL;
    data->entry_name = GLOBDECL_NAME(node);
    // printf("in globdecl: %s\n", data->entry_name);
    TRAVnext(data->current_scope);

    if (!data->link_ste) {
        node_st *new_entry = ASTste(NULL, data->entry_name,
                                    GLOBDECL_TYPE(node), 0, data->nest_lvl);
        insert_ste(data, new_entry);
    }
    else {
        printf("Warning: %s(%d:%d-%d) already declared.",
                    GLOBDECL_NAME(node), NODE_BLINE(node),
                    NODE_BCOL(node), NODE_ECOL(node));
    }
    data->link_ste = NULL;
    return node;
}

/**
 * @fn SAfundef
 */
node_st *SAfundef(node_st *node)
{
    struct data_sa *data = DATA_SA_GET();
    data->link_ste = NULL;
    data->entry_name = FUNDEF_NAME(node);
    // printf("in globdecl: %s\n", data->entry_name);
    // TRAVnext(data->current_scope);

    // if (data->link_ste) {
    //     printf("Warning: %s(%d:%d-%d) already declared.",
    //                 FUNDEF_NAME(node), NODE_BLINE(node),
    //                 NODE_BCOL(node), NODE_ECOL(node));
    //     return node;
    // }

    // node_st *new_entry = ASTste(NULL, data->entry_name,
    //                             FUNDEF_TYPE(node), 0, data->nest_lvl);
    // insert_ste(data, new_entry);

    // data->nest_lvl++;
    node_st *symtable = ASTsymtable(NULL, data->nest_lvl,
                                    data->current_scope, NULL);
    FUNDEF_SYMTABLE(node) = symtable;
    data->current_scope = symtable;

    // data->function_ste = new_entry;
    TRAVparams(node);
    TRAVbody(node);

    data->nest_lvl--;
    data->current_scope = SYMTABLE_PARENT(data->current_scope);
    // printf("new scope: %d\n", );

    return node;
}

/**
 * @fn SAparam
 */
node_st *SAparam(node_st *node)
{
    if (PARAM_TYPE(node) == CT_void) {
        printf("Error: %s(%d:%d-%d) has invalid void type.",
                    PARAM_NAME(node), NODE_BLINE(node),
                    NODE_BCOL(node), NODE_ECOL(node));

        return node;
    }

    struct data_sa *data = DATA_SA_GET();
    data->link_ste = NULL;
    data->entry_name = PARAM_NAME(node);
    // printf("in param: %s\n", data->entry_name);
    TRAVnext(data->current_scope);

    if (!data->link_ste) {
        node_st *new_entry = ASTste(NULL, data->entry_name,
                                    PARAM_TYPE(node), 0, data->nest_lvl);
        insert_ste(data, new_entry);
        // STE_ARITY(data->function_ste)++;
    }
    else {
        printf("Warning: %s(%d:%d-%d) already declared.",
                    PARAM_NAME(node), NODE_BLINE(node),
                    NODE_BCOL(node), NODE_ECOL(node));
    }

    TRAVnext(node);

    data->link_ste = NULL;
    return node;
}

/**
 * @fn SAvardecl
 */
node_st *SAvardecl(node_st *node)
{
    if (VARDECL_TYPE(node) == CT_void) {
        printf("Error: %s(%d:%d-%d) has invalid void type.",
                    VARDECL_NAME(node), NODE_BLINE(node),
                    NODE_BCOL(node), NODE_ECOL(node));

        return node;
    }

    struct data_sa *data = DATA_SA_GET();
    data->link_ste = NULL;
    data->entry_name = VARDECL_NAME(node);
    // printf("in vardecl: %s\n", data->entry_name);
    TRAVnext(data->current_scope);

    if (!data->link_ste) {
        node_st *new_entry = ASTste(NULL, data->entry_name,
                                    VARDECL_TYPE(node), 0, data->nest_lvl);
        insert_ste(data, new_entry);
    }
    else {
        printf("Warning: %s(%d:%d-%d) already declared.",
                    VARDECL_NAME(node), NODE_BLINE(node),
                    NODE_BCOL(node), NODE_ECOL(node));
    }

    TRAVnext(node);

    data->link_ste = NULL;
    return node;
}

/**
 * @fn SAvar
 */
node_st *SAvar(node_st *node)
{
    struct data_sa *data = DATA_SA_GET();
    data->link_ste = NULL;
    data->entry_name = VAR_NAME(node);

    search_ste(data);
    if (data->link_ste) {
        VAR_STE(node) = data->link_ste;
    }
    else {
        printf("Error: %s(%d:%d-%d) not declared.",
                    VAR_NAME(node), NODE_BLINE(node),
                    NODE_BCOL(node), NODE_ECOL(node));
    }

    data->link_ste = NULL;
    return node;
}

/**
 * @fn SAsymtable
 */
node_st *SAsymtable(node_st *node)
{
    TRAVnext(node);
    return node;
}

/**
 * @fn SAste
 */
node_st *SAste(node_st *node)
{
    struct data_sa *data = DATA_SA_GET();
    if (!strcmp(data->entry_name, STE_NAME(node))) {
        data->link_ste = node;
    }
    else {
        TRAVnext(node);
    }
    return node;
}

/**
 * @fn SAvarlet
 */
node_st *SAvarlet(node_st *node)
{
    struct data_sa *data = DATA_SA_GET();
    data->link_ste = NULL;
    data->entry_name = VARLET_NAME(node);

    search_ste(data);
    if (data->link_ste) {
        VARLET_STE(node) = data->link_ste;
    }
    else {
        printf("Error: %s(%d:%d-%d) not declared.",
                    VARLET_NAME(node), NODE_BLINE(node),
                    NODE_BCOL(node), NODE_ECOL(node));
    }

    data->link_ste = NULL;
    return node;
}

