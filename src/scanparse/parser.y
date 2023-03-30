%{


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "palm/memory.h"
#include "palm/ctinfo.h"
#include "palm/dbug.h"
#include "palm/str.h"
#include "ccngen/ast.h"
#include "ccngen/enum.h"
#include "global/globals.h"

#define YYDEBUG 1

static node_st *parseresult = NULL;
extern int yylex();
static int yyerror( char *errname);
extern FILE *yyin;
static void AddLocToNode(node_st *node, void *begin_loc, void *end_loc);


%}

%union {
 char               *id;
 int                 cint;
 float               cflt;
 enum binop_type     cbinop;
 enum monop_type     cmonop;
 enum Type           ctype;
 node_st             *node;
}

%locations

%define parse.error verbose

%token TRUEVAL FALSEVAL LET
%token INTTYPE FLOATTYPE BOOLTYPE VOIDTYPE
%token IF ELSE DO WHILE FOR RETURN EXPORT EXTERN
%left OR
%left AND
%left EQ NE
%left LE LT GE GT
%left MINUS PLUS
%left STAR SLASH PERCENT
%left EXCLAMATION
%left BRACKET_L BRACKET_R BRACE_L BRACE_R COMMA SEMICOLON

%token <cint> NUM
%token <cflt> FLOAT
%token <id> ID

%type <node> intval floatval boolval constant funcall expr exprs block param binmon
%type <node> ifelse while dowhile for return
%type <node> stmts stmt exprstmt assign varlet program vardecl
%type <node> funbody
%type <node> decls decl fundef fundefs globdecl globdef
%type <cbinop> binop
%type <cmonop> monop
/* %type <ctype> returntype */
%type <ctype> vartype

%start program

%%

program: decls
         {
           parseresult = ASTprogram($1, NULL, NULL);
         }
       ;

decls: decl decls
       {
         $$ = ASTdecls($1, $2);
         AddLocToNode($$, &@1, &@1);
       }
     | decl
       {
         $$ = ASTdecls($1, NULL);
         AddLocToNode($$, &@1, &@1);
       }
     ;

decl: fundef
      {
        $$ = $1;
      }
    | globdecl
      {
        $$ = $1;
      }
    | globdef
      {
        $$ = $1;
      }
    ;

fundefs: fundef fundefs
         {
           $$ = ASTfundefs($1, $2);
           AddLocToNode($$, &@1, &@1);
         }
       | fundef
         {
           $$ = ASTfundefs($1, NULL);
           AddLocToNode($$, &@1, &@1);
         }
       ;


fundef: EXPORT vartype[funtype] ID[name] BRACKET_L param[parameters] BRACKET_R funbody[body]
        {
          $$ = ASTfundef($body, $parameters, NULL, $funtype, $name, true);
          AddLocToNode($$, &@funtype, &@body);
        }
        /* wel export geen parameters, wel body */
      | EXPORT vartype[funtype] ID[name] BRACKET_L BRACKET_R funbody[body]
        {
          $$ = ASTfundef($body, NULL, NULL, $funtype, $name, true);
          AddLocToNode($$, &@funtype, &@body);
        }
        /* geen export, wel parameters, wel body */
      | vartype[funtype] ID[name] BRACKET_L param[parameters] BRACKET_R funbody[body]
        {
          $$ = ASTfundef($body, $parameters, NULL, $funtype, $name, false);
          AddLocToNode($$, &@funtype, &@body);
        }
        /* geen export, geen parameters, wel body */
      | vartype[funtype] ID[name] BRACKET_L BRACKET_R funbody[body]
        {
          $$ = ASTfundef($body, NULL, NULL, $funtype, $name, false);
          AddLocToNode($$, &@funtype, &@body);
        }

      | EXTERN vartype[funtype] ID[name] BRACKET_L BRACKET_R SEMICOLON
        {
          $$ = ASTfundef(NULL, NULL, NULL, $funtype, $name, false);
          AddLocToNode($$, &@funtype, &@name);
        }
      | EXTERN vartype[funtype] ID[name] BRACKET_L param[parameters] BRACKET_R SEMICOLON
        {
          $$ = ASTfundef(NULL, false, NULL, $funtype, $name, false);
          AddLocToNode($$, &@funtype, &@parameters);
        }
      ;

globdecl: EXTERN vartype[type] ID[name] SEMICOLON
          {
            $$ = ASTglobdecl(NULL, $type, $name);
            AddLocToNode($$, &@1, &@name);
          }
        ;

