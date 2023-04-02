%{

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ccngen/ast.h"
#include "ccngen/enum.h"
#include "parser.h"
#include "palm/str.h"
#include "global/globals.h"
#include "palm/ctinfo.h"


#define FILTER(token) \
  global.col += yyleng;  \
  return( token);

#define LINEBUF_SIZE 256
#define YY_NO_UNPUT
#define YY_NO_INPUT

static inline void token_action();

int yycolumn = 1;
#define YY_USER_ACTION token_action();


#define COMMENT(token) \
    int count = 0; \
    char *line = strtok(token, "\n"); \
    while (line) { \
        count++; \
        line = strtok(NULL, "\n"); \
    }\
  global.line += count -1;\

#define HANDLE_ERROR(col, len, text) \
    CTI(CTI_ERROR, false, "Line %d, Column %d: Unexpected token: %s\n", \
            len, col, text); \
    exit(1); \

%}

%p 6000 /* set positions to 6000 */
%e 2000 /* set nodes to 1100 */
%option noyywrap
%option nounput
%option yylineno


%%


"//".*                                  { }
[/][*][^*]*[*]+([^*/][^*]*[*]+)*[/]       { COMMENT(yytext) }

"export"                   { FILTER( EXPORT);  }
"extern"                   { FILTER( EXTERN);  }

"("                        { FILTER( BRACKET_L); }
")"                        { FILTER( BRACKET_R); }
"{"                        { FILTER( BRACE_L); }
"}"                        { FILTER( BRACE_R); }
","                        { FILTER( COMMA); }
";"                        { FILTER( SEMICOLON); }

"-"                        { FILTER( MINUS); }
"+"                        { FILTER( PLUS);  }
"*"                        { FILTER( STAR);  } 
"/"                        { FILTER( SLASH);  } 
"%"                        { FILTER( PERCENT);  } 

"<="                       { FILTER( LE);    }
"<"                        { FILTER( LT);    } 
">="                       { FILTER( GE);    }
">"                        { FILTER( GT);    }
"=="                       { FILTER( EQ);    }
"!="                       { FILTER( NE);    }
"&&"                       { FILTER( AND);    }
"||"                       { FILTER( OR);    }

"!"                        { FILTER( EXCLAMATION);    }

"="                        { FILTER( LET);    }

"bool"                     { FILTER( BOOLTYPE);  }
"int"                      { FILTER( INTTYPE);  }
"float"                    { FILTER( FLOATTYPE);  }
"void"                     { FILTER( VOIDTYPE);  }

"if"                       { FILTER( IF);   }
"else"                     { FILTER( ELSE);   }
"do"                       { FILTER( DO);   }
"while"                    { FILTER( WHILE);   }
"for"                      { FILTER( FOR);   }
"return"                   { FILTER( RETURN);   }

"true"                     { FILTER( TRUEVAL); }
"false"                    { FILTER( FALSEVAL); }

[A-Za-z]+[A-Za-z0-9_]*      { yylval.id = STRcpy(yytext);
                             FILTER( ID);
                           }

[0-9]+                     { yylval.cint=atoi(yytext);
                             FILTER( NUM);
                           }

[0-9]*"."[0-9]+            { yylval.cflt=atof(yytext);
                             FILTER( FLOAT);
                           }

\n.*                       { 
                             yycolumn = 1;
                             global.line += 1;
                             global.col = 0;
                             yyless(1);
                           }

[ \t]                      { global.col += yyleng;
                           } 

.                          { HANDLE_ERROR(yycolumn, yyleng, yytext);
                           }
%%

static inline void token_action() {
    yylloc.first_line = yylloc.last_line = yylineno;
    yylloc.first_column = yycolumn;
    yylloc.last_column = yycolumn + yyleng - 1;
    yycolumn += yyleng;
}

