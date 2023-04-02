/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/scanparse/parser.y"



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



#line 96 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TRUEVAL = 258,                 /* TRUEVAL  */
    FALSEVAL = 259,                /* FALSEVAL  */
    LET = 260,                     /* LET  */
    INTTYPE = 261,                 /* INTTYPE  */
    FLOATTYPE = 262,               /* FLOATTYPE  */
    BOOLTYPE = 263,                /* BOOLTYPE  */
    VOIDTYPE = 264,                /* VOIDTYPE  */
    IF = 265,                      /* IF  */
    ELSE = 266,                    /* ELSE  */
    DO = 267,                      /* DO  */
    WHILE = 268,                   /* WHILE  */
    FOR = 269,                     /* FOR  */
    RETURN = 270,                  /* RETURN  */
    EXPORT = 271,                  /* EXPORT  */
    EXTERN = 272,                  /* EXTERN  */
    OR = 273,                      /* OR  */
    AND = 274,                     /* AND  */
    EQ = 275,                      /* EQ  */
    NE = 276,                      /* NE  */
    LE = 277,                      /* LE  */
    LT = 278,                      /* LT  */
    GE = 279,                      /* GE  */
    GT = 280,                      /* GT  */
    MINUS = 281,                   /* MINUS  */
    PLUS = 282,                    /* PLUS  */
    STAR = 283,                    /* STAR  */
    SLASH = 284,                   /* SLASH  */
    PERCENT = 285,                 /* PERCENT  */
    EXCLAMATION = 286,             /* EXCLAMATION  */
    UMINUS = 287,                  /* UMINUS  */
    BRACKET_L = 288,               /* BRACKET_L  */
    BRACKET_R = 289,               /* BRACKET_R  */
    BRACE_L = 290,                 /* BRACE_L  */
    BRACE_R = 291,                 /* BRACE_R  */
    COMMA = 292,                   /* COMMA  */
    SEMICOLON = 293,               /* SEMICOLON  */
    NUM = 294,                     /* NUM  */
    FLOAT = 295,                   /* FLOAT  */
    ID = 296                       /* ID  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 26 "src/scanparse/parser.y"

 char               *id;
 int                 cint;
 float               cflt;
 enum Type           ctype;
 node_st             *node;

#line 192 "parser.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;

int yyparse (void);



/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TRUEVAL = 3,                    /* TRUEVAL  */
  YYSYMBOL_FALSEVAL = 4,                   /* FALSEVAL  */
  YYSYMBOL_LET = 5,                        /* LET  */
  YYSYMBOL_INTTYPE = 6,                    /* INTTYPE  */
  YYSYMBOL_FLOATTYPE = 7,                  /* FLOATTYPE  */
  YYSYMBOL_BOOLTYPE = 8,                   /* BOOLTYPE  */
  YYSYMBOL_VOIDTYPE = 9,                   /* VOIDTYPE  */
  YYSYMBOL_IF = 10,                        /* IF  */
  YYSYMBOL_ELSE = 11,                      /* ELSE  */
  YYSYMBOL_DO = 12,                        /* DO  */
  YYSYMBOL_WHILE = 13,                     /* WHILE  */
  YYSYMBOL_FOR = 14,                       /* FOR  */
  YYSYMBOL_RETURN = 15,                    /* RETURN  */
  YYSYMBOL_EXPORT = 16,                    /* EXPORT  */
  YYSYMBOL_EXTERN = 17,                    /* EXTERN  */
  YYSYMBOL_OR = 18,                        /* OR  */
  YYSYMBOL_AND = 19,                       /* AND  */
  YYSYMBOL_EQ = 20,                        /* EQ  */
  YYSYMBOL_NE = 21,                        /* NE  */
  YYSYMBOL_LE = 22,                        /* LE  */
  YYSYMBOL_LT = 23,                        /* LT  */
  YYSYMBOL_GE = 24,                        /* GE  */
  YYSYMBOL_GT = 25,                        /* GT  */
  YYSYMBOL_MINUS = 26,                     /* MINUS  */
  YYSYMBOL_PLUS = 27,                      /* PLUS  */
  YYSYMBOL_STAR = 28,                      /* STAR  */
  YYSYMBOL_SLASH = 29,                     /* SLASH  */
  YYSYMBOL_PERCENT = 30,                   /* PERCENT  */
  YYSYMBOL_EXCLAMATION = 31,               /* EXCLAMATION  */
  YYSYMBOL_UMINUS = 32,                    /* UMINUS  */
  YYSYMBOL_BRACKET_L = 33,                 /* BRACKET_L  */
  YYSYMBOL_BRACKET_R = 34,                 /* BRACKET_R  */
  YYSYMBOL_BRACE_L = 35,                   /* BRACE_L  */
  YYSYMBOL_BRACE_R = 36,                   /* BRACE_R  */
  YYSYMBOL_COMMA = 37,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 38,                 /* SEMICOLON  */
  YYSYMBOL_NUM = 39,                       /* NUM  */
  YYSYMBOL_FLOAT = 40,                     /* FLOAT  */
  YYSYMBOL_ID = 41,                        /* ID  */
  YYSYMBOL_YYACCEPT = 42,                  /* $accept  */
  YYSYMBOL_program = 43,                   /* program  */
  YYSYMBOL_decls = 44,                     /* decls  */
  YYSYMBOL_decl = 45,                      /* decl  */
  YYSYMBOL_fundef = 46,                    /* fundef  */
  YYSYMBOL_globdecl = 47,                  /* globdecl  */
  YYSYMBOL_globdef = 48,                   /* globdef  */
  YYSYMBOL_funbody = 49,                   /* funbody  */
  YYSYMBOL_stmts = 50,                     /* stmts  */
  YYSYMBOL_stmt = 51,                      /* stmt  */
  YYSYMBOL_exprstmt = 52,                  /* exprstmt  */
  YYSYMBOL_vardecl = 53,                   /* vardecl  */
  YYSYMBOL_assign = 54,                    /* assign  */
  YYSYMBOL_dowhile = 55,                   /* dowhile  */
  YYSYMBOL_while = 56,                     /* while  */
  YYSYMBOL_ifelse = 57,                    /* ifelse  */
  YYSYMBOL_for = 58,                       /* for  */
  YYSYMBOL_varlet = 59,                    /* varlet  */
  YYSYMBOL_expr = 60,                      /* expr  */
  YYSYMBOL_exprs = 61,                     /* exprs  */
  YYSYMBOL_return = 62,                    /* return  */
  YYSYMBOL_funcall = 63,                   /* funcall  */
  YYSYMBOL_param = 64,                     /* param  */
  YYSYMBOL_block = 65,                     /* block  */
  YYSYMBOL_constant = 66,                  /* constant  */
  YYSYMBOL_floatval = 67,                  /* floatval  */
  YYSYMBOL_intval = 68,                    /* intval  */
  YYSYMBOL_boolval = 69,                   /* boolval  */
  YYSYMBOL_binmon = 70,                    /* binmon  */
  YYSYMBOL_vartype = 71                    /* vartype  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   879

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  97
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  199

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   296


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    64,    64,    70,    75,    82,    86,    90,    96,   102,
     108,   114,   119,   124,   131,   138,   143,   148,   153,   160,
     165,   170,   175,   181,   186,   193,   197,   201,   205,   209,
     213,   217,   223,   230,   236,   242,   248,   255,   262,   269,
     276,   281,   286,   291,   296,   301,   306,   311,   316,   321,
     326,   331,   338,   343,   351,   358,   362,   366,   371,   375,
     379,   386,   391,   398,   403,   410,   415,   422,   427,   434,
     438,   442,   449,   453,   457,   463,   470,   477,   482,   489,
     494,   499,   504,   509,   514,   519,   524,   529,   534,   539,
     544,   549,   554,   559,   566,   567,   568,   569
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TRUEVAL", "FALSEVAL",
  "LET", "INTTYPE", "FLOATTYPE", "BOOLTYPE", "VOIDTYPE", "IF", "ELSE",
  "DO", "WHILE", "FOR", "RETURN", "EXPORT", "EXTERN", "OR", "AND", "EQ",
  "NE", "LE", "LT", "GE", "GT", "MINUS", "PLUS", "STAR", "SLASH",
  "PERCENT", "EXCLAMATION", "UMINUS", "BRACKET_L", "BRACKET_R", "BRACE_L",
  "BRACE_R", "COMMA", "SEMICOLON", "NUM", "FLOAT", "ID", "$accept",
  "program", "decls", "decl", "fundef", "globdecl", "globdef", "funbody",
  "stmts", "stmt", "exprstmt", "vardecl", "assign", "dowhile", "while",
  "ifelse", "for", "varlet", "expr", "exprs", "return", "funcall", "param",
  "block", "constant", "floatval", "intval", "boolval", "binmon",
  "vartype", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-146)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-55)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     216,  -146,  -146,  -146,  -146,    86,    86,     7,  -146,   216,
    -146,  -146,  -146,   -32,   -27,   -26,  -146,  -146,    23,    26,
     -25,   573,    69,  -146,   573,   118,  -146,   182,  -146,  -146,
    -146,   573,   573,   557,  -146,  -146,   -15,   597,  -146,  -146,
    -146,  -146,  -146,  -146,   -16,   -11,   -12,   618,   -16,    -8,
      -6,    -1,  -146,  -146,   741,    18,    81,   573,   573,   573,
     573,   573,   573,   573,   573,   573,   573,   573,   573,   573,
    -146,   132,  -146,   -16,    25,  -146,  -146,   -16,  -146,    27,
    -146,   573,  -146,   701,    29,   838,   849,   233,   233,   166,
     166,   166,   166,    39,    39,  -146,  -146,  -146,    40,   172,
      46,    47,   573,  -146,    22,    36,   541,    45,   205,  -146,
    -146,  -146,  -146,  -146,    83,   826,    48,    49,  -146,    86,
    -146,  -146,  -146,   573,  -146,   573,   239,  -146,    76,   573,
      91,   826,  -146,  -146,  -146,  -146,    62,   573,  -146,    12,
    -146,  -146,   758,  -146,    64,    68,   775,    65,  -146,   639,
     573,    86,   273,  -146,   573,   172,   104,  -146,   660,  -146,
     306,    99,   792,  -146,   573,    86,   100,    77,   340,    79,
     721,  -146,   373,   107,   406,  -146,  -146,   573,   440,  -146,
     474,  -146,    92,   681,  -146,    94,   507,  -146,  -146,   172,
     573,  -146,  -146,    96,  -146,   809,  -146,   172,  -146
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    95,    96,    94,    97,     0,     0,     0,     2,     4,
       5,     6,     7,     0,     0,     0,     1,     3,     0,     0,
       0,     0,     0,    18,     0,     0,    16,     0,    14,    77,
      78,     0,     0,     0,    76,    75,    57,     0,    58,    56,
      72,    73,    74,    59,     0,     0,     0,     0,     0,     0,
       0,     0,    92,    93,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      17,     0,    11,     0,    68,    15,     9,     0,    12,     0,
      55,     0,    65,    62,     0,    90,    91,    88,    89,    84,
      85,    86,    87,    80,    79,    81,    82,    83,     0,     0,
       0,     0,    64,    22,    57,     0,    24,     0,     0,    25,
      30,    29,    28,    31,     0,    32,     0,     0,    10,     0,
       8,    13,    60,     0,    66,     0,     0,    71,     0,     0,
       0,    63,    21,    23,    27,    20,     0,     0,    26,     0,
      67,    61,     0,    70,     0,     0,     0,     0,    19,     0,
       0,    36,     0,    69,     0,     0,     0,    37,     0,    35,
       0,    50,     0,    39,     0,    34,    51,     0,     0,     0,
       0,    33,     0,    49,     0,    46,    38,     0,     0,    48,
       0,    47,     0,     0,    43,     0,     0,    44,    45,     0,
       0,    41,    42,     0,    53,     0,    40,     0,    52
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -146,  -146,   125,  -146,  -146,  -146,  -146,   -43,   -55,   -98,
    -146,  -145,  -146,  -146,  -146,  -146,  -146,  -146,   -21,    14,
    -146,  -146,   -23,  -131,  -146,  -146,  -146,  -146,  -146,    16
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     7,     8,     9,    10,    11,    12,    72,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,    84,
     116,    38,    45,   128,    39,    40,    41,    42,    43,    46
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      37,   127,    49,    47,    51,    76,   159,    16,    27,    18,
      52,    53,    54,    28,    19,    20,    13,   150,    56,    71,
     171,    14,    15,    73,   163,    13,    77,   -54,    21,    74,
     118,    24,    78,    79,   120,    83,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    55,
     151,   133,    81,   136,   161,    56,    22,   127,   194,    25,
     122,    23,   119,   124,    26,   121,   198,    67,    68,    69,
     175,   144,   132,   125,   179,     1,     2,     3,     4,   129,
     130,   131,   187,   134,    29,    30,   138,   117,   137,   145,
     139,   127,     1,     2,     3,     4,   140,   147,   148,   127,
     153,   154,    83,    44,   142,   167,   156,    31,   146,   164,
     168,   172,    32,   173,    33,    82,   149,   176,   180,   182,
      34,    35,    36,   185,     1,     2,     3,     4,   188,   158,
     191,   193,   196,   162,    17,    29,    30,   141,     1,     2,
       3,     4,    98,   170,    99,   100,   101,   102,     0,     0,
       0,     0,    48,     0,     0,     0,   183,     0,    31,     0,
       0,     0,     0,    32,     0,    33,     0,   117,   103,   195,
       0,    34,    35,   104,     0,    29,    30,     0,     0,     0,
       0,   117,    98,     0,    99,   100,   101,   102,     1,     2,
       3,     4,    65,    66,    67,    68,    69,     0,    31,     0,
       0,     0,     0,    32,     0,    33,     0,   126,    29,    30,
       0,    34,    35,   104,     0,    98,    50,    99,   100,   101,
     102,     0,     1,     2,     3,     4,     0,     0,     0,     0,
       0,    31,     5,     6,     0,     0,    32,     0,    33,     0,
       0,   135,    29,    30,    34,    35,   104,     0,     0,    98,
       0,    99,   100,   101,   102,    61,    62,    63,    64,    65,
      66,    67,    68,    69,     0,    31,     0,     0,     0,     0,
      32,     0,    33,     0,     0,   143,    29,    30,    34,    35,
     104,     0,     0,    98,     0,    99,   100,   101,   102,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    31,
       0,     0,     0,     0,    32,     0,    33,     0,   160,    29,
      30,     0,    34,    35,   104,     0,    98,     0,    99,   100,
     101,   102,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    31,     0,     0,     0,     0,    32,     0,    33,
       0,     0,   166,    29,    30,    34,    35,   104,     0,     0,
      98,     0,    99,   100,   101,   102,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    31,     0,     0,     0,
       0,    32,     0,    33,     0,   174,    29,    30,     0,    34,
      35,   104,     0,    98,     0,    99,   100,   101,   102,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    31,
       0,     0,     0,     0,    32,     0,    33,     0,   178,    29,
      30,     0,    34,    35,   104,     0,    98,     0,    99,   100,
     101,   102,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    31,     0,     0,     0,     0,    32,     0,    33,
       0,     0,   181,    29,    30,    34,    35,   104,     0,     0,
      98,     0,    99,   100,   101,   102,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    31,     0,     0,     0,
       0,    32,     0,    33,     0,     0,   184,    29,    30,    34,
      35,   104,     0,     0,    98,     0,    99,   100,   101,   102,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      31,     0,     0,     0,     0,    32,     0,    33,     0,   186,
      29,    30,     0,    34,    35,   104,     0,    98,     0,    99,
     100,   101,   102,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    31,     0,     0,     0,     0,    32,     0,
      33,     0,     0,   192,    29,    30,    34,    35,   104,     0,
       0,    98,     0,    99,   100,   101,   102,     0,     0,     0,
      29,    30,     0,     1,     2,     3,     4,    31,     0,     0,
       0,     0,    32,     0,    33,     0,    29,    30,     0,     0,
      34,    35,   104,    31,     0,     0,     0,     0,    32,     0,
      33,     0,     0,     0,     0,     0,    34,    35,    36,    31,
       0,     0,     0,     0,    32,     0,    33,     0,     0,     0,
       0,     0,    34,    35,    36,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,     0,     0,
       0,     0,     0,     0,     0,    70,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,     0,
       0,     0,     0,     0,     0,     0,    75,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
       0,     0,     0,     0,     0,     0,     0,   157,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,     0,     0,     0,     0,     0,     0,     0,   165,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,     0,     0,     0,   189,     0,     0,   190,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,     0,     0,     0,     0,     0,     0,   123,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,     0,     0,     0,     0,     0,     0,   177,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,     0,     0,     0,    80,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,     0,
       0,     0,   152,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,     0,     0,     0,   155,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,     0,     0,     0,   169,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
       0,     0,     0,   197,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69
};

static const yytype_int16 yycheck[] =
{
      21,    99,    25,    24,    27,    48,   151,     0,    33,    41,
      31,    32,    33,    38,    41,    41,     0,     5,    33,    35,
     165,     5,     6,    34,   155,     9,    34,     5,     5,    41,
      73,     5,    38,    34,    77,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    33,
      38,   106,    34,   108,   152,    33,    33,   155,   189,    33,
      81,    38,    37,    34,    38,    38,   197,    28,    29,    30,
     168,   126,    36,    33,   172,     6,     7,     8,     9,    33,
      33,   102,   180,    38,     3,     4,    38,    71,     5,    13,
      41,   189,     6,     7,     8,     9,   119,     6,    36,   197,
      36,    33,   123,    34,   125,   160,    41,    26,   129,     5,
      11,    11,    31,    36,    33,    34,   137,    38,    11,   174,
      39,    40,    41,   178,     6,     7,     8,     9,    36,   150,
      36,   186,    36,   154,     9,     3,     4,   123,     6,     7,
       8,     9,    10,   164,    12,    13,    14,    15,    -1,    -1,
      -1,    -1,    34,    -1,    -1,    -1,   177,    -1,    26,    -1,
      -1,    -1,    -1,    31,    -1,    33,    -1,   151,    36,   190,
      -1,    39,    40,    41,    -1,     3,     4,    -1,    -1,    -1,
      -1,   165,    10,    -1,    12,    13,    14,    15,     6,     7,
       8,     9,    26,    27,    28,    29,    30,    -1,    26,    -1,
      -1,    -1,    -1,    31,    -1,    33,    -1,    35,     3,     4,
      -1,    39,    40,    41,    -1,    10,    34,    12,    13,    14,
      15,    -1,     6,     7,     8,     9,    -1,    -1,    -1,    -1,
      -1,    26,    16,    17,    -1,    -1,    31,    -1,    33,    -1,
      -1,    36,     3,     4,    39,    40,    41,    -1,    -1,    10,
      -1,    12,    13,    14,    15,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    -1,    26,    -1,    -1,    -1,    -1,
      31,    -1,    33,    -1,    -1,    36,     3,     4,    39,    40,
      41,    -1,    -1,    10,    -1,    12,    13,    14,    15,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,
      -1,    -1,    -1,    -1,    31,    -1,    33,    -1,    35,     3,
       4,    -1,    39,    40,    41,    -1,    10,    -1,    12,    13,
      14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    26,    -1,    -1,    -1,    -1,    31,    -1,    33,
      -1,    -1,    36,     3,     4,    39,    40,    41,    -1,    -1,
      10,    -1,    12,    13,    14,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,    -1,
      -1,    31,    -1,    33,    -1,    35,     3,     4,    -1,    39,
      40,    41,    -1,    10,    -1,    12,    13,    14,    15,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,
      -1,    -1,    -1,    -1,    31,    -1,    33,    -1,    35,     3,
       4,    -1,    39,    40,    41,    -1,    10,    -1,    12,    13,
      14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    26,    -1,    -1,    -1,    -1,    31,    -1,    33,
      -1,    -1,    36,     3,     4,    39,    40,    41,    -1,    -1,
      10,    -1,    12,    13,    14,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,    -1,
      -1,    31,    -1,    33,    -1,    -1,    36,     3,     4,    39,
      40,    41,    -1,    -1,    10,    -1,    12,    13,    14,    15,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      26,    -1,    -1,    -1,    -1,    31,    -1,    33,    -1,    35,
       3,     4,    -1,    39,    40,    41,    -1,    10,    -1,    12,
      13,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,    31,    -1,
      33,    -1,    -1,    36,     3,     4,    39,    40,    41,    -1,
      -1,    10,    -1,    12,    13,    14,    15,    -1,    -1,    -1,
       3,     4,    -1,     6,     7,     8,     9,    26,    -1,    -1,
      -1,    -1,    31,    -1,    33,    -1,     3,     4,    -1,    -1,
      39,    40,    41,    26,    -1,    -1,    -1,    -1,    31,    -1,
      33,    -1,    -1,    -1,    -1,    -1,    39,    40,    41,    26,
      -1,    -1,    -1,    -1,    31,    -1,    33,    -1,    -1,    -1,
      -1,    -1,    39,    40,    41,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    38,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    -1,    -1,    -1,    34,    -1,    -1,    37,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    -1,    -1,    -1,    -1,    -1,    -1,    37,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    -1,    -1,    -1,    -1,    -1,    -1,    37,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    -1,    -1,    -1,    34,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    -1,
      -1,    -1,    34,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    -1,    -1,    -1,    34,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    -1,    -1,    -1,    34,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      -1,    -1,    -1,    34,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,     7,     8,     9,    16,    17,    43,    44,    45,
      46,    47,    48,    71,    71,    71,     0,    44,    41,    41,
      41,     5,    33,    38,     5,    33,    38,    33,    38,     3,
       4,    26,    31,    33,    39,    40,    41,    60,    63,    66,
      67,    68,    69,    70,    34,    64,    71,    60,    34,    64,
      34,    64,    60,    60,    60,    71,    33,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      38,    35,    49,    34,    41,    38,    49,    34,    38,    34,
      34,    34,    34,    60,    61,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    10,    12,
      13,    14,    15,    36,    41,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    62,    71,    49,    37,
      49,    38,    60,    37,    34,    33,    35,    51,    65,    33,
      33,    60,    36,    50,    38,    36,    50,     5,    38,    41,
      64,    61,    60,    36,    50,    13,    60,     6,    36,    60,
       5,    38,    34,    36,    33,    34,    41,    38,    60,    53,
      35,    51,    60,    65,     5,    38,    36,    50,    11,    34,
      60,    53,    11,    36,    35,    51,    38,    37,    35,    51,
      11,    36,    50,    60,    36,    50,    35,    51,    36,    34,
      37,    36,    36,    50,    65,    60,    36,    34,    65
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    42,    43,    44,    44,    45,    45,    45,    46,    46,
      46,    46,    46,    46,    47,    48,    48,    48,    48,    49,
      49,    49,    49,    50,    50,    51,    51,    51,    51,    51,
      51,    51,    52,    53,    53,    53,    53,    54,    55,    56,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    58,    58,    59,    60,    60,    60,    60,    60,
      60,    61,    61,    62,    62,    63,    63,    64,    64,    65,
      65,    65,    66,    66,    66,    67,    68,    69,    69,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    71,    71,    71,    71
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     7,     6,
       6,     5,     6,     7,     4,     6,     4,     5,     3,     4,
       3,     3,     2,     2,     1,     1,     2,     2,     1,     1,
       1,     1,     1,     6,     5,     4,     3,     4,     7,     5,
      11,    10,    10,     9,     9,     9,     7,     8,     8,     7,
       5,     6,    12,    10,     1,     3,     1,     1,     1,     1,
       4,     3,     1,     2,     1,     3,     4,     4,     2,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: decls  */
