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
void AddLocToNode(node_st *node, void *begin_loc, void *end_loc);


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

%define parse.error detailed

%token BRACKET_L BRACKET_R BRACE_L BRACE_R COMMA SEMICOLON
%token MINUS PLUS STAR SLASH PERCENT LE LT GE GT EQ NE OR AND EXCLAMATION
%token TRUEVAL FALSEVAL LET
%token INTTYPE FLOATTYPE BOOLTYPE VOIDTYPE
%token IF ELSE DO WHILE FOR RETURN EXPORT EXTERN

%token <cint> NUM
%token <cflt> FLOAT
%token <id> ID

%type <node> intval floatval boolval constant funcall expr exprs block param
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
           parseresult = $1;
         }
       ;

decls: decl decls
       {
         $$ = ASTdecls($1, $2);
         $$ = ASTdecls($1, $2);
       }
     | decl
       {
         $$ = ASTdecls($1, NULL);
         $$ = ASTdecls($1, NULL);
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
         }
       | fundef
         {
           $$ = ASTfundefs($1, NULL);
         }
       ;


fundef: EXPORT vartype[funtype] ID[name] BRACKET_L param[parameters] BRACKET_R BRACE_L funbody[body] BRACE_R
        {
          $$ = ASTfundef($body, $parameters, $funtype, $name, true);
        }
        /* wel export geen parameters, wel body */
      | EXPORT vartype[funtype] ID[name] BRACKET_L BRACKET_R BRACE_L funbody[body] BRACE_R
        {
          $$ = ASTfundef($body, NULL, $funtype, $name, true);
        }
        /* geen export, wel parameters, wel body */
      | vartype[funtype] ID[name] BRACKET_L param[parameters] BRACKET_R BRACE_L funbody[body] BRACE_R
        {
          $$ = ASTfundef($body, $parameters, $funtype, $name, false);
        }
      | EXTERN vartype[funtype] ID[name] BRACKET_L BRACKET_R SEMICOLON
        {
          $$ = ASTfundef(NULL, NULL, $funtype, $name, false);
        }
      | EXTERN vartype[funtype] ID[name] BRACKET_L param[parameters] BRACKET_R SEMICOLON
        {
          $$ = ASTfundef(NULL, false, $funtype, $name, false);
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

funbody: vardecl stmts
         {
           $$ = ASTfunbody($1, NULL, $2);
         }
       ;

stmts: stmt stmts
       {
         $$ = ASTstmts($1, $2);
       }
     | stmt
       {
         $$ = ASTstmts($1, NULL);
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
          }
        ;

vardecl: vartype[type] ID[name] LET expr[init] SEMICOLON vardecl[next]
         {
           $$ = ASTvardecl(NULL, $init, $next, $name, $type);
           
         }
         /* declaration + initialisation, no next */
       | vartype[type] ID[name] LET expr[init] SEMICOLON
         {
           $$ = ASTvardecl(NULL, $init, NULL, $name, $type);
           
         }
         /* declaration, no initialisation, next */
       | vartype[type] ID[name] SEMICOLON vardecl[next]
         {
           $$ = ASTvardecl(NULL, NULL, $next, $name, $type);
         }
         /* declaration, no initialisation, no next */
       | vartype[type] ID[name] SEMICOLON
         {
           $$ = ASTvardecl(NULL, NULL, NULL, $name, $type);
         }
       ;

assign: varlet LET expr SEMICOLON
        {
          $$ = ASTassign($1, $3);
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
       $$ = ASTfor($start, $stop, $step, $forblock, $var);
       AddLocToNode($$, &@1, &@forblock);
     }
   | FOR BRACKET_L INTTYPE ID[var] LET expr[start] COMMA expr[stop] BRACKET_R block[forblock]
     {
       $$ = ASTfor($start, $stop, NULL, $forblock, $var);
       AddLocToNode($$, &@1, &@forblock);
     }
   ;


varlet: ID
        {
          $$ = ASTvarlet(NULL, $1, NULL);
          AddLocToNode($$, &@1, &@1);
        }
      ;

/* Hoe werkt het met de haakjes? Meegeven of niet?
 * Nu worden ze namelijk niet geprint, maar ze zijn wel belangrijk
 * In de AST komen ze natuurlijk terug in de vorm van precedence (toch..?)
 * maar nu verdwijnen ze eigenlijk wel.? */
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
      }
    | funcall
      {
        $$ = $1;
      }
    | expr[left] binop[type] expr[right]
      {
        $$ = ASTbinop( $left, $right, $type);
        AddLocToNode($$, &@left, &@right);
      }
    | monop[type] expr[operand]
      {
        $$ = ASTmonop( $operand, $type);
        AddLocToNode($$, &@type, &@operand);
      }
    | BRACKET_L vartype[type] BRACKET_R expr
      {
        $$ = ASTcast( $4, $type);
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
       }
     | vartype[type] ID[name]
       {
         $$ = ASTparam(NULL, NULL, $name, $type);
       }
     ;

block: BRACE_L stmts BRACE_R
       {
         $$ = $2;
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
            $$ = ASTfloat($1);
          }
        ;

intval: NUM
        {
          $$ = ASTnum($1);
        }
      ;

boolval: TRUEVAL
         {
           $$ = ASTbool(true);
         }
       | FALSEVAL
         {
           $$ = ASTbool(false);
         }
       ;

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

void AddLocToNode(node_st *node, void *begin_loc, void *end_loc)
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
