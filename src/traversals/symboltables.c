/**
 * @file
 *
 * Traversal: SymbolTables
 * UID      : ST
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
void insert_ste(struct data_st *data, node_st *new_entry) {
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


void search_ste(struct data_st *data) {
    node_st *cur_table = data->current_scope;
    do {
        TRAVnext(cur_table);
        cur_table = SYMTABLE_PARENT(cur_table);
    }
    while (!(data->link_ste) && cur_table);
}

static char *copy_entry_name(char *original) {
    char *entry_name_cpy = (char *)malloc(sizeof(char)
                                        * (strlen(original) + 1));
    strcpy(entry_name_cpy, original);
    return entry_name_cpy;
}

void STinit()
{
    struct data_st *data = DATA_ST_GET();
    data->current_scope = NULL;
    data->entry_name = "";
    data->link_ste = NULL;
    data->function_ste = NULL;
}
void STfini() { return; }


/**
 * @fn STprogram
 */
node_st *STprogram(node_st *node)
{
    struct data_st *data = DATA_ST_GET();
    data->nest_lvl = 0;

    node_st *global_symtable = ASTsymtable(NULL, data->nest_lvl, NULL, NULL);
    PROGRAM_GLOBAL(node) = global_symtable;
    data->current_scope = global_symtable;
    // printf("%ld\n", data->current_scope);

    TRAVdecls(node);

    return node;
}

/**
 * @fn STglobdef
 */
node_st *STglobdef(node_st *node)
{
    if (GLOBDEF_TYPE(node) == CT_void) {
        printf("Error: %s(%d:%d-%d) has invalid void type.",
                    GLOBDEF_NAME(node), NODE_BLINE(node),
                    NODE_BCOL(node), NODE_ECOL(node));

        return node;
    }

    struct data_st *data = DATA_ST_GET();
    // Check if already in table
    data->link_ste = NULL;
    data->entry_name = GLOBDEF_NAME(node);
    // printf("in globdef: %s\n", data->entry_name);
    TRAVnext(data->current_scope);

    if (!data->link_ste) {
        node_st *new_entry = ASTste(NULL, copy_entry_name(data->entry_name),
                                    GLOBDEF_TYPE(node), false, 0, NULL,
                                    data->nest_lvl);
        insert_ste(data, new_entry);
    }
    else {
        // Could add where it has been declared before.
        printf("Error: %s(%d:%d-%d) already declared.",
                    GLOBDEF_NAME(node), NODE_BLINE(node),
                    NODE_BCOL(node), NODE_ECOL(node));
    }

    data->link_ste = NULL;
    return node;
}

/**
 * @fn STglobdecl
 */