#line 65 "src/scanparse/parser.y"
         {
           parseresult = ASTprogram((yyvsp[0].node), NULL, NULL);
         }
#line 1906 "parser.tab.c"
    break;

  case 3: /* decls: decl decls  */
#line 71 "src/scanparse/parser.y"
       {
         (yyval.node) = ASTdecls((yyvsp[-1].node), (yyvsp[0].node));
         AddLocToNode((yyval.node), &(yylsp[-1]), &(yylsp[-1]));
       }
#line 1915 "parser.tab.c"
    break;

  case 4: /* decls: decl  */
#line 76 "src/scanparse/parser.y"
       {
         (yyval.node) = ASTdecls((yyvsp[0].node), NULL);
         AddLocToNode((yyval.node), &(yylsp[0]), &(yylsp[0]));
       }
#line 1924 "parser.tab.c"
    break;

  case 5: /* decl: fundef  */
#line 83 "src/scanparse/parser.y"
      {
        (yyval.node) = (yyvsp[0].node);
      }
#line 1932 "parser.tab.c"
    break;

  case 6: /* decl: globdecl  */
#line 87 "src/scanparse/parser.y"
      {
        (yyval.node) = (yyvsp[0].node);
      }
#line 1940 "parser.tab.c"
    break;

  case 7: /* decl: globdef  */
