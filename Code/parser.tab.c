/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include "ourgetopt.cpp"
#include <string.h>
#include <stdio.h>
#include <map>
#include "scanType.h"
#include "ASTreeNode.h"
#include "symbolTable.cpp"
#include "memloc.cpp"
#include "semantic.cpp"
#include "yyerror.cpp"
#include "codegen.cpp"

extern int yylex();
extern int yyleng;
extern FILE *yyin;	                         // input source file
extern int line; 	                           // line number from flex scanner
extern int yydebug;                          // yydebug flag

extern int ourGetopt( int, char **, char*);  // function definition for get option program from course website

static ASTreeNode* treeRec; // root of the tree


#line 95 "parser.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    BOOL = 258,
    CHAR = 259,
    INT = 260,
    INC = 261,
    ADDASS = 262,
    SUBASS = 263,
    MULTASS = 264,
    DIVASS = 265,
    ASGN = 266,
    SYMBOL = 267,
    ID = 268,
    CHARCONST = 269,
    NUMCONST = 270,
    STRINGCONST = 271,
    BOOLCONST = 272,
    STATIC = 273,
    FOR = 274,
    TO = 275,
    BY = 276,
    WHILE = 277,
    DO = 278,
    RETURN = 279,
    BREAK = 280,
    NOT = 281,
    AND = 282,
    OR = 283,
    IF = 284,
    THEN = 285,
    LT = 286,
    GT = 287,
    EQ = 288,
    GEQ = 289,
    LEQ = 290,
    NEQ = 291,
    DEC = 292,
    CONDITIONAL = 293,
    ELSE = 294,
    ADD = 295,
    SUB = 296,
    MULT = 297,
    DIV = 298,
    MOD = 299,
    LPAREN = 300,
    RPAREN = 301,
    LBRACKET = 302,
    RBRACKET = 303,
    LBRACE = 304,
    RBRACE = 305,
    COMMA = 306,
    COLON = 307,
    SEMICOLON = 308
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 26 "parser.y"

  struct Token *tokenData;
  struct ASTreeNode *treeNode;

#line 206 "parser.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */



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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  18
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   735

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  46
/* YYNRULES -- Number of rules.  */
#define YYNRULES  156
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  245

#define YYUNDEFTOK  2
#define YYMAXUTOK   308


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    49,    49,    52,    63,    66,    67,    68,    72,    83,
      96,    97,   100,   104,   108,   109,   110,   113,   119,   134,
     135,   136,   139,   152,   167,   176,   177,   178,   181,   190,
     191,   195,   200,   201,   202,   208,   209,   212,   223,   224,
     225,   228,   239,   242,   252,   253,   254,   257,   260,   266,
     270,   274,   280,   293,   296,   297,   300,   301,   302,   303,
     306,   307,   308,   311,   312,   321,   322,   323,   324,   325,
     331,   332,   335,   336,   339,   340,   343,   346,   357,   358,
     359,   362,   365,   368,   369,   370,   373,   374,   379,   380,
     386,   387,   393,   394,   397,   398,   401,   404,   405,   408,
     411,   412,   415,   418,   421,   424,   429,   430,   433,   435,
     436,   439,   441,   442,   446,   448,   449,   452,   457,   463,
     464,   465,   466,   469,   484,   487,   488,   491,   505,   506,
     509,   514,   519,   522,   527,   532,   537,   542,   547,   553,
     554,   555,   558,   559,   562,   565,   568,   573,   574,   575,
     576,   577,   578,   581,   587,   596,   602
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "BOOL", "CHAR", "INT", "INC", "ADDASS",
  "SUBASS", "MULTASS", "DIVASS", "ASGN", "SYMBOL", "ID", "CHARCONST",
  "NUMCONST", "STRINGCONST", "BOOLCONST", "STATIC", "FOR", "TO", "BY",
  "WHILE", "DO", "RETURN", "BREAK", "NOT", "AND", "OR", "IF", "THEN", "LT",
  "GT", "EQ", "GEQ", "LEQ", "NEQ", "DEC", "CONDITIONAL", "ELSE", "ADD",
  "SUB", "MULT", "DIV", "MOD", "LPAREN", "RPAREN", "LBRACKET", "RBRACKET",
  "LBRACE", "RBRACE", "COMMA", "COLON", "SEMICOLON", "$accept", "program",
  "decList", "dec", "varDec", "funDec", "compStmt", "localDecs",
  "scopedVarDec", "varDecList", "varDecInit", "varDecID", "params",
  "paramList", "paramTypeList", "paramIdList", "paramID", "type",
  "stmtList", "stmt", "matchedif", "unmatchedif", "iterRange", "expStmt",
  "exp", "simpleExp", "andExp", "unaryRelExp", "relExp", "sumExp",
  "mulExp", "unaryExp", "factor", "mutable", "immutable", "call", "args",
  "argList", "returnStmt", "breakStmt", "assignop", "mulop", "sumop",
  "unaryop", "relop", "constant", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308
};
# endif

