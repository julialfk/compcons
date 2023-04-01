/**
 * @file
 *
 * Traversal: Assembler
 * UID      : AS
 *
 *
 */

#include <string.h>

#include "ccn/ccn.h"
#include "ccngen/ast.h"
#include "ccngen/trav.h"
#include "palm/dbug.h"
#include "ccngen/enum.h"
#include "palm/ctinfo.h"


/* Print the character associated with the basic type.
 *
 * type: the basic type
 */
void print_type(enum Type type) {
    switch(type) {
      case CT_int:
        printf("int");
        break;
      case CT_float:
        printf("float");
        break;
      case CT_bool:
        printf("bool");
        break;
      case CT_void:
        printf("void");
        break;
      default:
        DBUG_ASSERT(false, "unknown type detected!");
    }
}

void print_types(node_st *node) {
    print_type(STE_TYPE(node));
    node_st *arg = STE_FIRST_PARAM(node);
    for (int i = STE_ARITY(node); i > 0; i--) {
        printf(" ");
        print_type(STE_TYPE(arg));
        arg = STE_NEXT(arg);
    }
}

/* Print the character associated with the basic type.
 *
 * type: the basic type
 */
void print_type_char(enum Type type) {
    switch(type) {
      case CT_int:
        printf("i");
        break;
      case CT_float:
        printf("f");
        break;
      case CT_bool:
        printf("b");
        break;
      default:
        DBUG_ASSERT(false, "unknown type detected!");
    }
}

/* Return the resulting type of an expression
 *
 * expr: the expression
 */
static enum Type get_type(node_st *expr) {
    enum Type type;
    switch (NODE_TYPE(expr)) {
      case NT_CAST:
        type = CAST_TYPE(expr);
        break;
      case NT_FUNCALL:
        type = STE_TYPE(FUNCALL_STE(expr));
        break;
      case NT_VAR:
        type = STE_TYPE(VAR_STE(expr));
        break;
      case NT_NUM:
        type = CT_int;
        break;
      case NT_FLOAT:
        type = CT_float;
        break;
      case NT_BOOL:
        type = CT_bool;
        break;
      case NT_BINOP:
        type = BINOP_EXPR_TYPE(expr);
        break;
      case NT_MONOP:
        type = MONOP_EXPR_TYPE(expr);
    }

    return type;
}

void ASinit()
{
    struct data_as *data = DATA_AS_GET();
    data->cur_lvl = 0;
    data->tag_index = 1;
    data->init = false;
    data->returned = false;
    data->local_vars = 0;
}
void ASfini() { return; }

/**
 * @fn ASprogram
 */
node_st *ASprogram(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    TRAVdecls(node);
    TRAVconstants(node);
    if (data->init) {
        printf(".exportfun \"__init\" void __init\n");
    }
    TRAVglobal(node);



    // while (global_ste) {
    //     if (!STE_FUNCTION(global_ste)) {
    //         if (STE_EXPORT(global_ste)) {
    //             printf(".exportvar \"%s\" %d\n",
    //                         STE_NAME(global_ste), STE_INDEX(global_ste));
    //         }
    //         printf(".global ");
    //         print_type(STE_TYPE(global_ste));
    //         printf("\n");
    //     }
    //     else {

    //     }
    //     global_ste = STE_NEXT(global_ste);
    // }


    // if (global_ste && !STE_FUNCTION(global_ste)) {
    //     do {
    //         if (STE_EXPORT(global_ste)) {
    //             printf(".exportvar \"%s\" %d\n",
    //                         STE_NAME(global_ste), STE_INDEX(global_ste));
    //         }
    //         printf(".global ");
    //         print_type(STE_TYPE(global_ste));
    //         printf("\n");
    //         global_ste = STE_NEXT(global_ste);
    //     }
    //     while (global_ste && !STE_FUNCTION(global_ste));
    // }
    return node;
}

/**
 * @fn ASdecls
 */
node_st *ASdecls(node_st *node)
{
    TRAVchildren(node);
    return node;
}

/**
 * @fn ASexprs
 */
node_st *ASexprs(node_st *node)
{
    TRAVchildren(node);
    return node;
}

/**
 * @fn ASarrexpr
 */
node_st *ASarrexpr(node_st *node)
{
    return node;
}

/**
 * @fn ASids
 */
node_st *ASids(node_st *node)
{
    return node;
}

/**
 * @fn ASexprstmt
 */
node_st *ASexprstmt(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    TRAVexpr(node);

    node_st *expr = EXPRSTMT_EXPR(node);
    enum Type type = get_type(expr);
    if (type != CT_void) {
        printf("    ");
        print_type_char(get_type(expr));
        printf("pop");
    }

    return node;
}

/**
 * @fn ASreturn
 */
node_st *ASreturn(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    TRAVexpr(node);
    printf("    ");
    if (RETURN_EXPR(node)) {
        enum Type type = get_type(RETURN_EXPR(node));
        if (type != CT_void) {
          print_type_char(type);
        }
    }
    printf("return\n");
    data->returned = true;
    return node;
}