#line 91 "src/scanparse/parser.y"
      {
        (yyval.node) = (yyvsp[0].node);
      }
#line 1948 "parser.tab.c"
    break;

  case 8: /* fundef: EXPORT vartype ID BRACKET_L param BRACKET_R funbody  */
#line 97 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTfundef((yyvsp[0].node), (yyvsp[-2].node), NULL, (yyvsp[-5].ctype), (yyvsp[-4].id), true, false, NULL);
          AddLocToNode((yyval.node), &(yylsp[-5]), &(yylsp[0]));
        }
#line 1957 "parser.tab.c"
    break;

  case 9: /* fundef: EXPORT vartype ID BRACKET_L BRACKET_R funbody  */
#line 103 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTfundef((yyvsp[0].node), NULL, NULL, (yyvsp[-4].ctype), (yyvsp[-3].id), true, false, NULL);
          AddLocToNode((yyval.node), &(yylsp[-4]), &(yylsp[0]));
        }
#line 1966 "parser.tab.c"
    break;

  case 10: /* fundef: vartype ID BRACKET_L param BRACKET_R funbody  */
#line 109 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTfundef((yyvsp[0].node), (yyvsp[-2].node), NULL, (yyvsp[-5].ctype), (yyvsp[-4].id), false, false, NULL);
          AddLocToNode((yyval.node), &(yylsp[-5]), &(yylsp[0]));
        }
