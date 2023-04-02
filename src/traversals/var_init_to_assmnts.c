// Right now declarations can feature initialisations.
// These have to be removed and replaced by assignments.
// This is done in this traversal.

// Local variables:
// the new assignment statement prefixes the old initialisation
// statement in the list of statements of the function
// the new assignment statement is inserted before the old

/**
 * @file
 *
 * Traversal: VarInitsToAssignments
 * UID      : VITA
 *
 *
 */

#include <string.h>
#include <stdio.h>

#include "ccn/ccn.h"
#include "ccngen/ast.h"
#include "ccngen/trav.h"


static void AddLocToNode(node_st *old_node, node_st *new_node)
{
    NODE_BLINE(new_node) = NODE_BLINE(old_node);
    NODE_BCOL(new_node) = NODE_BCOL(old_node);
    NODE_ELINE(new_node) = NODE_ELINE(old_node);
    NODE_ECOL(new_node) = NODE_ECOL(old_node);
}

static void search_ste(struct data_vita *data) {
    node_st *cur_table = data->current_scope;
    do {
        TRAVnext(cur_table);
        cur_table = SYMTABLE_PARENT(data->current_scope);
        // printf("searching: ")
    }
    while (!data->link_ste && cur_table);
}

char *copy_entry_name(char *original) {
    char *entry_name_cpy = (char *)malloc(sizeof(char)
                                        * (strlen(original) + 1));
    strcpy(entry_name_cpy, original);
    return entry_name_cpy;
}

void VITAinit() {
    struct data_vita *data = DATA_VITA_GET();
    data->init_fundef = NULL;
    data->init_funbody = NULL;
    data->last_stmts_init = NULL;
    data->first_stmts_local = NULL;
    data->last_stmts_local = NULL;
    return;
}

void VITAfini() { return; }

/**
 * @fn VITAglobdef
 */
node_st *VITAglobdef(node_st *node)
{
    struct data_vita *data = DATA_VITA_GET();
    if (GLOBDEF_INIT(node) != NULL) {
        data->entry_name = GLOBDEF_NAME(node);
        TRAVnext(data->current_scope);

        if (data->init_fundef == NULL) {
            node_st *funbody_init = ASTfunbody(NULL, NULL, NULL);
            node_st *symtable_init = ASTsymtable(NULL, 0, data->current_scope,
                                                    NULL, 0);
            node_st *fundef_init = ASTfundef(funbody_init, NULL, symtable_init,
                                                CT_void,
                                                copy_entry_name("__init"),
                                                true, false, NULL);
            data->init_fundef = fundef_init;
            data->init_funbody = funbody_init;
        }
        data->link_ste = NULL;
        search_ste(data);
        node_st *new_varlet = ASTvarlet(NULL,
                                        copy_entry_name(GLOBDEF_NAME(node)),
                                        data->link_ste);
        AddLocToNode(new_varlet, node);
        node_st *new_assignment = ASTassign(new_varlet, GLOBDEF_INIT(node));
        AddLocToNode(new_assignment, node);
        node_st *new_stmts = ASTstmts(new_assignment, NULL);
        AddLocToNode(new_stmts, node);
        if (data->last_stmts_init == NULL) {
            FUNBODY_STMTS(data->init_funbody) = new_stmts;
        }
        else {
            STMTS_NEXT(data->last_stmts_init) = new_stmts;
        }
        data->last_stmts_init = new_stmts;
        GLOBDEF_INIT(node) = NULL;
    }
    return node;
}

/**
 * @fn VITAprogram
 */
node_st *VITAprogram(node_st *node)
{
    struct data_vita *data = DATA_VITA_GET();
    data->current_scope = PROGRAM_GLOBAL(node);
    TRAVdecls(node);

    // add the __init function to the AST
    if (data->init_fundef != NULL) {
        node_st *init_decl = ASTdecls(data->init_fundef, PROGRAM_DECLS(node));
        PROGRAM_DECLS(node) = init_decl;

    }
    return node;
}



/**
 * @fn VITAfundef
 */
node_st *VITAfundef(node_st *node)
{   
    struct data_vita *data = DATA_VITA_GET();
    data->last_stmts_local = NULL;
    data->last_stmts_local = NULL;
    data->current_scope = FUNDEF_SYMTABLE(node);
    TRAVbody(node);
    data->current_scope = SYMTABLE_PARENT(node);
    return node;
}

/**
 * @fn VITAfunbody
 */
node_st *VITAfunbody(node_st *node)
{
    struct data_vita *data = DATA_VITA_GET();
    if (FUNBODY_DECLS(node) != NULL) {
        node_st *old_stmts_head = FUNBODY_STMTS(node);
        TRAVdecls(node);
        if (data->last_stmts_local != NULL) {
            FUNBODY_STMTS(node) = data->first_stmts_local;
            STMTS_NEXT(data->last_stmts_local) = old_stmts_head;
        }
    }
    return node;
}


/**
 * @fn VITAvardecl
 */
node_st *VITAvardecl(node_st *node)
{
    if (VARDECL_INIT(node) != NULL) {
        struct data_vita *data = DATA_VITA_GET();

        data->entry_name = VARDECL_NAME(node);
        data->link_ste = NULL;
        search_ste(data);
        node_st *new_varlet = ASTvarlet(NULL, copy_entry_name(VARDECL_NAME(node)), data->link_ste);
        AddLocToNode(new_varlet, node);
        node_st *new_assignment = ASTassign(new_varlet, VARDECL_INIT(node));
        AddLocToNode(new_assignment, node);
        node_st *new_stmts = ASTstmts(new_assignment, NULL);
        AddLocToNode(new_stmts, node);
        if (data->first_stmts_local == NULL) {
            data->first_stmts_local = new_stmts;
            data->last_stmts_local = new_stmts;
        }
        else {
            STMTS_NEXT(data->last_stmts_local) = new_stmts;
            data->last_stmts_local = new_stmts;
        }
        VARDECL_INIT(node) = NULL;
    }
    TRAVnext(node);
    return node;
}

// deze functie traveset de symbol table op zoek naar de juiste
// var. Die var wordt dan opgeslagen in data->link_ste
/**
 * @fn VITAste
 */
node_st *VITAste(node_st *node)
{
    struct data_vita *data = DATA_VITA_GET();
    if (!strcmp(data->entry_name, STE_NAME(node))) {
        data->link_ste = node;
    }
    else {
        TRAVnext(node);
    }
    return node;
}