/**
 * @fn ASfuncall
 */
node_st *ASfuncall(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    printf("    isrg\n");
    TRAVargs(node);
    printf("    jsr %d %s\n",
                STE_ARITY(FUNCALL_STE(node)), FUNCALL_NAME(node));

    // int nest_lvl = STE_NEST_LVL(FUNCALL_STE(node));
    // int index = STE_INDEX(FUNCALL_STE(node));
    // if (nest_lvl == 0) {
    //     printf("g\n");
    // }
    // else if (nest_lvl == data->cur_lvl) {
    //     printf("l\n");
    // }
    // else {
    //     printf("n %d\n", data->cur_lvl - nest_lvl);
    // }

    return node;
}

/**
 * @fn AScast
 */
node_st *AScast(node_st *node)
{
    TRAVexpr(node);
    // niet casten als types toch al gelijk zijn
    if (CAST_TYPE(node) == get_type(CAST_EXPR(node))) {
        return node;
    }
    printf("    ");
    if (CAST_TYPE(node) == CT_int) {
        printf("f2i");
    }
    else if (CAST_TYPE(node) == CT_float) {
        printf("i2f");
    }

    return node;
}

/**
 * @fn ASfundefs
 */
node_st *ASfundefs(node_st *node)
{
    TRAVchildren(node);
    return node;
}

/**
 * @fn ASfundef
 */
node_st *ASfundef(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    if (!strcmp(FUNDEF_NAME(node), "__init")) {
        data->init = true;
    }
    printf("%s:\n", FUNDEF_NAME(node));
    data->cur_lvl++;
    TRAVbody(node);
    data->cur_lvl--;
    printf("\n");
    return node;
}

/**
 * @fn ASfunbody
 */
node_st *ASfunbody(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    if (FUNBODY_DECLS(node)) {
        TRAVdecls(node);
        printf("    esr %d\n", data->local_vars);
        data->local_vars = 0;
    }

    TRAVstmts(node);
    if (!(data->returned)) {
        printf("    return\n");
    }
    data->returned = false;
    return node;
}

/**
 * @fn ASifelse
 */
node_st *ASifelse(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    TRAVcond(node);

    int fst_tag_index = data->tag_index++;
    printf("    branch_f %d", fst_tag_index);

    if (IFELSE_ELSE_BLOCK(node)) {
        printf("_else\n");
        int snd_tag_index = data->tag_index++;

        TRAVthen(node);

        printf("    jump %d_end\n"
               "\n%d_else:\n", snd_tag_index, fst_tag_index);
        TRAVelse_block(node);

        printf("%d_end:\n", snd_tag_index);
    }
    else {
        printf("_end\n");
        TRAVthen(node);
        printf("\n%d_end:\n", fst_tag_index);
    }

    data->returned = false;
    return node;
}

/**
 * @fn ASwhile
 */
node_st *ASwhile(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    int while_index = data->tag_index++;
    int end_index = data->tag_index++;
    printf("%d_while:\n", while_index);
    TRAVcond(node);
    printf("    branch_f %d_end\n", end_index);

    TRAVblock(node);
    printf("    jump %d_while\n"
           "%d_end:\n", while_index, end_index);

    data->returned = false;
    return node;
}

/**
 * @fn ASdowhile
 */
node_st *ASdowhile(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    int dowhile_index = data->tag_index++;
    int end_index = data->tag_index++;
    printf("%d_dowhile:\n", dowhile_index);
    TRAVblock(node);
    TRAVcond(node);
    printf("    branch_t %d_dowhile\n", dowhile_index);

    data->returned = false;
    return node;
}

/**
 * @fn ASfor
 */
node_st *ASfor(node_st *node)
{
    return node;
}

/**
 * @fn ASglobdecl
 */
node_st *ASglobdecl(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    TRAVchildren(node);
    return node;
}

/**
 * @fn ASglobdef
 */
node_st *ASglobdef(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    TRAVchildren(node);
    return node;
}

/**
 * @fn ASparam
 */
node_st *ASparam(node_st *node)
{
    return node;
}

/**
 * @fn ASvardecl
 */
node_st *ASvardecl(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    data->local_vars++;
    TRAVnext(node);
    return node;
}

/**
 * @fn ASstmts
 */
node_st *ASstmts(node_st *node)
{
    TRAVstmt(node);
    TRAVnext(node);
    return node;
}

/**
 * @fn ASassign
 */
node_st *ASassign(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    TRAVexpr(node);
    TRAVlet(node);
    return node;
}

/**
 * @fn ASternary
 */
node_st *ASternary(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    TRAVchildren(node);
    return node;
}

/**
 * @fn ASbinop
 */