#line 1975 "parser.tab.c"
    break;

  case 11: /* fundef: vartype ID BRACKET_L BRACKET_R funbody  */
#line 115 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTfundef((yyvsp[0].node), NULL, NULL, (yyvsp[-4].ctype), (yyvsp[-3].id), false, false, NULL);
          AddLocToNode((yyval.node), &(yylsp[-4]), &(yylsp[0]));
        }
#line 1984 "parser.tab.c"
    break;

  case 12: /* fundef: EXTERN vartype ID BRACKET_L BRACKET_R SEMICOLON  */
#line 120 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTfundef(NULL, NULL, NULL, (yyvsp[-4].ctype), (yyvsp[-3].id), false, true, NULL);
          AddLocToNode((yyval.node), &(yylsp[-4]), &(yylsp[-3]));
        }
#line 1993 "parser.tab.c"
    break;

  case 13: /* fundef: EXTERN vartype ID BRACKET_L param BRACKET_R SEMICOLON  */
#line 125 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTfundef(NULL, (yyvsp[-2].node), NULL, (yyvsp[-5].ctype), (yyvsp[-4].id), false, true, NULL);
          AddLocToNode((yyval.node), &(yylsp[-5]), &(yylsp[-2]));
        }
#line 2002 "parser.tab.c"
    break;

  case 14: /* globdecl: EXTERN vartype ID SEMICOLON  */
