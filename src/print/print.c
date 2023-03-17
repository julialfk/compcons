/**
 * @file
 *
 * This file contains the code for the Print traversal.
 * The traversal has the uid: PRT
 *
 *
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"
#include "ccngen/trav.h"
#include "palm/dbug.h"

/**
 * @fn PRTprogram
 */
node_st *PRTprogram(node_st *node)
{
    printf("\n/* Global symbol table: \n\n");
    TRAVglobal(node);
    printf("\n*/\n");

    TRAVdecls(node);

    return node;
}

/**
 * @fn PRTdecls
 */
node_st *PRTdecls(node_st *node)
{
    TRAVdecl(node);
    TRAVnext(node);
    return node;
}

/**
 * @fn PRTexprs
 */
node_st *PRTexprs(node_st *node)
{
    printf("(");
    TRAVexpr(node);
    if (EXPRS_NEXT(node)){
        printf(",");
        TRAVnext(node);
    }
    printf(")");
    return node;
}

/**
 * @fn PRTarrexpr
 */
node_st *PRTarrexpr(node_st *node)
{
    return node;
}

/**
 * @fn PRTids
 */
node_st *PRTids(node_st *node)
{
    return node;
}

/**
 * @fn PRTexprstmt
 */
node_st *PRTexprstmt(node_st *node)
{
    TRAVexpr(node);
    printf("\n");
    return node;
}

/**
 * @fn PRTreturn
 */
node_st *PRTreturn(node_st *node)
{
    printf("return ");
    TRAVexpr(node);
    printf(";");
    // printf( "(%d:%d-%d)", NODE_BLINE(node), NODE_BCOL(node), NODE_ECOL(node));
    printf("\n");
    return node;
}

/**
 * @fn PRTfuncall
 */
node_st *PRTfuncall(node_st *node)
{
    printf("%s(", FUNCALL_NAME(node));
    TRAVargs(node);
    printf(")");
    // printf( "(%d:%d-%d)", NODE_BLINE(node), NODE_BCOL(node), NODE_ECOL(node));

    return node;
}

/**
 * @fn PRTcast
 */
node_st *PRTcast(node_st *node)
{
    char *tmp = NULL;
    // printf( "( ");

    switch (CAST_TYPE(node)) {
    case CT_bool:
      tmp = "bool";
      break;
    case CT_int:
      tmp = "int";
      break;
    case CT_float:
      tmp = "float";
      break;
    case CT_NULL:
      DBUG_ASSERT(false, "unknown cast type detected!");
    }

    printf( "(%s)", tmp);

    TRAVexpr(node);

    // printf( "(%d:%d-%d)", NODE_BLINE(node), NODE_BCOL(node), NODE_ECOL(node));
    return node;
}

/**
 * @fn PRTfundefs
 */
node_st *PRTfundefs(node_st *node)
{
    TRAVfundef(node);
    TRAVnext(node);
    return node;
}

/**
 * @fn PRTfundef
 */
node_st *PRTfundef(node_st *node)
{
    if (FUNDEF_EXPORT(node) != NULL) {
      printf("export ");
    }
    if (FUNDEF_BODY(node) == NULL) {
      printf("extern ");
    }
    char *tmp = NULL;
    switch (FUNDEF_TYPE(node)) {
    case CT_bool:
      tmp = "bool";
      break;
    case CT_int:
      tmp = "int";
      break;
    case CT_float:
      tmp = "float";
      break;
    case CT_void:
      tmp = "void";
      break;
    }
    printf("%s %s(", tmp, FUNDEF_NAME(node));
    TRAVparams(node);
    printf(")");

    printf("\n/* Symbol table: \n\n");
    TRAVsymtable(node);
    printf("\n*/\n");

    if (FUNDEF_BODY(node) == NULL) {
      printf(";\n");
    }
    else {
      printf(" {\n");
      TRAVbody(node);
      printf("}\n");
    }

    return node;
}

/**
 * @fn PRTfunbody
 */
node_st *PRTfunbody(node_st *node)
{
    TRAVdecls(node);
    // TRAVlocal_fundefs(node);
    TRAVstmts(node);
    return node;
}