globdef: EXPORT vartype[type] ID[name] LET expr[init] SEMICOLON
         {
           $$ = ASTglobdef(NULL, $init, $type, $name, true);
           AddLocToNode($$, &@1, &@init);
         }
       | EXPORT vartype[type] ID[name] SEMICOLON
         {
           $$ = ASTglobdef(NULL, NULL, $type, $name, true);
           AddLocToNode($$, &@1, &@name);
         }
       | vartype[type] ID[name] LET expr[init] SEMICOLON
         {
           $$ = ASTglobdef(NULL, $init, $type, $name, false);
           AddLocToNode($$, &@1, &@init);
         }
       | vartype[type] ID[name] SEMICOLON
         {
           $$ = ASTglobdef(NULL, NULL, $type, $name, false);
           AddLocToNode($$, &@1, &@name);
         }
       ;

funbody: BRACE_L vardecl stmts BRACE_R
         {
           $$ = ASTfunbody($2, NULL, $3);
           AddLocToNode($$, &@2, &@3);
         }
       | BRACE_L vardecl BRACE_R
         {
           $$ = ASTfunbody($2, NULL, NULL);
           AddLocToNode($$, &@2, &@2);
         }
       | BRACE_L stmts BRACE_R
         {
           $$ = ASTfunbody(NULL, NULL, $2);
           AddLocToNode($$, &@2, &@2);
         }
 
       | BRACE_L BRACE_R
         {
           $$ = ASTfunbody(NULL, NULL, NULL);
         }
      ;

stmts: stmt stmts
       {
         $$ = ASTstmts($1, $2);
         AddLocToNode($$, &@1, &@1);
       }
     | stmt
       {
         $$ = ASTstmts($1, NULL);
         AddLocToNode($$, &@1, &@1);
       }
     ;

stmt: assign
      {
        $$ = $1;
      }
    | return SEMICOLON
      {
        $$ = $1;
      }
    | exprstmt SEMICOLON
      {
        $$ = $1;
      }
    | ifelse
      {
        $$ = $1;
      }
    | while
      {
        $$ = $1;
      }
    | dowhile
      {
        $$ = $1;
      }
    | for
      {
         $$ = $1;
      }
    ;

exprstmt: expr
          {
            $$ = ASTexprstmt($1);
            AddLocToNode($$, &@1, &@1);
          }
        ;

vardecl: vartype[type] ID[name] LET expr[init] SEMICOLON vardecl[next]
         {
           $$ = ASTvardecl(NULL, $init, $next, $name, $type);
           AddLocToNode($$, &@type, &@init);
         }
         /* declaration + initialisation, no next */
       | vartype[type] ID[name] LET expr[init] SEMICOLON
         {
           $$ = ASTvardecl(NULL, $init, NULL, $name, $type);
           AddLocToNode($$, &@type, &@init);
         }
         /* declaration, no initialisation, next */
       | vartype[type] ID[name] SEMICOLON vardecl[next]
         {
           $$ = ASTvardecl(NULL, NULL, $next, $name, $type);
           AddLocToNode($$, &@type, &@name);
         }
         /* declaration, no initialisation, no next */
       | vartype[type] ID[name] SEMICOLON
         {
           $$ = ASTvardecl(NULL, NULL, NULL, $name, $type);
           AddLocToNode($$, &@type, &@name);
         }
       ;

assign: varlet LET expr SEMICOLON
        {
          $$ = ASTassign($1, $3);
          AddLocToNode($$, &@1, &@3);
        }
      ;

dowhile: DO block[doblock] WHILE BRACKET_L expr[cond] BRACKET_R SEMICOLON
         {
           $$ = ASTdowhile($cond, $doblock);
           AddLocToNode($$, &@1, &@doblock);
         }
       ;

while: WHILE BRACKET_L expr[cond] BRACKET_R block[whileblock]
       {
         $$ = ASTwhile($cond, $whileblock);
         AddLocToNode($$, &@1, &@whileblock);
       }
     ;

ifelse: IF BRACKET_L expr[cond] BRACKET_R block[then] ELSE block[elseblock]
        {
          $$ = ASTifelse($cond, $then, $elseblock);
          AddLocToNode($$, &@1, &@elseblock);
        }
      | IF BRACKET_L expr[cond] BRACKET_R block[then]
        {
          $$ = ASTifelse($cond, $then, NULL);
          AddLocToNode($$, &@1, &@then);
        }
      ;