#line 132 "src/scanparse/parser.y"
          {
            (yyval.node) = ASTglobdecl(NULL, (yyvsp[-2].ctype), (yyvsp[-1].id));
            AddLocToNode((yyval.node), &(yylsp[-3]), &(yylsp[-1]));
          }
#line 2011 "parser.tab.c"
    break;

  case 15: /* globdef: EXPORT vartype ID LET expr SEMICOLON  */
#line 139 "src/scanparse/parser.y"
         {
           (yyval.node) = ASTglobdef(NULL, (yyvsp[-1].node), (yyvsp[-4].ctype), (yyvsp[-3].id), true);
           AddLocToNode((yyval.node), &(yylsp[-5]), &(yylsp[-1]));
         }
#line 2020 "parser.tab.c"
    break;

  case 16: /* globdef: EXPORT vartype ID SEMICOLON  */
#line 144 "src/scanparse/parser.y"
         {
           (yyval.node) = ASTglobdef(NULL, NULL, (yyvsp[-2].ctype), (yyvsp[-1].id), true);
           AddLocToNode((yyval.node), &(yylsp[-3]), &(yylsp[-1]));
         }
#line 2029 "parser.tab.c"
    break;

  case 17: /* globdef: vartype ID LET expr SEMICOLON  */
#line 149 "src/scanparse/parser.y"
         {
           (yyval.node) = ASTglobdef(NULL, (yyvsp[-1].node), (yyvsp[-4].ctype), (yyvsp[-3].id), false);
           AddLocToNode((yyval.node), &(yylsp[-4]), &(yylsp[-1]));
         }
#line 2038 "parser.tab.c"
    break;

  case 18: /* globdef: vartype ID SEMICOLON  */
#line 154 "src/scanparse/parser.y"
         {
           (yyval.node) = ASTglobdef(NULL, NULL, (yyvsp[-2].ctype), (yyvsp[-1].id), false);
           AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[-1]));
         }
#line 2047 "parser.tab.c"
    break;

  case 19: /* funbody: BRACE_L vardecl stmts BRACE_R  */
#line 161 "src/scanparse/parser.y"
         {
           (yyval.node) = ASTfunbody((yyvsp[-2].node), NULL, (yyvsp[-1].node));
           AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[-1]));
         }
#line 2056 "parser.tab.c"
    break;

  case 20: /* funbody: BRACE_L vardecl BRACE_R  */
#line 166 "src/scanparse/parser.y"
         {
           (yyval.node) = ASTfunbody((yyvsp[-1].node), NULL, NULL);
           AddLocToNode((yyval.node), &(yylsp[-1]), &(yylsp[-1]));
         }
#line 2065 "parser.tab.c"
    break;

  case 21: /* funbody: BRACE_L stmts BRACE_R  */
#line 171 "src/scanparse/parser.y"
         {
           (yyval.node) = ASTfunbody(NULL, NULL, (yyvsp[-1].node));
           AddLocToNode((yyval.node), &(yylsp[-1]), &(yylsp[-1]));
         }
#line 2074 "parser.tab.c"
    break;

  case 22: /* funbody: BRACE_L BRACE_R  */
#line 176 "src/scanparse/parser.y"
         {
           (yyval.node) = ASTfunbody(NULL, NULL, NULL);
         }
#line 2082 "parser.tab.c"
    break;

  case 23: /* stmts: stmt stmts  */
#line 182 "src/scanparse/parser.y"
       {
         (yyval.node) = ASTstmts((yyvsp[-1].node), (yyvsp[0].node));
         AddLocToNode((yyval.node), &(yylsp[-1]), &(yylsp[-1]));
       }
#line 2091 "parser.tab.c"
    break;

  case 24: /* stmts: stmt  */
#line 187 "src/scanparse/parser.y"
       {
         (yyval.node) = ASTstmts((yyvsp[0].node), NULL);
         AddLocToNode((yyval.node), &(yylsp[0]), &(yylsp[0]));
       }
#line 2100 "parser.tab.c"
    break;

  case 25: /* stmt: assign  */
#line 194 "src/scanparse/parser.y"
      {
        (yyval.node) = (yyvsp[0].node);
      }
#line 2108 "parser.tab.c"
    break;

  case 26: /* stmt: return SEMICOLON  */
#line 198 "src/scanparse/parser.y"
      {
        (yyval.node) = (yyvsp[-1].node);
      }
#line 2116 "parser.tab.c"
    break;

  case 27: /* stmt: exprstmt SEMICOLON  */
#line 202 "src/scanparse/parser.y"
      {
        (yyval.node) = (yyvsp[-1].node);
      }
#line 2124 "parser.tab.c"
    break;

  case 28: /* stmt: ifelse  */