/**
 * @fn PRTifelse
 */
node_st *PRTifelse(node_st *node)
{
    printf("if (");
    TRAVcond(node);
    printf(") {\n");
    TRAVthen(node);
    if (IFELSE_ELSE_BLOCK(node)) {
        printf("}\n else {\n");
        TRAVelse_block(node);
    }
    printf("}\n");
    // printf( "(%d:%d-%d)\n", NODE_BLINE(node), NODE_BCOL(node), NODE_ECOL(node));
    return node;
}

/**
 * @fn PRTwhile
 */
node_st *PRTwhile(node_st *node)
{
    printf("while (");
    TRAVcond(node);
    printf(") {\n\t");
    TRAVblock(node);
    printf("}\n");
    return node;
}

/**
 * @fn PRTdowhile
 */
node_st *PRTdowhile(node_st *node)
{
    printf("do {\n\t");
    TRAVblock(node);
    printf("}\n");
    printf("while (");
    TRAVcond(node);
    printf(")\n");
    return node;
}

/**
 * @fn PRTfor
 */
node_st *PRTfor(node_st *node)
{
    printf("for (int %s = ", FOR_VAR(node));
    TRAVstart_expr(node);
    printf(", ");
    TRAVstop(node);
    if (FOR_STEP(node)) {
        printf(", ");
        TRAVstep(node);
    }
    printf(") {\n");
    TRAVblock(node);
    printf("}\n");
    // printf( "(%d:%d-%d)\n", NODE_BLINE(node), NODE_BCOL(node), NODE_ECOL(node));
    return node;
}

/**
 * @fn PRTglobdecl
 */
node_st *PRTglobdecl(node_st *node)
{
    char *tmp = NULL;
    printf("extern ");
    switch (GLOBDECL_TYPE(node)) {
    case CT_bool:
      tmp = "bool";
      break;
    case CT_int:
      tmp = "int";
      break;
    case CT_float:
      tmp = "float";
      break;
    case CT_NULL:
      DBUG_ASSERT(false, "unknown var type detected!");
    }
    printf("%s %s;\n", tmp, GLOBDECL_NAME(node));
    return node;
}

/**
 * @fn PRTglobdef
 */
node_st *PRTglobdef(node_st *node)
{
    if (GLOBDEF_EXPORT(node)) {
        printf("export ");
    }

    char *tmp = NULL;
    switch (GLOBDEF_TYPE(node)) {
    case CT_bool:
      tmp = "bool";
      break;
    case CT_int:
      tmp = "int";
      break;
    case CT_float:
      tmp = "float";
      break;
    case CT_NULL:
      DBUG_ASSERT(false, "unknown var type detected!");
    }
    printf("%s %s", tmp, GLOBDEF_NAME(node));

    if (GLOBDEF_INIT(node)) {
        printf(" = ");
        TRAVinit(node);
    }
    printf(";\n");
    return node;
}

/**
 * @fn PRTparam
 */
node_st *PRTparam(node_st *node)
{
    char *tmp = NULL;
    switch (PARAM_TYPE(node)) {
    case CT_bool:
      tmp = "bool";
      break;
    case CT_int:
      tmp = "int";
      break;
    case CT_float:
      tmp = "float";
      break;
    }
    printf("%s %s", tmp, PARAM_NAME(node));
    if (PARAM_NEXT(node) != NULL) {
      printf(", ");
    }
    TRAVnext(node);
    return node;
}




/**
 * @fn PRTvardecl
 */
node_st *PRTvardecl(node_st *node)
{

    char *tmp = NULL;
    switch (VARDECL_TYPE(node)) {
    case CT_bool:
      tmp = "bool";
      break;
    case CT_int:
      tmp = "int";
      break;
    case CT_float:
      tmp = "float";
      break;
    case CT_void:
      tmp = "void";
      break;
    }

    printf( "%s %s", tmp, VARDECL_NAME(node));

    if (VARDECL_INIT(node) != NULL) {
      printf(" = ");
    }

    TRAVinit(node);

    printf(";\n");

    // printf(" (%d:%d-%d)", NODE_BLINE(node), NODE_BCOL(node), NODE_ECOL(node));

    TRAVnext(node);

    return node;
}

