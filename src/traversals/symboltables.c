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
#include "palm/ctinfo.h"
#include "palm/str.h"


/* Append the new Ste node to the end of the symbol table.
 *
 * data     : pointer to trav data
 * new_entry: the new ste node
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

/* Traverse through the symbol tables to find the ste for a var or varlet.
 *
 * data: pointer to trav data
 */
static void search_ste(struct data_st *data) {
    node_st *cur_table = data->current_scope;
    do {
        TRAVnext(cur_table);
        cur_table = SYMTABLE_PARENT(cur_table);
        // printf("data->link_ste: %ld\n", data->link_ste);
    }
    while (!data->link_ste && cur_table);
}

/* Raise an error when void has been used incorrectly.
 *
 * node: the node with the incorrect void type
 * name: the name string of the variable with the incorrect type
 */
void void_error(node_st *node, char *name) {
    CTI(CTI_ERROR, false, "Line %d, Col %d \"%s\" has invalid void type.",
            NODE_BLINE(node), NODE_BCOL(node), name);
    CCNerrorAction();
}

/* Raise an error when a variable is found that has not previously been
 * declared.
 *
 * node: the node with the incorrect void type
 * name: the name string of the undeclared variable
 */
void not_declared_error(node_st *node, char *name) {
    CTI(CTI_ERROR, false, "Line %d, Col %d \"%s\" is not declared.",
            NODE_BLINE(node), NODE_BCOL(node), name);
    CCNerrorAction();
}

/* Raise an error when the program tries to declare a variable that has already
 * been declared in that scope.
 *
 * node: the node with the incorrect void type
 * name: the name string of the variable that was already declared
 */
void already_declared_error(node_st *node, char *name) {
    CTI(CTI_ERROR, false, "Line %d, Col %d \"%s\" is already declared.",
            NODE_BLINE(node), NODE_BCOL(node), name);
    CCNerrorAction();
}

void STinit()
{
    struct data_st *data = DATA_ST_GET();
    data->current_scope = NULL;
    data->nest_lvl = 0;
    data->index_extern_fun = 0;
    data->index_extern_var = 0;
    data->index_var = 0;
    data->index_fun = 0;
    data->entry_name = "";
    data->link_ste = NULL;
    data->function_ste = NULL;
    data->globals_finished = false;
}
void STfini() { return; }


/**
 * @fn STprogram
 */
node_st *STprogram(node_st *node)
{
    struct data_st *data = DATA_ST_GET();

    node_st *global_symtable = ASTsymtable(NULL, data->nest_lvl, NULL, NULL, 0);
    PROGRAM_GLOBAL(node) = global_symtable;
    data->current_scope = global_symtable;

    TRAVdecls(node);
    data->globals_finished = true;
    TRAVdecls(node);

    return node;
}

/**
 * @fn STglobdef
 */
node_st *STglobdef(node_st *node)
{
    if (GLOBDEF_TYPE(node) == CT_void) {
        void_error(node, GLOBDEF_NAME(node));
    }

    struct data_st *data = DATA_ST_GET();
    if (data->globals_finished) {
        return node;
    }
    // Check if the variable is already in the table.
    data->link_ste = NULL;
    data->entry_name = GLOBDEF_NAME(node);
    TRAVnext(data->current_scope);

    if (!data->link_ste) {
        node_st *new_entry = ASTste(NULL, STRcpy(data->entry_name),
                                    GLOBDEF_TYPE(node), false, 0, NULL,
                                    data->nest_lvl, data->index_var++, false,
                                    GLOBDEF_EXPORT(node));
        insert_ste(data, new_entry);
    }
    else {
        already_declared_error(node, GLOBDEF_NAME(node));
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
        void_error(node, GLOBDECL_NAME(node));
    }

    struct data_st *data = DATA_ST_GET();
    if (data->globals_finished) {
        return node;
    }

    data->link_ste = NULL;
    data->entry_name = GLOBDECL_NAME(node);
    TRAVnext(data->current_scope);

    if (!data->link_ste) {
        node_st *new_entry = ASTste(NULL, STRcpy(data->entry_name),
                                    GLOBDECL_TYPE(node), false, 0, NULL,
                                    data->nest_lvl, data->index_extern_var++,
                                    true, false);
        insert_ste(data, new_entry);
    }
    else {
        already_declared_error(node, GLOBDECL_NAME(node));
    }

    data->link_ste = NULL;
    return node;
}