for: FOR BRACKET_L INTTYPE ID[var] LET expr[start] COMMA expr[stop] COMMA expr[step] BRACKET_R block[forblock]
     {
       $$ = ASTfor($start, $stop, $step, $forblock, NULL, $var);
       AddLocToNode($$, &@1, &@forblock);
     }
   | FOR BRACKET_L INTTYPE ID[var] LET expr[start] COMMA expr[stop] BRACKET_R block[forblock]
     {
       $$ = ASTfor($start, $stop, NULL, $forblock, NULL, $var);
       AddLocToNode($$, &@1, &@forblock);
     }
   ;


varlet: ID
        {
          $$ = ASTvarlet(NULL, $1, NULL);
          AddLocToNode($$, &@1, &@1);
        }
      ;

expr: BRACKET_L expr BRACKET_R
      {
        $$ = $2;
      }
    | constant
      {
        $$ = $1;
      }
    | ID
      {
        $$ = ASTvar(NULL, $1, NULL);
        AddLocToNode($$, &@1, &@1);
      }
    | funcall
      {
        $$ = $1;
      }
    | binmon
      {
        $$ = $1;
      }
    | BRACKET_L vartype[type] BRACKET_R expr
      {
        $$ = ASTcast( $4, $type, CT_NULL);
        AddLocToNode($$, &@type, &@4);
      }
    ;

exprs: expr COMMA exprs[next]
       {
        $$ = ASTexprs($1, $next);
        AddLocToNode($$, &@1, &@next);
       }
     | expr
       {
        $$ = ASTexprs($1, NULL);
        AddLocToNode($$, &@1, &@1);
       }
     ;

return: RETURN expr
        {
          $$ = ASTreturn($2);
          AddLocToNode($$, &@1, &@2);
        }
      | RETURN
        {
          $$ = ASTreturn(NULL);
          AddLocToNode($$, &@1, &@1);
        }
      ;

funcall: ID[name] BRACKET_L BRACKET_R
         {
           $$ = ASTfuncall(NULL, $name, NULL);
           AddLocToNode($$, &@name, &@name);
         }
       | ID[name] BRACKET_L exprs[args] BRACKET_R
         {
           $$ = ASTfuncall($args, $name, NULL);
           AddLocToNode($$, &@name, &@args);
         }
       ;

param: vartype[type] ID[name] COMMA param[next]
       {
         $$ = ASTparam(NULL, $next, $name, $type);
         AddLocToNode($$, &@type, &@next);
       }
     | vartype[type] ID[name]
       {
         $$ = ASTparam(NULL, NULL, $name, $type);
         AddLocToNode($$, &@type, &@name);
       }
     ;

block: BRACE_L stmts BRACE_R
       {
         $$ = $2;
       }
     | BRACE_L BRACE_R
       {
         $$ = NULL;
       }
     | stmt
       {
         $$ = ASTstmts($1, NULL);
         AddLocToNode($$, &@1, &@1);
       }
     ;

constant: floatval
          {
            $$ = $1;
          }
        | intval
          {
            $$ = $1;
          }
        | boolval
          {
            $$ = $1;
          }
        ;

floatval: FLOAT
          {
            $$ = ASTfloat($1, NULL);
            AddLocToNode($$, &@1, &@1);
          }
        ;

intval: NUM
        {
          $$ = ASTnum($1, NULL);
          AddLocToNode($$, &@1, &@1);
        }
      ;

boolval: TRUEVAL
         {
           $$ = ASTbool(true);
           AddLocToNode($$, &@1, &@1);
         }
       | FALSEVAL
         {
           $$ = ASTbool(false);
           AddLocToNode($$, &@1, &@1);
         }
       ;