#line 206 "src/scanparse/parser.y"
      {
        (yyval.node) = (yyvsp[0].node);
      }
#line 2132 "parser.tab.c"
    break;

  case 29: /* stmt: while  */
#line 210 "src/scanparse/parser.y"
      {
        (yyval.node) = (yyvsp[0].node);
      }
#line 2140 "parser.tab.c"
    break;

  case 30: /* stmt: dowhile  */
#line 214 "src/scanparse/parser.y"
      {
        (yyval.node) = (yyvsp[0].node);
      }
#line 2148 "parser.tab.c"
    break;

  case 31: /* stmt: for  */
#line 218 "src/scanparse/parser.y"
      {
         (yyval.node) = (yyvsp[0].node);
      }
#line 2156 "parser.tab.c"
    break;

  case 32: /* exprstmt: expr  */
#line 224 "src/scanparse/parser.y"
          {
            (yyval.node) = ASTexprstmt((yyvsp[0].node));
            AddLocToNode((yyval.node), &(yylsp[0]), &(yylsp[0]));
          }
#line 2165 "parser.tab.c"
    break;

  case 33: /* vardecl: vartype ID LET expr SEMICOLON vardecl  */
#line 231 "src/scanparse/parser.y"
         {
           (yyval.node) = ASTvardecl(NULL, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-4].id), (yyvsp[-5].ctype));
           AddLocToNode((yyval.node), &(yylsp[-5]), &(yylsp[-2]));
         }
#line 2174 "parser.tab.c"
    break;

  case 34: /* vardecl: vartype ID LET expr SEMICOLON  */
#line 237 "src/scanparse/parser.y"
         {
           (yyval.node) = ASTvardecl(NULL, (yyvsp[-1].node), NULL, (yyvsp[-3].id), (yyvsp[-4].ctype));
           AddLocToNode((yyval.node), &(yylsp[-4]), &(yylsp[-1]));
         }
#line 2183 "parser.tab.c"
    break;

  case 35: /* vardecl: vartype ID SEMICOLON vardecl  */
#line 243 "src/scanparse/parser.y"
         {
           (yyval.node) = ASTvardecl(NULL, NULL, (yyvsp[0].node), (yyvsp[-2].id), (yyvsp[-3].ctype));
           AddLocToNode((yyval.node), &(yylsp[-3]), &(yylsp[-2]));
         }
#line 2192 "parser.tab.c"
    break;

  case 36: /* vardecl: vartype ID SEMICOLON  */
#line 249 "src/scanparse/parser.y"
         {
           (yyval.node) = ASTvardecl(NULL, NULL, NULL, (yyvsp[-1].id), (yyvsp[-2].ctype));
           AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[-1]));
         }
#line 2201 "parser.tab.c"
    break;

  case 37: /* assign: varlet LET expr SEMICOLON  */
#line 256 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTassign((yyvsp[-3].node), (yyvsp[-1].node));
          AddLocToNode((yyval.node), &(yylsp[-3]), &(yylsp[-1]));
        }
#line 2210 "parser.tab.c"
    break;

  case 38: /* dowhile: DO block WHILE BRACKET_L expr BRACKET_R SEMICOLON  */
#line 263 "src/scanparse/parser.y"
         {
           (yyval.node) = ASTdowhile((yyvsp[-2].node), (yyvsp[-5].node));
           AddLocToNode((yyval.node), &(yylsp[-6]), &(yylsp[-5]));
         }
#line 2219 "parser.tab.c"
    break;

  case 39: /* while: WHILE BRACKET_L expr BRACKET_R block  */
#line 270 "src/scanparse/parser.y"
       {
         (yyval.node) = ASTwhile((yyvsp[-2].node), (yyvsp[0].node));
         AddLocToNode((yyval.node), &(yylsp[-4]), &(yylsp[0]));
       }
#line 2228 "parser.tab.c"
    break;

  case 40: /* ifelse: IF BRACKET_L expr BRACKET_R BRACE_L stmts BRACE_R ELSE BRACE_L stmts BRACE_R  */
#line 277 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTifelse((yyvsp[-8].node), (yyvsp[-5].node), (yyvsp[-1].node));
          AddLocToNode((yyval.node), &(yylsp[-10]), &(yylsp[0]));
        }
#line 2237 "parser.tab.c"
    break;

  case 41: /* ifelse: IF BRACKET_L expr BRACKET_R BRACE_L BRACE_R ELSE BRACE_L stmts BRACE_R  */
#line 282 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTifelse((yyvsp[-7].node), NULL, (yyvsp[-1].node));
          AddLocToNode((yyval.node), &(yylsp[-9]), &(yylsp[0]));
        }
#line 2246 "parser.tab.c"
    break;

  case 42: /* ifelse: IF BRACKET_L expr BRACKET_R BRACE_L stmts BRACE_R ELSE BRACE_L BRACE_R  */
#line 287 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTifelse((yyvsp[-7].node), (yyvsp[-4].node), NULL);
          AddLocToNode((yyval.node), &(yylsp[-9]), &(yylsp[0]));
        }
#line 2255 "parser.tab.c"
    break;

  case 43: /* ifelse: IF BRACKET_L expr BRACKET_R BRACE_L BRACE_R ELSE BRACE_L BRACE_R  */
#line 292 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTifelse((yyvsp[-6].node), NULL, NULL);
          AddLocToNode((yyval.node), &(yylsp[-8]), &(yylsp[0]));
        }
#line 2264 "parser.tab.c"
    break;

  case 44: /* ifelse: IF BRACKET_L expr BRACKET_R BRACE_L stmts BRACE_R ELSE stmt  */
#line 297 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTifelse((yyvsp[-6].node), (yyvsp[-3].node), elseblock);
          AddLocToNode((yyval.node), &(yylsp[-8]), &(yylsp[0]));
        }
#line 2273 "parser.tab.c"
    break;

  case 45: /* ifelse: IF BRACKET_L expr BRACKET_R stmt ELSE BRACE_L stmts BRACE_R  */
#line 302 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTifelse((yyvsp[-6].node), (yyvsp[-4].node), elseblock);
          AddLocToNode((yyval.node), &(yylsp[-8]), &(yylsp[0]));
        }
#line 2282 "parser.tab.c"
    break;

  case 46: /* ifelse: IF BRACKET_L expr BRACKET_R stmt ELSE stmt  */
#line 307 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTifelse((yyvsp[-4].node), (yyvsp[-2].node), elseblock);
          AddLocToNode((yyval.node), &(yylsp[-6]), &(yylsp[0]));
        }