node_st *STglobdecl(node_st *node)
{
    if (GLOBDECL_TYPE(node) == CT_void) {
        printf("Error: %s(%d:%d-%d) has invalid void type.",
                    GLOBDECL_NAME(node), NODE_BLINE(node),
                    NODE_BCOL(node), NODE_ECOL(node));

        return node;
    }

    struct data_st *data = DATA_ST_GET();
    data->link_ste = NULL;
    data->entry_name = GLOBDECL_NAME(node);
    // printf("in globdecl: %s\n", data->entry_name);
    TRAVnext(data->current_scope);

    if (!data->link_ste) {
        node_st *new_entry = ASTste(NULL, copy_entry_name(data->entry_name),
                                    GLOBDECL_TYPE(node), false, 0, NULL,
                                    data->nest_lvl);
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
 * @fn STfor
 */
node_st *STfor(node_st *node) {
    struct data_st *data = DATA_ST_GET();
    // printf("%d\n", data->nest_lvl);
    node_st *new_entry = ASTste(NULL, copy_entry_name(FOR_VAR(node)),
                                CT_int, false, 0, NULL, data->nest_lvl + 1);
    node_st *symtable = ASTsymtable(new_entry, data->nest_lvl + 1,
                                    data->current_scope, new_entry);
    // if (NODE_TYPE(symtable) == NT_SYMTABLE) {
    //     printf("correct code type\n");
    // }
    FOR_SYMTABLE(node) = symtable;
    TRAVblock(node);

    return node;
}

/**
 * @fn STfuncall
 */
node_st *STfuncall(node_st *node)
{
    struct data_st *data = DATA_ST_GET();
    data->link_ste = NULL;
    data->entry_name = FUNCALL_NAME(node);

    search_ste(data);
    if (data->link_ste) {
        FUNCALL_STE(node) = data->link_ste;
    }
    else {
        printf("Error: %s(%d:%d-%d) not declared.",
                    VAR_NAME(node), NODE_BLINE(node),
                    NODE_BCOL(node), NODE_ECOL(node));
    }

    data->link_ste = NULL;
    TRAVargs(node);
    return node;
}

/**
 * @fn STfundef
 */
node_st *STfundef(node_st *node)
{
    struct data_st *data = DATA_ST_GET();
    data->link_ste = NULL;
    data->entry_name = FUNDEF_NAME(node);
    TRAVnext(data->current_scope);

    if (data->link_ste) {
        printf("Error: %s(%d:%d-%d) already declared.",
                    FUNDEF_NAME(node), NODE_BLINE(node),
                    NODE_BCOL(node), NODE_ECOL(node));
        return node;
    }

    node_st *new_entry = ASTste(NULL, copy_entry_name(data->entry_name),
                                FUNDEF_TYPE(node), true, 0, NULL,
                                data->nest_lvl);
    insert_ste(data, new_entry);

    data->nest_lvl++;
    node_st *symtable = ASTsymtable(NULL, data->nest_lvl,
                                    data->current_scope, NULL);
    FUNDEF_SYMTABLE(node) = symtable;
    data->current_scope = symtable;

    data->function_ste = new_entry;
    TRAVparams(node);
    TRAVbody(node);

    data->nest_lvl--;
    data->current_scope = SYMTABLE_PARENT(data->current_scope);

    return node;
}

/**
 * @fn STparam
 */
node_st *STparam(node_st *node)
{
    if (PARAM_TYPE(node) == CT_void) {
        printf("Error: %s(%d:%d-%d) has invalid void type.",
                    PARAM_NAME(node), NODE_BLINE(node),
                    NODE_BCOL(node), NODE_ECOL(node));

        return node;
    }

    struct data_st *data = DATA_ST_GET();
    data->link_ste = NULL;
    data->entry_name = PARAM_NAME(node);
    TRAVnext(data->current_scope);

    if (!data->link_ste) {
        node_st *new_entry = ASTste(NULL, copy_entry_name(data->entry_name),
                                    PARAM_TYPE(node), false, 0, NULL,
                                    data->nest_lvl);
        insert_ste(data, new_entry);
        if (STE_ARITY(data->function_ste) == 0) {
            STE_FIRST_PARAM(data->function_ste) = new_entry;
        }
        STE_ARITY(data->function_ste)++;
    }
    else {
        printf("Error: %s(%d:%d-%d) already declared.",
                    PARAM_NAME(node), NODE_BLINE(node),
                    NODE_BCOL(node), NODE_ECOL(node));
    }

    TRAVnext(node);

    data->link_ste = NULL;
    return node;
}

/**
 * @fn STvardecl
 */
node_st *STvardecl(node_st *node)
{
    if (VARDECL_TYPE(node) == CT_void) {
        printf("Error: %s(%d:%d-%d) has invalid void type.",
                    VARDECL_NAME(node), NODE_BLINE(node),
                    NODE_BCOL(node), NODE_ECOL(node));

        return node;
    }

    struct data_st *data = DATA_ST_GET();
    data->link_ste = NULL;
    data->entry_name = VARDECL_NAME(node);
    TRAVnext(data->current_scope);

    if (!data->link_ste) {
        node_st *new_entry = ASTste(NULL, copy_entry_name(data->entry_name),
                                    VARDECL_TYPE(node), false, 0, NULL,
                                    data->nest_lvl);
        insert_ste(data, new_entry);
    }
    else {
        printf("Error: %s(%d:%d-%d) already declared.",
                    VARDECL_NAME(node), NODE_BLINE(node),
                    NODE_BCOL(node), NODE_ECOL(node));
    }
    TRAVinit(node);
    TRAVnext(node);

    data->link_ste = NULL;
    return node;
}

/**
 * @fn STvar
 */
node_st *STvar(node_st *node)
{
    struct data_st *data = DATA_ST_GET();
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
 * @fn STsymtable
 */
node_st *STsymtable(node_st *node)
{
    TRAVnext(node);
    return node;
}

/**
 * @fn STste
 */
node_st *STste(node_st *node)
{
    struct data_st *data = DATA_ST_GET();
    if (!strcmp(data->entry_name, STE_NAME(node))) {
        data->link_ste = node;
    }
    else {
        TRAVnext(node);
    }
    return node;
}

/**
 * @fn STvarlet
 */
node_st *STvarlet(node_st *node)
{
    struct data_st *data = DATA_ST_GET();
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