node_st *ASbinop(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    TRAVleft(node);
    TRAVright(node);

    printf("    ");
    print_type_char(get_type(BINOP_RIGHT(node)));

    switch (BINOP_OP(node)) {
      case BO_add:
        printf("add\n");
        break;
      case BO_sub:
        printf("sub\n");
        break;
      case BO_mul:
        printf("mul\n");
        break;
      case BO_div:
        printf("div\n");
        break;
      case BO_mod:
        printf("mod\n");
        break;
      case BO_lt:
        printf("lt\n");
        break;
      case BO_le:
        printf("le\n");
        break;
      case BO_gt:
        printf("gt\n");
        break;
      case BO_ge:
        printf("ge\n");
        break;
      case BO_eq:
        printf("eq\n");
        break;
      case BO_ne:
        printf("ne\n");
        break;
      default:
        DBUG_ASSERT(false, "unknown binop detected!");
    }

    return node;
}

/**
 * @fn ASmonop
 */
node_st *ASmonop(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    TRAVoperand(node);

    printf("    ");
    print_type_char(get_type(MONOP_OPERAND(node)));

    switch (MONOP_OP(node)) {
    case MO_not:
      printf("not\n");
      break;
    case MO_neg:
      printf("neg\n");
      break;
    default:
      DBUG_ASSERT(false, "unknown monop detected!");
    }

    return node;
}

/**
 * @fn ASvarlet
 */
node_st *ASvarlet(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    enum Type type = STE_TYPE(VARLET_STE(node));
    printf("    ");
    print_type_char(type);
    printf("store");

    int nest_lvl = STE_NEST_LVL(VARLET_STE(node));
    int index = STE_INDEX(VARLET_STE(node));
    if (nest_lvl == 0) {
        printf("g ");
    }
    else if (nest_lvl == data->cur_lvl) {
        printf(" ");
    }
    else {
        printf("n %d ", data->cur_lvl - nest_lvl);
    }
    printf("%d\n", index);

    return node;
}

/**
 * @fn ASvar
 */
node_st *ASvar(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    enum Type type = STE_TYPE(VAR_STE(node));
    // printf("Var %s", VAR_NAME(node));
    printf("    ");
    print_type_char(type);
    printf("load");

    int nest_lvl = STE_NEST_LVL(VAR_STE(node));
    int index = STE_INDEX(VAR_STE(node));
    if (nest_lvl == 0) {
        printf("g ");
    }
    else if (nest_lvl == data->cur_lvl) {
        if (index <= 3) {
            printf("_");
        }
        else {
            printf(" ");
        }
    }
    else {
        printf("n %d ", data->cur_lvl - nest_lvl);
    }
    printf("%d\n", index);

    return node;
}

/**
 * @fn ASnum
 */
node_st *ASnum(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    switch (NUM_VAL(node)) {
      case 0:
        printf("    iloadc_0\n");
        break;
      case 1:
        printf("    iloadc_1\n");
        break;
      default:
        printf("    iloadc %d\n", CTE_INDEX(NUM_CTE(node)));
    }
    return node;
}

/**
 * @fn ASfloat
 */
node_st *ASfloat(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    if (FLOAT_VAL(node) == 0.0) {
        printf("    floadc_0\n");
    }
    else if (FLOAT_VAL(node) == 1.0) {
        printf("    floadc_1\n");
    }
    else {
        printf("    floadc %d\n", CTE_INDEX(FLOAT_CTE(node)));
    }
    return node;
}

/**
 * @fn ASbool
 */
node_st *ASbool(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    if (BOOL_VAL(node)) {
        printf("    bloadc_t\n");
    }
    else {
        printf("    bloadc_f\n");
    }
    return node;
}

/**
 * @fn ASsymtable
 */
node_st *ASsymtable(node_st *node)
{
    TRAVnext(node);
    return node;
}

/**
 * @fn ASste
 */
node_st *ASste(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    if (STE_FUNCTION(node)) {
        if (STE_EXTERN_BOOL(node)) {
            printf(".importfun \"%s\" ", STE_NAME(node));
            print_types(node);
            printf("\n");
        }
        else if (STE_EXPORT(node)) {
            printf(".exportfun \"%s\" ", STE_NAME(node));
            print_types(node);
            printf(" %s\n", STE_NAME(node));
        }
    }
    else if (STE_EXTERN_BOOL(node)) {
        printf(".importvar \"%s\" ", STE_NAME(node));
        print_type(STE_TYPE(node));
        printf("\n");
    }
    else {
        if (STE_EXPORT(node)) {
            printf(".exportvar \"%s\" %d\n", STE_NAME(node), STE_INDEX(node));
        }
        printf(".global ");
        print_type(STE_TYPE(node));
        printf("\n");
    }
    TRAVnext(node);
    return node;
}

/**
 * @fn AScte
 */
node_st *AScte(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    printf(".const ");
    print_type(CTE_TYPE(node));
    if (CTE_TYPE(node) == CT_int) {
        printf(" %d\n", CTE_INT_VAL(node));
    }
    else {
        printf(" %f\n", CTE_FLOAT_VAL(node));
    }

    TRAVnext(node);
    return node;
}