#line 2291 "parser.tab.c"
    break;

  case 47: /* ifelse: IF BRACKET_L expr BRACKET_R stmt ELSE BRACE_L BRACE_R  */
#line 312 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTifelse((yyvsp[-5].node), then, NULL);
          AddLocToNode((yyval.node), &(yylsp[-7]), &(yylsp[0]));
        }
#line 2300 "parser.tab.c"
    break;

  case 48: /* ifelse: IF BRACKET_L expr BRACKET_R BRACE_L BRACE_R ELSE stmt  */
#line 317 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTifelse((yyvsp[-5].node), NULL, elseblock);
          AddLocToNode((yyval.node), &(yylsp[-7]), &(yylsp[0]));
        }
#line 2309 "parser.tab.c"
    break;

  case 49: /* ifelse: IF BRACKET_L expr BRACKET_R BRACE_L stmts BRACE_R  */
#line 322 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTifelse((yyvsp[-4].node), (yyvsp[-1].node), NULL);
          AddLocToNode((yyval.node), &(yylsp[-6]), &(yylsp[0]));
        }
#line 2318 "parser.tab.c"
    break;

  case 50: /* ifelse: IF BRACKET_L expr BRACKET_R stmt  */
#line 327 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTifelse((yyvsp[-2].node), (yyvsp[0].node), NULL);
          AddLocToNode((yyval.node), &(yylsp[-4]), &(yylsp[0]));
        }
#line 2327 "parser.tab.c"
    break;

  case 51: /* ifelse: IF BRACKET_L expr BRACKET_R BRACE_L BRACE_R  */
#line 332 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTifelse((yyvsp[-3].node), NULL, NULL);
          AddLocToNode((yyval.node), &(yylsp[-5]), &(yylsp[0]));
        }
#line 2336 "parser.tab.c"
    break;

  case 52: /* for: FOR BRACKET_L INTTYPE ID LET expr COMMA expr COMMA expr BRACKET_R block  */
#line 339 "src/scanparse/parser.y"
     {
       (yyval.node) = ASTfor((yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), NULL, (yyvsp[-8].id));
       AddLocToNode((yyval.node), &(yylsp[-11]), &(yylsp[0]));
     }
#line 2345 "parser.tab.c"
    break;

  case 53: /* for: FOR BRACKET_L INTTYPE ID LET expr COMMA expr BRACKET_R block  */
#line 344 "src/scanparse/parser.y"
     {
       (yyval.node) = ASTfor((yyvsp[-4].node), (yyvsp[-2].node), NULL, (yyvsp[0].node), NULL, (yyvsp[-6].id));
       AddLocToNode((yyval.node), &(yylsp[-9]), &(yylsp[0]));
     }
#line 2354 "parser.tab.c"
    break;

  case 54: /* varlet: ID  */
#line 352 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTvarlet(NULL, (yyvsp[0].id), NULL);
          AddLocToNode((yyval.node), &(yylsp[0]), &(yylsp[0]));
        }
#line 2363 "parser.tab.c"
    break;

  case 55: /* expr: BRACKET_L expr BRACKET_R  */
#line 359 "src/scanparse/parser.y"
      {
        (yyval.node) = (yyvsp[-1].node);
      }
#line 2371 "parser.tab.c"
    break;

  case 56: /* expr: constant  */
#line 363 "src/scanparse/parser.y"
      {
        (yyval.node) = (yyvsp[0].node);
      }
#line 2379 "parser.tab.c"
    break;

  case 57: /* expr: ID  */
#line 367 "src/scanparse/parser.y"
      {
        (yyval.node) = ASTvar(NULL, (yyvsp[0].id), NULL);
        AddLocToNode((yyval.node), &(yylsp[0]), &(yylsp[0]));
      }
#line 2388 "parser.tab.c"
    break;

  case 58: /* expr: funcall  */
#line 372 "src/scanparse/parser.y"
      {
        (yyval.node) = (yyvsp[0].node);
      }
#line 2396 "parser.tab.c"
    break;

  case 59: /* expr: binmon  */
#line 376 "src/scanparse/parser.y"
      {
        (yyval.node) = (yyvsp[0].node);
      }
#line 2404 "parser.tab.c"
    break;

  case 60: /* expr: BRACKET_L vartype BRACKET_R expr  */
#line 380 "src/scanparse/parser.y"
      {
        (yyval.node) = ASTcast( (yyvsp[0].node), (yyvsp[-2].ctype));
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
      }
#line 2413 "parser.tab.c"
    break;

  case 61: /* exprs: expr COMMA exprs  */
#line 387 "src/scanparse/parser.y"
       {
        (yyval.node) = ASTexprs((yyvsp[-2].node), (yyvsp[0].node));
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
       }
#line 2422 "parser.tab.c"
    break;

  case 62: /* exprs: expr  */
#line 392 "src/scanparse/parser.y"
       {
        (yyval.node) = ASTexprs((yyvsp[0].node), NULL);
        AddLocToNode((yyval.node), &(yylsp[0]), &(yylsp[0]));
       }
#line 2431 "parser.tab.c"
    break;

  case 63: /* return: RETURN expr  */
#line 399 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTreturn((yyvsp[0].node));
          AddLocToNode((yyval.node), &(yylsp[-1]), &(yylsp[0]));
        }
#line 2440 "parser.tab.c"
    break;

  case 64: /* return: RETURN  */
#line 404 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTreturn(NULL);
          AddLocToNode((yyval.node), &(yylsp[0]), &(yylsp[0]));
        }
#line 2449 "parser.tab.c"
    break;

  case 65: /* funcall: ID BRACKET_L BRACKET_R  */
#line 411 "src/scanparse/parser.y"
         {
           (yyval.node) = ASTfuncall(NULL, (yyvsp[-2].id), NULL);
           AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[-2]));
         }
#line 2458 "parser.tab.c"
    break;

  case 66: /* funcall: ID BRACKET_L exprs BRACKET_R  */
#line 416 "src/scanparse/parser.y"
         {
           (yyval.node) = ASTfuncall((yyvsp[-1].node), (yyvsp[-3].id), NULL);
           AddLocToNode((yyval.node), &(yylsp[-3]), &(yylsp[-1]));
         }
#line 2467 "parser.tab.c"
    break;

  case 67: /* param: vartype ID COMMA param  */
#line 423 "src/scanparse/parser.y"
       {
         (yyval.node) = ASTparam(NULL, (yyvsp[0].node), (yyvsp[-2].id), (yyvsp[-3].ctype));
         AddLocToNode((yyval.node), &(yylsp[-3]), &(yylsp[0]));
       }