binmon: expr[left] PLUS expr[right]
        {
          $$ = ASTbinop( $left, $right, BO_add, CT_NULL);
          AddLocToNode($$, &@left, &@right);
        }
      | expr[left] MINUS expr[right]
        {
          $$ = ASTbinop( $left, $right, BO_sub, CT_NULL);
          AddLocToNode($$, &@left, &@right);
        }
      | expr[left] STAR expr[right]
        {
          $$ = ASTbinop( $left, $right, BO_mul, CT_NULL);
          AddLocToNode($$, &@left, &@right);
        }
      | expr[left] SLASH expr[right]
        {
          $$ = ASTbinop( $left, $right, BO_div, CT_NULL);
          AddLocToNode($$, &@left, &@right);
        }
      | expr[left] PERCENT expr[right]
        {
          $$ = ASTbinop( $left, $right, BO_mod, CT_NULL);
          AddLocToNode($$, &@left, &@right);
        }
      | expr[left] LE expr[right]
        {
          $$ = ASTbinop( $left, $right, BO_le, CT_bool);
          AddLocToNode($$, &@left, &@right);
        }
      | expr[left] LT expr[right]
        {
          $$ = ASTbinop( $left, $right, BO_lt, CT_bool);
          AddLocToNode($$, &@left, &@right);
        }
      | expr[left] GE expr[right]
        {
          $$ = ASTbinop( $left, $right, BO_ge, CT_bool);
          AddLocToNode($$, &@left, &@right);
        }
      | expr[left] GT expr[right]
        {
          $$ = ASTbinop( $left, $right, BO_gt, CT_bool);
          AddLocToNode($$, &@left, &@right);
        }
      | expr[left] EQ expr[right]
        {
          $$ = ASTbinop( $left, $right, BO_eq, CT_bool);
          AddLocToNode($$, &@left, &@right);
        }
      | expr[left] NE expr[right]
        {
          $$ = ASTbinop( $left, $right, BO_ne, CT_bool);
          AddLocToNode($$, &@left, &@right);
        }
      | expr[left] OR expr[right]
        {
          $$ = ASTbinop( $left, $right, BO_or, CT_bool);
          AddLocToNode($$, &@left, &@right);
        }
      | expr[left] AND expr[right]
        {
          $$ = ASTbinop( $left, $right, BO_and, CT_bool);
          AddLocToNode($$, &@left, &@right);
        }
      | MINUS expr[operand]
        {
          $$ = ASTmonop( $operand, MO_neg, CT_NULL);
          AddLocToNode($$, &@1, &@operand);
        }
      | EXCLAMATION expr[operand]
        {
          $$ = ASTmonop( $operand, MO_not, CT_bool);
          AddLocToNode($$, &@1, &@operand);
        }


binop: PLUS      { $$ = BO_add; }
     | MINUS     { $$ = BO_sub; }
     | STAR      { $$ = BO_mul; }
     | SLASH     { $$ = BO_div; }
     | PERCENT   { $$ = BO_mod; }
     | LE        { $$ = BO_le; }
     | LT        { $$ = BO_lt; }
     | GE        { $$ = BO_ge; }
     | GT        { $$ = BO_gt; }
     | EQ        { $$ = BO_eq; }
     | NE        { $$ = BO_ne; }
     | OR        { $$ = BO_or; }
     | AND       { $$ = BO_and; }
     ;

monop: MINUS        { $$ = MO_neg; }
     | EXCLAMATION  { $$ = MO_not; }
     ;

/* voidtype in globals later met type checker filteren */
vartype: BOOLTYPE      { $$ = CT_bool; }
       | INTTYPE       { $$ = CT_int; }
       | FLOATTYPE     { $$ = CT_float; }
       | VOIDTYPE        { $$ = CT_void; }
       ;
%%

static void AddLocToNode(node_st *node, void *begin_loc, void *end_loc)
{
    // Needed because YYLTYPE unpacks later than top-level decl.
    YYLTYPE *loc_b = (YYLTYPE*)begin_loc;
    YYLTYPE *loc_e = (YYLTYPE*)end_loc;
    NODE_BLINE(node) = loc_b->first_line;
    NODE_BCOL(node) = loc_b->first_column;
    NODE_ELINE(node) = loc_e->last_line;
    NODE_ECOL(node) = loc_e->last_column;
}

static int yyerror( char *error)
{
  CTI(CTI_ERROR, true, "line %d, col %d\nError parsing source code: %s\n",
            global.line, global.col, error);
  CTIabortOnError();
  return( 0);
}

node_st *SPdoScanParse(node_st *root)
{
    DBUG_ASSERT(root == NULL, "Started parsing with existing syntax tree.");
    yyin = fopen(global.input_file, "r");
    if (yyin == NULL) {
        CTI(CTI_ERROR, true, "Cannot open file '%s'.", global.input_file);
        CTIabortOnError();
    }
    yydebug = 1;  // Turn on yacc debugging
    yyparse();
    return parseresult;
}