/**
 * @fn STassign
 */
node_st *STassign(node_st *node)
{
    TRAVexpr(node);
    TRAVlet(node);
    return node;
}


/**
 * @fn STfor
 */
node_st *STfor(node_st *node) {
    struct data_st *data = DATA_ST_GET();
    node_st *new_entry = ASTste(NULL, STRcpy(FOR_VAR(node)),
                                CT_int, false, 0, NULL, data->nest_lvl + 1, 0,
                                false, false);
    node_st *symtable = ASTsymtable(new_entry, data->nest_lvl + 1,
                                    data->current_scope, new_entry, 1);
    FOR_SYMTABLE(node) = symtable;

    data->current_scope = symtable;
    TRAVstop(node);
    if (FOR_STEP(node)) {
        TRAVstep(node);
    }
    if (FOR_BLOCK(node)) {
        TRAVblock(node);
    }
    data->current_scope = SYMTABLE_PARENT(data->current_scope);

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
        not_declared_error(node, VAR_NAME(node));
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
    if (!(data->globals_finished)) {
        data->link_ste = NULL;
        data->entry_name = FUNDEF_NAME(node);
        TRAVnext(data->current_scope);

        if (data->link_ste) {
            already_declared_error(node, FUNDEF_NAME(node));
            return node;
        }

        node_st *new_entry;
        if (FUNDEF_EXTERN_BOOL(node)) {
            new_entry = ASTste(NULL, STRcpy(data->entry_name),
                                    FUNDEF_TYPE(node), true, 0, NULL,
                                    data->nest_lvl, data->index_extern_fun++,
                                    true, false);
        }
        else {
            new_entry = ASTste(NULL, STRcpy(data->entry_name),
                                    FUNDEF_TYPE(node), true, 0, NULL,
                                    data->nest_lvl, data->index_fun++,
                                    false, FUNDEF_EXPORT(node));
        }
        insert_ste(data, new_entry);
        FUNDEF_STE(node) = new_entry;
    }
    else {
        data->nest_lvl++;
        node_st *symtable = ASTsymtable(NULL, data->nest_lvl,
                                        data->current_scope, NULL, 0);
        FUNDEF_SYMTABLE(node) = symtable;
        data->current_scope = symtable;

        data->function_ste = FUNDEF_STE(node);
        TRAVparams(node);
        TRAVbody(node);

        data->nest_lvl--;
        data->current_scope = SYMTABLE_PARENT(data->current_scope);
        data->function_ste = NULL;
    }

    return node;
}

/**
 * @fn STparam
 */
node_st *STparam(node_st *node)
{
    if (PARAM_TYPE(node) == CT_void) {
        void_error(node, PARAM_NAME(node));
    }

    struct data_st *data = DATA_ST_GET();
    data->link_ste = NULL;
    data->entry_name = PARAM_NAME(node);
    TRAVnext(data->current_scope);

    if (!data->link_ste) {
        node_st *new_entry = ASTste(NULL, STRcpy(data->entry_name),
                                    PARAM_TYPE(node), false, 0, NULL,
                                    data->nest_lvl,
                                    SYMTABLE_NEXT_INDEX(data->current_scope)++,
                                    false, false);
        insert_ste(data, new_entry);
        if (STE_ARITY(data->function_ste) == 0) {
            STE_FIRST_PARAM(data->function_ste) = new_entry;
        }
        STE_ARITY(data->function_ste)++;
    }
    else {
        already_declared_error(node, PARAM_NAME(node));
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
        void_error(node, VARDECL_NAME(node));
    }

    struct data_st *data = DATA_ST_GET();
    data->link_ste = NULL;
    data->entry_name = VARDECL_NAME(node);
    TRAVnext(data->current_scope);

    if (!data->link_ste) {
        node_st *new_entry = ASTste(NULL, STRcpy(data->entry_name),
                                    VARDECL_TYPE(node), false, 0, NULL,
                                    data->nest_lvl,
                                    SYMTABLE_NEXT_INDEX(data->current_scope)++,
                                    false, false);
        insert_ste(data, new_entry);
    }
    else {
        already_declared_error(node, VARDECL_NAME(node));
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
        not_declared_error(node, VAR_NAME(node));
    }

    data->link_ste = NULL;
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
        not_declared_error(node, VARLET_NAME(node));
    }

    data->link_ste = NULL;
    return node;
}