#line 2476 "parser.tab.c"
    break;

  case 68: /* param: vartype ID  */
#line 428 "src/scanparse/parser.y"
       {
         (yyval.node) = ASTparam(NULL, NULL, (yyvsp[0].id), (yyvsp[-1].ctype));
         AddLocToNode((yyval.node), &(yylsp[-1]), &(yylsp[0]));
       }
#line 2485 "parser.tab.c"
    break;

  case 69: /* block: BRACE_L stmts BRACE_R  */
#line 435 "src/scanparse/parser.y"
       {
         (yyval.node) = (yyvsp[-1].node);
       }
#line 2493 "parser.tab.c"
    break;

  case 70: /* block: BRACE_L BRACE_R  */
#line 439 "src/scanparse/parser.y"
       {
         (yyval.node) = NULL;
       }
#line 2501 "parser.tab.c"
    break;

  case 71: /* block: stmt  */
#line 443 "src/scanparse/parser.y"
       {
         (yyval.node) = ASTstmts((yyvsp[0].node), NULL);
         AddLocToNode((yyval.node), &(yylsp[0]), &(yylsp[0]));
       }
#line 2510 "parser.tab.c"
    break;

  case 72: /* constant: floatval  */
#line 450 "src/scanparse/parser.y"
          {
            (yyval.node) = (yyvsp[0].node);
          }
#line 2518 "parser.tab.c"
    break;

  case 73: /* constant: intval  */
#line 454 "src/scanparse/parser.y"
          {
            (yyval.node) = (yyvsp[0].node);
          }
#line 2526 "parser.tab.c"
    break;

  case 74: /* constant: boolval  */
#line 458 "src/scanparse/parser.y"
          {
            (yyval.node) = (yyvsp[0].node);
          }
#line 2534 "parser.tab.c"
    break;

  case 75: /* floatval: FLOAT  */
#line 464 "src/scanparse/parser.y"
          {
            (yyval.node) = ASTfloat((yyvsp[0].cflt), NULL);
            AddLocToNode((yyval.node), &(yylsp[0]), &(yylsp[0]));
          }
#line 2543 "parser.tab.c"
    break;

  case 76: /* intval: NUM  */
#line 471 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTnum((yyvsp[0].cint), NULL);
          AddLocToNode((yyval.node), &(yylsp[0]), &(yylsp[0]));
        }
#line 2552 "parser.tab.c"
    break;

  case 77: /* boolval: TRUEVAL  */
#line 478 "src/scanparse/parser.y"
         {
           (yyval.node) = ASTbool(true);
           AddLocToNode((yyval.node), &(yylsp[0]), &(yylsp[0]));
         }
#line 2561 "parser.tab.c"
    break;

  case 78: /* boolval: FALSEVAL  */
#line 483 "src/scanparse/parser.y"
         {
           (yyval.node) = ASTbool(false);
           AddLocToNode((yyval.node), &(yylsp[0]), &(yylsp[0]));
         }
#line 2570 "parser.tab.c"
    break;

  case 79: /* binmon: expr PLUS expr  */
#line 490 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_add, CT_NULL);
          AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        }
#line 2579 "parser.tab.c"
    break;

  case 80: /* binmon: expr MINUS expr  */
#line 495 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_sub, CT_NULL);
          AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        }
#line 2588 "parser.tab.c"
    break;

  case 81: /* binmon: expr STAR expr  */
#line 500 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_mul, CT_NULL);
          AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        }
#line 2597 "parser.tab.c"
    break;

  case 82: /* binmon: expr SLASH expr  */
#line 505 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_div, CT_NULL);
          AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        }
#line 2606 "parser.tab.c"
    break;

  case 83: /* binmon: expr PERCENT expr  */
#line 510 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_mod, CT_NULL);
          AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        }
#line 2615 "parser.tab.c"
    break;

  case 84: /* binmon: expr LE expr  */
#line 515 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_le, CT_bool);
          AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        }
#line 2624 "parser.tab.c"
    break;

  case 85: /* binmon: expr LT expr  */
#line 520 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_lt, CT_bool);
          AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        }
#line 2633 "parser.tab.c"
    break;

  case 86: /* binmon: expr GE expr  */
#line 525 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_ge, CT_bool);
          AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        }
#line 2642 "parser.tab.c"
    break;

  case 87: /* binmon: expr GT expr  */
#line 530 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_gt, CT_bool);
          AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        }
#line 2651 "parser.tab.c"
    break;

  case 88: /* binmon: expr EQ expr  */
#line 535 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_eq, CT_bool);
          AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        }
#line 2660 "parser.tab.c"
    break;

  case 89: /* binmon: expr NE expr  */
#line 540 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_ne, CT_bool);
          AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        }
#line 2669 "parser.tab.c"
    break;

  case 90: /* binmon: expr OR expr  */
#line 545 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_or, CT_bool);
          AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        }
#line 2678 "parser.tab.c"
    break;

  case 91: /* binmon: expr AND expr  */
#line 550 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_and, CT_bool);
          AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        }
#line 2687 "parser.tab.c"
    break;

  case 92: /* binmon: MINUS expr  */
#line 555 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTmonop( (yyvsp[0].node), MO_neg, CT_NULL);
          AddLocToNode((yyval.node), &(yylsp[-1]), &(yylsp[0]));
        }
#line 2696 "parser.tab.c"
    break;

  case 93: /* binmon: EXCLAMATION expr  */
#line 560 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTmonop( (yyvsp[0].node), MO_not, CT_bool);
          AddLocToNode((yyval.node), &(yylsp[-1]), &(yylsp[0]));
        }
#line 2705 "parser.tab.c"
    break;

  case 94: /* vartype: BOOLTYPE  */
#line 566 "src/scanparse/parser.y"
                       { (yyval.ctype) = CT_bool; }
#line 2711 "parser.tab.c"
    break;

  case 95: /* vartype: INTTYPE  */
#line 567 "src/scanparse/parser.y"
                       { (yyval.ctype) = CT_int; }
#line 2717 "parser.tab.c"
    break;

  case 96: /* vartype: FLOATTYPE  */
#line 568 "src/scanparse/parser.y"
                       { (yyval.ctype) = CT_float; }
#line 2723 "parser.tab.c"
    break;

  case 97: /* vartype: VOIDTYPE  */
#line 569 "src/scanparse/parser.y"
                       { (yyval.ctype) = CT_void; }
#line 2729 "parser.tab.c"
    break;


#line 2733 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 571 "src/scanparse/parser.y"


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
    /* yydebug = 1;  // Turn on yacc debugging */
    yyparse();
    return parseresult;
}
