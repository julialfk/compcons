// Right now declarations can feature initialisations.
// These have to be removed and replaced by assignments.
// This is done in this traversal.

// Local variables:
// the new assignment statement prefixes the old initialisation
// statement in the list of statements of the function
// the new assignment statement is inserted before the old

// Global variables:
// Create a top-level function named __init (for every compilation unit)
// This function collects all initialisations of global variables
// in the order of their syntactic appearance
// add this function to the AST (doens't really matter where (?))
// this function will be called first by the assembler
// in this __init function, the assignments are created
// change the original initialisation statements to declarations



/**
 * @file
 *
 * Traversal: VarInitsToAssignments
 * UID      : VITA
 *
 *
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"

void VITAinit() {
    node_st *funbody_init = ASTfunbody(NULL, NULL, NULL);
    node_st *fundef_init = ASTfundef(funbody_init, NULL, NULL, CT_void, "__init", false);
    struct data_vita *data = DATA_VITA_GET();
    data->init_funbody = fundef_init;
    data->last_stmts = NULL;
    return;
}

void VITAfini()
{
    struct data_vita *data = DATA_VITA_GET();
    return;
}

/**
 * @fn VITAglobdef
 */
node_st *VITAglobdef(node_st *node)
{
    if (GLOBDEF_INIT(node) != NULL) {
        struct data_vita *data = DATA_VITA_GET();
        data->entry_name = GLOBDEF_NAME(node);
        TRAVnext(data->current_scope);
        node_st *new_varlet = ASTvarlet(NULL, GLOBDEF_NAME(node), data->link_ste);
        node_st *new_assignment = ASTassign(new_varlet, GLOBDEF_INIT(node));
        node_st *new_stmts = ASTstmts(new_assignment, NULL);
        if (data->last_stmts == NULL) {
            FUNBODY_STMTS(data->init_funbody) = new_stmts;
        }
        else {
            STMTS_NEXT(data->last_stmts) = new_stmts;
        }
        data->last_stmts = new_stmts;
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
    return node;
}


/**
 * @fn VITAfundefs
 */
node_st *VITAfundefs(node_st *node)
{
    struct data_vita *data = DATA_VITA_GET();
    // add the __init function to the AST
    if (FUNDEFS_NEXT(node) == NULL) {
        FUNDEFS_NEXT(node) = data->init_funbody;
    }
}


/**
 * @fn VITAfundef
 */
node_st *VITAfundef(node_st *node)
{
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


// in program de pointer naar de symbol table opslaan in
// de travdata
// dit is de symbol table van waar je op dat moment mee bezig bent



// node Assign {
//     children {
//         VarLet let { constructor },
//         Expr expr { constructor, mandatory }
//     }
// };

// node GlobDef {
//     children {
//         Exprs dims { constructor },
//         Expr init { constructor }
//     },

//     attributes {
//         Type type { constructor },
//         string name { constructor },
//         bool export { constructor }
//     }
// };

// node VarLet {
//     children {
//         Exprs indices { constructor }
//     }, 

//     attributes {
//         string name { constructor },
//         Link ste { constructor }
//     }
// };