#define YYPACT_NINF (-142)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-127)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     198,   273,  -142,  -142,  -142,   -12,    47,   315,  -142,  -142,
    -142,    45,    65,    15,    83,  -142,    63,    17,  -142,  -142,
     183,   180,   190,  -142,   381,    26,    97,  -142,   381,  -142,
      21,    24,  -142,   119,  -142,    25,  -142,    46,   211,  -142,
    -142,  -142,  -142,   386,  -142,  -142,  -142,   419,    71,   111,
    -142,  -142,   646,   237,  -142,  -142,  -142,  -142,  -142,   647,
    -142,  -142,   106,    65,  -142,    71,     4,   247,   124,   149,
     125,  -142,    66,   151,  -142,   347,   424,    46,  -142,    86,
     154,    71,   118,   457,   462,  -142,  -142,  -142,  -142,  -142,
    -142,  -142,  -142,   652,   657,  -142,  -142,  -142,   690,    46,
    -142,  -142,  -142,   145,  -142,  -142,  -142,   168,   120,   175,
      86,  -142,   191,   189,   196,  -142,  -142,  -142,  -142,  -142,
    -142,  -142,   424,  -142,  -142,  -142,   495,    46,   111,    46,
    -142,    46,   237,    46,   -25,    46,  -142,    39,   204,  -142,
    -142,  -142,  -142,  -142,   500,  -142,  -142,    86,  -142,   289,
    -142,   152,  -142,  -142,   246,    86,  -142,   152,   213,    77,
     171,   533,    23,   202,   538,  -142,  -142,  -142,  -142,  -142,
    -142,  -142,   229,  -142,  -142,   216,  -142,  -142,  -142,   279,
       0,    88,    98,  -142,   244,  -142,    36,   255,  -142,  -142,
     571,   288,   330,  -142,  -142,   330,   288,   330,   -11,   283,
      -3,   176,   533,   576,  -142,  -142,  -142,   269,  -142,  -142,
     272,  -142,   308,   288,   330,   609,   310,   129,   143,   270,
     330,   330,  -142,  -142,  -142,  -142,    46,   164,   571,   288,
     288,   288,  -142,  -142,  -142,  -142,   614,   299,   284,   285,
      46,    71,   288,   288,   288
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    49,    50,    51,     0,     0,     0,     4,     5,
       6,     0,    27,    34,     0,    26,    30,     0,     1,     3,
      14,    34,     8,    33,     0,     0,     0,    10,     0,    40,
       0,    35,    38,     0,    11,     0,     9,     0,   117,   155,
     153,   154,   156,     0,   146,   144,   145,     0,    29,    96,
      99,   102,   104,   108,   111,   114,   115,   116,   121,     0,
     122,    32,     0,    25,    24,    28,     0,     0,    42,    47,
      41,    44,    15,     0,   124,     0,     0,   100,   101,   120,
       0,    93,   115,     0,     0,   147,   149,   151,   150,   148,
     152,   142,   143,     0,     0,   139,   140,   141,     0,   112,
     113,    31,    16,     0,    13,    39,    37,     0,     0,     0,
       0,   128,     0,   125,     0,    90,   135,   136,   137,   138,
     134,    92,     0,   119,    89,    91,     0,    94,    95,    97,
      98,   106,   107,   105,   103,   109,   110,     0,     0,    48,
      45,    43,    12,   123,     0,   118,    86,    88,    87,     0,
      20,     0,    19,    18,     0,   129,   127,     0,     0,     0,
       0,     0,     0,     0,     0,    17,    84,    69,    52,    54,
      55,    68,     0,    66,    67,     0,    23,    85,    65,     0,
      61,     0,     0,   130,     0,   133,    56,     0,    83,    22,
       0,     0,     0,   132,   131,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    60,    62,    76,    70,    72,    57,
      71,    73,     0,     0,     0,     0,     0,     0,    56,     0,
       0,     0,    79,    63,    64,    77,    78,    80,     0,     0,
       0,     0,    58,    74,    59,    75,     0,     0,     0,     0,
      82,    81,     0,     0,     0
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -142,  -142,  -142,   318,  -142,  -142,   -58,  -142,   194,   -10,
     301,  -142,   300,  -142,   267,  -142,   228,     7,  -142,  -142,
    -141,    18,   110,  -142,   -44,   -22,   256,   -32,  -142,   248,
     257,   -50,  -142,   -24,  -142,  -142,  -142,  -142,  -142,  -142,
     258,  -142,  -142,  -142,  -142,  -142
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    10,   167,   138,   150,    14,
      15,    16,    30,    31,    32,    70,    71,    33,   154,   168,
     205,   170,   199,   171,   172,    81,    49,    50,    51,    52,
      53,    54,    55,    82,    57,    58,   112,   113,   173,   174,
     122,    98,    93,    59,    94,    60
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      56,    22,    48,    80,    56,   102,    65,    11,   104,   100,
     212,    78,   213,   169,    11,    91,    92,   215,    29,    56,
       2,     3,     4,   191,   182,    83,    72,    61,     2,     3,
       4,   111,   114,    17,    74,    56,    38,    39,    40,    41,
      42,    62,     2,     3,     4,    74,    20,    18,   136,    43,
     204,   142,   130,   103,   207,   209,   210,   149,    21,    56,
      56,    44,    25,   -36,    45,    46,   195,    66,    47,    56,
      56,   -36,   223,   224,    56,   196,   183,    67,   146,   232,
     234,    74,   148,   115,   116,   117,   118,   119,   120,   238,
     239,    74,   115,   116,   117,   118,   119,   120,    63,    83,
     156,   224,   232,   234,   115,   116,   117,   118,   119,   120,
      13,   192,   -40,    23,   121,    28,    83,    24,   184,   -40,
      68,   140,    74,   121,   124,   116,   117,   118,   119,   120,
     177,    74,    69,    69,    26,   121,    27,    56,    84,   181,
      56,   158,   187,    74,   151,   151,   137,   175,   -21,   -21,
     -21,   193,   229,    12,   101,   125,   157,    83,   -21,   -21,
     -21,   -21,   -21,   -21,   -21,    13,    56,   -21,   200,   -21,
     -21,   -21,   178,   230,   -21,   -46,   108,   178,    56,    56,
     217,   219,   196,   -21,   179,   236,   -21,   -21,    74,   216,
     -21,    56,    83,   227,   -21,   -21,   107,   109,   -21,     1,
     123,     2,     3,     4,    56,   152,   200,     2,     3,     4,
     206,     5,    56,   208,   241,   211,   139,   -53,   -53,   -53,
     -53,   -53,   149,   -53,   103,    35,   -53,    25,   -53,   -53,
     -53,    23,   225,   -53,   -27,    24,    34,   143,   233,   235,
     144,    26,   -53,    36,   145,   -53,   -53,   159,   105,   -53,
       2,     3,     4,   -53,   -53,   185,    75,   -53,    76,    38,
      39,    40,    41,    42,    26,   160,   176,    26,   161,   189,
     162,   163,    43,    -7,    12,   164,    -7,    -7,    -7,    95,
      96,    97,   188,    83,    44,   197,    13,    45,    46,   159,
     190,    47,     2,     3,     4,   103,   165,   194,    83,   166,
     231,    38,    39,    40,    41,    42,   214,   201,   220,   222,
     202,   221,   162,   163,    43,    -2,     1,   203,     2,     3,
       4,   228,   242,   243,   244,    19,    44,    64,     5,    45,
      46,   159,   153,    47,   106,    73,   141,   103,   237,   128,
     126,   166,   134,    38,    39,    40,    41,    42,   110,   160,
     132,     0,   161,     0,   162,   163,    43,     0,     0,   164,
      38,    39,    40,    41,    42,     0,     0,     0,    44,     0,
       0,    45,    46,    43,     0,    47,     0,     0,     0,   103,
       0,     0,    37,   166,     0,    44,     0,    77,    45,    46,
       0,     0,    47,  -126,    38,    39,    40,    41,    42,    38,
      39,    40,    41,    42,     0,     0,     0,    43,     0,     0,
       0,     0,    43,     0,     0,     0,     0,     0,     0,    44,
      79,     0,    45,    46,    44,   110,    47,    45,    46,     0,
       0,    47,    38,    39,    40,    41,    42,    38,    39,    40,
      41,    42,     0,     0,     0,    43,     0,     0,     0,     0,
      43,     0,     0,     0,     0,     0,     0,    44,   127,     0,
      45,    46,    44,   129,    47,    45,    46,     0,     0,    47,
      38,    39,    40,    41,    42,    38,    39,    40,    41,    42,
       0,     0,     0,    43,     0,     0,     0,     0,    43,     0,
       0,     0,     0,     0,     0,    44,   147,     0,    45,    46,
      44,   155,    47,    45,    46,     0,     0,    47,    38,    39,
      40,    41,    42,    38,    39,    40,    41,    42,     0,     0,
       0,    43,     0,     0,     0,     0,    43,     0,     0,     0,
       0,     0,     0,    44,   180,     0,    45,    46,    44,   186,
      47,    45,    46,     0,     0,    47,    38,    39,    40,    41,
      42,    38,    39,    40,    41,    42,     0,     0,     0,    43,
       0,     0,     0,     0,    43,     0,     0,     0,     0,     0,
       0,    44,   198,     0,    45,    46,    44,   218,    47,    45,
      46,     0,     0,    47,    38,    39,    40,    41,    42,    38,
      39,    40,    41,    42,     0,     0,     0,    43,     0,     0,
       0,     0,    43,     0,     0,     0,     0,     0,     0,    44,
     226,     0,    45,    46,    44,   240,    47,    45,    46,     0,
       0,    47,    38,    39,    40,    41,    42,    38,    39,    40,
      41,    42,     0,     0,     0,    43,     0,     0,     0,     0,
      43,     0,     0,     0,     0,     0,     0,    44,    99,     0,
      45,    46,    44,   131,    47,    45,    46,     0,   133,    47,
      38,    39,    40,    41,    42,    38,    39,    40,    41,    42,
      38,    39,    40,    41,    42,     0,     0,    85,    86,    87,
      88,    89,    90,     0,     0,    44,    91,    92,    45,    46,
      44,   135,    47,    45,    46,    44,     0,    47,    45,    46,
       0,     0,    47,    38,    39,    40,    41,    42,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    44,     0,
       0,    45,    46,     0,     0,    47
};

