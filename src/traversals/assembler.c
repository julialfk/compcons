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


void print_type(enum Type type) {
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

void ASinit()
{
    struct data_as *data = DATA_AS_GET();
    data->last_type = CT_NULL;
}
void ASfini() { return; }

/**
 * @fn ASprogram
 */
node_st *ASprogram(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    TRAVchildren(node);
    return node;
}

/**
 * @fn ASdecls
 */
node_st *ASdecls(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    TRAVchildren(node);
    return node;
}

/**
 * @fn ASexprs
 */
node_st *ASexprs(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    TRAVchildren(node);
    return node;
}

/**
 * @fn ASarrexpr
 */
node_st *ASarrexpr(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    TRAVchildren(node);
    return node;
}

/**
 * @fn ASids
 */
node_st *ASids(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    TRAVchildren(node);
    return node;
}

/**
 * @fn ASexprstmt
 */
node_st *ASexprstmt(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    TRAVchildren(node);
    return node;
}

/**
 * @fn ASreturn
 */
node_st *ASreturn(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    TRAVchildren(node);
    return node;
}

/**
 * @fn ASfuncall
 */
node_st *ASfuncall(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    TRAVchildren(node);
    return node;
}

/**
 * @fn AScast
 */
node_st *AScast(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    TRAVchildren(node);
    return node;
}

/**
 * @fn ASfundefs
 */
node_st *ASfundefs(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    TRAVchildren(node);
    return node;
}

/**
 * @fn ASfundef
 */
node_st *ASfundef(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    TRAVchildren(node);
    return node;
}

/**
 * @fn ASfunbody
 */
node_st *ASfunbody(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    TRAVchildren(node);
    return node;
}

/**
 * @fn ASifelse
 */
node_st *ASifelse(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    TRAVchildren(node);
    return node;
}

/**
 * @fn ASwhile
 */
node_st *ASwhile(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    TRAVchildren(node);
    return node;
}

/**
 * @fn ASdowhile
 */
node_st *ASdowhile(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    TRAVchildren(node);
    return node;
}

/**
 * @fn ASfor
 */
node_st *ASfor(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    TRAVchildren(node);
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
    struct data_as *data = DATA_AS_GET();
    TRAVchildren(node);
    return node;
}

/**
 * @fn ASvardecl
 */
node_st *ASvardecl(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    TRAVchildren(node);
    return node;
}

/**
 * @fn ASstmts
 */
node_st *ASstmts(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    TRAVchildren(node);
    return node;
}

/**
 * @fn ASassign
 */
node_st *ASassign(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    TRAVchildren(node);
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

    switch (BINOP_OP(node)) {
    case BO_add:
      print_type(data->last_type);
      printf("add\n");
      break;
    case BO_sub:
      print_type(data->last_type);
      printf("sub\n");
      break;
    case BO_mul:
      print_type(data->last_type);
      printf("mul\n");
      break;
    case BO_div:
      print_type(data->last_type);
      printf("div\n");
      break;
    case BO_mod:
      print_type(data->last_type);
      printf("mod\n");
      break;
    case BO_lt:
      print_type(data->last_type);
      printf("lt\n");
      break;
    case BO_le:
      print_type(data->last_type);
      printf("le\n");
      break;
    case BO_gt:
      print_type(data->last_type);
      printf("gt\n");
      break;
    case BO_ge:
      print_type(data->last_type);
      printf("ge\n");
      break;
    case BO_eq:
      print_type(data->last_type);
      printf("eq\n");
      break;
    case BO_ne:
      print_type(data->last_type);
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
    print_type(data->last_type);

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
    return node;
}

/**
 * @fn ASvar
 */
node_st *ASvar(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
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

    data->last_type = CT_int;
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

    data->last_type = CT_float;
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
    data->last_type = CT_bool;
    return node;
}

/**
 * @fn ASsymtable
 */
node_st *ASsymtable(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    return node;
}

/**
 * @fn ASste
 */
node_st *ASste(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    return node;
}

/**
 * @fn AScte
 */
node_st *AScte(node_st *node)
{
    struct data_as *data = DATA_AS_GET();
    return node;
}