/**
 * @fn PRTstmts
 */
node_st *PRTstmts(node_st *node)
{
    TRAVstmt(node);
    TRAVnext(node);
    return node;
}

/**
 * @fn PRTassign
 */
node_st *PRTassign(node_st *node)
{
    if (ASSIGN_LET(node) != NULL) {
        TRAVlet(node);
        printf( " = ");
    }

    TRAVexpr(node);
    printf( ";\n");


    return node;
}

node_st *PRTbinop(node_st *node)
{
    char *tmp = NULL;
    printf( "( ");

    TRAVleft(node);

    switch (BINOP_OP(node)) {
    case BO_add:
      tmp = "+";
      break;
    case BO_sub:
      tmp = "-";
      break;
    case BO_mul:
      tmp = "*";
      break;
    case BO_div:
      tmp = "/";
      break;
    case BO_mod:
      tmp = "%";
      break;
    case BO_lt:
      tmp = "<";
      break;
    case BO_le:
      tmp = "<=";
      break;
    case BO_gt:
      tmp = ">";
      break;
    case BO_ge:
      tmp = ">=";
      break;
    case BO_eq:
      tmp = "==";
      break;
    case BO_ne:
      tmp = "!=";
      break;
    case BO_or:
      tmp = "||";
      break;
    case BO_and:
      tmp = "&&";
      break;
    case BO_NULL:
      DBUG_ASSERT(false, "unknown binop detected!");
    }

    printf( " %s ", tmp);

    TRAVright(node);

    printf(")");
    // printf( "(%d:%d-%d)", NODE_BLINE(node), NODE_BCOL(node), NODE_ECOL(node));

    return node;
}

/**
 * @fn PRTmonop
 */
node_st *PRTmonop(node_st *node)
{
    char *tmp = NULL;
    printf( "( ");

    switch (MONOP_OP(node)) {
    case MO_neg:
      tmp = "-";
      break;
    case MO_not:
      tmp = "!";
      break;
    case BO_NULL:
      DBUG_ASSERT(false, "unknown binop detected!");
    }

    printf( "%s", tmp);

    TRAVoperand(node);

    printf(")");
    // printf( "(%d:%d-%d)", NODE_BLINE(node), NODE_BCOL(node), NODE_ECOL(node));
    return node;
}

/**
 * @fn PRTvarlet
 */
node_st *PRTvarlet(node_st *node)
{
    printf("%s", VARLET_NAME(node));
    // printf("%s(%d:%d)", VARLET_NAME(node), NODE_BLINE(node), NODE_BCOL(node));
    return node;
}

/**
 * @fn PRTvar
 */
node_st *PRTvar(node_st *node)
{
    printf( "%s", VAR_NAME(node));
    return node;
}

/**
 * @fn PRTnum
 */
node_st *PRTnum(node_st *node)
{
    printf("%d", NUM_VAL(node));
    return node;
}

/**
 * @fn PRTfloat
 */
node_st *PRTfloat(node_st *node)
{
    printf( "%f", FLOAT_VAL(node));
    return node;
}

/**
 * @fn PRTbool
 */
node_st *PRTbool(node_st *node)
{
    char *bool_str = BOOL_VAL(node) ? "true" : "false";
    printf("%s", bool_str);
    return node;
}

/**
 * @fn PRTsymtable
 */
node_st *PRTsymtable(node_st *node)
{
    TRAVnext(node);
    return node;
}

/**
 * @fn PRTste
 */
node_st *PRTste(node_st *node)
{
    char *tmp = NULL;
    switch (STE_TYPE(node)) {
    case CT_bool:
      tmp = "bool";
      break;
    case CT_int:
      tmp = "int";
      break;
    case CT_float:
      tmp = "float";
      break;
    case CT_void:
      tmp = "void";
      break;
    }

    printf("%s:%s\n", STE_NAME(node), tmp);
    TRAVnext(node);
    return node;
}