static const yytype_int16 yycheck[] =
{
      24,    11,    24,    47,    28,     1,    28,     0,    66,    59,
      21,    43,    23,   154,     7,    40,    41,    20,     1,    43,
       3,     4,     5,    23,     1,    28,     1,     1,     3,     4,
       5,    75,    76,    45,    45,    59,    13,    14,    15,    16,
      17,    15,     3,     4,     5,    45,     1,     0,    98,    26,
     191,   109,    84,    49,   195,   196,   197,    18,    13,    83,
      84,    38,    47,    46,    41,    42,    30,    46,    45,    93,
      94,    46,   213,   214,    98,    39,    53,    53,   122,   220,
     221,    45,   126,     6,     7,     8,     9,    10,    11,   230,
     231,    45,     6,     7,     8,     9,    10,    11,     1,    28,
     144,   242,   243,   244,     6,     7,     8,     9,    10,    11,
      13,    23,    46,    48,    37,    52,    28,    52,   162,    53,
       1,     1,    45,    37,     6,     7,     8,     9,    10,    11,
      53,    45,    13,    13,    51,    37,    53,   161,    27,   161,
     164,   151,   164,    45,   137,   138,     1,   157,     3,     4,
       5,    53,    23,     1,    48,    37,   149,    28,    13,    14,
      15,    16,    17,    18,    19,    13,   190,    22,   190,    24,
      25,    26,     1,    30,    29,    51,    51,     1,   202,   203,
     202,   203,    39,    38,    13,    21,    41,    42,    45,    13,
      45,   215,    28,   215,    49,    50,    47,    46,    53,     1,
      46,     3,     4,     5,   228,     1,   228,     3,     4,     5,
     192,    13,   236,   195,   236,   197,    48,    13,    14,    15,
      16,    17,    18,    19,    49,    45,    22,    47,    24,    25,
      26,    48,   214,    29,    51,    52,    53,    46,   220,   221,
      51,    51,    38,    53,    48,    41,    42,     1,     1,    45,
       3,     4,     5,    49,    50,    53,    45,    53,    47,    13,
      14,    15,    16,    17,    51,    19,    53,    51,    22,    53,
      24,    25,    26,     0,     1,    29,     3,     4,     5,    42,
      43,    44,    53,    28,    38,    30,    13,    41,    42,     1,
      11,    45,     3,     4,     5,    49,    50,    53,    28,    53,
      30,    13,    14,    15,    16,    17,    23,    19,    39,     1,
      22,    39,    24,    25,    26,     0,     1,    29,     3,     4,
       5,    11,    23,    39,    39,     7,    38,    26,    13,    41,
      42,     1,   138,    45,    67,    35,   108,    49,   228,    83,
      82,    53,    94,    13,    14,    15,    16,    17,     1,    19,
      93,    -1,    22,    -1,    24,    25,    26,    -1,    -1,    29,
      13,    14,    15,    16,    17,    -1,    -1,    -1,    38,    -1,
      -1,    41,    42,    26,    -1,    45,    -1,    -1,    -1,    49,
      -1,    -1,     1,    53,    -1,    38,    -1,     1,    41,    42,
      -1,    -1,    45,    46,    13,    14,    15,    16,    17,    13,
      14,    15,    16,    17,    -1,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    38,
       1,    -1,    41,    42,    38,     1,    45,    41,    42,    -1,
      -1,    45,    13,    14,    15,    16,    17,    13,    14,    15,
      16,    17,    -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    38,     1,    -1,
      41,    42,    38,     1,    45,    41,    42,    -1,    -1,    45,
      13,    14,    15,    16,    17,    13,    14,    15,    16,    17,
      -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    38,     1,    -1,    41,    42,
      38,     1,    45,    41,    42,    -1,    -1,    45,    13,    14,
      15,    16,    17,    13,    14,    15,    16,    17,    -1,    -1,
      -1,    26,    -1,    -1,    -1,    -1,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    38,     1,    -1,    41,    42,    38,     1,
      45,    41,    42,    -1,    -1,    45,    13,    14,    15,    16,
      17,    13,    14,    15,    16,    17,    -1,    -1,    -1,    26,
      -1,    -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    38,     1,    -1,    41,    42,    38,     1,    45,    41,
      42,    -1,    -1,    45,    13,    14,    15,    16,    17,    13,
      14,    15,    16,    17,    -1,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    38,
       1,    -1,    41,    42,    38,     1,    45,    41,    42,    -1,
      -1,    45,    13,    14,    15,    16,    17,    13,    14,    15,
      16,    17,    -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    38,     1,    -1,
      41,    42,    38,     1,    45,    41,    42,    -1,     1,    45,
      13,    14,    15,    16,    17,    13,    14,    15,    16,    17,
      13,    14,    15,    16,    17,    -1,    -1,    31,    32,    33,
      34,    35,    36,    -1,    -1,    38,    40,    41,    41,    42,
      38,     1,    45,    41,    42,    38,    -1,    45,    41,    42,
      -1,    -1,    45,    13,    14,    15,    16,    17,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,
      -1,    41,    42,    -1,    -1,    45
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     3,     4,     5,    13,    55,    56,    57,    58,
      59,    71,     1,    13,    63,    64,    65,    45,     0,    57,
       1,    13,    63,    48,    52,    47,    51,    53,    52,     1,
      66,    67,    68,    71,    53,    45,    53,     1,    13,    14,
      15,    16,    17,    26,    38,    41,    42,    45,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    97,
      99,     1,    15,     1,    64,    79,    46,    53,     1,    13,
      69,    70,     1,    66,    45,    45,    47,     1,    81,     1,
      78,    79,    87,    28,    27,    31,    32,    33,    34,    35,
      36,    40,    41,    96,    98,    42,    43,    44,    95,     1,
      85,    48,     1,    49,    60,     1,    68,    47,    51,    46,
       1,    78,    90,    91,    78,     6,     7,     8,     9,    10,
      11,    37,    94,    46,     6,    37,    94,     1,    80,     1,
      81,     1,    84,     1,    83,     1,    85,     1,    61,    48,
       1,    70,    60,    46,    51,    48,    78,     1,    78,    18,
      62,    71,     1,    62,    72,     1,    78,    71,    63,     1,
      19,    22,    24,    25,    29,    50,    53,    60,    73,    74,
      75,    77,    78,    92,    93,    63,    53,    53,     1,    13,
       1,    79,     1,    53,    78,    53,     1,    79,    53,    53,
      11,    23,    23,    53,    53,    30,    39,    30,     1,    76,
      79,    19,    22,    29,    74,    74,    75,    74,    75,    74,
      74,    75,    21,    23,    23,    20,    13,    79,     1,    79,
      39,    39,     1,    74,    74,    75,     1,    79,    11,    23,
      30,    30,    74,    75,    74,    75,    21,    76,    74,    74,
       1,    79,    23,    39,    39
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    54,    55,    56,    56,    57,    57,    57,    58,    58,
      58,    58,    59,    59,    59,    59,    59,    60,    61,    61,
      61,    61,    62,    62,    63,    63,    63,    63,    64,    64,
      64,    65,    65,    65,    65,    66,    66,    67,    67,    67,
      67,    68,    68,    69,    69,    69,    69,    70,    70,    71,
      71,    71,    72,    72,    73,    73,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      75,    75,    75,    75,    75,    75,    75,    75,    76,    76,
      76,    76,    76,    77,    77,    77,    78,    78,    78,    78,
      78,    78,    78,    78,    79,    79,    79,    80,    80,    80,
      81,    81,    81,    82,    82,    82,    83,    83,    83,    84,
      84,    84,    85,    85,    85,    86,    86,    87,    87,    88,
      88,    88,    88,    89,    89,    90,    90,    91,    91,    91,
      92,    92,    92,    93,    94,    94,    94,    94,    94,    95,
      95,    95,    96,    96,    97,    97,    97,    98,    98,    98,
      98,    98,    98,    99,    99,    99,    99
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     2,     3,
       3,     3,     6,     5,     2,     4,     5,     4,     2,     2,
       2,     0,     4,     3,     3,     3,     1,     1,     3,     3,
       1,     4,     3,     2,     1,     1,     0,     3,     1,     3,
       1,     2,     2,     3,     1,     3,     1,     1,     3,     1,
       1,     1,     2,     0,     1,     1,     2,     4,     6,     6,
       4,     2,     4,     6,     6,     2,     1,     1,     1,     1,
       4,     4,     4,     4,     6,     6,     4,     6,     3,     3,
       3,     5,     5,     2,     1,     2,     3,     3,     3,     2,
       2,     2,     2,     1,     3,     3,     1,     3,     3,     1,
       2,     2,     1,     3,     1,     3,     3,     3,     1,     3,
       3,     1,     2,     2,     1,     1,     1,     1,     4,     3,
       2,     1,     1,     4,     2,     1,     0,     3,     1,     3,
       2,     3,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
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
#  endif
# endif

# ifndef yytnamerr
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
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
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
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
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
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 49 "parser.y"
                  { treeRec = (yyvsp[0].treeNode); /*save tree for traversal and print*/}
#line 1662 "parser.tab.c"
    break;

  case 3:
#line 52 "parser.y"
                      {ASTreeNode* l = (yyvsp[-1].treeNode);
                          if(l != NULL)
                          {
                            while(l->sibling != NULL) // traverse as far right as possible
                            {
                              l = l->sibling;
                            }
                            l->sibling = (yyvsp[0].treeNode);
                            (yyval.treeNode) = (yyvsp[-1].treeNode);
                          }else (yyval.treeNode) = (yyvsp[0].treeNode);
                      }
#line 1678 "parser.tab.c"
    break;

  case 4:
#line 63 "parser.y"
                      {(yyval.treeNode) = (yyvsp[0].treeNode);}
#line 1684 "parser.tab.c"
    break;

  case 5:
#line 66 "parser.y"
              {(yyval.treeNode) = (yyvsp[0].treeNode);}
#line 1690 "parser.tab.c"
    break;

  case 6:
#line 67 "parser.y"
              {(yyval.treeNode) = (yyvsp[0].treeNode);}
#line 1696 "parser.tab.c"
    break;

  case 7:
#line 68 "parser.y"
              { (yyval.treeNode) = NULL;}
#line 1702 "parser.tab.c"
    break;

  case 8:
#line 72 "parser.y"
                                  {
                                    ASTreeNode* l = (yyvsp[0].treeNode);
                                    while(l != NULL)
                                    {
                                      l->type = (yyvsp[-1].treeNode)->type;
                                      if(l->children[0] != NULL && l->children[0]->subkind.exp == InitK) l->children[0]->type = (yyvsp[-1].treeNode)->type;
                                      l = l->sibling;
                                    }

                                    (yyval.treeNode) = (yyvsp[0].treeNode);
                                  }
#line 1718 "parser.tab.c"
    break;

  case 9:
#line 83 "parser.y"
                                  {
                                    ASTreeNode* l = (yyvsp[-1].treeNode);
                                    while(l != NULL)
                                    {
                                        //std::cout << "\t" << l->attrib.name << " gets type " << typeToStr($1->type) << std::endl;
                                      l->type = (yyvsp[-2].treeNode)->type;
                                      if(l->children[0] != NULL && l->children[0]->subkind.exp == InitK) l->children[0]->type = (yyvsp[-2].treeNode)->type;
                                      l = l->sibling;
                                    }

                                    (yyval.treeNode) = (yyvsp[-1].treeNode);
                                    yyerrok;
                                  }
#line 1736 "parser.tab.c"
    break;

  case 10:
#line 96 "parser.y"
                                   { (yyval.treeNode) = NULL; yyerrok; }
#line 1742 "parser.tab.c"
    break;

  case 11:
#line 97 "parser.y"
                             { (yyval.treeNode) = NULL; yyerrok; yyerrok; }
#line 1748 "parser.tab.c"
    break;

  case 12:
#line 100 "parser.y"
                                              {
                                                (yyval.treeNode) = createDeclNode(FuncK, (yyvsp[-5].treeNode)->type, (yyvsp[-4].tokenData)->token_str, (yyvsp[-4].tokenData)->linenum, (yyvsp[-2].treeNode), (yyvsp[0].treeNode), NULL);
                                                (yyvsp[0].treeNode)->attrib.name = (yyvsp[-4].tokenData)->token_str;  // save name for scope creation
                                              }
#line 1757 "parser.tab.c"
    break;

  case 13:
#line 104 "parser.y"
                                              {
                                                (yyval.treeNode) = createDeclNode(FuncK, Void, (yyvsp[-4].tokenData)->token_str, (yyvsp[-4].tokenData)->linenum, (yyvsp[-2].treeNode), (yyvsp[0].treeNode), NULL);
                                                (yyvsp[0].treeNode)->attrib.name = (yyvsp[-4].tokenData)->token_str;  // save name for scope creation
                                              }
#line 1766 "parser.tab.c"
    break;

  case 14:
#line 108 "parser.y"
                                              { (yyval.treeNode) = NULL; }
#line 1772 "parser.tab.c"
    break;

  case 15:
#line 109 "parser.y"
                                              { (yyval.treeNode) = NULL; }
#line 1778 "parser.tab.c"
    break;

  case 16:
#line 110 "parser.y"
                                              { (yyval.treeNode) = NULL; }
#line 1784 "parser.tab.c"
    break;

  case 17:
#line 113 "parser.y"
                                           {
                                              (yyval.treeNode) = createStmtNode(CompoundK, "", (yyvsp[-3].tokenData)->linenum, (yyvsp[-2].treeNode), (yyvsp[-1].treeNode), NULL);
                                              (yyval.treeNode)->attrib.name = strdup("comp scope");
                                              yyerrok;
                                            }
#line 1794 "parser.tab.c"
    break;

  case 18:
#line 119 "parser.y"
                                  {
                                    ASTreeNode* l = (yyvsp[-1].treeNode);
                                    if(l != NULL)
                                    {
                                      while(l->sibling != NULL)
                                      {
                                          l = l->sibling;
                                      }

                                      l->sibling = (yyvsp[0].treeNode); // scopedVarDec is the final sibling
                                      (yyval.treeNode) = (yyvsp[-1].treeNode);
                                    }else{
                                      (yyval.treeNode) = (yyvsp[0].treeNode);
                                    }
                                  }
#line 1814 "parser.tab.c"
    break;

  case 19:
#line 134 "parser.y"
                                  {(yyval.treeNode) = NULL;}
#line 1820 "parser.tab.c"
    break;

  case 20:
#line 135 "parser.y"
                                  {(yyval.treeNode) = NULL;}
#line 1826 "parser.tab.c"
    break;

  case 21:
#line 136 "parser.y"
                                  {(yyval.treeNode) = NULL;}
#line 1832 "parser.tab.c"
    break;

  case 22:
#line 139 "parser.y"
                                                {
                                                  (yyval.treeNode) = (yyvsp[-1].treeNode);
                                                  ASTreeNode* l = (yyvsp[-1].treeNode);;
                                                  while(l != NULL)
                                                  {
                                                      //std::cout << "\t" << l->attrib.name << " gets type" << std::endl;
                                                    l->type = (yyvsp[-2].treeNode)->type;
                                                    if(l->children[0] != NULL && l->children[0]->subkind.exp == InitK) l->children[0]->type = (yyvsp[-2].treeNode)->type;
                                                    l->isStatic = true;
                                                    l = l->sibling;
                                                  }
                                                  yyerrok;
                                                }
#line 1850 "parser.tab.c"
    break;

  case 23:
#line 152 "parser.y"
                                                {
                                                  (yyval.treeNode) = (yyvsp[-1].treeNode);
                                                  //std::cout << "passing type " << typeToStr($1->type) << " to variables on line " << $1->linenum << std::endl;
                                                  ASTreeNode* l = (yyvsp[-1].treeNode);
                                                  while(l != NULL)
                                                  {
                                                    //std::cout << "\t" << l->attrib.name << " gets type" << std::endl;
                                                    l->type = (yyvsp[-2].treeNode)->type;
                                                    if(l->children[0] != NULL && l->children[0]->subkind.exp == InitK) l->children[0]->type = (yyvsp[-2].treeNode)->type;
                                                    l = l->sibling;
                                                  }
                                                  yyerrok;
                                                }
#line 1868 "parser.tab.c"
    break;

  case 24:
#line 167 "parser.y"
                                        {
                                          if((yyvsp[-2].treeNode) != NULL){ASTreeNode* l = (yyvsp[-2].treeNode);
                                          while(l->sibling != NULL)
                                            l = l->sibling;

                                          l->sibling = (yyvsp[0].treeNode);
                                          (yyval.treeNode) = (yyvsp[-2].treeNode);}
                                          yyerrok;
                                        }
#line 1882 "parser.tab.c"
    break;

  case 25:
#line 176 "parser.y"
                                        { (yyval.treeNode) = NULL; }
#line 1888 "parser.tab.c"
    break;

  case 26:
#line 177 "parser.y"
                                        { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1894 "parser.tab.c"
    break;

  case 27:
#line 178 "parser.y"
                                        { (yyval.treeNode) = NULL; }
#line 1900 "parser.tab.c"
    break;

  case 28:
#line 181 "parser.y"
                                      {
                                            (yyval.treeNode) = (yyvsp[-2].treeNode);
                                            if((yyvsp[0].treeNode) != NULL){
                                                (yyval.treeNode)->children[0] = (yyvsp[0].treeNode);
                                                (yyval.treeNode)->isInitialized = true;
                                                //$3->subkind.exp = InitK;
                                                (yyval.treeNode)->hasInit = true;
                                            }
                                      }
#line 1914 "parser.tab.c"
    break;

  case 29:
#line 190 "parser.y"
                                      { (yyval.treeNode) = NULL; yyerrok; }
#line 1920 "parser.tab.c"
    break;

  case 30:
#line 191 "parser.y"
                                      {
                                        (yyval.treeNode) = (yyvsp[0].treeNode);
                                      }
#line 1928 "parser.tab.c"
    break;

  case 31:
#line 195 "parser.y"
                                        {
                                          (yyval.treeNode) = createDeclNode(VarK, UndefinedType, (yyvsp[-3].tokenData)->token_str, (yyvsp[-3].tokenData)->linenum, NULL, NULL, NULL);
                                          (yyval.treeNode)->isArray = true;
                                          (yyval.treeNode)->size = (yyvsp[-1].tokenData)->numValue + 1; // arrays should be size + 1 in length with first element holding size
                                        }
#line 1938 "parser.tab.c"
    break;

  case 32:
#line 200 "parser.y"
                                        { (yyval.treeNode) = NULL; }
#line 1944 "parser.tab.c"
    break;

  case 33:
#line 201 "parser.y"
                                        { (yyval.treeNode) = NULL; yyerrok; }
#line 1950 "parser.tab.c"
    break;

  case 34:
#line 202 "parser.y"
                                        {
                                          (yyval.treeNode) = createDeclNode(VarK, UndefinedType, (yyvsp[0].tokenData)->token_str, (yyvsp[0].tokenData)->linenum, NULL, NULL, NULL);
                                          (yyval.treeNode)->size = 1;
                                        }
#line 1959 "parser.tab.c"
    break;

  case 35:
#line 208 "parser.y"
                    {(yyval.treeNode) = (yyvsp[0].treeNode);}
#line 1965 "parser.tab.c"
    break;

  case 36:
#line 209 "parser.y"
                    {(yyval.treeNode) = NULL;}
#line 1971 "parser.tab.c"
    break;

  case 37:
#line 212 "parser.y"
                                              {
                                                (yyval.treeNode) = (yyvsp[-2].treeNode);
                                                if((yyvsp[-2].treeNode) != NULL){ASTreeNode* l = (yyvsp[-2].treeNode);
                                                while(l->sibling != NULL)
                                                {
                                                  l = l->sibling;
                                                  if(l->isArray) l->size = 1; // arrays are passed by reference so 1 word in size
                                                }

                                                l->sibling = (yyvsp[0].treeNode);}
                                              }
#line 1987 "parser.tab.c"
    break;

  case 38:
#line 223 "parser.y"
                                              {(yyval.treeNode) = (yyvsp[0].treeNode);}
#line 1993 "parser.tab.c"
    break;

  case 39:
#line 224 "parser.y"
                                              { (yyval.treeNode) = NULL; }
#line 1999 "parser.tab.c"
    break;

  case 40:
#line 225 "parser.y"
                                              { (yyval.treeNode) = NULL; }
#line 2005 "parser.tab.c"
    break;

  case 41:
#line 228 "parser.y"
                                {
                                  (yyval.treeNode) = (yyvsp[0].treeNode);
                                  ASTreeNode* l = (yyvsp[0].treeNode);
                                  while(l != NULL)
                                  {
                                      //std::cout << "\t" << l->attrib.name << " gets type" << typeToStr(l->type) << std::endl;
                                    l->type = (yyvsp[-1].treeNode)->type;
                                    l->size = 1;
                                    l = l->sibling;
                                  }
                                }
#line 2021 "parser.tab.c"
    break;

  case 42:
#line 239 "parser.y"
                                { (yyval.treeNode) = NULL; }
#line 2027 "parser.tab.c"
    break;

  case 43:
#line 242 "parser.y"
                                        {
                                          (yyval.treeNode) = (yyvsp[-2].treeNode);
                                          if((yyvsp[-2].treeNode) != NULL){ASTreeNode* l = (yyvsp[-2].treeNode);
                                          while(l->sibling != NULL){
                                            l = l->sibling;
                                          }

                                          l->sibling = (yyvsp[0].treeNode);}
                                          yyerrok;
                                        }
#line 2042 "parser.tab.c"
    break;

  case 44:
#line 252 "parser.y"
                                        { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2048 "parser.tab.c"
    break;

  case 45:
#line 253 "parser.y"
                                        { (yyval.treeNode) = NULL; }
#line 2054 "parser.tab.c"
    break;

  case 46:
#line 254 "parser.y"
                                        { (yyval.treeNode) = NULL; }
#line 2060 "parser.tab.c"
    break;

  case 47:
#line 257 "parser.y"
                                {
                                  (yyval.treeNode) = createDeclNode(ParamK, UndefinedType, (yyvsp[0].tokenData)->token_str, (yyvsp[0].tokenData)->linenum, NULL, NULL, NULL);
                                }
#line 2068 "parser.tab.c"
    break;

  case 48:
#line 260 "parser.y"
                                {
                                  (yyval.treeNode) = createDeclNode(ParamK, UndefinedType, (yyvsp[-2].tokenData)->token_str, (yyvsp[-2].tokenData)->linenum, NULL, NULL, NULL);
                                  (yyval.treeNode)->isArray = true;
                                }
#line 2077 "parser.tab.c"
    break;

  case 49:
#line 266 "parser.y"
            {
              (yyval.treeNode) = tokenToNode((yyvsp[0].tokenData));
              (yyval.treeNode)->type = Boolean;
            }
#line 2086 "parser.tab.c"
    break;

  case 50:
#line 270 "parser.y"
            {
              (yyval.treeNode) = tokenToNode((yyvsp[0].tokenData));
              (yyval.treeNode)->type = Char;
            }
#line 2095 "parser.tab.c"
    break;

  case 51:
#line 274 "parser.y"
            {
              (yyval.treeNode) = tokenToNode((yyvsp[0].tokenData));
              (yyval.treeNode)->type = Integer;
            }
#line 2104 "parser.tab.c"
    break;

  case 52:
#line 280 "parser.y"
                          {
                            ASTreeNode* l = (yyvsp[-1].treeNode);
                            if(l != NULL)
                            {
                              while(l->sibling != NULL)
                              {
                                l = l->sibling;
                              }

                              l->sibling = (yyvsp[0].treeNode);
                              (yyval.treeNode) = (yyvsp[-1].treeNode);
                            }else (yyval.treeNode) = (yyvsp[0].treeNode);
                          }
#line 2122 "parser.tab.c"
    break;

  case 53:
#line 293 "parser.y"
                          {(yyval.treeNode) = NULL;}
#line 2128 "parser.tab.c"
    break;

  case 54:
#line 296 "parser.y"
                {(yyval.treeNode) = (yyvsp[0].treeNode);}
#line 2134 "parser.tab.c"
    break;

  case 55:
#line 297 "parser.y"
                  {(yyval.treeNode) = (yyvsp[0].treeNode);}
#line 2140 "parser.tab.c"
    break;

  case 56:
#line 300 "parser.y"
                                                      { (yyval.treeNode) = NULL; }
#line 2146 "parser.tab.c"
    break;

  case 57:
#line 301 "parser.y"
                                                      { (yyval.treeNode) = NULL; yyerrok; }
#line 2152 "parser.tab.c"
    break;

  case 58:
#line 302 "parser.y"
                                                      { (yyval.treeNode) = NULL; yyerrok; }
#line 2158 "parser.tab.c"
    break;

  case 59:
#line 303 "parser.y"
                                                      {
                                                        (yyval.treeNode) = createStmtNode(IfK, "if", (yyvsp[-5].tokenData)->linenum, (yyvsp[-4].treeNode), (yyvsp[-2].treeNode), (yyvsp[0].treeNode));
                                                      }
#line 2166 "parser.tab.c"
    break;

  case 60:
#line 306 "parser.y"
                                                      { (yyval.treeNode) = NULL; yyerrok; }
#line 2172 "parser.tab.c"
    break;

  case 61:
#line 307 "parser.y"
                                                      { (yyval.treeNode) = NULL; }
#line 2178 "parser.tab.c"
    break;

  case 62:
#line 308 "parser.y"
                                                      {
                                                        (yyval.treeNode) = createStmtNode(WhileK, "", (yyvsp[-3].tokenData)->linenum, (yyvsp[-2].treeNode), (yyvsp[0].treeNode), NULL);
                                                      }
#line 2186 "parser.tab.c"
    break;

  case 63:
#line 311 "parser.y"
                                                      { (yyval.treeNode) = NULL; yyerrok; }
#line 2192 "parser.tab.c"
    break;

  case 64:
#line 312 "parser.y"
                                                      {
                                                        ASTreeNode* n = tokenToNode((yyvsp[-4].tokenData));
                                                        n->nodekind = DeclK;
                                                        n->subkind.decl = VarK;
                                                        n->type = Integer;
                                                        n->isInitialized = true;
                                                        n->size = 1;
                                                        (yyval.treeNode) = createStmtNode(ForK, "", (yyvsp[-5].tokenData)->linenum, n, (yyvsp[-2].treeNode), (yyvsp[0].treeNode));
                                                      }
#line 2206 "parser.tab.c"
    break;

  case 65:
#line 321 "parser.y"
                                                      { (yyval.treeNode) = NULL; }
#line 2212 "parser.tab.c"
    break;

  case 66:
#line 322 "parser.y"
                                                      {(yyval.treeNode) = (yyvsp[0].treeNode);}
#line 2218 "parser.tab.c"
    break;

  case 67:
#line 323 "parser.y"
                                                      {(yyval.treeNode) = (yyvsp[0].treeNode);}
#line 2224 "parser.tab.c"
    break;

  case 68:
#line 324 "parser.y"
                                                      {(yyval.treeNode) = (yyvsp[0].treeNode);}
#line 2230 "parser.tab.c"
    break;

  case 69:
#line 325 "parser.y"
                                                      {
                                                          (yyval.treeNode) = (yyvsp[0].treeNode);
                                                          //$$->attrib.name = strdup("matchedif scope");
                                                      }
#line 2239 "parser.tab.c"
    break;

  case 70:
#line 331 "parser.y"
                                                            { (yyval.treeNode) = NULL; yyerrok; }
#line 2245 "parser.tab.c"
    break;

  case 71:
#line 332 "parser.y"
                                                            {
                                                              (yyval.treeNode) = createStmtNode(IfK, "if", (yyvsp[-3].tokenData)->linenum, (yyvsp[-2].treeNode), (yyvsp[0].treeNode), NULL);
                                                            }
#line 2253 "parser.tab.c"
    break;

  case 72:
#line 335 "parser.y"
                                                            { (yyval.treeNode) = NULL; yyerrok; }
#line 2259 "parser.tab.c"
    break;

  case 73:
#line 336 "parser.y"
                                                            {
                                                              (yyval.treeNode) = createStmtNode(IfK, "if", (yyvsp[-3].tokenData)->linenum, (yyvsp[-2].treeNode), (yyvsp[0].treeNode), NULL);
                                                            }
#line 2267 "parser.tab.c"
    break;

  case 74:
#line 339 "parser.y"
                                                            { (yyval.treeNode) = NULL; yyerrok; }
#line 2273 "parser.tab.c"
    break;

  case 75:
#line 340 "parser.y"
                                                            {
                                                              (yyval.treeNode) = createStmtNode(IfK, "if", (yyvsp[-5].tokenData)->linenum, (yyvsp[-4].treeNode), (yyvsp[-2].treeNode), (yyvsp[0].treeNode));
                                                            }
#line 2281 "parser.tab.c"
    break;

  case 76:
#line 343 "parser.y"
                                                            {
                                                              (yyval.treeNode) = createStmtNode(WhileK, "", (yyvsp[-3].tokenData)->linenum, (yyvsp[-2].treeNode), (yyvsp[0].treeNode), NULL);
                                                            }
#line 2289 "parser.tab.c"
    break;

  case 77:
#line 346 "parser.y"
                                                            {
                                                              ASTreeNode* n = tokenToNode((yyvsp[-4].tokenData));
                                                              n->nodekind = DeclK;
                                                              n->subkind.decl = VarK;
                                                              n->type = Integer;
                                                              n->isInitialized = true;
                                                              n->size = 1;
                                                              (yyval.treeNode) = createStmtNode(ForK, "", (yyvsp[-5].tokenData)->linenum, n, (yyvsp[-2].treeNode), (yyvsp[0].treeNode));
                                                            }
#line 2303 "parser.tab.c"
    break;

  case 78:
#line 357 "parser.y"
                                                { (yyval.treeNode) = NULL; }
#line 2309 "parser.tab.c"
    break;

  case 79:
#line 358 "parser.y"
                                                { (yyval.treeNode) = NULL; yyerrok; }
#line 2315 "parser.tab.c"
    break;

  case 80:
#line 359 "parser.y"
                                                {
                                                  (yyval.treeNode) = createStmtNode(RangeK, "", (yyvsp[-1].tokenData)->linenum, (yyvsp[-2].treeNode), (yyvsp[0].treeNode), NULL);
                                                }
#line 2323 "parser.tab.c"
    break;

  case 81:
#line 362 "parser.y"
                                                {
                                                  (yyval.treeNode) = createStmtNode(RangeK, "", (yyvsp[-3].tokenData)->linenum, (yyvsp[-4].treeNode), (yyvsp[-2].treeNode), (yyvsp[0].treeNode));
                                                }
#line 2331 "parser.tab.c"
    break;

  case 82:
#line 365 "parser.y"
                                                { (yyval.treeNode) = NULL; }
#line 2337 "parser.tab.c"
    break;

  case 83:
#line 368 "parser.y"
                          {(yyval.treeNode) = (yyvsp[-1].treeNode);}
#line 2343 "parser.tab.c"
    break;

  case 84:
#line 369 "parser.y"
                          {(yyval.treeNode) = NULL;}
#line 2349 "parser.tab.c"
    break;

  case 85:
#line 370 "parser.y"
                          { (yyval.treeNode) = NULL; yyerrok; }
#line 2355 "parser.tab.c"
    break;

  case 86:
#line 373 "parser.y"
                            { (yyval.treeNode) = NULL; yyerrok; }
#line 2361 "parser.tab.c"
    break;

  case 87:
#line 374 "parser.y"
                            {
                              (yyval.treeNode) = (yyvsp[-1].treeNode);
                              (yyval.treeNode)->children[0] = (yyvsp[-2].treeNode);
                              (yyval.treeNode)->children[1] = (yyvsp[0].treeNode);
                            }
#line 2371 "parser.tab.c"
    break;

  case 88:
#line 379 "parser.y"
                             { (yyval.treeNode) = NULL; }
#line 2377 "parser.tab.c"
    break;

  case 89:
#line 380 "parser.y"
                            {
                              (yyval.treeNode) = tokenToNode((yyvsp[0].tokenData));
                              (yyval.treeNode)->nodekind = ExpK;
                              (yyval.treeNode)->subkind.exp = AssignK;
                              (yyval.treeNode)->children[0] = (yyvsp[-1].treeNode);
                            }
#line 2388 "parser.tab.c"
    break;

  case 90:
#line 386 "parser.y"
                            { (yyval.treeNode) = NULL; yyerrok; }
#line 2394 "parser.tab.c"
    break;

  case 91:
#line 387 "parser.y"
                            {
                              (yyval.treeNode) = tokenToNode((yyvsp[0].tokenData));
                              (yyval.treeNode)->nodekind = ExpK;
                              (yyval.treeNode)->subkind.exp = AssignK;
                              (yyval.treeNode)->children[0] = (yyvsp[-1].treeNode);
                            }
#line 2405 "parser.tab.c"
    break;

  case 92:
#line 393 "parser.y"
                            { (yyval.treeNode) = NULL; yyerrok; }
#line 2411 "parser.tab.c"
    break;

  case 93:
#line 394 "parser.y"
                            { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2417 "parser.tab.c"
    break;

  case 94:
#line 397 "parser.y"
                                { (yyval.treeNode) = NULL; }
#line 2423 "parser.tab.c"
    break;

  case 95:
#line 398 "parser.y"
                                {
                                  (yyval.treeNode) = createOpNode((yyvsp[-1].tokenData)->token_str, (yyvsp[-1].tokenData)->linenum, (yyvsp[-2].treeNode), (yyvsp[0].treeNode), NULL);
                                }
#line 2431 "parser.tab.c"
    break;

  case 96:
#line 401 "parser.y"
                                {(yyval.treeNode) = (yyvsp[0].treeNode);}
#line 2437 "parser.tab.c"
    break;

  case 97:
#line 404 "parser.y"
                                { (yyval.treeNode) = NULL; }
#line 2443 "parser.tab.c"
    break;

  case 98:
#line 405 "parser.y"
                                {
                                  (yyval.treeNode) = createOpNode((yyvsp[-1].tokenData)->token_str, (yyvsp[-1].tokenData)->linenum, (yyvsp[-2].treeNode), (yyvsp[0].treeNode), NULL);
                                }
#line 2451 "parser.tab.c"
    break;

  case 99:
#line 408 "parser.y"
                                {(yyval.treeNode) = (yyvsp[0].treeNode);}
#line 2457 "parser.tab.c"
    break;

  case 100:
#line 411 "parser.y"
                              { (yyval.treeNode) = NULL; }
#line 2463 "parser.tab.c"
    break;

  case 101:
#line 412 "parser.y"
                              {
                                (yyval.treeNode) = createOpNode((yyvsp[-1].tokenData)->token_str, (yyvsp[0].treeNode)->linenum, (yyvsp[0].treeNode), NULL, NULL);
                              }
#line 2471 "parser.tab.c"
    break;

  case 102:
#line 415 "parser.y"
                              {(yyval.treeNode) = (yyvsp[0].treeNode);}
#line 2477 "parser.tab.c"
    break;

  case 103:
#line 418 "parser.y"
                            {
                              (yyval.treeNode) = createOpNode((yyvsp[-1].tokenData)->token_str, (yyvsp[-1].tokenData)->linenum, (yyvsp[-2].treeNode), (yyvsp[0].treeNode), NULL);
                            }
#line 2485 "parser.tab.c"
    break;

  case 104:
#line 421 "parser.y"
                            {
                              (yyval.treeNode) = (yyvsp[0].treeNode);
                            }
#line 2493 "parser.tab.c"
    break;

  case 105:
#line 424 "parser.y"
                            {
                                (yyval.treeNode) = NULL;
                            }
#line 2501 "parser.tab.c"
    break;

  case 106:
#line 429 "parser.y"
                              { (yyval.treeNode) = NULL; }
#line 2507 "parser.tab.c"
    break;

  case 107:
#line 430 "parser.y"
                              {
                                (yyval.treeNode) = createOpNode((yyvsp[-1].treeNode)->attrib.name, (yyvsp[-1].treeNode)->linenum, (yyvsp[-2].treeNode), (yyvsp[0].treeNode), NULL);
                              }
#line 2515 "parser.tab.c"
    break;

  case 108:
#line 433 "parser.y"
                              {(yyval.treeNode) = (yyvsp[0].treeNode);}
#line 2521 "parser.tab.c"
    break;

  case 109:
#line 435 "parser.y"
                              { (yyval.treeNode) = NULL; }
#line 2527 "parser.tab.c"
    break;

  case 110:
#line 436 "parser.y"
                              {
                                (yyval.treeNode) = createOpNode((yyvsp[-1].treeNode)->attrib.name, (yyvsp[-1].treeNode)->linenum, (yyvsp[-2].treeNode), (yyvsp[0].treeNode), NULL);
                              }
#line 2535 "parser.tab.c"
    break;

  case 111:
#line 439 "parser.y"
                              {(yyval.treeNode) = (yyvsp[0].treeNode);}
#line 2541 "parser.tab.c"
    break;

  case 112:
#line 441 "parser.y"
                              { (yyval.treeNode) = NULL; }
#line 2547 "parser.tab.c"
    break;

  case 113:
#line 442 "parser.y"
                              {
                                (yyval.treeNode) = (yyvsp[-1].treeNode);
                                (yyval.treeNode)->children[0] = (yyvsp[0].treeNode); // unaryExp
                              }
#line 2556 "parser.tab.c"
    break;

  case 114:
#line 446 "parser.y"
                              { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2562 "parser.tab.c"
    break;

  case 115:
#line 448 "parser.y"
                  {(yyval.treeNode) = (yyvsp[0].treeNode);}
#line 2568 "parser.tab.c"
    break;

  case 116:
#line 449 "parser.y"
                  {(yyval.treeNode) = (yyvsp[0].treeNode);}
#line 2574 "parser.tab.c"
    break;

  case 117:
#line 452 "parser.y"
                                    {
                                      (yyval.treeNode) = tokenToNode((yyvsp[0].tokenData));
                                      (yyval.treeNode)->subkind.exp = IdK;
                                      (yyval.treeNode)->type = UndefinedType;
                                    }
#line 2584 "parser.tab.c"
    break;

  case 118:
#line 457 "parser.y"
                                    {
                                      (yyval.treeNode) = createOpNode("[", (yyvsp[-3].tokenData)->linenum, tokenToNode((yyvsp[-3].tokenData)), (yyvsp[-1].treeNode), NULL);
                                      (yyval.treeNode)->children[0]->subkind.exp = IdK;
                                      //$$->children[0]->isArray = true;
                                    }
#line 2594 "parser.tab.c"
    break;

  case 119:
#line 463 "parser.y"
                                { (yyval.treeNode) = (yyvsp[-1].treeNode); yyerrok; }
#line 2600 "parser.tab.c"
    break;

  case 120:
#line 464 "parser.y"
                                { (yyval.treeNode) = NULL; }
#line 2606 "parser.tab.c"
    break;

  case 121:
#line 465 "parser.y"
                                {(yyval.treeNode) = (yyvsp[0].treeNode);}
#line 2612 "parser.tab.c"
    break;

  case 122:
#line 466 "parser.y"
                                {(yyval.treeNode) = (yyvsp[0].treeNode);}
#line 2618 "parser.tab.c"
    break;

  case 123:
#line 469 "parser.y"
                            {
                              (yyval.treeNode) = createNode(ExpK);
                              (yyval.treeNode)->subkind.exp = CallK;
                              (yyval.treeNode)->attrib.name = strdup((yyvsp[-3].tokenData)->token_str);
                              (yyval.treeNode)->linenum = (yyvsp[-3].tokenData)->linenum;
                              // count args
                              int count = 0;
                              ASTreeNode* l = (yyvsp[-1].treeNode);
                              while(l != NULL){
                                count++;
                                l = l->sibling;
                              }
                              (yyval.treeNode)->num_params = count;   // save number of params
                              if((yyvsp[-1].treeNode) != NULL) (yyval.treeNode)->children[0] = (yyvsp[-1].treeNode);
                            }
#line 2638 "parser.tab.c"
    break;

  case 124:
#line 484 "parser.y"
                            { (yyval.treeNode) = NULL; yyerrok; }
#line 2644 "parser.tab.c"
    break;

  case 125:
#line 487 "parser.y"
                  {(yyval.treeNode) = (yyvsp[0].treeNode);}
#line 2650 "parser.tab.c"
    break;

  case 126:
#line 488 "parser.y"
                  {(yyval.treeNode) = NULL;}
#line 2656 "parser.tab.c"
    break;

  case 127:
#line 491 "parser.y"
                            {
                              ASTreeNode* l = (yyvsp[-2].treeNode);
                              if(l != NULL)
                              {
                                while(l->sibling != NULL){
                                  l = l->sibling;
                                }

                                l->sibling = (yyvsp[0].treeNode);
                                (yyval.treeNode) = (yyvsp[-2].treeNode);

                              }else (yyval.treeNode) = (yyvsp[0].treeNode);
                              yyerrok;
                            }
#line 2675 "parser.tab.c"
    break;

  case 128:
#line 505 "parser.y"
                            {(yyval.treeNode) = (yyvsp[0].treeNode);}
#line 2681 "parser.tab.c"
    break;

  case 129:
#line 506 "parser.y"
                              { (yyval.treeNode) = NULL; yyerrok; }
#line 2687 "parser.tab.c"
    break;

  case 130:
#line 509 "parser.y"
                                  {
                                      (yyval.treeNode) = createStmtNode(ReturnK, "", (yyvsp[-1].tokenData)->linenum, NULL, NULL, NULL);
                                      (yyval.treeNode)->type = Integer; // the type associated with the default return value
                                      (yyval.treeNode)->numCVal = 0; // the value returned by non-specific return statements
                                  }
#line 2697 "parser.tab.c"
    break;

  case 131:
#line 514 "parser.y"
                                  {
                                      (yyval.treeNode) = createStmtNode(ReturnK, "", (yyvsp[-2].tokenData)->linenum, (yyvsp[-1].treeNode), NULL, NULL);
                                      (yyval.treeNode)->type = UndefinedType;
                                      yyerrok;
                                  }
#line 2707 "parser.tab.c"
    break;

  case 132:
#line 519 "parser.y"
                                   { (yyval.treeNode) = NULL; yyerrok; }
#line 2713 "parser.tab.c"
    break;

  case 133:
#line 522 "parser.y"
                            {
                                (yyval.treeNode) = createStmtNode(BreakK, "", (yyvsp[-1].tokenData)->linenum, NULL, NULL, NULL);
                            }
#line 2721 "parser.tab.c"
    break;

  case 134:
#line 527 "parser.y"
                    {
                      (yyval.treeNode) = tokenToNode((yyvsp[0].tokenData));
                      (yyval.treeNode)->nodekind = ExpK;
                      (yyval.treeNode)->subkind.exp = AssignK;
                    }
#line 2731 "parser.tab.c"
    break;

  case 135:
#line 532 "parser.y"
                    {
                      (yyval.treeNode) = tokenToNode((yyvsp[0].tokenData));
                      (yyval.treeNode)->nodekind = ExpK;
                      (yyval.treeNode)->subkind.exp = AssignK;
                    }
#line 2741 "parser.tab.c"
    break;

  case 136:
#line 537 "parser.y"
                    {
                      (yyval.treeNode) = tokenToNode((yyvsp[0].tokenData));
                      (yyval.treeNode)->nodekind = ExpK;
                      (yyval.treeNode)->subkind.exp = AssignK;
                    }
#line 2751 "parser.tab.c"
    break;

  case 137:
#line 542 "parser.y"
                    {
                      (yyval.treeNode) = tokenToNode((yyvsp[0].tokenData));
                      (yyval.treeNode)->nodekind = ExpK;
                      (yyval.treeNode)->subkind.exp = AssignK;
                    }
#line 2761 "parser.tab.c"
    break;

  case 138:
#line 547 "parser.y"
                    {
                      (yyval.treeNode) = tokenToNode((yyvsp[0].tokenData));
                      (yyval.treeNode)->nodekind = ExpK;
                      (yyval.treeNode)->subkind.exp = AssignK;
                    }
#line 2771 "parser.tab.c"
    break;

  case 139:
#line 553 "parser.y"
              {(yyval.treeNode) = tokenToNode((yyvsp[0].tokenData)); (yyval.treeNode)->subkind.exp = OpK;}
#line 2777 "parser.tab.c"
    break;

  case 140:
#line 554 "parser.y"
              {(yyval.treeNode) = tokenToNode((yyvsp[0].tokenData)); (yyval.treeNode)->subkind.exp = OpK; }
#line 2783 "parser.tab.c"
    break;

  case 141:
#line 555 "parser.y"
              {(yyval.treeNode) = tokenToNode((yyvsp[0].tokenData)); (yyval.treeNode)->subkind.exp = OpK;}
#line 2789 "parser.tab.c"
    break;

  case 142:
#line 558 "parser.y"
              {(yyval.treeNode) = tokenToNode((yyvsp[0].tokenData)); (yyval.treeNode)->subkind.exp = OpK;}
#line 2795 "parser.tab.c"
    break;

  case 143:
#line 559 "parser.y"
              {(yyval.treeNode) = tokenToNode((yyvsp[0].tokenData)); (yyval.treeNode)->subkind.exp = OpK;}
#line 2801 "parser.tab.c"
    break;

  case 144:
#line 562 "parser.y"
                      {
                        (yyval.treeNode) = createOpNode("chsign", (yyvsp[0].tokenData)->linenum, NULL, NULL, NULL);
                      }
#line 2809 "parser.tab.c"
    break;

  case 145:
#line 565 "parser.y"
                      {
                        (yyval.treeNode) = createOpNode("sizeof", (yyvsp[0].tokenData)->linenum, NULL, NULL, NULL);
                      }
#line 2817 "parser.tab.c"
    break;

  case 146:
#line 568 "parser.y"
                      {
                        (yyval.treeNode) = createOpNode((yyvsp[0].tokenData)->token_str, (yyvsp[0].tokenData)->linenum, NULL, NULL, NULL);
                      }
#line 2825 "parser.tab.c"
    break;

  case 147:
#line 573 "parser.y"
              {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 2831 "parser.tab.c"
    break;

  case 148:
#line 574 "parser.y"
              {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 2837 "parser.tab.c"
    break;

  case 149:
#line 575 "parser.y"
              {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 2843 "parser.tab.c"
    break;

  case 150:
#line 576 "parser.y"
              {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 2849 "parser.tab.c"
    break;

  case 151:
#line 577 "parser.y"
              {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 2855 "parser.tab.c"
    break;

  case 152:
#line 578 "parser.y"
              {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 2861 "parser.tab.c"
    break;

  case 153:
#line 581 "parser.y"
                        {
                            (yyval.treeNode) = tokenToNode((yyvsp[0].tokenData));
                            (yyval.treeNode)->nodekind = ExpK;
                            (yyval.treeNode)->subkind.exp = ConstantK;
                            (yyval.treeNode)->type = Integer;
                        }
#line 2872 "parser.tab.c"
    break;

  case 154:
#line 587 "parser.y"
                        {
                            (yyval.treeNode) = tokenToNode((yyvsp[0].tokenData));
                            (yyval.treeNode)->nodekind = ExpK;
                            (yyval.treeNode)->subkind.exp = ConstantK;
                            (yyval.treeNode)->varkind = Global;
                            (yyval.treeNode)->type = Char;
                            (yyval.treeNode)->isArray = true;
                            (yyval.treeNode)->size = (yyvsp[0].tokenData)->length + 1; // add 1 for NUL terminal
                        }
#line 2886 "parser.tab.c"
    break;

  case 155:
#line 596 "parser.y"
                        {
                            (yyval.treeNode) = tokenToNode((yyvsp[0].tokenData));
                            (yyval.treeNode)->nodekind = ExpK;
                            (yyval.treeNode)->subkind.exp = ConstantK;
                            (yyval.treeNode)->type = Char; // NOTE: this used to be CharInt to represent 'c'
                        }
#line 2897 "parser.tab.c"
    break;

  case 156:
#line 602 "parser.y"
                        {
                            (yyval.treeNode) = tokenToNode((yyvsp[0].tokenData));
                            (yyval.treeNode)->nodekind = ExpK;
                            (yyval.treeNode)->subkind.exp = ConstantK;
                            (yyval.treeNode)->type = Boolean;
                        }
#line 2908 "parser.tab.c"
    break;


#line 2912 "parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



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
                      yytoken, &yylval);
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 610 "parser.y"


int numErrors = 0;
int numWarnings = 0;

/*
    Compile the provided program printing only warnings and errors.
    IF no errors are thrown, calculate offsets, then finish with generating 3 address code.
*/
void compileNoArgs(char* argv[]){
    int fileIndex = 1;
    if ((yyin = fopen(argv[fileIndex], "r"))){
        // PARSE INPUT
        initErrorProcessing();  // init map for standardized error messages
        yyparse();              // parse file for semantic completeness
        // SEMANTIC ANALYSIS
        SemanticAnalyzer sa = SemanticAnalyzer();   // create object for semantic analysis
        sa.semanticCheck(treeRec, false);           // perform semantic analysis, check that all code "makes sense"
        // OFFSET CALCULATION
        int goffset = 0;
        if(sa.getErrors() == 0){ // if there still aren't errors calculate memory/stack offsets
            Memloc memController = Memloc();
            goffset = memController.traverseTree(treeRec); // fill tree with memory locations
        }
        // CODE GEN
        if(sa.getErrors() == 0){ // check redundant, here just to separate code
            // traverse AST tree in one(or more) passes and construct 3 address code for tm.c
            CodeGenerator cg(treeRec);
        }
    }
}

int main(int argc, char *argv[]){
    bool printAnnotatedTree = false, printAugmentedTree = false, printTreeFlag = false, printSTDebug = false;

    // get argument inputs, set flags
    int c;
    c = ourGetopt( argc, argv, (char *)"pPdDMh" );
    int goodArgs = 0;
    while(c != -1) {
        goodArgs++;
 		switch ( c )
 		{
            case 'p':
				printTreeFlag = true;
                break;
            case 'P':
                printAnnotatedTree = true;
                break;
    		case 'd':
    			yydebug = 1;
                break;
            case 'M':
                printAugmentedTree = true;
                printAnnotatedTree = true;
                break;
            case 'D':
                printSTDebug = true;
                break;
            case 'h':
                {
                    const char* usage_msg = "usage: -c [options] [sourcefile]\noptions:\n"
                                  "-d          - turn on parser debugging\n"
                                  "-D          - turn on symbol table debugging\n"
                                  "-h          - print this usage message\n"
                                  "-M          - print augmented tree with variable sizes and locations\n"
                                  "-p          - print the abstract syntax tree\n"
                                  "-P          - print the abstract syntax tree plus type information";
                    printf("%s", usage_msg);
                    break;
                }
            default:
                printf("ignoring %i\n", c);
        }
        //c = ourGetopt( argc, argv, (char *)"pd" );
    }
    if(c == -1 && argc > 1){ // if no arguments provided with file, run semantic check, memory allocation, and if no errors do code gen
        compileNoArgs(argv);

    }else if (argc > 1) // open file passed for compiling
    {
        int fileIndex = 1 + goodArgs;
        if ((yyin = fopen(argv[fileIndex], "r"))){
            // file open successful
            initErrorProcessing();
            yyparse();

            // execute options for flags set by args
            if(printTreeFlag){
                TreePrinter::printTree(treeRec);
            }

            SemanticAnalyzer sa = SemanticAnalyzer();

            if(numErrors <= 0){ // check the tree for semantic errors and print them
                sa.semanticCheck(treeRec, printSTDebug);

                // if there still aren't errors do memory allocation
                if(numErrors == 0){
                    int goffset;
                    if(sa.getErrors() == 0){
                        Memloc memController = Memloc();
                        goffset = memController.traverseTree(treeRec); // fill tree with memory locations
                    }

                    if(printAnnotatedTree){
                        sa.printSemanticOutput();
                        if(sa.getErrors() == 0 && printAugmentedTree){
                            TreePrinter::printAugmentedTree(treeRec);
                            printf("Offset for end of global space: %d\n", goffset);
                        }else if(!printAugmentedTree && sa.getErrors() == 0 && printAnnotatedTree){
                            // print the tree with added type information
                            TreePrinter::printAnnotatedTree(treeRec);
                        }
                    }
                }
            }
            // print error and warning counts
            printf("Number of warnings: %d\n", sa.getWarnings());
            printf("Number of errors: %d\n", sa.getErrors());

            return 0;
        }
        else{
            // failed to open file
            printf("ERROR(ARGLIST): source file \"%s\" could not be opened.\n", argv[fileIndex]);
            numErrors++;
            printf("Number of warnings: %d\n", numWarnings);
            printf("Number of errors: %d\n", numErrors);
            exit(1);
        }

    }


}
