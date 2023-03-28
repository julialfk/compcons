/**
 * @file
 *
 * Traversal: BooleanCasts
 * UID      : BC
 *
 *
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"

/**
 * @fn BCcast
 */
node_st *BCcast(node_st *node)
{
    if (CAST_TYPE(node) == CT_bool) {
        
    }
    return node;
}

/**
 * @fn BCbinop
 */
node_st *BCbinop(node_st *node)
{
    return node;
}

/**
 * @fn BCbool
 */
node_st *BCbool(node_st *node)
{
    return node;
}

/**
 * @fn BCmonop
 */
node_st *BCmonop(node_st *node)
{
    return node;
}

/**
 * @fn BCfloat
 */
node_st *BCfloat(node_st *node)
{
    return node;
}

/**
 * @fn BCfuncall
 */
node_st *BCfuncall(node_st *node)
{
    return node;
}

/**
 * @fn BCnum
 */
node_st *BCnum(node_st *node)
{
    return node;
}

/**
 * @fn BCvar
 */
node_st *BCvar(node_st *node)
{
    return node;
}


// node Cast {
//     children {
//         Expr expr {constructor, mandatory }
//     }, 
//     attributes {
//         Type type { constructor }
//     }
// };
