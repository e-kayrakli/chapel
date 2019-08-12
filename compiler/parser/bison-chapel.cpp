/* A Bison parser, made by GNU Bison 3.0.5.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018 Free Software Foundation, Inc.

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 1

/* Pull parsers.  */
#define YYPULL 0




/* Copy the first part of user declarations.  */

#line 67 "bison-chapel.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "bison-chapel.h".  */
#ifndef YY_YY_INCLUDE_BISON_CHAPEL_H_INCLUDED
# define YY_YY_INCLUDE_BISON_CHAPEL_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 32 "chapel.ypp" /* yacc.c:355  */

  #include <string>
  extern int         captureTokens;
  extern std::string captureString;
#line 45 "chapel.ypp" /* yacc.c:355  */

  #ifndef _BISON_CHAPEL_DEFINES_0_
  #define _BISON_CHAPEL_DEFINES_0_

  #define YYLEX_NEWLINE                  -1
  #define YYLEX_SINGLE_LINE_COMMENT      -2
  #define YYLEX_BLOCK_COMMENT            -3

  typedef void* yyscan_t;

  int processNewline(yyscan_t scanner);
  void stringBufferInit();

  #endif
#line 65 "chapel.ypp" /* yacc.c:355  */

  #ifndef _BISON_CHAPEL_DEFINES_1_
  #define _BISON_CHAPEL_DEFINES_1_

  #include "symbol.h"

  #include <cstdio>
  #include <utility>
  #include <vector>

  class ArgSymbol;
  class BlockStmt;
  class CallExpr;
  class DefExpr;
  class EnumType;
  class Expr;
  class FnSymbol;
  class Type;

  enum   ProcIter {
    ProcIter_PROC,
    ProcIter_ITER
  };

  struct OnlyRename {
    enum{SINGLE, DOUBLE} tag;

    union {
      Expr*  elem;
      std::pair<Expr*, Expr*>* renamed;
    };
  };

  struct WhereAndLifetime {
    Expr* where;
    Expr* lifetime;
  };
  static inline
  WhereAndLifetime makeWhereAndLifetime(Expr* w, Expr* lt) {
    WhereAndLifetime ret;
    ret.where = w;
    ret.lifetime = lt;
    return ret;
  }

  // The lexer only uses pch.
  // The remaining types are for parser productions
  union  YYSTYPE {
    const char*               pch;

    Vec<const char*>*         vpch;
    RetTag                    retTag;
    AggregateTag              aggrTag;
    bool                      b;
    IntentTag                 pt;
    Expr*                     pexpr;
    DefExpr*                  pdefexpr;
    CallExpr*                 pcallexpr;
    BlockStmt*                pblockstmt;
    Type*                     ptype;
    EnumType*                 penumtype;
    std::vector<DefExpr*>*    pvecOfDefs;
    FnSymbol*                 pfnsymbol;
    ModuleSymbol*             pmodsymbol;
    ProcIter                  procIter;
    FlagSet*                  flagSet;
    ShadowVarSymbol*          pShadowVar;
    ShadowVarPrefix           pShadowVarPref;
    std::vector<OnlyRename*>* ponlylist;
    std::set<Flag>*           pflagset;
    WhereAndLifetime          lifetimeAndWhere;
  };

  #endif
#line 145 "chapel.ypp" /* yacc.c:355  */

  #ifndef _BISON_CHAPEL_DEFINES_2_
  #define _BISON_CHAPEL_DEFINES_2_

  struct YYLTYPE {
    int         first_line;
    int         first_column;
    int         last_line;
    int         last_column;
    const char* comment;
    const char* prevModule;
  };

  #define YYLTYPE_IS_DECLARED 1
  #define YYLTYPE_IS_TRIVIAL  1

  #endif
#line 168 "chapel.ypp" /* yacc.c:355  */

  #ifndef _BISON_CHAPEL_DEFINES_3_
  #define _BISON_CHAPEL_DEFINES_3_

  class ParserContext {
  public:
    ParserContext()
    {
      scanner       = 0;
      latestComment = 0;
      generatedStmt = 0;
    }

    ParserContext(yyscan_t scannerIn)
    {
      scanner       = scannerIn;
      latestComment = 0;
      generatedStmt = 0;
    }

    yyscan_t    scanner;
    const char* latestComment;
    BaseAST*    generatedStmt;
  };

  #endif

#line 238 "bison-chapel.cpp" /* yacc.c:355  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TIDENT = 258,
    INTLITERAL = 259,
    REALLITERAL = 260,
    IMAGLITERAL = 261,
    STRINGLITERAL = 262,
    CSTRINGLITERAL = 263,
    EXTERNCODE = 264,
    TALIGN = 265,
    TAS = 266,
    TATOMIC = 267,
    TBEGIN = 268,
    TBREAK = 269,
    TBOOL = 270,
    TBORROWED = 271,
    TBY = 272,
    TCATCH = 273,
    TCLASS = 274,
    TCOBEGIN = 275,
    TCOFORALL = 276,
    TCOMPLEX = 277,
    TCONFIG = 278,
    TCONST = 279,
    TCONTINUE = 280,
    TDEFER = 281,
    TDELETE = 282,
    TDMAPPED = 283,
    TDO = 284,
    TDOMAIN = 285,
    TELSE = 286,
    TENUM = 287,
    TEXCEPT = 288,
    TEXPORT = 289,
    TEXTERN = 290,
    TFALSE = 291,
    TFOR = 292,
    TFORALL = 293,
    TFORWARDING = 294,
    TIF = 295,
    TIMAG = 296,
    TIN = 297,
    TINDEX = 298,
    TINLINE = 299,
    TINOUT = 300,
    TINT = 301,
    TITER = 302,
    TINITEQUALS = 303,
    TLABEL = 304,
    TLAMBDA = 305,
    TLET = 306,
    TLIFETIME = 307,
    TLOCAL = 308,
    TLOCALE = 309,
    TMINUSMINUS = 310,
    TMODULE = 311,
    TNEW = 312,
    TNIL = 313,
    TNOINIT = 314,
    TNONE = 315,
    TNOTHING = 316,
    TON = 317,
    TONLY = 318,
    TOTHERWISE = 319,
    TOUT = 320,
    TOVERRIDE = 321,
    TOWNED = 322,
    TPARAM = 323,
    TPLUSPLUS = 324,
    TPRAGMA = 325,
    TPRIMITIVE = 326,
    TPRIVATE = 327,
    TPROC = 328,
    TPROTOTYPE = 329,
    TPUBLIC = 330,
    TREAL = 331,
    TRECORD = 332,
    TREDUCE = 333,
    TREF = 334,
    TREQUIRE = 335,
    TRETURN = 336,
    TSCAN = 337,
    TSELECT = 338,
    TSERIAL = 339,
    TSHARED = 340,
    TSINGLE = 341,
    TSPARSE = 342,
    TSTRING = 343,
    TSUBDOMAIN = 344,
    TSYNC = 345,
    TTHEN = 346,
    TTHIS = 347,
    TTHROW = 348,
    TTHROWS = 349,
    TTRUE = 350,
    TTRY = 351,
    TTRYBANG = 352,
    TTYPE = 353,
    TUINT = 354,
    TUNDERSCORE = 355,
    TUNION = 356,
    TUNMANAGED = 357,
    TUSE = 358,
    TVAR = 359,
    TVOID = 360,
    TWHEN = 361,
    TWHERE = 362,
    TWHILE = 363,
    TWITH = 364,
    TYIELD = 365,
    TZIP = 366,
    TALIAS = 367,
    TAND = 368,
    TASSIGN = 369,
    TASSIGNBAND = 370,
    TASSIGNBOR = 371,
    TASSIGNBXOR = 372,
    TASSIGNDIVIDE = 373,
    TASSIGNEXP = 374,
    TASSIGNLAND = 375,
    TASSIGNLOR = 376,
    TASSIGNMINUS = 377,
    TASSIGNMOD = 378,
    TASSIGNMULTIPLY = 379,
    TASSIGNPLUS = 380,
    TASSIGNREDUCE = 381,
    TASSIGNSL = 382,
    TASSIGNSR = 383,
    TBANG = 384,
    TBAND = 385,
    TBNOT = 386,
    TBOR = 387,
    TBXOR = 388,
    TCOLON = 389,
    TCOMMA = 390,
    TDIVIDE = 391,
    TDOT = 392,
    TDOTDOT = 393,
    TDOTDOTDOT = 394,
    TEQUAL = 395,
    TEXP = 396,
    TGREATER = 397,
    TGREATEREQUAL = 398,
    THASH = 399,
    TIO = 400,
    TLESS = 401,
    TLESSEQUAL = 402,
    TMINUS = 403,
    TMOD = 404,
    TNOTEQUAL = 405,
    TOR = 406,
    TPLUS = 407,
    TQUESTION = 408,
    TSEMI = 409,
    TSHIFTLEFT = 410,
    TSHIFTRIGHT = 411,
    TSTAR = 412,
    TSWAP = 413,
    TLCBR = 414,
    TRCBR = 415,
    TLP = 416,
    TRP = 417,
    TLSBR = 418,
    TRSBR = 419,
    TNOELSE = 420,
    TUPLUS = 421,
    TUMINUS = 422
  };
#endif

/* Value type.  */

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



#ifndef YYPUSH_MORE_DEFINED
# define YYPUSH_MORE_DEFINED
enum { YYPUSH_MORE = 4 };
#endif

typedef struct yypstate yypstate;

int yypush_parse (yypstate *ps, int pushed_char, YYSTYPE const *pushed_val, YYLTYPE *pushed_loc, ParserContext* context);

yypstate * yypstate_new (void);
void yypstate_delete (yypstate *ps);
/* "%code provides" blocks.  */
#line 199 "chapel.ypp" /* yacc.c:355  */

  extern int yydebug;

  void yyerror(YYLTYPE*       ignored,
               ParserContext* context,
               const char*    str);

#line 451 "bison-chapel.cpp" /* yacc.c:355  */

#endif /* !YY_YY_INCLUDE_BISON_CHAPEL_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 457 "bison-chapel.cpp" /* yacc.c:358  */
/* Unqualified %code blocks.  */
#line 38 "chapel.ypp" /* yacc.c:359  */

  #include <string>
  int         captureTokens;
  std::string captureString;
#line 207 "chapel.ypp" /* yacc.c:359  */

  #include "build.h"
  #include "CatchStmt.h"
  #include "DeferStmt.h"
  #include "DoWhileStmt.h"
  #include "driver.h"
  #include "flex-chapel.h"
  #include "ForallStmt.h"
  #include "ForLoop.h"
  #include "IfExpr.h"
  #include "misc.h"
  #include "parser.h"
  #include "stmt.h"
  #include "stringutil.h"
  #include "TryStmt.h"
  #include "vec.h"
  #include "WhileDoStmt.h"

  #include <cstdio>
  #include <cstdlib>
  #include <cstring>
  #include <stdint.h>

  static int query_uid = 1;

  #define YYLLOC_DEFAULT(Current, Rhs, N)                                 \
    if (N) {                                                              \
      (Current).first_line   = (Rhs)[1].first_line;                       \
      (Current).first_column = (Rhs)[1].first_column;                     \
      (Current).last_line    = (Rhs)[N].last_line;                        \
      (Current).last_column  = (Rhs)[N].last_column;                      \
      (Current).comment      = NULL;                                      \
                                                                          \
      if ((Current).first_line)                                           \
        yystartlineno = (Current).first_line;                             \
                                                                          \
    } else  {                                                             \
      (Current) = yylloc;                                                 \
    }

  void yyerror(YYLTYPE*       ignored,
               ParserContext* context,
               const char*    str) {

    // like USR_FATAL_CONT
    setupError("parser", __FILE__, __LINE__, 3);

    // TODO -- should this begin with error:
    if (!chplParseString) {
      const char* yyText = yyget_text(context->scanner);
      fprintf(stderr, "%s:%d: %s", yyfilename, chplLineno, str);

      if (strlen(yyText) > 0) {
        fprintf(stderr, ": near '%s'", yyText);
      }
    } else {
      fprintf(stderr, "%s: %s", yyfilename, str);

      if (chplParseStringMsg && (strlen(chplParseStringMsg) > 0)) {
        fprintf(stderr, " %s", chplParseStringMsg);
      }
    }

    fprintf(stderr, "\n");
  }

#line 531 "bison-chapel.cpp" /* yacc.c:359  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   16290

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  168
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  141
/* YYNRULES -- Number of rules.  */
#define YYNRULES  594
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1049

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   422

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   489,   489,   494,   495,   501,   502,   507,   508,   513,
     514,   515,   516,   517,   518,   519,   520,   521,   522,   523,
     524,   525,   526,   527,   528,   529,   530,   531,   532,   533,
     534,   535,   536,   537,   538,   539,   540,   541,   542,   546,
     559,   564,   569,   577,   578,   579,   583,   584,   597,   598,
     599,   604,   605,   610,   615,   620,   624,   631,   636,   640,
     645,   649,   650,   651,   655,   656,   657,   661,   665,   667,
     669,   671,   673,   680,   681,   685,   686,   687,   688,   689,
     690,   691,   694,   695,   696,   697,   698,   699,   711,   712,
     723,   724,   725,   726,   727,   728,   729,   730,   731,   732,
     733,   734,   735,   736,   737,   738,   739,   743,   747,   748,
     749,   750,   751,   752,   753,   754,   755,   756,   767,   768,
     773,   774,   779,   780,   784,   785,   789,   790,   794,   795,
     796,   797,   798,   799,   800,   801,   805,   806,   810,   811,
     812,   813,   817,   824,   825,   826,   827,   828,   829,   830,
     831,   832,   833,   834,   835,   836,   837,   838,   839,   840,
     841,   842,   848,   854,   860,   866,   873,   880,   884,   891,
     895,   896,   897,   898,   899,   901,   903,   905,   910,   913,
     914,   915,   916,   917,   918,   922,   923,   927,   928,   929,
     933,   934,   938,   941,   943,   948,   949,   953,   955,   957,
     964,   974,   984,   994,  1007,  1012,  1017,  1025,  1026,  1031,
    1032,  1034,  1039,  1055,  1062,  1071,  1079,  1083,  1090,  1091,
    1096,  1101,  1095,  1128,  1134,  1141,  1147,  1153,  1164,  1170,
    1163,  1202,  1206,  1211,  1215,  1220,  1227,  1228,  1232,  1233,
    1234,  1235,  1236,  1237,  1238,  1239,  1240,  1241,  1242,  1243,
    1244,  1245,  1246,  1247,  1248,  1249,  1250,  1251,  1252,  1253,
    1254,  1255,  1256,  1257,  1258,  1259,  1263,  1264,  1265,  1266,
    1267,  1268,  1269,  1270,  1271,  1272,  1273,  1274,  1278,  1279,
    1283,  1287,  1288,  1289,  1293,  1295,  1297,  1299,  1301,  1306,
    1307,  1311,  1312,  1313,  1314,  1315,  1316,  1317,  1318,  1319,
    1323,  1324,  1325,  1326,  1327,  1328,  1332,  1333,  1337,  1338,
    1339,  1340,  1341,  1342,  1346,  1347,  1350,  1351,  1355,  1356,
    1360,  1362,  1367,  1368,  1372,  1373,  1377,  1378,  1380,  1382,
    1384,  1389,  1390,  1393,  1394,  1395,  1396,  1397,  1398,  1399,
    1402,  1403,  1406,  1408,  1410,  1415,  1428,  1445,  1446,  1448,
    1453,  1454,  1455,  1456,  1457,  1461,  1467,  1473,  1481,  1482,
    1490,  1492,  1497,  1499,  1501,  1506,  1508,  1510,  1517,  1518,
    1519,  1524,  1526,  1528,  1532,  1536,  1538,  1542,  1550,  1551,
    1552,  1553,  1554,  1559,  1560,  1561,  1562,  1563,  1583,  1587,
    1591,  1599,  1606,  1607,  1608,  1612,  1614,  1620,  1622,  1624,
    1629,  1630,  1631,  1632,  1633,  1639,  1640,  1641,  1642,  1646,
    1647,  1651,  1652,  1653,  1657,  1658,  1662,  1663,  1667,  1668,
    1672,  1673,  1674,  1675,  1679,  1680,  1691,  1693,  1698,  1699,
    1700,  1701,  1702,  1703,  1705,  1707,  1709,  1711,  1713,  1715,
    1718,  1720,  1722,  1724,  1726,  1728,  1730,  1732,  1737,  1739,
    1741,  1743,  1745,  1747,  1749,  1751,  1753,  1755,  1757,  1759,
    1761,  1768,  1774,  1780,  1786,  1795,  1805,  1813,  1814,  1815,
    1816,  1817,  1818,  1819,  1820,  1825,  1826,  1830,  1834,  1835,
    1839,  1843,  1844,  1848,  1852,  1856,  1863,  1864,  1865,  1866,
    1867,  1868,  1872,  1873,  1878,  1883,  1891,  1892,  1893,  1894,
    1895,  1896,  1897,  1898,  1899,  1901,  1903,  1905,  1907,  1909,
    1914,  1915,  1918,  1919,  1920,  1923,  1924,  1925,  1926,  1937,
    1938,  1939,  1943,  1944,  1945,  1949,  1950,  1951,  1952,  1960,
    1961,  1962,  1963,  1967,  1968,  1972,  1973,  1974,  1975,  1976,
    1977,  1978,  1979,  1980,  1981,  1982,  1983,  1987,  1995,  1996,
    2000,  2001,  2002,  2003,  2004,  2005,  2006,  2007,  2008,  2009,
    2010,  2011,  2012,  2013,  2014,  2015,  2016,  2017,  2018,  2019,
    2020,  2021,  2022,  2026,  2027,  2028,  2029,  2030,  2031,  2032,
    2036,  2037,  2038,  2039,  2043,  2044,  2045,  2046,  2051,  2052,
    2053,  2054,  2055,  2056,  2057
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TIDENT", "INTLITERAL", "REALLITERAL",
  "IMAGLITERAL", "STRINGLITERAL", "CSTRINGLITERAL", "EXTERNCODE", "TALIGN",
  "TAS", "TATOMIC", "TBEGIN", "TBREAK", "TBOOL", "TBORROWED", "TBY",
  "TCATCH", "TCLASS", "TCOBEGIN", "TCOFORALL", "TCOMPLEX", "TCONFIG",
  "TCONST", "TCONTINUE", "TDEFER", "TDELETE", "TDMAPPED", "TDO", "TDOMAIN",
  "TELSE", "TENUM", "TEXCEPT", "TEXPORT", "TEXTERN", "TFALSE", "TFOR",
  "TFORALL", "TFORWARDING", "TIF", "TIMAG", "TIN", "TINDEX", "TINLINE",
  "TINOUT", "TINT", "TITER", "TINITEQUALS", "TLABEL", "TLAMBDA", "TLET",
  "TLIFETIME", "TLOCAL", "TLOCALE", "TMINUSMINUS", "TMODULE", "TNEW",
  "TNIL", "TNOINIT", "TNONE", "TNOTHING", "TON", "TONLY", "TOTHERWISE",
  "TOUT", "TOVERRIDE", "TOWNED", "TPARAM", "TPLUSPLUS", "TPRAGMA",
  "TPRIMITIVE", "TPRIVATE", "TPROC", "TPROTOTYPE", "TPUBLIC", "TREAL",
  "TRECORD", "TREDUCE", "TREF", "TREQUIRE", "TRETURN", "TSCAN", "TSELECT",
  "TSERIAL", "TSHARED", "TSINGLE", "TSPARSE", "TSTRING", "TSUBDOMAIN",
  "TSYNC", "TTHEN", "TTHIS", "TTHROW", "TTHROWS", "TTRUE", "TTRY",
  "TTRYBANG", "TTYPE", "TUINT", "TUNDERSCORE", "TUNION", "TUNMANAGED",
  "TUSE", "TVAR", "TVOID", "TWHEN", "TWHERE", "TWHILE", "TWITH", "TYIELD",
  "TZIP", "TALIAS", "TAND", "TASSIGN", "TASSIGNBAND", "TASSIGNBOR",
  "TASSIGNBXOR", "TASSIGNDIVIDE", "TASSIGNEXP", "TASSIGNLAND",
  "TASSIGNLOR", "TASSIGNMINUS", "TASSIGNMOD", "TASSIGNMULTIPLY",
  "TASSIGNPLUS", "TASSIGNREDUCE", "TASSIGNSL", "TASSIGNSR", "TBANG",
  "TBAND", "TBNOT", "TBOR", "TBXOR", "TCOLON", "TCOMMA", "TDIVIDE", "TDOT",
  "TDOTDOT", "TDOTDOTDOT", "TEQUAL", "TEXP", "TGREATER", "TGREATEREQUAL",
  "THASH", "TIO", "TLESS", "TLESSEQUAL", "TMINUS", "TMOD", "TNOTEQUAL",
  "TOR", "TPLUS", "TQUESTION", "TSEMI", "TSHIFTLEFT", "TSHIFTRIGHT",
  "TSTAR", "TSWAP", "TLCBR", "TRCBR", "TLP", "TRP", "TLSBR", "TRSBR",
  "TNOELSE", "TUPLUS", "TUMINUS", "$accept", "program", "toplevel_stmt_ls",
  "toplevel_stmt", "pragma_ls", "stmt", "module_decl_start",
  "module_decl_stmt", "access_control", "opt_prototype", "block_stmt",
  "stmt_ls", "only_ls", "opt_only_ls", "except_ls", "use_access_control",
  "use_stmt", "require_stmt", "assignment_stmt", "opt_label_ident",
  "ident_fn_def", "ident_def", "ident_use", "internal_type_ident_def",
  "unres_type_ident_def", "scalar_type", "reserved_type_ident_use",
  "opt_string", "do_stmt", "return_stmt", "class_level_stmt",
  "private_decl", "forwarding_stmt", "extern_block_stmt", "loop_stmt",
  "zippered_iterator", "if_stmt", "defer_stmt", "try_stmt",
  "catch_stmt_ls", "catch_stmt", "catch_expr", "throw_stmt", "select_stmt",
  "when_stmt_ls", "when_stmt", "class_decl_stmt", "class_tag",
  "opt_inherit", "class_level_stmt_ls", "enum_decl_stmt", "enum_header",
  "enum_ls", "enum_item", "lambda_decl_expr", "$@1", "$@2", "linkage_spec",
  "fn_decl_stmt", "$@3", "$@4", "fn_decl_stmt_inner",
  "fn_decl_receiver_expr", "fn_ident", "assignop_ident", "opt_formal_ls",
  "req_formal_ls", "formal_ls", "formal", "opt_intent_tag",
  "required_intent_tag", "opt_this_intent_tag", "proc_or_iter",
  "opt_ret_tag", "opt_throws_error", "opt_function_body_stmt",
  "function_body_stmt", "query_expr", "opt_query_expr", "var_arg_expr",
  "opt_lifetime_where", "lifetime_components_expr", "lifetime_expr",
  "lifetime_ident", "type_alias_decl_stmt", "type_alias_decl_stmt_inner",
  "opt_init_type", "var_decl_type", "var_decl_stmt",
  "var_decl_stmt_inner_ls", "var_decl_stmt_inner",
  "tuple_var_decl_component", "tuple_var_decl_stmt_inner_ls",
  "opt_init_expr", "ret_array_type", "opt_ret_type", "opt_type",
  "array_type", "opt_formal_array_elt_type", "formal_array_type",
  "opt_formal_type", "expr_ls", "simple_expr_ls", "tuple_component",
  "tuple_expr_ls", "opt_actual_ls", "actual_ls", "actual_expr",
  "ident_expr", "type_level_expr", "sub_type_level_expr", "for_expr",
  "cond_expr", "nil_expr", "stmt_level_expr", "opt_task_intent_ls",
  "task_intent_clause", "task_intent_ls", "forall_intent_clause",
  "forall_intent_ls", "intent_expr", "shadow_var_prefix", "io_expr",
  "new_expr", "let_expr", "expr", "opt_expr", "opt_try_expr", "lhs_expr",
  "fun_expr", "call_expr", "dot_expr", "parenthesized_expr",
  "bool_literal", "literal_expr", "assoc_expr_ls", "binary_op_expr",
  "unary_op_expr", "reduce_expr", "scan_expr", "reduce_scan_op_expr", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422
};
# endif

#define YYPACT_NINF -926

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-926)))

#define YYTABLE_NINF -545

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -926,    66,  2865,  -926,   -27,  -926,  -926,  -926,  -926,  -926,
    -926,  4317,    71,   267,  -926, 11958,  -926,    71,  9754,  -926,
     316,   207,   267,  4317,  9754,  4317,   126,  -926,  9754,  6856,
    -926,  8236,  8834,  6695,  9754,  -926,   159,  -926,  -926, 16185,
    -926, 12345,  8972,  -926,  9754,  9754,  -926,  -926,  -926,  9754,
    -926, 11958,  -926,  9754,   287,   199,  1926,  2349,  -926,  -926,
    -926,  9110,  7776,  9754,  8972, 11958,  9754,   307,  -926,   200,
    4317,  -926,  9754,  -926,  9892,  9892, 16185,  -926,  -926, 11958,
    -926,  -926,  9754,  9754,  -926,  9754,  -926,  9754,  -926,  -926,
   11824,  9754,  -926,  9754,  -926,  -926,  3351,  6994,  8374,  -926,
    4156,  -926,   238,  -926,   330,  -926,   305,  -926,  -926,  -926,
    -926,  -926,  -926,  -926,  -926,  -926,  -926,  -926,  -926,  -926,
    -926,  -926,  -926,  -926, 16185,  -926, 16185,   -62,   218,  -926,
    -926, 12345,  -926,   286,  -926,   268,  -926,  -926,   293,   303,
     284,   306,   311, 15912,  1993,    30,   326,   331,  -926,  -926,
    -926,  -926,  -926,  -926,  -926,   152,  -926,  -926, 15912,   309,
    4317,  -926,  -926,   332,  9754,  9754,  9754,  9754,  9754,  9110,
    9110,   220,  -926,  -926,  -926,  -926,   352,   250,  -926,  -926,
     333, 14117, 16185, 12345,  -926,   343,  -926,   148, 15912,   390,
    7937, 15912,  -926,   166,  -926, 16185,   173,   321, 16185,   341,
      18, 13636,     6, 13595,   321,  9754,  -926, 14020, 12844,  7937,
    -926,  -926,  -926,  -926,  -926,  -926,  -926,  -926,  -926,  -926,
    -926,  -926,  -926,  -926,  -926,  -926,  -926,  -926,  -926,  -926,
    -926,  -926,  4317,  -926,   342,  1998,    36,    -6,  -926,  4317,
    -926,  -926, 13779,   587,   352, 13779,   352,   587,  -926,  7937,
    9754,  -926,  -926, 16185,  -926,   211, 15912,  9754,  9754,  -926,
   15912,   357, 13967,  -926, 13779,   352, 15912,   354,  7937,  -926,
   15912, 14346,  -926,  -926, 14403, 11821,  -926,  -926, 14489,   403,
     364,   352, 13779, 14546,   340,   340,  1232,   587,   587,   222,
    -926,  -926,  3512,   140,  -926,  9754,  -926,    61,    90,  -926,
       4,   -12, 14632,   -44,   512,  -926,  3673,  -926,   465,  9110,
     389,   365,  -926,  -926,  -926,   212,  -926,  -926,  9754,  9754,
    9754,  9754,  8834,  8834,  9754,   275,  9754,  9754,  9754,  9754,
    9754,   490, 11824,  9754,  9754,  9754,  9754,  9754,  9754,  9754,
    9754,  9754,  9754,  9754,  9754,  9754,  9754,  9754,  -926,  -926,
    -926,  -926,  -926,  -926,  8535,  8535,  -926,  -926,  -926,  -926,
    8535,  -926,  -926,  8535,  8535,  7937,  7937,  8834,  8834,  7477,
    -926,  -926, 14163, 14260, 14586,     3,  3834,  -926,  8834,    18,
     372,   215,  -926,  9754,  -926,  9754,   411,  -926,   373,   399,
    -926,  -926,   382, 16185, 12345,   495,  9110,  -926,  4478,  8834,
    -926,   381,  -926,    18,  4639,  8834,  -926,    18,   321, 10030,
    9754,  -926,  4317,   520,  9754,   392,  -926,   541,  -926,  -926,
    1998,  -926,   417,   394,  -926, 10168,   444,  9754, 12345,  -926,
    -926,  -926,   402,  -926,  9110,  -926, 15912, 15912,  -926,    42,
    -926,  7937,   405,  -926,   557,  -926,   557,  -926, 10306,   442,
    -926,  -926,  -926,  -926,  -926,  -926,  8673,  -926, 12693,  7155,
    -926,  7316,  -926,  4317,   416,  8834,  6088,  3190,   421,  9754,
    6412,  -926,  -926,   277,  -926,  3995, 16185,   255, 14306,  9110,
     420, 16118,    49,  -926, 14729, 13734, 13734,   371,  -926,   371,
    -926,   371, 14443,  1100,  1519,  1635,   352,   340,  -926,  -926,
    -926,  -926,  1232, 15103,   371, 14689, 14689, 13734, 14689, 14689,
     705,   340, 15103, 13869,   705,   587,   587,   340,   427,   438,
     439,   440,   447,   434,   449,  -926,   371,  -926,   371,    35,
    -926,  -926,  -926,    97,  -926,   665, 15961,   203, 10444,  8834,
   10582,  8834,  9754,  8834, 12186,    71, 14782,  -926,  -926,  -926,
   15912, 14822,  7937,  -926,  7937,  -926,   389,   256,  9754,    98,
    9754, 15912,    19, 13824,  7477,  -926,  9754, 15912,    17, 13681,
    -926,   454,   468,   460, 14879,   468,   462,   586, 14965,  4317,
   13922,  -926,    54,  -926,  -926,  -926,  -926,  -926,  -926,   542,
     101,  -926, 12426,  -926,   163,   457,  1998,    36,   126,   159,
    9754,  9754,  5927,  -926,  -926,   464,  8098,  -926, 15912,  -926,
    -926,  -926, 15912,   467,    58,   463,  -926, 12267,  -926,  -926,
     272, 16185,  -926,  -926,  -926,  -926,  -926,  -926,  -926,  4317,
     115,  1408,  -926,  -926, 15912,  4317, 15912,  -926, 15022,  -926,
    -926,  -926,  -926, 10030,  9754,   493,  2332,   469,   516,   204,
    -926,   552,  -926,  -926,  -926,  -926,  6536,  -926,  -926,  -926,
    -926,  -926,  -926,  -926,  -926,  -926,  7477,  -926,    27,  8834,
    8834,  9754,   605, 15054,  9754,   606, 15197,   474,  2690,    18,
      18,  -926,  -926,  -926,  -926,   484,  -926, 13779,  -926, 12920,
    4800,  -926,  4961,  -926,   109,  -926, 12996,  5122,  -926,    18,
    5283,  -926,    18,  9754,  -926,  9754,  -926,  4317,  9754,  -926,
    4317,   614,  -926,  -926, 16185,   851,  -926,  1998,   519,   575,
    -926,  -926,  -926,    92,  -926,  -926,   444,   500,    46,  -926,
    -926,  -926,  5444,  9110,  -926,  -926,  -926, 16185,  -926,   523,
     333,  -926,  -926,  5605,   502,  5766,   506,  -926,  9754,   518,
     521,   513,  1009,  -926,  9754, 16185,  -926,  -926,   163,   517,
     100,  -926,   537,  -926,   540,   555,   551,   553,  -926,   554,
     564,   559,   561,   562,   151,   572,   565,   568,  -926,  -926,
   16185,  -926,  -926,  -926,  -926,  -926,  -926,  -926,  -926,  -926,
    -926,  -926,  -926,  -926,  -926,  -926,  -926,  -926,  -926,  -926,
    9754,  -926,   578,   580,  -926,   573,   517,   517,  -926,  -926,
     444,   114,   133, 15165, 10720, 10858, 15308, 10996, 11134, 11272,
   11410,  -926,  -926,  2475,  -926,  4317,  9754, 15912,  9754, 15912,
    7477,  -926,  4317,  9754, 15912,  -926,  9754, 15912,  -926, 15340,
   15912,  -926, 15912,   681,  4317,   519,  -926,   556,  9271,   234,
    -926,   175,  -926,  -926,  8834, 12072,  4317,  -926,    10,   558,
    9754,  -926,  9754,  -926, 15912,  4317,  9754,  -926, 15912,  4317,
   15912,  -926,  -926,  -926,  7638,   834,   834,  -926,  2489,  -926,
   15912,  -926,    94,   541,  -926,  -926, 12733,  -926, 12493,  -926,
    -926,  -926,  9754,  9754,  9754,  9754,  9754,  9754,  9754,  9754,
     567,  1126, 14965, 13072, 13148,  -926, 14965, 13224, 13300,  9754,
    4317,  -926,   444,   519,  6250,  -926,  -926,  -926,   127,  9110,
    -926,  -926,    29,  9754,   -25, 12549,  -926,  1165,   390,  -926,
     333, 15912, 13376,  -926, 13452,  -926,  -926,  -926, 11548,   619,
     134,  -926,   585,  -926,   588,   517,   517, 15451, 15483, 15594,
   15626, 15737, 15769,  -926,  -926,  4317,  4317,  4317,  4317, 15912,
    -926,  -926,   234,  9432,    48,  -926,  -926, 15912,  -926,    80,
    -926,   -26,  -926,   348, 15880,  -926,  -926,  -926, 11410,  -926,
    4317,  4317,  3026,  -926,  -926,   183,  -926,   175,  -926,  -926,
    -926,  9754,  9754,  9754,  9754,  9754,  9754, 14965, 14965, 14965,
   14965,  -926,  -926,  -926,  -926,  -926,   224,  8834,  2634,  -926,
    9754,    29,    80,    80,    80,    80,    80,    80,    29,  1639,
   14965, 14965,   571, 11686,    76,   -19, 12636,  -926,  -926, 15912,
    -926,  -926,  -926,  -926,  -926,  -926,  -926,   590,  -926,  -926,
     325,  2185,  -926,  -926,  -926,  9593,  -926,   415,  -926
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       3,     0,     0,     1,     0,    88,   536,   537,   538,   539,
     540,     0,   475,    73,   108,   446,   204,   475,     0,   113,
       0,   351,    73,     0,     0,     0,     0,   214,   510,   510,
     533,     0,     0,     0,     0,   112,     0,   224,   109,     0,
     220,     0,     0,   115,     0,     0,   466,   541,   116,     0,
     227,   440,   350,     0,     0,     0,    45,    44,   111,   205,
     352,     0,     0,     0,     0,   444,     0,     0,   114,     0,
       0,    89,     0,   534,     0,     0,     0,   110,   206,   442,
     354,   117,     0,     0,   590,     0,   592,     0,   593,   594,
     509,     0,   591,   588,   128,   589,     0,     0,     0,     4,
       0,     5,     0,     9,    46,    10,     0,    11,    12,    14,
     424,   425,    22,    13,   129,   135,    15,    17,    16,    19,
      20,    21,    18,   134,     0,   132,     0,   501,     0,   136,
     133,     0,   137,   515,   497,   426,   498,   430,   428,     0,
       0,   502,   503,     0,   429,     0,   516,   517,   518,   535,
     496,   432,   431,   499,   500,     0,    38,    24,   438,     0,
       0,   476,    74,     0,     0,     0,     0,     0,     0,     0,
       0,   501,   515,   428,   502,   503,   447,   429,   516,   517,
       0,   475,     0,     0,   353,     0,   178,     0,   409,     0,
     416,   511,   225,   539,   142,     0,     0,   226,     0,     0,
       0,     0,     0,     0,     0,   510,   141,     0,     0,   416,
      82,    90,   100,    95,   102,    85,    94,   103,    91,   104,
      83,   105,    98,    93,    99,    97,    96,    84,    86,    92,
     101,   106,     0,    87,     0,     0,     0,     0,   358,     0,
     125,    32,     0,   575,   494,     0,   441,   576,     7,   416,
     510,   131,   130,   321,   406,     0,   405,     0,     0,   126,
     514,     0,     0,    35,     0,   445,   433,     0,   416,    36,
     439,     0,   185,   181,     0,   429,   185,   182,     0,   347,
       0,   443,     0,     0,   577,   579,   508,   574,   573,     0,
      48,    51,     0,     0,   411,     0,   413,     0,     0,   412,
       0,     0,   405,     0,     0,     6,     0,    47,     0,     0,
     207,     0,   307,   306,   228,     0,   427,    23,     0,     0,
       0,     0,     0,     0,     0,   578,     0,     0,     0,     0,
       0,     0,   507,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   266,   273,
     274,   275,   270,   272,     0,     0,   268,   271,   269,   267,
       0,   277,   276,     0,     0,   416,   416,     0,     0,     0,
      25,    26,     0,     0,     0,     0,     0,    27,     0,     0,
       0,     0,    28,     0,    29,     0,   424,   422,     0,   417,
     418,   423,     0,     0,     0,     0,     0,   151,     0,     0,
     150,     0,   159,     0,     0,     0,   157,     0,     0,     0,
      57,   138,     0,   171,     0,     0,    30,   289,   221,   362,
       0,   363,   365,     0,   387,     0,   368,     0,     0,   124,
      31,    33,     0,   320,     0,    67,   512,   513,   127,     0,
      34,   416,     0,   192,   183,   179,   184,   180,     0,   345,
     342,   144,    37,    50,    49,    52,     0,   542,     0,     0,
     529,     0,   531,     0,     0,     0,     0,     0,     0,     0,
       0,   546,     8,     0,    40,     0,     0,     0,   405,     0,
       0,     0,   300,   357,   474,   570,   569,   572,   581,   580,
     585,   584,   566,   563,   564,   565,   505,   553,   527,   528,
     526,   525,   506,   557,   568,   562,   560,   571,   561,   559,
     551,   556,   558,   567,   550,   554,   555,   552,     0,     0,
       0,     0,     0,     0,     0,   583,   582,   587,   586,   486,
     487,   489,   491,     0,   478,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   544,   475,   475,   147,   343,   355,
     410,     0,     0,   435,     0,   344,   207,     0,     0,     0,
       0,   450,     0,     0,     0,   160,     0,   456,     0,     0,
     158,   589,    60,     0,    53,    58,     0,   170,     0,     0,
       0,   434,   294,   291,   292,   293,   297,   298,   299,   289,
       0,   282,     0,   290,   308,     0,   366,     0,   120,   121,
     119,   118,     0,   386,   385,   497,     0,   360,   495,   359,
     524,   408,   407,     0,     0,     0,   436,     0,   186,   349,
     497,     0,   543,   504,   530,   414,   532,   415,   167,     0,
       0,     0,   545,   165,   460,     0,   548,   547,     0,    42,
      41,    39,    64,     0,    57,   208,     0,     0,   218,     0,
     215,   304,   301,   302,   305,   229,     0,    71,    72,    70,
      69,    68,   522,   523,   488,   490,     0,   477,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   143,   420,   421,   419,     0,   356,     0,   169,     0,
       0,   149,     0,   148,     0,   481,     0,     0,   155,     0,
       0,   153,     0,     0,   139,     0,   140,     0,     0,   173,
       0,   175,   295,   296,     0,   289,   280,     0,   400,   309,
     312,   311,   313,     0,   364,   367,   368,     0,     0,   369,
     370,   194,     0,     0,   193,   196,   437,     0,   187,   190,
       0,   346,   168,     0,     0,     0,     0,   166,     0,     0,
       0,     0,   223,   213,     0,   216,   212,   303,   308,   278,
      75,   261,    90,   259,    95,    78,    94,    91,   264,   104,
      76,   105,    93,   107,    77,    79,    92,   106,   258,   240,
     243,   241,   242,   253,   244,   257,   249,   247,   260,   263,
     248,   246,   251,   256,   245,   250,   254,   255,   252,   262,
       0,   238,     0,    81,    80,     0,   278,   278,   236,   479,
     368,   515,   515,     0,     0,     0,     0,     0,     0,     0,
       0,   146,   145,     0,   152,     0,     0,   449,     0,   448,
       0,   480,     0,     0,   455,   156,     0,   454,   154,    55,
      54,   172,   465,   174,     0,   400,   283,     0,     0,   368,
     310,   326,   361,   391,     0,   544,     0,   198,     0,     0,
       0,   188,     0,   163,   462,     0,     0,   161,   461,     0,
     549,    65,    66,   202,   510,   223,   223,   200,   223,   210,
     219,   217,     0,   289,   235,   239,     0,   265,     0,   231,
     232,   483,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   223,   453,     0,     0,   482,   459,     0,     0,     0,
       0,   177,   368,   400,     0,   403,   402,   404,   497,   322,
     286,   284,     0,     0,     0,     0,   389,   497,   199,   197,
       0,   191,     0,   164,     0,   162,   211,   382,     0,   314,
       0,   237,    75,   107,    77,   278,   278,     0,     0,     0,
       0,     0,     0,   203,   201,     0,     0,     0,     0,    56,
     176,   285,   368,   392,     0,   323,   325,   324,   340,     0,
     341,   328,   331,     0,   327,   318,   319,   222,     0,   189,
       0,     0,     0,   381,   380,   497,   315,   326,   279,   233,
     234,     0,     0,     0,     0,     0,     0,   452,   451,   458,
     457,   288,   287,   394,   395,   397,   497,     0,   544,   339,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   497,
     464,   463,     0,   372,     0,     0,     0,   396,   398,   330,
     332,   333,   336,   337,   338,   334,   335,   329,   377,   375,
     497,   544,   316,   230,   317,   392,   376,   497,   399
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -926,  -926,  -926,     1,  -401,   476,  -926,  -926,  -926,  -926,
     360,   425,  -399,    96,    95,  -926,  -926,  -926,    56,   720,
    -926,   180,  -149,  -630,  -926,  -926,  -799,  -926,  1648,  -900,
    -694,   -48,  -926,  -926,  -926,   105,  -926,  -926,  -926,   470,
    -926,    11,  -926,  -926,  -926,  -926,  -926,   563,   191,   -74,
    -926,  -926,  -926,    -5,   777,  -926,  -926,  -926,  -926,  -926,
    -926,  -926,  -926,  -137,  -143,  -737,  -926,  -131,    39,   169,
    -926,  -926,  -926,    -3,  -926,  -926,  -264,     5,  -926,  -200,
    -222,  -252,  -242,  -365,  -926,  -170,  -926,     9,   738,  -116,
     345,  -926,  -376,  -707,  -925,  -926,  -508,  -443,  -845,  -859,
    -770,    -4,  -926,  -158,  -926,  -144,  -926,   223,   660,  -341,
    -926,  -926,  -926,  1115,  -926,    -7,  -926,  -926,  -189,  -926,
    -558,  -926,  -926,  1191,  1432,   -11,    -1,    89,   996,  -926,
    1757,  1902,  -926,  -926,  -926,  -926,  -926,  -926,  -926,  -926,
    -367
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,   291,   100,   577,   102,   103,   104,   308,
     105,   292,   572,   576,   573,   106,   107,   108,   109,   163,
     801,   236,   110,   233,   804,   111,   603,   196,   241,   112,
     113,   114,   115,   116,   117,   677,   118,   119,   120,   444,
     618,   740,   121,   122,   614,   735,   123,   124,   480,   752,
     125,   126,   649,   650,   171,   234,   594,   128,   129,   482,
     758,   655,   805,   806,   414,   884,   418,   590,   591,   592,
     593,   656,   314,   723,   987,  1043,   977,   254,   966,   920,
     924,   971,   972,   973,   130,   280,   449,   131,   132,   237,
     238,   422,   423,   607,   984,   939,   426,   604,  1004,   917,
     849,   293,   187,   297,   298,   388,   389,   390,   172,   134,
     135,   136,   137,   173,   139,   160,   161,   533,   403,   694,
     534,   535,   140,   174,   175,   143,   197,   391,   177,   145,
     178,   179,   148,   149,   150,   303,   151,   152,   153,   154,
     155
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     158,   364,   537,    99,   176,   619,   695,   181,   251,   252,
     180,   575,   380,   188,   407,   315,   589,   191,   191,   852,
     201,   203,   207,   208,   976,   392,   803,   192,   424,   183,
     465,   242,   968,   243,   244,   239,   427,   424,   245,   239,
     246,   386,   247,   613,   595,   543,   697,   239,   690,   915,
     256,   260,   262,   264,   265,   266,    62,   255,   879,   270,
     386,   271,    62,   274,   278,   415,     3,   381,   281,   889,
     890,   282,   283,   651,   284,   912,   285,   664,  -383,   286,
     287,  1010,   288,   968,   605,   256,   260,   302,   854,   726,
    1007,   470,  -471,   424,   301,   937,   712,   401,  1039,  -521,
     386,  -521,   296,   891,  1005,   432,  -195,   620,   809,  1011,
     969,   464,   468,   401,   665,   401,  1046,   652,   543,   386,
     471,   970,   732,   466,   442,   976,   401,   156,   653,   428,
     273,   277,   364,   713,   376,  1042,   200,   202,   466,   983,
     376,  -383,   921,   962,  -383,   434,  -378,   654,  -195,  1028,
    -383,   261,   467,   158,   372,   373,   374,   270,   256,   302,
     810,   425,  -383,  1027,   733,   376,   375,   544,   463,   376,
     425,  -383,   970,  -383,   379,  -378,   376,   376,   376,   260,
     159,   466,   501,   466,   936,  -123,   299,   719,  -378,  -383,
    -383,   365,    16,   366,   191,   387,   459,   537,   260,  -383,
    1048,  -378,  -195,   300,   408,   961,   394,   879,   989,   990,
     855,   466,  1008,   183,   387,   851,   386,   386,   734,   232,
     725,   523,   524,   460,   401,   461,   425,   922,   938,   -82,
     367,   720,   666,   434,   368,  -379,   715,   -88,   260,   191,
    1041,  -401,   721,  -123,   830,   575,   436,   437,  -378,  -485,
      59,  -383,   462,  -378,   387,  1002,   279,   260,   803,   667,
     688,   722,  -401,   716,  -379,   312,  -401,  -123,  -484,   715,
     162,   831,   905,   387,    78,   456,  -485,  -379,   557,   743,
     -84,   670,   923,   383,   458,   368,   184,   190,   -89,  -401,
    -379,   313,   386,   455,   248,  -484,   988,   615,   478,   537,
     457,   625,   384,   627,   310,   477,   311,   484,   485,   486,
     487,   489,   491,   492,   589,   493,   494,   495,   496,   497,
     209,   502,   503,   504,   505,   506,   507,   508,   509,   510,
     511,   512,   513,   514,   515,   516,   517,  -379,  -393,   755,
      21,   847,  -379,   260,   260,    21,   434,   428,   606,   260,
     428,   878,   260,   260,   260,   260,   526,   528,   536,  -393,
     249,   268,   279,  -393,   756,   435,   483,   546,   321,   549,
     387,   387,   550,   919,   551,   279,   156,  -371,   395,   699,
     702,  -521,   453,  -521,    52,   256,  -393,   561,   563,    52,
     434,   428,   559,   567,   569,    60,   267,   306,   574,   574,
      60,   578,   240,   580,   307,   386,  -371,  -348,   309,   642,
     686,  -519,   926,  -519,   182,   421,   608,   394,   322,  -371,
      80,   316,   323,   612,   240,    80,  -348,   488,   490,   318,
     260,   156,  -371,   433,   272,   276,  -520,   639,  -520,   611,
    -468,   744,   746,   518,   519,   612,   387,  -467,   260,   520,
     260,   741,   521,   522,   631,   612,   634,   317,   636,   638,
    -472,   611,  1012,   537,   296,  -473,   296,  -373,   256,   325,
     369,   611,   525,   527,   329,   645,   455,   331,   101,  -371,
    -470,   334,   589,   545,  -371,  -469,   371,   157,  1013,   331,
    1014,  1015,   376,     5,  1016,  1017,  -373,   382,   385,   186,
     878,   189,   396,   417,   562,   329,  -384,   918,   331,  -373,
     568,   438,   334,   807,   927,   441,  -384,   448,   450,   472,
     498,   476,  -373,   479,   481,   552,   548,   561,   673,   567,
     676,   578,   678,   634,   554,   553,   555,   558,   679,   680,
     377,   260,   564,   260,   499,  -384,   269,   687,   299,   689,
     299,   579,   596,   536,   581,   696,   597,   682,   606,   387,
     240,   240,   240,   240,   610,   582,   582,   616,   413,  -373,
     630,  -384,   101,   556,  -373,   617,   305,   621,  -384,   646,
     629,   657,    71,   583,   583,   635,   584,   584,   500,   266,
     270,   302,   658,   659,   660,   260,   662,   985,   728,  -384,
     421,   661,   240,   703,  1009,   240,   585,   585,   -59,   586,
     586,    54,   304,   663,   704,   321,   706,   707,  -384,   724,
     587,   587,  1006,  -384,   240,   736,  -384,   731,   434,   753,
     754,   757,   574,   574,   814,   817,   370,  1019,   819,   588,
     588,   683,   240,   823,   672,   844,   675,  1031,  1032,  1033,
    1034,  1035,  1036,   848,   850,   536,   641,   860,   489,   526,
     813,   648,   133,   816,   853,   322,   865,  1006,     5,   323,
     869,   133,   871,   873,  -108,   872,  -281,  -113,   883,   827,
      14,   829,  1040,   133,   -85,   133,   834,    19,  -112,   837,
    -109,  -115,   839,   -83,   840,   730,  -116,   842,  -111,  -114,
    1047,   -86,  -110,  -281,  1006,  -117,    35,   887,   416,   -87,
     888,    38,   910,   986,   -82,   429,   325,   -84,   913,    43,
     930,   329,   256,   330,   331,  1011,    48,   953,   334,   858,
     133,   475,   864,   321,   868,  1038,   341,   870,   749,   240,
     750,    58,   185,   880,   347,   946,   446,   685,   859,   901,
     881,   945,   940,    68,   846,   882,   133,    71,   714,   393,
     133,  1044,  1001,   240,    77,  1025,  1037,   240,   101,  1030,
      81,   206,   718,   609,   488,   525,   421,   684,     0,   127,
       0,     0,   101,   322,     0,     0,     0,   323,   127,   886,
       0,     0,     0,     0,     0,     0,     0,   739,     0,     0,
     127,   279,   127,   827,   829,     0,   834,   837,   864,   868,
       0,     0,     0,     0,   902,   903,     0,   904,     0,   536,
     133,   906,   907,     0,     0,   908,     0,   251,   252,     0,
       0,     0,     0,     0,   325,   326,   802,   327,   328,   329,
       0,   330,   331,   925,   634,     0,   334,   127,     0,   931,
       0,   932,   101,   916,   341,   934,     0,   204,    21,     0,
     345,   346,   347,   191,     0,     0,     0,     0,    28,   250,
       0,     0,     0,   127,   429,   582,     0,   127,    37,     0,
     429,   902,   947,   948,   906,   949,   950,   951,   952,     0,
       0,     0,   133,   583,   845,     0,   584,   421,   959,   133,
      50,     0,    52,   302,     0,     0,     0,     0,   967,     0,
     964,     0,   974,    60,     0,     0,   585,   739,     0,   586,
       0,    54,   240,   240,   965,     0,     0,     0,   240,   240,
     587,     0,     0,     0,     0,   648,     0,   127,    80,   628,
     711,     0,     0,   633,   997,   998,   999,  1000,     0,   588,
       0,   101,   133,     0,     0,     0,     0,     0,     0,     0,
     885,     0,     0,     0,     0,     0,   133,   868,  1003,  1020,
    1021,   302,     0,     0,     0,     0,     0,   738,  1024,     0,
     997,   998,   999,  1000,  1020,  1021,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1026,   634,   144,  1029,
       0,     0,     0,     0,     0,     0,     0,   144,     0,   127,
       0,     0,     0,  1003,     0,     0,   127,     0,     0,   144,
       0,   144,     0,     0,     0,     0,     0,     0,    16,     0,
     634,     0,    20,    21,   868,     0,   133,     0,     0,   240,
     240,    27,     0,    28,   874,     0,     0,   240,    33,   413,
    1003,     0,     0,    37,     0,   709,   413,     0,   133,   240,
       0,     0,   240,     0,   133,     0,   144,     0,   802,   127,
     275,   275,   133,     0,     0,    50,     0,    52,     0,    54,
       0,   875,     0,   127,   876,     0,    59,     0,    60,     0,
       0,     0,   144,     0,     0,     0,   144,     0,     0,     0,
     861,     0,     0,     0,     0,   742,     0,    76,     0,     0,
      78,   747,     0,    80,     0,     0,     0,   138,     0,     0,
       0,     0,     0,   133,     0,     0,   138,   133,   321,     0,
       0,     0,     0,     0,     0,   133,     0,     0,   138,     0,
     138,     0,     0,     0,     0,    16,     0,     0,     0,    20,
      21,     0,     0,   127,     0,     0,   144,     0,    27,     0,
      28,   874,     0,    94,     0,    33,   429,     0,   429,   877,
      37,     0,     0,   429,     0,   127,   429,     0,   322,     0,
       0,   127,   323,   841,     0,   138,   843,     0,     0,   127,
       0,     0,    50,   141,    52,   668,    54,     0,   875,     0,
       0,   876,   141,    59,     0,    60,     0,  -388,   857,     0,
       0,   138,     0,     0,   141,   138,   141,  -388,   240,   863,
       0,   867,     0,     0,    76,     0,     0,    78,   144,   325,
      80,     0,     0,     0,   329,   144,   330,   331,     0,   133,
     127,   334,     0,     0,   127,     0,  -388,     0,     0,   341,
       0,     0,   127,     0,     0,   345,   346,   347,     0,     0,
     321,   141,     0,   413,   413,     0,     0,   413,   413,     0,
       0,     0,  -388,     0,     0,   138,     0,     0,     0,  -388,
      94,     0,     0,     0,   975,     0,   954,   141,   144,   133,
     979,   141,   413,     0,   413,   133,     0,     0,     0,     0,
    -388,     0,   144,     0,     0,     0,     0,     0,     0,     0,
     322,     0,     0,     0,   323,     0,   808,     0,     0,  -388,
     911,     0,     0,     0,  -388,     0,     0,  -388,     0,   811,
     812,     0,   928,     0,     0,     0,     0,     0,     0,     0,
       0,   933,     0,     0,     0,   935,     0,   138,     0,     0,
     133,   141,   133,     0,   138,     0,   127,   133,     0,     0,
     133,   325,   326,     0,   327,   328,   329,   133,   330,   331,
     133,     0,   144,   334,     0,     0,     0,     0,     0,     0,
     340,   341,     0,     0,   344,   975,   960,   345,   346,   347,
       0,     0,   133,     0,   144,     0,     0,     0,     0,     0,
     144,     0,     0,   133,     0,   133,   127,   138,   144,     0,
       0,     0,   127,     0,     0,     0,     0,     0,   319,     0,
       0,   138,     0,   141,     0,   320,     0,     0,     0,     0,
     141,     0,     0,     0,   142,     0,   321,     0,     0,     0,
       0,     0,     0,   142,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   142,     0,   142,     0,   144,
       0,     0,     0,   144,     0,     0,     0,   127,     0,   127,
       0,   144,     0,     0,   127,     0,     0,   127,     0,     0,
       0,     0,     0,   141,   127,   133,   322,   127,     0,     0,
     323,   138,   133,     0,     0,     0,     0,   141,     0,     0,
       0,     0,   142,     0,   133,     0,     0,     0,     0,   127,
       0,     0,     0,   138,     0,     0,   133,   401,     0,   138,
     127,   324,   127,     0,     0,   133,     0,   138,   142,   133,
       0,     0,   142,     0,     0,     0,     0,   325,   326,     0,
     327,   328,   329,     0,   330,   331,   332,   321,   333,   334,
     335,   336,   337,     0,   338,   339,   340,   341,   342,   343,
     344,     0,     0,   345,   346,   347,     0,   141,     0,     0,
     133,     0,   745,     0,     0,   144,     0,     0,   138,     0,
       0,     0,   138,     0,     0,     0,     0,     0,     0,   141,
     138,     0,   142,     0,     0,   141,     0,   322,     0,     0,
       0,   323,   127,   141,     0,     0,     0,     0,     0,   127,
       0,     0,     0,     0,     0,   133,   133,   133,   133,     0,
       0,   127,     0,     0,     0,   144,     0,     0,     0,     0,
       0,   144,     0,   127,     0,     0,     0,     0,     0,     0,
     133,   133,   127,     0,     0,     0,   127,     0,   325,   326,
       0,     0,   328,   329,   141,   330,   331,     0,   141,     0,
     334,     0,     0,   321,   142,     0,   141,     0,   341,     0,
       0,   142,     0,     0,   345,   346,   347,     0,     0,     0,
       0,  -390,     0,     0,     0,     0,   144,   127,   144,     0,
       0,  -390,     0,   144,   138,     0,   144,     0,     0,     0,
       0,     0,     0,   144,     0,     0,   144,     0,     0,     0,
       0,     0,   263,   322,     0,     0,     0,   323,     0,     0,
    -390,     0,     0,     0,   142,     0,     0,     0,   144,     0,
       0,     0,   127,   127,   127,   127,     0,     0,   142,   144,
       0,   144,     0,     0,   138,     0,  -390,     0,     0,     0,
     138,     0,     0,  -390,     0,     0,     0,   127,   127,   146,
       0,     0,     0,     0,   325,   326,     0,     0,   146,   329,
     141,   330,   331,     0,  -390,     0,   334,     0,     0,     0,
     146,     0,   146,     0,   341,     0,     0,     0,     0,     0,
     345,   346,   347,  -390,     0,     0,     0,     0,  -390,     0,
       0,  -390,     0,     0,     0,   138,     0,   138,   142,     0,
       0,     0,   138,     0,     0,   138,     0,     0,     0,     0,
     141,   144,   138,     0,     0,   138,   141,   146,   144,     0,
     142,     0,     0,     0,     0,     0,   142,     0,     0,     0,
     144,     0,     0,     0,   142,     0,     0,   138,   397,   400,
     402,   406,   144,   146,     0,     0,     0,   146,   138,     0,
     138,   144,     0,     0,     0,   144,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   141,     0,   141,     0,     0,     0,     0,   141,     0,
     430,   141,     0,   431,     0,   142,     0,     0,   141,   142,
       0,   141,     0,     0,   147,     0,   144,   142,     0,     0,
       0,     0,   440,   147,     0,     0,     0,   146,     0,     0,
       0,     0,     0,   141,     0,   147,     0,   147,     0,     0,
     451,     0,     0,     0,   141,     0,   141,     0,     0,     0,
     138,     0,     0,     0,     0,     0,     0,   138,     0,   204,
      21,   144,   144,   144,   144,     0,     0,     0,     0,   138,
      28,   250,     0,     0,     0,     0,     0,     0,     0,     0,
      37,   138,   147,  -223,     0,     0,   144,   144,     0,     0,
     138,     0,     0,     0,   138,     0,     0,     0,     0,   146,
       0,     0,    50,     0,    52,     0,   146,     0,   147,  -223,
       0,   210,   147,     0,     0,    60,     0,     0,     0,     0,
       0,   142,     0,   211,   212,     0,   141,     0,     0,     0,
     213,     0,     0,   141,     0,   138,     0,   547,   214,   -63,
      80,     0,     0,     0,   215,   141,     0,     0,     0,   216,
       0,   217,     0,     0,   218,     0,     0,   141,     0,   146,
       0,   565,   219,     0,     0,   570,   141,     0,   220,   221,
     141,   142,   147,   146,     0,   222,     0,   142,     0,     0,
     138,   138,   138,   138,   223,     0,     0,     0,     0,     0,
       0,     0,     0,   224,   225,     0,     0,     0,   226,     0,
     227,     0,     0,   228,     0,   138,   138,   229,   419,     0,
     230,   141,     0,   231,     0,     0,     0,   348,   349,   350,
     351,   352,   353,   354,   355,   356,   357,   358,   359,   360,
     361,   362,   142,     0,   142,     0,     0,     0,     0,   142,
       0,     0,   142,   146,   147,     0,     0,     0,  -492,   142,
       0,   147,   142,     0,     0,     0,   141,   141,   141,   141,
       0,   363,     0,     0,  -519,   146,  -519,     0,     0,   420,
       0,   146,     0,     0,   142,     0,     0,     0,     0,   146,
       0,   141,   141,     0,     0,   142,     0,   142,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     5,     6,
       7,     8,     9,    10,   147,     0,     0,   164,     0,     0,
      14,    15,     0,     0,     0,     0,     0,    19,   147,     0,
     691,   693,     0,     0,     0,    26,   698,   701,     0,     0,
     146,    30,   165,   166,   146,   167,    35,     0,    36,     0,
       0,    38,   146,     0,     0,    40,    41,  -374,     0,    43,
      44,     0,    45,    46,     0,    47,    48,     0,     0,     0,
       0,     0,    51,     0,    53,     0,    55,   142,     0,     0,
       0,    58,     0,     0,   142,     0,  -374,     0,     0,     0,
      65,    66,    67,    68,    69,   168,   142,    71,   147,  -374,
      73,     0,     0,     0,    77,     0,     0,    79,   142,     0,
      81,     0,  -374,     0,     0,     0,     0,   142,     0,     0,
     147,   142,     0,     0,     0,     0,   147,     0,     0,     0,
       0,     0,     0,     0,   147,     0,    87,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   821,   822,     0,
       0,     0,     0,   751,     0,   824,   146,     0,     0,  -374,
       0,     0,   142,     0,  -374,     0,    97,   835,   982,     0,
     838,  -209,     0,     0,     0,  -209,  -209,     0,     0,     0,
       0,     0,     0,     0,  -209,   147,  -209,  -209,     0,   147,
       0,  -209,   204,    21,     0,     0,  -209,   147,     0,  -209,
       0,     0,     0,    28,   250,     0,   146,   142,   142,   142,
     142,     0,   146,    37,     0,     0,  -223,     0,  -209,     0,
    -209,     0,  -209,     0,  -209,  -209,     0,  -209,     0,  -209,
       0,  -209,   142,   142,     0,    50,     0,    52,     0,     0,
       0,     0,  -223,     0,     0,     0,     0,     0,    60,     0,
    -209,     0,     0,  -209,     0,     0,  -209,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   146,     0,   146,
       0,     0,   -62,    80,   146,     0,     0,   146,     0,     0,
       0,     0,     0,     0,   146,     0,     0,   146,     0,     0,
       0,     0,     0,     0,     0,     0,   900,     0,     0,     0,
       0,   147,     0,     0,     0,     0,  -209,     0,     0,   146,
       0,     0,  -209,     0,  -209,     0,     0,     0,  -209,  -209,
     146,     0,   146,     0,     0,     0,   929,  -209,    16,  -209,
    -209,     0,    20,    21,  -209,     0,     0,     0,     0,  -209,
       0,    27,  -209,    28,   874,     0,     0,     0,    33,     0,
       0,   147,     0,    37,     0,     0,     0,   147,     0,     0,
       0,  -209,     0,  -209,     0,  -209,     0,  -209,  -209,     0,
    -209,     0,  -209,     0,  -209,    50,     0,    52,     0,   304,
       0,   875,     0,     0,   876,     0,    59,     0,    60,     0,
       0,     0,     0,  -209,     0,     0,  -209,     0,     0,  -209,
       0,     0,   146,     0,     0,     0,     0,    76,     0,   146,
      78,     0,   147,    80,   147,     0,     0,     0,     0,   147,
       0,   146,   147,     0,     0,     0,     0,     0,     0,   147,
       0,     0,   147,   146,     0,     0,     0,     0,     0,     0,
       0,     0,   146,     0,     0,     0,   146,     0,     0,  -209,
       0,     0,     0,     0,   147,  -209,     0,     5,     6,     7,
       8,     9,    10,    94,     0,   147,   164,   147,     0,    14,
      15,     0,     0,     0,     0,     0,    19,     0,     0,     0,
       0,     0,     0,     0,    26,     0,     0,   146,     0,     0,
      30,   165,   166,     0,   167,    35,     0,    36,     0,     0,
      38,     0,     0,     0,    40,    41,     0,     0,    43,    44,
       0,    45,    46,     0,    47,    48,     0,     0,     0,     0,
     319,    51,     0,    53,     0,    55,     0,   320,     0,     0,
      58,     0,   146,   146,   146,   146,     0,     0,   321,    65,
      66,    67,    68,    69,   168,     0,    71,   147,     0,    73,
       0,     0,     0,    77,   147,     0,    79,   146,   146,    81,
       0,     0,     0,     0,     0,     0,   147,     0,  -392,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   147,     0,
       0,     0,     0,     0,     0,    87,     0,   147,   322,  -392,
       0,   147,   323,  -392,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   253,     0,     0,
       0,     0,     0,   169,     0,    97,  -392,   914,     0,     0,
       0,     0,     0,   324,     0,     0,     0,     0,     0,     0,
       0,     0,   147,     0,     0,     0,     0,     0,     0,   325,
     326,     0,   327,   328,   329,     0,   330,   331,   332,     0,
     333,   334,   335,   336,   337,     0,   338,   339,   340,   341,
     342,   343,   344,     0,     0,   345,   346,   347,     0,     0,
       0,     0,     0,     0,   820,     0,     0,   147,   147,   147,
     147,     0,     0,     0,     0,    -2,     4,     0,     5,     6,
       7,     8,     9,    10,     0,     0,     0,    11,    12,    13,
      14,    15,   147,   147,    16,    17,    18,    19,    20,    21,
      22,    23,    24,     0,    25,    26,     0,    27,     0,    28,
      29,    30,    31,    32,    33,    34,    35,     0,    36,    37,
       0,    38,  -223,     0,    39,    40,    41,     0,    42,    43,
      44,   -43,    45,    46,     0,    47,    48,    49,     0,     0,
       0,    50,    51,    52,    53,    54,    55,    56,  -223,   -43,
      57,    58,    59,     0,    60,    61,    62,     0,    63,    64,
      65,    66,    67,    68,    69,    70,     0,    71,    72,     0,
      73,    74,    75,    76,    77,     0,    78,    79,   -61,    80,
      81,     0,     0,    82,     0,    83,     0,     0,    84,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    85,    86,    87,    88,    89,     0,
       0,     0,     0,    90,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    91,     0,     0,    92,    93,     0,    94,
       0,     0,    95,     0,    96,     0,    97,  1022,    98,     5,
       6,     7,     8,     9,    10,     0,     0,     0,   164,     0,
       0,    14,    15,     0,     0,     0,     0,     0,    19,     0,
       0,     0,     0,     0,     0,     0,    26,     0,     0,     0,
       0,     0,    30,   165,   166,     0,   167,    35,     0,    36,
       0,     0,    38,     0,     0,     0,    40,    41,     0,     0,
      43,    44,     0,    45,    46,     0,    47,    48,     0,     0,
       0,     0,     0,    51,     0,    53,     0,    55,     0,     0,
       0,     0,    58,     0,     0,     0,     0,     0,     0,     0,
       0,    65,    66,    67,    68,    69,   168,     0,    71,     0,
       0,    73,     0,     0,     0,    77,     0,     0,    79,     0,
       0,    81,     0,     0,     0,     0,     0,     0,     0,    84,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    85,    86,    87,    88,    89,
       0,     0,     0,     0,    90,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    91,     0,     0,    92,    93,   253,
       0,     0,     0,    95,     0,   169,     0,    97,     0,   170,
    1023,     4,     0,     5,     6,     7,     8,     9,    10,     0,
    -544,     0,    11,    12,    13,    14,    15,  -544,     0,    16,
      17,    18,    19,    20,    21,    22,    23,    24,  -544,    25,
      26,  -544,    27,     0,    28,    29,    30,    31,    32,    33,
      34,    35,     0,    36,    37,     0,    38,  -223,     0,    39,
      40,    41,     0,    42,    43,    44,   -43,    45,    46,     0,
      47,    48,    49,     0,     0,     0,    50,    51,    52,    53,
       0,    55,    56,  -223,   -43,    57,    58,    59,  -544,    60,
      61,    62,  -544,    63,    64,    65,    66,    67,    68,    69,
      70,     0,    71,    72,     0,    73,    74,    75,    76,    77,
       0,    78,    79,   -61,    80,    81,     0,     0,    82,     0,
      83,     0,     0,  -544,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -544,
    -544,    87,  -544,  -544,  -544,  -544,  -544,  -544,  -544,     0,
    -544,  -544,  -544,  -544,  -544,     0,  -544,  -544,  -544,  -544,
    -544,  -544,  -544,  -544,    94,  -544,  -544,  -544,     0,    96,
    -544,    97,   289,    98,     5,     6,     7,     8,     9,    10,
       0,     0,     0,    11,    12,    13,    14,    15,     0,     0,
      16,    17,    18,    19,    20,    21,    22,    23,    24,     0,
      25,    26,     0,    27,     0,    28,    29,    30,    31,    32,
      33,    34,    35,     0,    36,    37,     0,    38,  -223,     0,
      39,    40,    41,     0,    42,    43,    44,   -43,    45,    46,
       0,    47,    48,    49,     0,     0,     0,    50,    51,    52,
      53,    54,    55,    56,  -223,   -43,    57,    58,    59,     0,
      60,    61,    62,     0,    63,    64,    65,    66,    67,    68,
      69,    70,     0,    71,    72,     0,    73,    74,    75,    76,
      77,     0,    78,    79,   -61,    80,    81,     0,     0,    82,
       0,    83,     0,     0,    84,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      85,    86,    87,    88,    89,     0,     0,     0,     0,    90,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    91,
       0,     0,    92,    93,   253,    94,     0,     0,    95,     0,
      96,   290,    97,     4,    98,     5,     6,     7,     8,     9,
      10,     0,     0,     0,    11,    12,    13,    14,    15,     0,
       0,    16,    17,    18,    19,    20,    21,    22,    23,    24,
       0,    25,    26,     0,    27,     0,    28,    29,    30,    31,
      32,    33,    34,    35,     0,    36,    37,     0,    38,  -223,
       0,    39,    40,    41,     0,    42,    43,    44,   -43,    45,
      46,     0,    47,    48,    49,     0,     0,     0,    50,    51,
      52,    53,    54,    55,    56,  -223,   -43,    57,    58,    59,
       0,    60,    61,    62,     0,    63,    64,    65,    66,    67,
      68,    69,    70,     0,    71,    72,     0,    73,    74,    75,
      76,    77,     0,    78,    79,   -61,    80,    81,     0,     0,
      82,     0,    83,     0,     0,    84,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    85,    86,    87,    88,    89,     0,     0,     0,     0,
      90,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      91,     0,     0,    92,    93,     0,    94,     0,     0,    95,
       0,    96,   454,    97,   473,    98,     5,     6,     7,     8,
       9,    10,     0,     0,     0,    11,    12,    13,    14,    15,
       0,     0,    16,    17,    18,    19,    20,    21,    22,    23,
      24,     0,    25,    26,     0,    27,     0,    28,    29,    30,
      31,    32,    33,    34,    35,     0,    36,    37,     0,    38,
    -223,     0,    39,    40,    41,     0,    42,    43,    44,   -43,
      45,    46,     0,    47,    48,    49,     0,     0,     0,    50,
      51,    52,    53,    54,    55,    56,  -223,   -43,    57,    58,
      59,     0,    60,    61,    62,     0,    63,    64,    65,    66,
      67,    68,    69,    70,     0,    71,    72,     0,    73,    74,
      75,    76,    77,     0,    78,    79,   -61,    80,    81,     0,
       0,    82,     0,    83,     0,     0,    84,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    85,    86,    87,    88,    89,     0,     0,     0,
       0,    90,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    91,     0,     0,    92,    93,     0,    94,     0,     0,
      95,     0,    96,   474,    97,   289,    98,     5,     6,     7,
       8,     9,    10,     0,     0,     0,    11,    12,    13,    14,
      15,     0,     0,    16,    17,    18,    19,    20,    21,    22,
      23,    24,     0,    25,    26,     0,    27,     0,    28,    29,
      30,    31,    32,    33,    34,    35,     0,    36,    37,     0,
      38,  -223,     0,    39,    40,    41,     0,    42,    43,    44,
     -43,    45,    46,     0,    47,    48,    49,     0,     0,     0,
      50,    51,    52,    53,    54,    55,    56,  -223,   -43,    57,
      58,    59,     0,    60,    61,    62,     0,    63,    64,    65,
      66,    67,    68,    69,    70,     0,    71,    72,     0,    73,
      74,    75,    76,    77,     0,    78,    79,   -61,    80,    81,
       0,     0,    82,     0,    83,     0,     0,    84,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    85,    86,    87,    88,    89,     0,     0,
       0,     0,    90,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    91,     0,     0,    92,    93,     0,    94,     0,
       0,    95,     0,    96,   290,    97,     4,    98,     5,     6,
       7,     8,     9,    10,     0,     0,     0,    11,    12,    13,
      14,    15,     0,     0,    16,    17,    18,    19,    20,    21,
      22,    23,    24,     0,    25,    26,     0,    27,     0,    28,
      29,    30,    31,    32,    33,    34,    35,     0,    36,    37,
       0,    38,  -223,     0,    39,    40,    41,     0,    42,    43,
      44,   -43,    45,    46,     0,    47,    48,    49,     0,     0,
       0,    50,    51,    52,    53,    54,    55,    56,  -223,   -43,
      57,    58,    59,     0,    60,    61,    62,     0,    63,    64,
      65,    66,    67,    68,    69,    70,     0,    71,    72,     0,
      73,    74,    75,    76,    77,     0,    78,    79,   -61,    80,
      81,     0,     0,    82,     0,    83,     0,     0,    84,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    85,    86,    87,    88,    89,     0,
       0,     0,     0,    90,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    91,     0,     0,    92,    93,     0,    94,
       0,     0,    95,     0,    96,   640,    97,     4,    98,     5,
       6,     7,     8,     9,    10,     0,     0,     0,    11,    12,
      13,    14,    15,     0,     0,    16,    17,    18,    19,    20,
      21,    22,    23,    24,     0,    25,    26,     0,    27,     0,
      28,    29,    30,    31,    32,    33,    34,    35,     0,    36,
      37,     0,    38,  -223,     0,    39,    40,    41,     0,    42,
      43,    44,   -43,    45,    46,     0,    47,    48,    49,     0,
       0,     0,    50,    51,    52,    53,   304,    55,    56,  -223,
     -43,    57,    58,    59,     0,    60,    61,    62,     0,    63,
      64,    65,    66,    67,    68,    69,    70,     0,    71,    72,
       0,    73,    74,    75,    76,    77,     0,    78,    79,   -61,
      80,    81,     0,     0,    82,     0,    83,     0,     0,    84,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    85,    86,    87,    88,    89,
       0,     0,     0,     0,    90,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    91,     0,     0,    92,    93,     0,
      94,     0,     0,    95,     0,    96,     0,    97,     4,    98,
       5,     6,     7,     8,     9,    10,     0,     0,     0,    11,
      12,    13,    14,    15,     0,     0,    16,    17,    18,    19,
      20,    21,    22,    23,    24,     0,    25,    26,     0,    27,
       0,    28,    29,    30,    31,    32,    33,    34,    35,     0,
      36,    37,     0,    38,  -223,     0,    39,    40,    41,     0,
      42,    43,    44,   -43,    45,    46,     0,    47,    48,    49,
       0,     0,     0,    50,    51,    52,    53,     0,    55,    56,
    -223,   -43,    57,    58,    59,     0,    60,    61,    62,     0,
      63,    64,    65,    66,    67,    68,    69,    70,     0,    71,
      72,     0,    73,    74,    75,    76,    77,     0,    78,    79,
     -61,    80,    81,     0,     0,    82,     0,    83,     0,     0,
      84,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    85,    86,    87,    88,
      89,     0,     0,     0,     0,    90,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    91,     0,     0,    92,    93,
       0,    94,     0,     0,    95,     0,    96,     0,    97,     4,
      98,     5,     6,     7,     8,     9,    10,     0,     0,     0,
      11,    12,    13,    14,    15,     0,     0,    16,    17,    18,
      19,    20,    21,    22,    23,    24,     0,    25,    26,     0,
      27,     0,    28,    29,    30,    31,    32,    33,   560,    35,
       0,    36,    37,     0,    38,  -223,     0,    39,    40,    41,
       0,    42,    43,    44,   -43,    45,    46,     0,    47,    48,
      49,     0,     0,     0,    50,    51,    52,    53,     0,    55,
      56,  -223,   -43,    57,    58,    59,     0,    60,    61,    62,
       0,    63,    64,    65,    66,    67,    68,    69,    70,     0,
      71,    72,     0,    73,    74,    75,    76,    77,     0,    78,
      79,   -61,    80,    81,     0,     0,    82,     0,    83,     0,
       0,    84,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    85,    86,    87,
      88,    89,     0,     0,     0,     0,    90,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    91,     0,     0,    92,
      93,     0,    94,     0,     0,    95,     0,    96,     0,    97,
       4,    98,     5,     6,     7,     8,     9,    10,     0,     0,
       0,    11,    12,    13,    14,    15,     0,     0,    16,    17,
      18,    19,    20,    21,    22,    23,    24,     0,    25,    26,
       0,    27,     0,    28,    29,    30,    31,    32,    33,   566,
      35,     0,    36,    37,     0,    38,  -223,     0,    39,    40,
      41,     0,    42,    43,    44,   -43,    45,    46,     0,    47,
      48,    49,     0,     0,     0,    50,    51,    52,    53,     0,
      55,    56,  -223,   -43,    57,    58,    59,     0,    60,    61,
      62,     0,    63,    64,    65,    66,    67,    68,    69,    70,
       0,    71,    72,     0,    73,    74,    75,    76,    77,     0,
      78,    79,   -61,    80,    81,     0,     0,    82,     0,    83,
       0,     0,    84,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    85,    86,
      87,    88,    89,     0,     0,     0,     0,    90,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    91,     0,     0,
      92,    93,     0,    94,     0,     0,    95,     0,    96,     0,
      97,     4,    98,     5,     6,     7,     8,     9,    10,     0,
       0,     0,    11,    12,    13,    14,    15,     0,     0,    16,
      17,    18,    19,    20,    21,    22,    23,    24,     0,    25,
      26,     0,    27,     0,    28,    29,    30,    31,    32,    33,
     826,    35,     0,    36,    37,     0,    38,  -223,     0,    39,
      40,    41,     0,    42,    43,    44,   -43,    45,    46,     0,
      47,    48,    49,     0,     0,     0,    50,    51,    52,    53,
       0,    55,    56,  -223,   -43,    57,    58,    59,     0,    60,
      61,    62,     0,    63,    64,    65,    66,    67,    68,    69,
      70,     0,    71,    72,     0,    73,    74,    75,    76,    77,
       0,    78,    79,   -61,    80,    81,     0,     0,    82,     0,
      83,     0,     0,    84,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    85,
      86,    87,    88,    89,     0,     0,     0,     0,    90,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    91,     0,
       0,    92,    93,     0,    94,     0,     0,    95,     0,    96,
       0,    97,     4,    98,     5,     6,     7,     8,     9,    10,
       0,     0,     0,    11,    12,    13,    14,    15,     0,     0,
      16,    17,    18,    19,    20,    21,    22,    23,    24,     0,
      25,    26,     0,    27,     0,    28,    29,    30,    31,    32,
      33,   828,    35,     0,    36,    37,     0,    38,  -223,     0,
      39,    40,    41,     0,    42,    43,    44,   -43,    45,    46,
       0,    47,    48,    49,     0,     0,     0,    50,    51,    52,
      53,     0,    55,    56,  -223,   -43,    57,    58,    59,     0,
      60,    61,    62,     0,    63,    64,    65,    66,    67,    68,
      69,    70,     0,    71,    72,     0,    73,    74,    75,    76,
      77,     0,    78,    79,   -61,    80,    81,     0,     0,    82,
       0,    83,     0,     0,    84,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      85,    86,    87,    88,    89,     0,     0,     0,     0,    90,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    91,
       0,     0,    92,    93,     0,    94,     0,     0,    95,     0,
      96,     0,    97,     4,    98,     5,     6,     7,     8,     9,
      10,     0,     0,     0,    11,    12,    13,    14,    15,     0,
       0,    16,    17,    18,    19,    20,    21,    22,    23,    24,
       0,    25,    26,     0,    27,     0,    28,    29,    30,    31,
      32,    33,   833,    35,     0,    36,    37,     0,    38,  -223,
       0,    39,    40,    41,     0,    42,    43,    44,   -43,    45,
      46,     0,    47,    48,    49,     0,     0,     0,    50,    51,
      52,    53,     0,    55,    56,  -223,   -43,    57,    58,    59,
       0,    60,    61,    62,     0,    63,    64,    65,    66,    67,
      68,    69,    70,     0,    71,    72,     0,    73,    74,    75,
      76,    77,     0,    78,    79,   -61,    80,    81,     0,     0,
      82,     0,    83,     0,     0,    84,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    85,    86,    87,    88,    89,     0,     0,     0,     0,
      90,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      91,     0,     0,    92,    93,     0,    94,     0,     0,    95,
       0,    96,     0,    97,     4,    98,     5,     6,     7,     8,
       9,    10,     0,     0,     0,    11,    12,    13,    14,    15,
       0,     0,    16,    17,    18,    19,    20,    21,    22,    23,
      24,     0,    25,    26,     0,    27,     0,    28,    29,    30,
      31,    32,    33,   836,    35,     0,    36,    37,     0,    38,
    -223,     0,    39,    40,    41,     0,    42,    43,    44,   -43,
      45,    46,     0,    47,    48,    49,     0,     0,     0,    50,
      51,    52,    53,     0,    55,    56,  -223,   -43,    57,    58,
      59,     0,    60,    61,    62,     0,    63,    64,    65,    66,
      67,    68,    69,    70,     0,    71,    72,     0,    73,    74,
      75,    76,    77,     0,    78,    79,   -61,    80,    81,     0,
       0,    82,     0,    83,     0,     0,    84,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    85,    86,    87,    88,    89,     0,     0,     0,
       0,    90,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    91,     0,     0,    92,    93,     0,    94,     0,     0,
      95,     0,    96,     0,    97,     4,    98,     5,     6,     7,
       8,     9,    10,     0,     0,     0,    11,    12,    13,    14,
      15,     0,     0,    16,    17,    18,    19,    20,    21,    22,
      23,    24,     0,   856,    26,     0,    27,     0,    28,    29,
      30,    31,    32,    33,    34,    35,     0,    36,    37,     0,
      38,  -223,     0,    39,    40,    41,     0,    42,    43,    44,
     -43,    45,    46,     0,    47,    48,    49,     0,     0,     0,
      50,    51,    52,    53,     0,    55,    56,  -223,   -43,    57,
      58,    59,     0,    60,    61,    62,     0,    63,    64,    65,
      66,    67,    68,    69,    70,     0,    71,    72,     0,    73,
      74,    75,    76,    77,     0,    78,    79,   -61,    80,    81,
       0,     0,    82,     0,    83,     0,     0,    84,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    85,    86,    87,    88,    89,     0,     0,
       0,     0,    90,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    91,     0,     0,    92,    93,     0,    94,     0,
       0,    95,     0,    96,     0,    97,     4,    98,     5,     6,
       7,     8,     9,    10,     0,     0,     0,    11,    12,    13,
      14,    15,     0,     0,    16,    17,    18,    19,    20,    21,
      22,    23,    24,     0,    25,    26,     0,    27,     0,    28,
      29,    30,    31,    32,    33,   862,    35,     0,    36,    37,
       0,    38,  -223,     0,    39,    40,    41,     0,    42,    43,
      44,   -43,    45,    46,     0,    47,    48,    49,     0,     0,
       0,    50,    51,    52,    53,     0,    55,    56,  -223,   -43,
      57,    58,    59,     0,    60,    61,    62,     0,    63,    64,
      65,    66,    67,    68,    69,    70,     0,    71,    72,     0,
      73,    74,    75,    76,    77,     0,    78,    79,   -61,    80,
      81,     0,     0,    82,     0,    83,     0,     0,    84,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    85,    86,    87,    88,    89,     0,
       0,     0,     0,    90,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    91,     0,     0,    92,    93,     0,    94,
       0,     0,    95,     0,    96,     0,    97,     4,    98,     5,
       6,     7,     8,     9,    10,     0,     0,     0,    11,    12,
      13,    14,    15,     0,     0,    16,    17,    18,    19,    20,
      21,    22,    23,    24,     0,    25,    26,     0,    27,     0,
      28,    29,    30,    31,    32,    33,   866,    35,     0,    36,
      37,     0,    38,  -223,     0,    39,    40,    41,     0,    42,
      43,    44,   -43,    45,    46,     0,    47,    48,    49,     0,
       0,     0,    50,    51,    52,    53,     0,    55,    56,  -223,
     -43,    57,    58,    59,     0,    60,    61,    62,     0,    63,
      64,    65,    66,    67,    68,    69,    70,     0,    71,    72,
       0,    73,    74,    75,    76,    77,     0,    78,    79,   -61,
      80,    81,     0,     0,    82,     0,    83,     0,     0,    84,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    85,    86,    87,    88,    89,
       0,     0,     0,     0,    90,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    91,     0,     0,    92,    93,     0,
      94,     0,     0,    95,     0,    96,     0,    97,   727,    98,
       5,     6,     7,     8,     9,    10,     0,     0,     0,   164,
       0,     0,    14,    15,     0,     0,     0,     0,     0,    19,
       0,     0,     0,     0,     0,     0,     0,    26,     0,     0,
       0,     0,     0,    30,   165,   166,     0,   167,    35,     0,
      36,     0,     0,    38,     0,     0,     0,    40,    41,     0,
       0,    43,    44,     0,    45,    46,     0,    47,    48,     0,
       0,     0,     0,     0,    51,     0,    53,     0,    55,     0,
       0,     0,     0,    58,     0,     0,     0,     0,     0,     0,
       0,     0,    65,    66,    67,    68,    69,   168,     0,    71,
       0,     0,    73,     0,     0,     0,    77,     0,     0,    79,
       0,     0,    81,     0,     0,     0,     0,     0,     0,     0,
      84,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    85,    86,    87,    88,
      89,     0,     0,     0,     0,    90,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    91,     0,     0,    92,    93,
     253,     0,     0,     0,    95,     0,   169,     0,    97,     0,
     170,     5,     6,     7,     8,     9,    10,     0,     0,     0,
     164,     0,     0,    14,    15,     0,     0,     0,     0,     0,
      19,     0,     0,     0,     0,     0,     0,     0,    26,     0,
       0,     0,     0,     0,    30,   165,   166,     0,   167,    35,
       0,    36,     0,     0,    38,     0,     0,     0,    40,    41,
       0,     0,    43,    44,     0,    45,    46,     0,    47,    48,
       0,     0,     0,     0,     0,    51,     0,    53,     0,    55,
       0,     0,     0,     0,    58,     0,     0,     0,     0,     0,
       0,     0,     0,    65,    66,    67,    68,    69,   168,     0,
      71,     0,     0,    73,     0,     0,     0,    77,     0,     0,
      79,     0,     0,    81,     0,     0,     0,     0,     0,     0,
       0,    84,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    85,    86,    87,
      88,    89,     0,     0,     0,     0,    90,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    91,     0,     0,    92,
      93,   253,     0,     0,     0,    95,     0,   169,     0,    97,
       0,   170,   632,     5,     6,     7,     8,     9,    10,     0,
       0,     0,   164,     0,     0,    14,    15,     0,     0,     0,
       0,     0,    19,     0,     0,     0,     0,     0,     0,     0,
      26,     0,     0,     0,     0,     0,    30,   165,   166,     0,
     167,    35,     0,    36,     0,     0,    38,     0,     0,     0,
      40,    41,     0,     0,    43,    44,     0,    45,    46,     0,
      47,    48,     0,     0,     0,     0,     0,    51,     0,    53,
       0,    55,     0,     0,     0,     0,    58,     0,     0,     0,
       0,     0,     0,     0,     0,    65,    66,    67,    68,    69,
     168,     0,    71,     0,     0,    73,     0,     0,     0,    77,
       0,     0,    79,     0,     0,    81,     0,     0,     0,     0,
       0,     0,     0,    84,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    85,
      86,    87,    88,    89,     0,     0,     0,     0,    90,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    91,     0,
       0,    92,    93,   253,     0,     0,     0,    95,     0,   169,
       0,    97,     0,   170,   963,     5,     6,     7,     8,     9,
      10,     0,     0,     0,   164,     0,     0,    14,    15,     0,
       0,     0,     0,     0,    19,     0,     0,     0,     0,     0,
       0,     0,    26,     0,     0,     0,     0,     0,    30,   165,
     166,     0,   167,    35,     0,    36,     0,     0,    38,     0,
       0,     0,    40,    41,     0,     0,    43,    44,     0,    45,
      46,     0,    47,    48,     0,     0,     0,     0,     0,    51,
       0,    53,     0,    55,     0,     0,     0,     0,    58,     0,
       0,     0,     0,     0,     0,     0,     0,    65,    66,    67,
      68,    69,   168,     0,    71,     0,     0,    73,     0,     0,
       0,    77,     0,     0,    79,     0,     0,    81,     0,     0,
       0,     0,     0,     0,     0,    84,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   759,     0,   760,
       0,    85,    86,    87,    88,    89,   761,     0,     0,     0,
      90,   762,   212,   763,     0,     0,     0,     0,   764,     0,
      91,     0,     0,    92,    93,     0,   214,     0,     0,    95,
       0,   169,   765,    97,     0,   170,   637,   766,     0,   217,
       0,     0,   767,     0,   768,     0,     0,     0,     0,     0,
     769,     0,     0,     0,     0,     0,   770,   771,     0,     0,
       0,     0,     0,   222,     0,     0,     0,     0,     0,     0,
       0,     0,   772,     0,     0,     0,     0,     0,     0,     0,
       0,   224,   225,     0,   773,     0,   226,     0,   774,     0,
       0,   775,     0,     0,     0,   776,     0,     0,   230,     0,
       0,   777,     0,     0,     0,     0,     0,     0,     0,     0,
     348,   349,   350,   351,   352,   353,     0,     0,   356,   357,
     358,   359,     0,   361,   362,   778,   779,   780,   781,   782,
       0,     0,   783,     0,     0,     0,   784,   785,   786,   787,
     788,   789,   790,   791,   792,   793,   794,     0,   795,     0,
       0,   796,   797,   798,   799,     0,     0,   800,     5,     6,
       7,     8,     9,    10,     0,     0,     0,   164,     0,     0,
      14,    15,     0,     0,     0,     0,     0,    19,   204,    21,
       0,     0,     0,     0,     0,    26,     0,     0,     0,     0,
     205,    30,   165,   166,     0,   167,    35,     0,    36,     0,
       0,    38,     0,     0,     0,    40,    41,     0,     0,    43,
      44,     0,    45,    46,     0,    47,    48,     0,     0,     0,
       0,     0,    51,    52,    53,     0,    55,     0,     0,     0,
       0,    58,     0,     0,    60,     0,     0,     0,     0,     0,
      65,    66,    67,    68,    69,   168,     0,    71,     0,     0,
      73,     0,     0,     0,    77,     0,     0,    79,     0,    80,
      81,     0,     0,     0,     0,     0,     0,     0,    84,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    85,    86,    87,    88,    89,     0,
       0,     0,     0,    90,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    91,     0,     0,    92,    93,     0,     0,
       0,     0,    95,     0,   169,     0,    97,     0,   170,     5,
       6,     7,     8,   193,    10,   194,     0,     0,   164,     0,
       0,    14,    15,     0,     0,  -122,     0,     0,    19,     0,
       0,     0,     0,     0,     0,     0,    26,     0,     0,     0,
       0,     0,    30,   165,   166,     0,   167,    35,     0,    36,
       0,     0,    38,     0,     0,     0,    40,    41,     0,     0,
      43,    44,     0,    45,    46,     0,    47,    48,     0,     0,
       0,     0,     0,    51,     0,    53,     0,    55,     0,     0,
       0,     0,    58,  -122,     0,     0,     0,     0,     0,     0,
       0,    65,    66,    67,    68,    69,   168,     0,    71,     0,
       0,    73,     0,     0,   195,    77,     0,  -122,    79,     0,
       0,    81,     0,     0,     0,     0,     0,     0,     0,    84,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    85,    86,    87,    88,    89,
       0,     0,     0,     0,    90,     0,     0,     5,     6,     7,
       8,     9,    10,     0,    91,     0,   164,    92,    93,    14,
      15,     0,     0,    95,     0,   169,    19,    97,     0,   170,
       0,     0,     0,     0,    26,     0,     0,     0,     0,     0,
      30,   165,   166,     0,   167,    35,     0,    36,     0,     0,
      38,     0,     0,     0,    40,    41,     0,     0,    43,    44,
       0,    45,    46,     0,    47,    48,     0,     0,     0,     0,
       0,    51,     0,    53,     0,    55,     0,     0,     0,     0,
      58,     0,     0,     0,     0,     0,     0,     0,     0,    65,
      66,    67,    68,    69,   168,     0,    71,     0,     0,    73,
     257,   258,     0,    77,   294,     0,    79,     0,     0,    81,
       0,     0,     0,     0,     0,     0,     0,    84,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    85,    86,    87,    88,    89,     0,     0,
       0,     0,    90,   295,     0,     0,     0,     0,     0,     0,
       0,     0,    91,     0,     0,    92,    93,   253,     0,     0,
       0,    95,     0,   169,     0,    97,     0,   170,     5,     6,
       7,     8,     9,    10,     0,     0,     0,   164,     0,     0,
      14,    15,     0,     0,     0,     0,     0,    19,     0,     0,
       0,     0,     0,     0,     0,    26,     0,     0,     0,     0,
       0,    30,   165,   166,     0,   167,    35,     0,    36,     0,
       0,    38,     0,     0,     0,    40,    41,     0,     0,    43,
      44,     0,    45,    46,     0,    47,    48,     0,     0,     0,
       0,     0,    51,     0,    53,     0,    55,     0,     0,     0,
       0,    58,     0,     0,     0,     0,     0,     0,     0,     0,
      65,    66,    67,    68,    69,   168,     0,    71,     0,     0,
      73,   257,   258,     0,    77,   294,     0,    79,     0,     0,
      81,     0,     0,     0,     0,     0,     0,     0,    84,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    85,    86,    87,    88,    89,     0,
       0,     0,     0,    90,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    91,     0,     0,    92,    93,   253,     0,
       0,     0,    95,     0,   169,     0,    97,   624,   170,     5,
       6,     7,     8,     9,    10,     0,     0,     0,   164,     0,
       0,    14,    15,     0,     0,     0,     0,     0,    19,     0,
       0,     0,     0,     0,     0,     0,    26,     0,     0,     0,
       0,     0,    30,   165,   166,     0,   167,    35,     0,    36,
       0,     0,    38,     0,     0,     0,    40,    41,     0,     0,
      43,    44,     0,    45,    46,     0,    47,    48,     0,     0,
       0,     0,     0,    51,     0,    53,     0,    55,     0,     0,
       0,     0,    58,     0,     0,     0,     0,     0,     0,     0,
       0,    65,    66,    67,    68,    69,   168,     0,    71,     0,
       0,    73,   257,   258,     0,    77,   294,     0,    79,     0,
       0,    81,     0,     0,     0,     0,     0,     0,     0,    84,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    85,    86,    87,    88,    89,
       0,     0,     0,     0,    90,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    91,     0,     0,    92,    93,   253,
       0,     0,     0,    95,     0,   169,     0,    97,   626,   170,
       5,     6,     7,     8,     9,    10,     0,     0,     0,   164,
       0,     0,    14,    15,     0,     0,     0,     0,     0,    19,
       0,   529,     0,     0,     0,     0,     0,    26,     0,     0,
       0,     0,     0,    30,   165,   166,     0,   167,    35,   530,
      36,     0,     0,    38,     0,     0,     0,    40,    41,     0,
       0,    43,    44,     0,    45,    46,     0,    47,    48,     0,
       0,     0,     0,     0,    51,     0,    53,     0,    55,     0,
       0,     0,     0,    58,     0,     0,   531,     0,     0,     0,
       0,     0,    65,    66,    67,    68,    69,   168,     0,    71,
       0,     0,    73,     0,     0,     0,    77,     0,     0,    79,
       0,   532,    81,     0,     0,     0,     0,     0,     0,     0,
      84,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    85,    86,    87,    88,
      89,     0,     0,     0,     0,    90,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    91,     0,     0,    92,    93,
       0,     0,     0,     0,    95,     0,   169,     0,    97,     0,
     170,     5,     6,     7,     8,   193,    10,     0,     0,     0,
     164,     0,     0,    14,    15,     0,     0,  -122,     0,     0,
      19,     0,     0,     0,     0,     0,     0,     0,    26,     0,
       0,     0,     0,     0,    30,   165,   166,     0,   167,    35,
       0,    36,     0,     0,    38,     0,     0,     0,    40,    41,
       0,     0,    43,    44,     0,    45,    46,     0,    47,    48,
       0,     0,     0,     0,     0,    51,     0,    53,     0,    55,
       0,     0,     0,     0,    58,  -122,     0,     0,     0,     0,
       0,     0,     0,    65,    66,    67,    68,    69,   168,     0,
      71,     0,     0,    73,     0,     0,   195,    77,     0,  -122,
      79,     0,     0,    81,     0,     0,     0,     0,     0,     0,
       0,    84,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    85,    86,    87,
      88,    89,     0,     0,     0,     0,    90,     0,     0,     5,
       6,     7,     8,     9,    10,     0,    91,     0,   164,    92,
      93,    14,    15,     0,     0,    95,     0,   169,    19,    97,
       0,   170,     0,     0,     0,     0,    26,     0,     0,     0,
       0,     0,    30,   165,   166,     0,   167,    35,     0,    36,
       0,     0,    38,     0,     0,     0,    40,    41,     0,     0,
      43,    44,     0,    45,    46,     0,    47,    48,     0,     0,
       0,     0,     0,    51,     0,    53,     0,    55,     0,     0,
       0,     0,    58,     0,     0,     0,     0,     0,     0,     0,
       0,    65,    66,    67,    68,    69,   168,     0,    71,     0,
       0,    73,   257,   258,     0,    77,     0,     0,    79,     0,
       0,    81,     0,     0,     0,     0,     0,     0,     0,    84,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    85,    86,    87,    88,    89,
       0,     0,     0,     0,    90,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    91,     0,     0,    92,    93,     0,
     259,     0,     0,    95,     0,   169,     0,    97,     0,   170,
       5,     6,     7,     8,     9,    10,     0,     0,     0,   164,
       0,     0,    14,    15,     0,     0,     0,     0,     0,    19,
       0,     0,     0,     0,     0,     0,     0,    26,     0,     0,
       0,     0,     0,    30,   165,   166,     0,   167,    35,     0,
      36,     0,     0,    38,     0,     0,     0,    40,    41,     0,
       0,    43,    44,     0,    45,    46,     0,    47,    48,     0,
       0,     0,     0,     0,    51,     0,    53,     0,    55,     0,
       0,     0,     0,    58,     0,     0,     0,     0,     0,     0,
       0,     0,    65,    66,    67,    68,    69,   168,     0,    71,
       0,     0,    73,   257,   258,     0,    77,     0,     0,    79,
       0,     0,    81,     0,     0,     0,     0,     0,     0,     0,
      84,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    85,    86,    87,    88,
      89,     0,     0,     0,     0,    90,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    91,     0,     0,    92,    93,
     253,     0,     0,     0,    95,     0,   169,     0,    97,     0,
     170,     5,     6,     7,     8,     9,    10,     0,     0,     0,
     164,     0,     0,    14,    15,     0,     0,     0,     0,     0,
      19,     0,     0,     0,     0,     0,     0,     0,    26,     0,
       0,     0,     0,     0,    30,   165,   166,     0,   167,    35,
       0,    36,     0,     0,    38,     0,     0,     0,    40,    41,
       0,     0,    43,    44,     0,    45,    46,   729,    47,    48,
       0,     0,     0,     0,     0,    51,     0,    53,     0,    55,
       0,     0,     0,     0,    58,     0,     0,     0,     0,     0,
       0,     0,     0,    65,    66,    67,    68,    69,   168,     0,
      71,     0,     0,    73,   257,   258,     0,    77,     0,     0,
      79,     0,     0,    81,     0,     0,     0,     0,     0,     0,
       0,    84,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    85,    86,    87,
      88,    89,     0,     0,     0,     0,    90,     0,     0,     5,
       6,     7,     8,     9,    10,     0,    91,     0,   164,    92,
      93,    14,    15,     0,     0,    95,     0,   169,    19,    97,
       0,   170,     0,     0,     0,     0,    26,     0,     0,     0,
       0,     0,    30,   165,   166,     0,   167,    35,     0,    36,
       0,     0,    38,     0,     0,     0,    40,    41,     0,     0,
      43,    44,     0,    45,    46,     0,    47,    48,     0,     0,
       0,     0,     0,    51,   198,    53,     0,    55,     0,     0,
       0,     0,    58,     0,     0,     0,     0,     0,     0,     0,
       0,    65,    66,    67,    68,    69,   168,     0,    71,     0,
       0,    73,     0,     0,     0,    77,     0,     0,    79,     0,
       0,    81,     0,     0,     0,     0,     0,   199,     0,    84,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    85,    86,    87,    88,    89,
       0,     0,     0,     0,    90,     0,     0,     5,     6,     7,
       8,     9,    10,     0,    91,     0,   164,    92,    93,    14,
      15,     0,     0,    95,     0,   169,    19,    97,     0,   170,
       0,     0,     0,     0,    26,     0,     0,     0,     0,     0,
      30,   165,   166,     0,   167,    35,     0,    36,     0,     0,
      38,     0,     0,     0,    40,    41,     0,     0,    43,    44,
       0,    45,    46,     0,    47,    48,     0,     0,     0,     0,
       0,    51,     0,    53,     0,    55,     0,     0,     0,     0,
      58,     0,     0,     0,     0,     0,     0,     0,     0,    65,
      66,    67,    68,    69,   168,     0,    71,     0,     0,    73,
       0,     0,     0,    77,     0,     0,    79,     0,     0,    81,
       0,     0,     0,     0,     0,   199,     0,    84,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    85,    86,    87,    88,    89,     0,     0,
       0,     0,    90,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    91,     0,     0,    92,    93,   253,     0,     0,
       0,    95,     0,   169,     0,    97,     0,   170,     5,     6,
       7,     8,     9,    10,     0,     0,     0,   164,     0,     0,
      14,    15,     0,     0,     0,     0,     0,    19,     0,     0,
       0,     0,     0,     0,     0,    26,     0,     0,     0,     0,
       0,    30,   165,   166,     0,   167,    35,     0,    36,     0,
       0,    38,     0,     0,     0,    40,    41,     0,     0,    43,
      44,     0,    45,    46,     0,    47,    48,     0,     0,     0,
       0,     0,    51,     0,    53,     0,    55,     0,     0,     0,
       0,    58,     0,     0,     0,     0,     0,     0,     0,     0,
      65,    66,    67,    68,    69,   168,     0,    71,     0,     0,
      73,   257,   258,     0,    77,     0,     0,    79,     0,     0,
      81,     0,     0,     0,     0,     0,     0,     0,    84,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    85,    86,    87,    88,    89,     0,
       0,     0,     0,    90,     0,     0,     5,     6,     7,     8,
       9,    10,     0,    91,     0,   164,    92,    93,    14,    15,
       0,     0,    95,     0,   169,    19,    97,     0,   170,     0,
       0,     0,     0,    26,     0,     0,     0,     0,     0,    30,
     165,   166,     0,   167,    35,     0,    36,     0,     0,    38,
       0,     0,     0,    40,    41,     0,     0,    43,    44,     0,
      45,    46,     0,    47,    48,     0,     0,     0,     0,     0,
      51,     0,    53,     0,    55,     0,     0,     0,     0,    58,
       0,     0,     0,     0,     0,     0,     0,     0,    65,    66,
      67,    68,    69,   168,     0,    71,     0,     0,    73,     0,
       0,     0,    77,     0,     0,    79,     0,     0,    81,     0,
       0,     0,     0,     0,     0,     0,    84,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    85,    86,    87,    88,    89,     0,     0,     0,
       0,    90,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    91,     0,     0,    92,    93,   253,     0,     0,     0,
      95,     0,   169,   622,    97,     0,   170,     5,     6,     7,
       8,     9,    10,     0,     0,     0,   164,     0,     0,    14,
      15,     0,     0,     0,     0,     0,    19,     0,     0,     0,
       0,     0,     0,     0,    26,     0,     0,     0,     0,     0,
      30,   165,   166,     0,   167,    35,     0,    36,     0,     0,
      38,     0,     0,     0,    40,    41,     0,     0,    43,    44,
       0,    45,    46,     0,    47,    48,     0,     0,     0,     0,
       0,    51,     0,    53,     0,    55,     0,     0,     0,     0,
      58,     0,     0,     0,     0,     0,     0,     0,     0,    65,
      66,    67,    68,    69,   168,     0,    71,     0,     0,    73,
       0,     0,     0,    77,     0,     0,    79,     0,     0,    81,
       0,     0,     0,     0,     0,   199,     0,    84,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    85,    86,    87,    88,    89,     0,     0,
       0,     0,    90,     0,     0,     5,     6,     7,     8,     9,
      10,     0,    91,     0,   164,    92,    93,    14,    15,     0,
       0,    95,     0,   169,    19,    97,     0,   170,     0,     0,
       0,   239,    26,     0,     0,     0,     0,     0,    30,   165,
     166,     0,   167,    35,     0,    36,     0,     0,    38,     0,
       0,     0,    40,    41,     0,     0,    43,    44,     0,    45,
      46,     0,    47,    48,     0,     0,     0,     0,     0,    51,
       0,    53,     0,    55,     0,     0,     0,     0,    58,     0,
       0,     0,     0,     0,     0,     0,     0,    65,    66,    67,
      68,    69,   168,     0,    71,     0,     0,    73,     0,     0,
       0,    77,     0,     0,    79,     0,     0,    81,     0,     0,
       0,     0,     0,     0,     0,    84,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    85,    86,    87,    88,    89,     0,     0,     0,     0,
      90,     0,     0,     5,     6,     7,     8,     9,    10,     0,
      91,     0,   164,    92,    93,    14,    15,     0,     0,    95,
       0,    96,    19,    97,     0,   170,     0,     0,     0,     0,
      26,     0,     0,     0,     0,     0,    30,   165,   166,     0,
     167,    35,     0,    36,     0,     0,    38,     0,     0,     0,
      40,    41,     0,     0,    43,    44,     0,    45,    46,     0,
      47,    48,     0,     0,     0,     0,     0,    51,     0,    53,
       0,    55,     0,     0,     0,     0,    58,     0,     0,     0,
       0,     0,     0,     0,     0,    65,    66,    67,    68,    69,
     168,     0,    71,     0,     0,    73,     0,     0,     0,    77,
       0,     0,    79,     0,     0,    81,     0,     0,     0,     0,
       0,     0,     0,    84,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    85,
      86,    87,    88,    89,     0,     0,     0,     0,    90,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    91,     0,
       0,    92,    93,   253,     0,     0,     0,    95,     0,   169,
       0,    97,     0,   170,     5,     6,     7,     8,     9,    10,
       0,     0,     0,   164,     0,     0,    14,    15,     0,     0,
       0,     0,     0,    19,     0,     0,     0,     0,     0,     0,
       0,   598,     0,     0,     0,     0,     0,    30,   165,   166,
       0,   167,    35,     0,   599,     0,     0,    38,     0,     0,
       0,    40,    41,     0,     0,    43,    44,     0,    45,    46,
       0,    47,    48,     0,     0,     0,     0,     0,    51,     0,
      53,     0,    55,     0,     0,     0,     0,    58,     0,     0,
       0,     0,     0,     0,     0,     0,    65,   600,    67,    68,
      69,   601,     0,    71,     0,     0,    73,     0,     0,     0,
      77,     0,     0,    79,     0,     0,    81,     0,     0,     0,
       0,     0,     0,     0,    84,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      85,    86,    87,    88,    89,     0,     0,     0,     0,    90,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    91,
       0,     0,    92,    93,   253,     0,     0,     0,    95,     0,
     169,     0,    97,     0,   914,     5,     6,     7,     8,     9,
      10,     0,     0,     0,   164,     0,     0,    14,    15,     0,
       0,     0,     0,     0,    19,     0,     0,     0,     0,     0,
       0,     0,    26,     0,     0,     0,     0,     0,    30,   165,
     166,     0,   167,    35,     0,    36,     0,     0,    38,     0,
       0,     0,    40,    41,     0,     0,    43,    44,     0,    45,
      46,     0,    47,    48,     0,     0,     0,     0,     0,    51,
       0,    53,     0,    55,     0,     0,     0,     0,    58,     0,
       0,     0,     0,     0,     0,     0,     0,    65,    66,    67,
      68,    69,   168,     0,    71,     0,     0,    73,     0,     0,
       0,    77,     0,     0,    79,     0,     0,    81,     0,     0,
       0,     0,     0,     0,     0,    84,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    85,    86,    87,    88,    89,     0,     0,     0,     0,
      90,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      91,     0,     0,    92,    93,   253,     0,     0,     0,    95,
       0,   169,     0,    97,     0,   914,     5,     6,     7,     8,
       9,    10,     0,     0,     0,   164,     0,     0,    14,    15,
       0,     0,     0,     0,     0,    19,     0,     0,     0,     0,
       0,     0,     0,    26,     0,     0,     0,     0,     0,    30,
     165,   166,     0,   899,    35,     0,    36,     0,     0,    38,
       0,     0,     0,    40,    41,     0,     0,    43,    44,     0,
      45,    46,     0,    47,    48,     0,     0,     0,     0,     0,
      51,     0,    53,     0,    55,     0,     0,     0,     0,    58,
       0,     0,     0,     0,     0,     0,     0,     0,    65,    66,
      67,    68,    69,   168,     0,    71,     0,     0,    73,     0,
       0,     0,    77,     0,     0,    79,     0,     0,    81,     0,
       0,     0,     0,     0,     0,     0,    84,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    85,    86,    87,    88,    89,     0,     0,     0,
       0,    90,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    91,     0,     0,    92,    93,   253,     0,     0,     0,
      95,     0,   169,     0,    97,     0,   170,     5,     6,     7,
       8,     9,    10,     0,     0,     0,   164,     0,     0,    14,
      15,     0,     0,     0,     0,     0,    19,     0,     0,     0,
       0,     0,     0,     0,    26,     0,     0,     0,     0,     0,
      30,   165,   166,     0,   167,    35,     0,    36,     0,     0,
      38,     0,     0,     0,    40,    41,     0,     0,    43,    44,
       0,    45,    46,     0,    47,    48,     0,     0,     0,     0,
       0,    51,     0,    53,     0,    55,     0,     0,     0,     0,
      58,     0,     0,     0,     0,     0,     0,     0,     0,    65,
      66,    67,    68,    69,   168,     0,    71,     0,     0,    73,
       0,     0,     0,    77,     0,     0,    79,     0,     0,    81,
       0,     0,     0,     0,     0,     0,     0,    84,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    85,    86,    87,    88,    89,     0,     0,
       0,     0,    90,     0,     0,     5,     6,     7,     8,     9,
      10,     0,    91,     0,   164,    92,    93,    14,    15,     0,
       0,    95,     0,   169,    19,    97,     0,   170,     0,     0,
       0,     0,    26,     0,     0,     0,     0,     0,    30,   165,
     166,     0,   167,    35,     0,    36,     0,     0,    38,     0,
       0,     0,    40,    41,     0,     0,    43,    44,     0,    45,
      46,     0,    47,    48,     0,     0,     0,     0,     0,    51,
       0,    53,     0,    55,     0,     0,     0,     0,    58,     0,
       0,     0,     0,     0,     0,     0,     0,    65,    66,    67,
      68,    69,   168,     0,    71,     0,     0,    73,     0,     0,
       0,    77,     0,     0,    79,     0,     0,    81,     0,     0,
       0,     0,     0,     0,     0,    84,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    85,    86,    87,    88,    89,     0,     0,     0,     0,
      90,     0,     0,     5,     6,     7,     8,     9,    10,     0,
      91,     0,   164,    92,    93,    14,    15,     0,     0,    95,
       0,    96,    19,    97,     0,   170,     0,     0,     0,     0,
      26,     0,     0,     0,     0,     0,    30,   165,   166,     0,
     167,    35,     0,    36,     0,     0,    38,     0,     0,     0,
      40,    41,     0,     0,    43,    44,     0,    45,    46,     0,
      47,    48,     0,     0,     0,     0,     0,    51,     0,    53,
       0,    55,     0,     0,     0,     0,    58,     0,     0,     0,
       0,     0,     0,     0,     0,    65,    66,    67,    68,    69,
     168,     0,    71,     0,     0,    73,     0,     0,     0,    77,
       0,     0,    79,     0,     0,    81,     0,     0,     0,     0,
       0,     0,     0,    84,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    85,
      86,    87,    88,    89,     0,     0,     0,     0,    90,     0,
       0,     5,     6,     7,     8,     9,    10,     0,    91,     0,
     164,    92,    93,    14,    15,     0,     0,   571,     0,   169,
      19,    97,     0,   170,     0,     0,     0,     0,   598,     0,
       0,     0,     0,     0,    30,   165,   166,     0,   167,    35,
       0,   599,     0,     0,    38,     0,     0,     0,    40,    41,
       0,     0,    43,    44,     0,    45,    46,     0,    47,    48,
       0,     0,     0,     0,     0,    51,     0,    53,     0,    55,
       0,     0,     0,     0,    58,     0,     0,     0,     0,     0,
       0,     0,     0,    65,   600,    67,    68,    69,   601,     0,
      71,     0,     0,    73,     0,     0,     0,    77,     0,     0,
      79,     0,     0,    81,     0,     0,     0,     0,     0,     0,
       0,    84,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    85,    86,    87,
      88,    89,     0,     0,     0,     0,    90,     0,     0,     5,
       6,     7,     8,     9,    10,     0,    91,     0,   164,    92,
      93,    14,    15,     0,     0,    95,     0,   169,    19,    97,
       0,   602,     0,     0,     0,     0,    26,     0,     0,     0,
       0,     0,    30,   165,   166,     0,   167,    35,     0,    36,
       0,     0,    38,     0,     0,     0,    40,    41,     0,     0,
      43,    44,     0,    45,    46,     0,    47,    48,     0,     0,
       0,     0,     0,    51,     0,    53,     0,    55,     0,     0,
       0,     0,    58,     0,     0,     0,     0,     0,     0,     0,
       0,    65,    66,    67,    68,    69,   168,     0,    71,     0,
       0,    73,     0,     0,     0,    77,     0,     0,    79,     0,
       0,    81,     0,     0,     0,     0,     0,     0,     0,    84,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    85,    86,    87,    88,    89,
       0,     0,     0,     0,    90,     0,     0,     5,     6,     7,
       8,     9,    10,     0,    91,     0,   164,    92,    93,    14,
      15,     0,     0,    95,     0,   169,    19,    97,     0,   602,
       0,     0,     0,     0,    26,     0,     0,     0,     0,     0,
      30,   165,   166,     0,   671,    35,     0,    36,     0,     0,
      38,     0,     0,     0,    40,    41,     0,     0,    43,    44,
       0,    45,    46,     0,    47,    48,     0,     0,     0,     0,
       0,    51,     0,    53,     0,    55,     0,     0,     0,     0,
      58,     0,     0,     0,     0,     0,     0,     0,     0,    65,
      66,    67,    68,    69,   168,     0,    71,     0,     0,    73,
       0,     0,     0,    77,     0,     0,    79,     0,     0,    81,
       0,     0,     0,     0,     0,     0,     0,    84,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    85,    86,    87,    88,    89,     0,     0,
       0,     0,    90,     0,     0,     5,     6,     7,     8,     9,
      10,     0,    91,     0,   164,    92,    93,    14,    15,     0,
       0,    95,     0,   169,    19,    97,     0,   170,     0,     0,
       0,     0,    26,     0,     0,     0,     0,     0,    30,   165,
     166,     0,   674,    35,     0,    36,     0,     0,    38,     0,
       0,     0,    40,    41,     0,     0,    43,    44,     0,    45,
      46,     0,    47,    48,     0,     0,     0,     0,     0,    51,
       0,    53,     0,    55,     0,     0,     0,     0,    58,     0,
       0,     0,     0,     0,     0,     0,     0,    65,    66,    67,
      68,    69,   168,     0,    71,     0,     0,    73,     0,     0,
       0,    77,     0,     0,    79,     0,     0,    81,     0,     0,
       0,     0,     0,     0,     0,    84,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    85,    86,    87,    88,    89,     0,     0,     0,     0,
      90,     0,     0,     5,     6,     7,     8,     9,    10,     0,
      91,     0,   164,    92,    93,    14,    15,     0,     0,    95,
       0,   169,    19,    97,     0,   170,     0,     0,     0,     0,
      26,     0,     0,     0,     0,     0,    30,   165,   166,     0,
     893,    35,     0,    36,     0,     0,    38,     0,     0,     0,
      40,    41,     0,     0,    43,    44,     0,    45,    46,     0,
      47,    48,     0,     0,     0,     0,     0,    51,     0,    53,
       0,    55,     0,     0,     0,     0,    58,     0,     0,     0,
       0,     0,     0,     0,     0,    65,    66,    67,    68,    69,
     168,     0,    71,     0,     0,    73,     0,     0,     0,    77,
       0,     0,    79,     0,     0,    81,     0,     0,     0,     0,
       0,     0,     0,    84,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    85,
      86,    87,    88,    89,     0,     0,     0,     0,    90,     0,
       0,     5,     6,     7,     8,     9,    10,     0,    91,     0,
     164,    92,    93,    14,    15,     0,     0,    95,     0,   169,
      19,    97,     0,   170,     0,     0,     0,     0,    26,     0,
       0,     0,     0,     0,    30,   165,   166,     0,   894,    35,
       0,    36,     0,     0,    38,     0,     0,     0,    40,    41,
       0,     0,    43,    44,     0,    45,    46,     0,    47,    48,
       0,     0,     0,     0,     0,    51,     0,    53,     0,    55,
       0,     0,     0,     0,    58,     0,     0,     0,     0,     0,
       0,     0,     0,    65,    66,    67,    68,    69,   168,     0,
      71,     0,     0,    73,     0,     0,     0,    77,     0,     0,
      79,     0,     0,    81,     0,     0,     0,     0,     0,     0,
       0,    84,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    85,    86,    87,
      88,    89,     0,     0,     0,     0,    90,     0,     0,     5,
       6,     7,     8,     9,    10,     0,    91,     0,   164,    92,
      93,    14,    15,     0,     0,    95,     0,   169,    19,    97,
       0,   170,     0,     0,     0,     0,    26,     0,     0,     0,
       0,     0,    30,   165,   166,     0,   896,    35,     0,    36,
       0,     0,    38,     0,     0,     0,    40,    41,     0,     0,
      43,    44,     0,    45,    46,     0,    47,    48,     0,     0,
       0,     0,     0,    51,     0,    53,     0,    55,     0,     0,
       0,     0,    58,     0,     0,     0,     0,     0,     0,     0,
       0,    65,    66,    67,    68,    69,   168,     0,    71,     0,
       0,    73,     0,     0,     0,    77,     0,     0,    79,     0,
       0,    81,     0,     0,     0,     0,     0,     0,     0,    84,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    85,    86,    87,    88,    89,
       0,     0,     0,     0,    90,     0,     0,     5,     6,     7,
       8,     9,    10,     0,    91,     0,   164,    92,    93,    14,
      15,     0,     0,    95,     0,   169,    19,    97,     0,   170,
       0,     0,     0,     0,    26,     0,     0,     0,     0,     0,
      30,   165,   166,     0,   897,    35,     0,    36,     0,     0,
      38,     0,     0,     0,    40,    41,     0,     0,    43,    44,
       0,    45,    46,     0,    47,    48,     0,     0,     0,     0,
       0,    51,     0,    53,     0,    55,     0,     0,     0,     0,
      58,     0,     0,     0,     0,     0,     0,     0,     0,    65,
      66,    67,    68,    69,   168,     0,    71,     0,     0,    73,
       0,     0,     0,    77,     0,     0,    79,     0,     0,    81,
       0,     0,     0,     0,     0,     0,     0,    84,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    85,    86,    87,    88,    89,     0,     0,
       0,     0,    90,     0,     0,     5,     6,     7,     8,     9,
      10,     0,    91,     0,   164,    92,    93,    14,    15,     0,
       0,    95,     0,   169,    19,    97,     0,   170,     0,     0,
       0,     0,    26,     0,     0,     0,     0,     0,    30,   165,
     166,     0,   898,    35,     0,    36,     0,     0,    38,     0,
       0,     0,    40,    41,     0,     0,    43,    44,     0,    45,
      46,     0,    47,    48,     0,     0,     0,     0,     0,    51,
       0,    53,     0,    55,     0,     0,     0,     0,    58,     0,
       0,     0,     0,     0,     0,     0,     0,    65,    66,    67,
      68,    69,   168,     0,    71,     0,     0,    73,     0,     0,
       0,    77,     0,     0,    79,     0,     0,    81,     0,     0,
       0,     0,     0,     0,     0,    84,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    85,    86,    87,    88,    89,     0,     0,     0,     0,
      90,     0,     0,     5,     6,     7,     8,     9,    10,     0,
      91,     0,   164,    92,    93,    14,    15,     0,     0,    95,
       0,   169,    19,    97,     0,   170,     0,     0,     0,     0,
      26,     0,     0,     0,     0,     0,    30,   165,   166,     0,
     899,    35,     0,    36,     0,     0,    38,     0,     0,     0,
      40,    41,     0,     0,    43,    44,     0,    45,    46,     0,
      47,    48,     0,     0,     0,     0,     0,    51,     0,    53,
       0,    55,     0,     0,     0,     0,    58,     0,     0,     0,
       0,     0,     0,     0,     0,    65,    66,    67,    68,    69,
     168,     0,    71,     0,     0,    73,     0,     0,     0,    77,
       0,     0,    79,     0,     0,    81,     0,     0,     0,     0,
       0,     0,     0,    84,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    85,
      86,    87,    88,    89,     0,     0,     0,     0,    90,     0,
       0,     5,     6,     7,     8,     9,    10,     0,    91,     0,
     164,    92,    93,    14,    15,     0,     0,    95,     0,   169,
      19,    97,     0,   170,     0,     0,     0,     0,   598,     0,
       0,     0,     0,     0,    30,   165,   166,     0,   167,    35,
       0,   599,     0,     0,    38,     0,     0,     0,    40,    41,
       0,     0,    43,    44,     0,    45,    46,     0,    47,    48,
       0,     0,     0,     0,     0,    51,     0,    53,     0,    55,
       0,     0,     0,     0,    58,     0,     0,     0,     0,     0,
       0,     0,     0,    65,   600,    67,    68,    69,   601,     0,
      71,     0,     0,    73,     0,     0,     0,    77,     0,     0,
      79,     0,     0,    81,     0,     0,     0,     0,     0,     0,
       0,    84,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    85,    86,    87,
      88,    89,     0,     0,     0,     0,    90,     0,     0,     5,
       6,     7,     8,     9,    10,     0,    91,     0,   164,    92,
      93,    14,    15,     0,     0,    95,     0,   169,    19,    97,
       0,   982,     0,     0,     0,     0,    26,     0,     0,     0,
       0,     0,    30,   165,   166,     0,   167,    35,     0,    36,
       0,     0,    38,     0,     0,     0,    40,    41,     0,     0,
      43,    44,     0,    45,    46,     0,    47,    48,     0,     0,
       0,     0,     0,    51,     0,    53,     0,    55,     0,     0,
       0,     0,    58,     0,     0,     0,     0,     0,     0,     0,
       0,    65,    66,    67,    68,    69,   168,     0,    71,     0,
       0,    73,     0,     0,     0,    77,     0,     0,    79,     0,
       0,    81,     0,     0,     0,     0,     0,     0,     0,    84,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    85,    86,    87,    88,    89,
       0,     0,     0,     0,    90,     0,     0,     5,     6,     7,
       8,     9,    10,     0,    91,     0,   164,    92,    93,    14,
      15,     0,     0,    95,     0,     0,    19,    97,     0,   982,
       0,     0,     0,     0,    26,     0,     0,     0,     0,     0,
      30,   165,   166,     0,   167,    35,     0,    36,     0,     0,
      38,     0,     0,     0,    40,    41,     0,     0,    43,    44,
       0,    45,    46,     0,    47,    48,     0,     0,     0,     0,
       0,    51,     0,    53,     0,    55,     0,     0,     0,     0,
      58,     0,     0,     0,     0,     0,     0,     0,     0,    65,
      66,    67,    68,    69,   168,     0,    71,     0,     0,    73,
       0,     0,     0,    77,     0,     0,    79,     0,     0,    81,
       0,     0,     0,     0,     0,   348,   349,   350,   351,   352,
     353,   354,   355,   356,   357,   358,   359,   360,   361,   362,
       0,     0,     0,    85,    86,    87,    88,    89,     0,     0,
       0,     5,     6,     7,     8,     9,    10,     0,     0,     0,
     164,     0,    91,    14,    15,     0,    93,     0,     0,   363,
      19,    95,  -519,   169,  -519,    97,     0,   170,    26,     0,
       0,     0,     0,     0,    30,   165,   166,     0,   167,    35,
       0,    36,     0,     0,    38,     0,     0,     0,    40,    41,
       0,     0,    43,    44,     0,    45,    46,     0,    47,    48,
       0,     0,     0,     0,     0,    51,     0,    53,     0,    55,
       0,     0,     0,     0,    58,     0,     0,     0,     0,     0,
       0,     0,     0,    65,    66,    67,    68,    69,   168,     0,
      71,     0,     0,    73,     0,     0,     0,    77,     0,     0,
      79,     0,     0,    81,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     5,     6,     7,     8,     9,
      10,     0,     0,     0,   164,     0,     0,    14,    15,    87,
       0,     0,     0,     0,    19,     0,     0,     0,     0,     0,
       0,     0,    26,     0,     0,     0,     0,     0,    30,   165,
     166,     0,   167,    35,     0,    36,     0,   169,    38,    97,
       0,   170,    40,    41,     0,     0,    43,    44,     0,    45,
      46,     0,    47,    48,     0,     0,     0,     0,     0,    51,
       0,    53,     0,    55,     0,     0,     0,     0,    58,     0,
       0,     0,     0,     0,     0,     0,     0,    65,    66,    67,
      68,    69,   168,     0,    71,     0,     0,    73,     0,     0,
       0,    77,     0,     0,    79,     0,     0,    81,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     5,
       6,     7,     8,     9,    10,     0,     0,     0,   164,     0,
       0,    14,    15,    87,     0,     0,     0,     0,    19,     0,
       0,     0,     0,     0,     0,     0,    26,     0,     0,     0,
       0,     0,    30,   165,   166,     0,   167,    35,     0,    36,
       0,   169,    38,    97,     0,   602,    40,    41,     0,     0,
      43,    44,     0,    45,    46,     0,    47,    48,     0,     0,
       0,     0,     0,    51,     0,    53,     0,    55,     0,     0,
       0,     0,    58,     0,     0,     0,     0,     0,     0,     0,
     210,    65,    66,    67,    68,    69,   168,     0,    71,     0,
       0,    73,   211,   212,     0,    77,     0,     0,    79,   213,
       0,    81,     0,     0,     0,     0,     0,   214,     0,     0,
       0,     0,     0,   215,     0,     0,     0,     0,   216,     0,
     217,     0,     0,   218,     0,     0,     0,    87,     0,     0,
       0,   219,     0,     0,     0,     0,     0,   220,   221,     0,
       0,     0,     0,     0,   222,     0,     0,     0,     0,     0,
       0,     0,     0,   223,     0,     0,     0,    97,   210,   170,
       0,     0,   224,   225,     0,     0,     0,   226,     0,   227,
     211,   212,   228,     0,     0,     0,   229,   213,     0,   230,
       0,     0,   231,     0,     0,   214,     0,     0,     0,     0,
       0,   215,     0,     0,     0,     0,   216,     0,   217,     0,
       0,   218,     0,     0,     0,     0,     0,     0,     0,   219,
       0,     0,     0,     0,     0,   220,   221,     0,     0,     0,
       0,     0,   222,     0,     0,     0,     0,     0,     0,     0,
       0,   223,     0,     0,     0,     0,   376,     0,   737,   210,
     224,   225,     0,     0,     0,   226,     0,   227,     0,     0,
     228,   211,   212,     0,   229,     0,     0,   230,   213,     0,
     231,     0,     0,     0,     0,     0,   214,     0,     0,     0,
       0,     0,   215,     0,     0,     0,     0,   216,     0,   217,
       0,     0,   218,     0,     0,     0,     0,     0,     0,     0,
     219,     0,     0,     0,     0,     0,   220,   221,     0,     0,
       0,     0,     0,   222,     0,     0,   942,     0,     0,     0,
       0,     0,   223,   761,     0,     0,   235,     0,   211,   212,
     763,   224,   225,     0,     0,   213,   226,     0,   227,     0,
       0,   228,     0,   214,     0,   229,     0,     0,   230,   765,
       0,   231,     0,     0,   216,     0,   217,     0,     0,   218,
       0,   768,     0,     0,     0,     0,     0,   219,     0,     0,
       0,     0,     0,   770,   221,     0,     0,     0,     0,   319,
     222,     0,     0,     0,     0,     0,   320,     0,     0,   223,
       0,     0,     0,     0,     0,     0,     0,   321,   224,   225,
       0,   943,     0,   226,     0,   944,     0,   717,   775,     0,
       0,     0,   229,     0,     0,   230,     0,     0,   231,     0,
       0,     0,     0,     0,     0,     0,     0,   348,   349,   350,
     351,   352,   353,     0,     0,   356,   357,   358,   359,     0,
     361,   362,   778,   779,   780,   781,   782,   322,     0,   783,
       0,   323,     0,   784,   785,   786,   787,   788,   789,   790,
     791,   792,   793,   794,     0,   795,   319,     0,   796,   797,
     798,   799,     0,   320,     0,     0,     0,     0,     0,     0,
       0,     0,   324,     0,   321,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   325,   326,
       0,   327,   328,   329,     0,   330,   331,   332,     0,   333,
     334,   335,   336,   337,     0,   338,   339,   340,   341,   342,
     343,   344,     0,   319,   345,   346,   347,     0,     0,     0,
     320,     0,     0,   978,   322,     0,     0,     0,   323,     0,
       0,   321,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   319,     0,     0,     0,     0,     0,   324,
     320,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   321,     0,     0,     0,   325,   326,     0,   327,   328,
     329,   322,   330,   331,   332,   323,   333,   334,   335,   336,
     337,     0,   338,   339,   340,   341,   342,   343,   344,     0,
       0,   345,   346,   347,     0,     0,     0,     0,     0,     0,
    1045,     0,     0,     0,     0,     0,   324,     0,     0,     0,
       0,   322,     0,     0,     0,   323,     0,     0,     0,     0,
       0,     0,   325,   326,     0,   327,   328,   329,     0,   330,
     331,   332,     0,   333,   334,   335,   336,   337,     0,   338,
     339,   340,   341,   342,   343,   344,   324,     0,   345,   346,
     347,     0,     0,     0,   319,   623,     0,     0,     0,     0,
       0,   320,   325,   326,     0,   327,   328,   329,     0,   330,
     331,   332,   321,   333,   334,   335,   336,   337,     0,   338,
     339,   340,   341,   342,   343,   344,     0,     0,   345,   346,
     347,     0,     0,     0,     0,   941,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   322,     0,     0,     0,   323,     0,     0,     0,
     319,     0,     0,     0,     0,   412,     0,   320,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   321,     0,
       0,     0,     0,     0,     0,     0,     0,   324,   348,   349,
     350,   351,   352,   353,     0,     0,   356,   357,   358,   359,
       0,   361,   362,   325,   326,     0,   327,   328,   329,     0,
     330,   331,   332,     0,   333,   334,   335,   336,   337,     0,
     338,   339,   340,   341,   342,   343,   344,     0,   322,   345,
     346,   347,   323,   376,     0,     0,   319,     0,     0,     0,
       0,   825,     0,   320,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   321,     0,     0,     0,     0,     0,
       0,     0,     0,   324,   348,   349,   350,   351,   352,   353,
       0,     0,   356,   357,   358,   359,     0,   361,   362,   325,
     326,     0,   327,   328,   329,     0,   330,   331,   332,     0,
     333,   334,   335,   336,   337,     0,   338,   339,   340,   341,
     342,   343,   344,     0,   322,   345,   346,   347,   323,   376,
       0,     0,   319,     0,     0,     0,     0,   832,     0,   320,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     321,     0,     0,     0,     0,     0,     0,     0,     0,   324,
     348,   349,   350,   351,   352,   353,     0,     0,   356,   357,
     358,   359,     0,   361,   362,   325,   326,     0,   327,   328,
     329,     0,   330,   331,   332,     0,   333,   334,   335,   336,
     337,     0,   338,   339,   340,   341,   342,   343,   344,     0,
     322,   345,   346,   347,   323,   376,     0,     0,   319,     0,
       0,     0,     0,   955,     0,   320,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   321,     0,     0,     0,
       0,     0,     0,     0,     0,   324,   348,   349,   350,   351,
     352,   353,     0,     0,   356,   357,   358,   359,     0,   361,
     362,   325,   326,     0,   327,   328,   329,     0,   330,   331,
     332,     0,   333,   334,   335,   336,   337,     0,   338,   339,
     340,   341,   342,   343,   344,     0,   322,   345,   346,   347,
     323,   376,     0,     0,   319,     0,     0,     0,     0,   956,
       0,   320,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   321,     0,     0,     0,     0,     0,     0,     0,
       0,   324,   348,   349,   350,   351,   352,   353,     0,     0,
     356,   357,   358,   359,     0,   361,   362,   325,   326,     0,
     327,   328,   329,     0,   330,   331,   332,     0,   333,   334,
     335,   336,   337,     0,   338,   339,   340,   341,   342,   343,
     344,     0,   322,   345,   346,   347,   323,   376,     0,     0,
     319,     0,     0,     0,     0,   957,     0,   320,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   321,     0,
       0,     0,     0,     0,     0,     0,     0,   324,   348,   349,
     350,   351,   352,   353,     0,     0,   356,   357,   358,   359,
       0,   361,   362,   325,   326,     0,   327,   328,   329,     0,
     330,   331,   332,     0,   333,   334,   335,   336,   337,     0,
     338,   339,   340,   341,   342,   343,   344,     0,   322,   345,
     346,   347,   323,   376,     0,     0,   319,     0,     0,     0,
       0,   958,     0,   320,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   321,     0,     0,     0,     0,     0,
       0,     0,     0,   324,   348,   349,   350,   351,   352,   353,
       0,     0,   356,   357,   358,   359,     0,   361,   362,   325,
     326,     0,   327,   328,   329,     0,   330,   331,   332,     0,
     333,   334,   335,   336,   337,     0,   338,   339,   340,   341,
     342,   343,   344,     0,   322,   345,   346,   347,   323,   376,
       0,     0,   319,     0,     0,     0,     0,   980,     0,   320,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     321,     0,     0,     0,     0,     0,     0,     0,     0,   324,
     348,   349,   350,   351,   352,   353,     0,     0,   356,   357,
     358,   359,     0,   361,   362,   325,   326,     0,   327,   328,
     329,     0,   330,   331,   332,     0,   333,   334,   335,   336,
     337,     0,   338,   339,   340,   341,   342,   343,   344,     0,
     322,   345,   346,   347,   323,   376,     0,     0,     0,     0,
       0,     0,     0,   981,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   324,   348,   349,   350,   351,
     352,   353,     0,     0,   356,   357,   358,   359,     0,   361,
     362,   325,   326,     0,   327,   328,   329,     0,   330,   331,
     332,     0,   333,   334,   335,   336,   337,     0,   338,   339,
     340,   341,   342,   343,   344,   319,     0,   345,   346,   347,
       0,   376,   320,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   321,   404,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   405,     0,     0,
       0,     0,     0,     0,     0,     0,   319,     0,     0,     0,
       0,     0,     0,   320,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   321,   398,     0,     0,     0,     0,
       0,     0,     0,   322,     0,     0,     0,   323,   399,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   319,     0,     0,     0,     0,     0,     0,   320,     0,
       0,     0,     0,     0,   401,     0,     0,     0,   324,   321,
     700,     0,     0,     0,   322,     0,     0,     0,   323,     0,
       0,     0,     0,     0,   325,   326,     0,   327,   328,   329,
       0,   330,   331,   332,     0,   333,   334,   335,   336,   337,
       0,   338,   339,   340,   341,   342,   343,   344,     0,   324,
     345,   346,   347,     0,   376,     0,     0,     0,     0,   322,
       0,     0,   321,   323,     0,   325,   326,     0,   327,   328,
     329,     0,   330,   331,   332,     0,   333,   334,   335,   336,
     337,     0,   338,   339,   340,   341,   342,   343,   344,   319,
     401,   345,   346,   347,   324,   376,   320,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   321,   239,     0,
     325,   326,   322,   327,   328,   329,   323,   330,   331,   332,
       0,   333,   334,   335,   336,   337,     0,   338,   339,   340,
     341,   342,   343,   344,   319,     0,   345,   346,   347,     0,
     376,   320,     0,     0,     0,     0,     0,   324,     0,     0,
       0,     0,   321,   692,     0,     0,     0,   322,     0,     0,
       0,   323,     0,   325,   326,     0,   327,   328,   329,     0,
     330,   331,   332,     0,   333,   334,   335,   336,     0,     0,
     338,   339,   340,   341,   342,   343,   344,     0,     0,   345,
     346,   347,   324,     0,     0,     0,     0,   321,     0,     0,
       0,     0,   322,     0,     0,     0,   323,     0,   325,   326,
       0,   327,   328,   329,     0,   330,   331,   332,     0,   333,
     334,   335,   336,   337,     0,   338,   339,   340,   341,   342,
     343,   344,   319,     0,   345,   346,   347,   324,   376,   320,
       0,     0,     0,     0,     0,     0,     0,   322,     0,     0,
     321,   323,     0,   325,   326,     0,   327,   328,   329,     0,
     330,   331,   332,     0,   333,   334,   335,   336,   337,     0,
     338,   339,   340,   341,   342,   343,   344,   319,     0,   345,
     346,   347,   324,   376,   320,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   321,     0,     0,   325,   326,
     322,   327,   328,   329,   323,   330,   331,   332,     0,   333,
     334,   335,   336,   710,     0,   338,   339,   340,   341,   342,
       0,   344,     0,     0,   345,   346,   347,     0,     0,     0,
     319,     0,     0,     0,     0,   324,     0,   320,     0,     0,
       0,     0,     0,     0,     0,   322,     0,     0,   321,   323,
       0,   325,   326,   409,   327,   328,   329,     0,   330,   331,
     332,     0,   333,   334,   335,   336,   337,     0,   338,   339,
     340,   341,   342,   343,   344,     0,     0,   345,   346,   347,
     324,   376,     0,   410,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   325,   326,   322,   327,
     328,   329,   323,   330,   331,   332,     0,   333,   334,   335,
     336,   337,     0,   338,   339,   340,   341,   342,   343,   344,
       0,     0,   345,   346,   347,     0,   439,   319,     0,     0,
       0,     0,     0,   324,   320,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   321,     0,     0,     0,   325,
     326,     0,   327,   328,   329,     0,   330,   331,   332,   378,
     333,   334,   335,   336,   337,     0,   338,   339,   340,   341,
     342,   343,   344,   319,   411,   345,   346,   347,     0,     0,
     320,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   321,   538,     0,     0,   322,     0,     0,     0,   323,
       0,     0,     0,     0,     0,   539,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   159,     0,     0,     0,
     324,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   322,     0,     0,     0,   323,   325,   326,     0,   327,
     328,   329,     0,   330,   331,   332,     0,   333,   334,   335,
     336,   337,     0,   338,   339,   340,   341,   342,   343,   344,
     319,     0,   345,   346,   347,     0,   324,   320,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   321,   540,
       0,     0,   325,   326,     0,   327,   328,   329,     0,   330,
     331,   332,   541,   333,   334,   335,   336,   337,     0,   338,
     339,   340,   341,   342,   343,   344,   319,     0,   345,   346,
     347,     0,     0,   320,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   321,     0,     0,     0,   322,   643,
       0,     0,   323,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   319,     0,     0,     0,
       0,     0,     0,   320,     0,     0,     0,     0,     0,   644,
       0,     0,     0,   324,   321,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   322,     0,     0,     0,   323,   325,
     326,     0,   327,   328,   329,     0,   330,   331,   332,     0,
     333,   334,   335,   336,   337,     0,   338,   339,   340,   341,
     342,   343,   344,   319,     0,   345,   346,   347,     0,   324,
     320,     0,     0,     0,   322,     0,     0,     0,   323,     0,
       0,   321,     0,     0,     0,   325,   326,     0,   327,   328,
     329,     0,   330,   331,   332,     0,   333,   334,   335,   336,
     337,     0,   338,   339,   340,   341,   342,   343,   344,   324,
       0,   345,   346,   347,     0,     0,     0,     0,     0,     0,
       0,   321,     0,     0,     0,   325,   326,     0,   327,   328,
     329,   322,   330,   331,   332,   323,   333,   334,   335,   336,
     337,     0,   338,   339,   340,   341,   342,   343,   344,   319,
     443,   345,   346,   347,     0,     0,   320,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   324,   321,     0,     0,
       0,   322,     0,     0,     0,   323,     0,     0,     0,     0,
       0,     0,   325,   326,     0,   327,   328,   329,     0,   330,
     331,   332,     0,   333,   334,   335,   336,   337,     0,   338,
     339,   340,   341,   342,   343,   344,   319,   445,   345,   346,
     347,     0,     0,   320,     0,     0,     0,   322,     0,     0,
       0,   323,   325,   326,   321,   327,   328,   329,     0,   330,
     331,   332,     0,   333,   334,   335,   336,     0,     0,   338,
     339,   340,   341,   342,     0,   344,   319,     0,   345,   346,
     347,     0,   324,   320,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   321,     0,     0,     0,   325,   326,
       0,   327,   328,   329,   322,   330,   331,   332,   323,   333,
     334,   335,   336,   337,     0,   338,   339,   340,   341,   342,
     343,   344,   319,   447,   345,   346,   347,     0,     0,   320,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   324,
     321,     0,     0,     0,   322,     0,     0,     0,   323,     0,
       0,     0,     0,     0,     0,   325,   326,   542,   327,   328,
     329,     0,   330,   331,   332,     0,   333,   334,   335,   336,
     337,     0,   338,   339,   340,   341,   342,   343,   344,   324,
     452,   345,   346,   347,     0,     0,     0,     0,     0,     0,
     322,     0,     0,     0,   323,   325,   326,   321,   327,   328,
     329,     0,   330,   331,   332,     0,   333,   334,   335,   336,
     337,     0,   338,   339,   340,   341,   342,   343,   344,   319,
       0,   345,   346,   347,   469,   324,   320,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   321,     0,     0,
       0,   325,   326,     0,   327,   328,   329,   322,   330,   331,
     332,   323,   333,   334,   335,   336,   337,     0,   338,   339,
     340,   341,   342,   343,   344,     0,     0,   345,   346,   347,
       0,     0,   319,     0,     0,     0,     0,     0,     0,   320,
       0,     0,     0,     0,     0,     0,     0,   322,     0,     0,
     321,   323,     0,     0,     0,     0,     0,     0,   325,   326,
       0,   327,   328,   329,     0,   330,   331,   332,     0,     0,
     334,     0,   319,     0,     0,     0,     0,   340,   341,   320,
       0,   344,   324,     0,   345,   346,   347,     0,     0,     0,
     321,     0,     0,     0,     0,     0,     0,     0,   325,   326,
     322,   327,   328,   329,   323,   330,   331,   332,     0,   333,
     334,   335,   336,   337,  -493,   338,   339,   340,   341,   342,
     343,   344,     0,     0,   345,   346,   347,     0,     0,   319,
     705,   159,     0,     0,     0,   324,   320,     0,     0,     0,
     322,     0,     0,     0,   323,     0,     0,   321,     0,     0,
       0,   325,   326,     0,   327,   328,   329,     0,   330,   331,
     332,     0,   333,   334,   335,   336,   337,     0,   338,   339,
     340,   341,   342,   343,   344,   324,     0,   345,   346,   347,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   325,   326,     0,   327,   328,   329,   322,   330,   331,
     332,   323,   333,   334,   335,   336,   337,     0,   338,   339,
     340,   341,   342,   343,   344,   319,   681,   345,   346,   347,
       0,     0,   320,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   324,   321,     0,     0,   708,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   325,   326,
       0,   327,   328,   329,     0,   330,   331,   332,     0,   333,
     334,   335,   336,   337,     0,   338,   339,   340,   341,   342,
     343,   344,   319,     0,   345,   346,   347,     0,     0,   320,
       0,     0,     0,   322,     0,     0,     0,   323,     0,     0,
     321,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   319,     0,     0,     0,     0,     0,
       0,   320,     0,     0,     0,     0,     0,     0,   324,     0,
       0,     0,   321,   815,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   325,   326,     0,   327,   328,   329,
     322,   330,   331,   332,   323,   333,   334,   335,   336,   337,
       0,   338,   339,   340,   341,   342,   343,   344,     0,     0,
     345,   346,   347,     0,     0,     0,     0,     0,     0,     0,
       0,   321,   322,     0,   748,   324,   323,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   325,   326,     0,   327,   328,   329,     0,   330,   331,
     332,     0,   333,   334,   335,   336,   337,   324,   338,   339,
     340,   341,   342,   343,   344,   319,     0,   345,   346,   347,
       0,   322,   320,   325,   326,   323,   327,   328,   329,     0,
     330,   331,   332,   321,   333,   334,   335,   336,   337,     0,
     338,   339,   340,   341,   342,   343,   344,   319,     0,   345,
     346,   347,     0,     0,   320,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   321,   818,     0,     0,     0,
       0,     0,   325,   326,     0,   327,   328,   329,     0,   330,
     331,   332,     0,   322,   334,   335,   336,   323,     0,   338,
     339,   340,   341,     0,     0,   344,   892,     0,   345,   346,
     347,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   322,     0,     0,   324,   323,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   325,   326,     0,   327,   328,   329,
       0,   330,   331,   332,     0,   333,   334,   335,   336,   337,
     324,   338,   339,   340,   341,   342,   343,   344,   319,     0,
     345,   346,   347,     0,     0,   320,   325,   326,     0,   327,
     328,   329,     0,   330,   331,   332,   321,   333,   334,   335,
     336,   337,     0,   338,   339,   340,   341,   342,   343,   344,
     319,   909,   345,   346,   347,     0,     0,   320,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   321,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   322,     0,     0,     0,
     323,     0,     0,     0,     0,     0,     0,     0,     0,   895,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   322,     0,
       0,   324,   323,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   325,   326,     0,
     327,   328,   329,     0,   330,   331,   332,     0,   333,   334,
     335,   336,   337,   324,   338,   339,   340,   341,   342,   343,
     344,   319,     0,   345,   346,   347,     0,     0,   320,   325,
     326,     0,   327,   328,   329,     0,   330,   331,   332,   321,
     333,   334,   335,   336,   337,     0,   338,   339,   340,   341,
     342,   343,   344,   319,     0,   345,   346,   347,     0,     0,
     320,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   321,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   322,
       0,     0,     0,   323,     0,     0,     0,     0,     0,     0,
       0,     0,   991,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   322,     0,     0,   324,   323,     0,     0,     0,     0,
       0,     0,     0,     0,   992,     0,     0,     0,     0,     0,
     325,   326,     0,   327,   328,   329,     0,   330,   331,   332,
       0,   333,   334,   335,   336,   337,   324,   338,   339,   340,
     341,   342,   343,   344,   319,     0,   345,   346,   347,     0,
       0,   320,   325,   326,     0,   327,   328,   329,     0,   330,
     331,   332,   321,   333,   334,   335,   336,   337,     0,   338,
     339,   340,   341,   342,   343,   344,   319,     0,   345,   346,
     347,     0,     0,   320,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   321,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   322,     0,     0,     0,   323,     0,     0,     0,
       0,     0,     0,     0,     0,   993,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   322,     0,     0,   324,   323,     0,
       0,     0,     0,     0,     0,     0,     0,   994,     0,     0,
       0,     0,     0,   325,   326,     0,   327,   328,   329,     0,
     330,   331,   332,     0,   333,   334,   335,   336,   337,   324,
     338,   339,   340,   341,   342,   343,   344,   319,     0,   345,
     346,   347,     0,     0,   320,   325,   326,     0,   327,   328,
     329,     0,   330,   331,   332,   321,   333,   334,   335,   336,
     337,     0,   338,   339,   340,   341,   342,   343,   344,   319,
       0,   345,   346,   347,     0,     0,   320,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   321,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   322,     0,     0,     0,   323,
       0,     0,     0,     0,     0,     0,     0,     0,   995,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   322,     0,     0,
     324,   323,     0,     0,     0,     0,     0,     0,     0,     0,
     996,     0,     0,     0,     0,     0,   325,   326,     0,   327,
     328,   329,     0,   330,   331,   332,     0,   333,   334,   335,
     336,   337,   324,   338,   339,   340,   341,   342,   343,   344,
     319,     0,   345,   346,   347,     0,     0,   320,   325,   326,
       0,   327,   328,   329,     0,   330,   331,   332,   321,   333,
     334,   335,   336,   337,     0,   338,   339,   340,   341,   342,
     343,   344,   319,     0,   345,   346,   347,     0,     0,   320,
       0,     0,  1018,     0,     0,     0,     0,     0,     0,     0,
     321,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   322,     0,
       0,     0,   323,     0,     0,     0,     0,     0,     0,     0,
       0,   319,     0,     0,     0,     0,     0,     0,   320,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   321,
     322,     0,     0,   324,   323,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   325,
     326,     0,   327,   328,   329,     0,   330,   331,   332,     0,
     333,   334,   335,   336,   337,   324,   338,   339,   340,   341,
     342,   343,   344,     0,     0,   345,   346,   347,     0,   669,
       0,   325,   326,   323,   327,   328,   329,     0,   330,   331,
     332,     0,   333,   334,   335,   336,   337,     0,   338,   339,
     340,   341,   342,   343,   344,     0,     0,   345,   346,   347,
       0,     0,     0,     0,   324,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     325,   326,     0,   327,   328,   329,     0,   330,   331,   332,
       0,   333,   334,   335,   336,   337,     0,   338,   339,   340,
     341,   342,   343,   344,     0,     0,   345,   346,   347,   647,
       0,   210,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   211,   212,     0,     0,     0,     0,     0,
     213,     0,     0,     0,     0,     0,     0,     0,   214,     0,
       0,     0,     0,     0,   215,     0,     0,     0,     0,   216,
       0,   217,     0,     0,   218,     0,     0,     0,     0,     0,
       0,     0,   219,     0,     0,     0,     0,     0,   220,   221,
       0,     0,     0,     0,     0,   222,     0,     0,   210,     0,
       0,     0,     0,     0,   223,     0,     0,     0,     0,     0,
     211,   212,     0,   224,   225,     0,     0,   213,   226,     0,
     227,     0,     0,   228,     0,   214,     0,   229,     0,     0,
     230,   215,     0,   231,     0,     0,   216,     0,   217,     0,
       0,   218,     0,     0,     0,     0,     0,     0,     0,   219,
       0,     0,     0,     0,     0,   220,   221,     0,     0,     0,
       0,     0,   222,     0,     0,     0,     0,     0,     0,     0,
       0,   223,     0,     0,     0,     0,     0,     0,     0,     0,
     224,   225,     0,     0,     0,   226,     0,   227,     0,     0,
     228,     0,     0,     0,   229,     0,     0,   230,     0,     0,
     231
};

static const yytype_int16 yycheck[] =
{
      11,   144,   369,     2,    15,   448,   564,    18,    56,    57,
      17,   410,   182,    24,   203,   131,   417,    28,    29,   726,
      31,    32,    33,    34,   924,   195,   656,    28,     1,    20,
      42,    42,     3,    44,    45,    29,    42,     1,    49,    29,
      51,   190,    53,     1,   420,    42,    29,    29,    29,   848,
      61,    62,    63,    64,    65,    66,    81,    61,   752,    70,
     209,    72,    81,    74,    75,   209,     0,   183,    79,   806,
     807,    82,    83,    24,    85,   845,    87,    42,    42,    90,
      91,   107,    93,     3,   425,    96,    97,    98,    42,   597,
      42,   135,   154,     1,    98,     1,    42,   109,  1023,   161,
     249,   163,    97,   810,   963,   249,    64,   448,   666,   135,
      81,   300,   301,   109,    79,   109,  1041,    68,    42,   268,
     164,    92,    64,   135,   268,  1025,   109,   154,    79,   135,
      74,    75,   275,    79,   159,   154,    31,    32,   135,   938,
     159,   114,   849,   913,    52,   135,    52,    98,   106,  1008,
     114,    62,   164,   164,   165,   166,   167,   168,   169,   170,
     668,   134,   135,  1008,   106,   159,   170,   164,   164,   159,
     134,   135,    92,    81,   181,    81,   159,   159,   159,   190,
     109,   135,   331,   135,   878,    19,    97,    24,    94,   162,
     154,   161,    19,   163,   205,   190,   135,   564,   209,   107,
    1045,   107,   160,    98,   205,   912,   197,   901,   945,   946,
     164,   135,   164,   204,   209,   723,   365,   366,   160,    39,
     596,   365,   366,   162,   109,   135,   134,    52,   134,   129,
      78,    68,   135,   135,    82,    52,   135,   137,   249,   250,
     164,   114,    79,    77,   135,   644,   257,   258,   154,   135,
      77,   159,   162,   159,   249,   962,    76,   268,   888,   162,
     162,    98,   135,   162,    81,    47,   139,   101,   135,   135,
       3,   162,   830,   268,   101,   135,   162,    94,   394,   164,
     129,    78,   107,   135,   295,    82,    79,   161,   137,   162,
     107,    73,   441,   292,     7,   162,   162,   441,   309,   666,
     160,   459,   154,   461,   124,   309,   126,   318,   319,   320,
     321,   322,   323,   324,   715,   326,   327,   328,   329,   330,
     161,   332,   333,   334,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   154,   114,   135,
      24,   717,   159,   354,   355,    24,   135,   135,   114,   360,
     135,   752,   363,   364,   365,   366,   367,   368,   369,   135,
     161,   161,   182,   139,   160,   154,   154,   378,    28,   154,
     365,   366,   383,   139,   385,   195,   154,    52,   198,   568,
     569,   161,   160,   163,    68,   396,   162,   398,   399,    68,
     135,   135,   396,   404,   405,    79,    89,   159,   409,   410,
      79,   412,    42,   414,    74,   554,    81,   135,   103,   154,
     154,   161,   855,   163,    98,   235,   427,   408,    78,    94,
     104,   153,    82,   434,    64,   104,   154,   322,   323,   145,
     441,   154,   107,   253,    74,    75,   161,   160,   163,   434,
     154,   630,   631,   354,   355,   456,   441,   154,   459,   360,
     461,   621,   363,   364,   465,   466,   467,   154,   469,   470,
     154,   456,   114,   830,   459,   154,   461,    52,   479,   129,
     161,   466,   367,   368,   134,   479,   475,   137,     2,   154,
     154,   141,   883,   378,   159,   154,   154,    11,   140,   137,
     142,   143,   159,     3,   146,   147,    81,   154,   108,    23,
     901,    25,   161,   161,   399,   134,    42,   848,   137,    94,
     405,   154,   141,   656,   855,   161,    52,   114,   154,     7,
      30,    56,   107,   134,   159,   114,   154,   538,   539,   540,
     541,   542,   543,   544,   135,   162,   154,    42,   545,   546,
     180,   552,   161,   554,    54,    81,    70,   558,   459,   560,
     461,    31,   135,   564,   162,   566,   162,   552,   114,   554,
     200,   201,   202,   203,   162,    24,    24,   162,   208,   154,
     465,   107,    96,   393,   159,    18,   100,   135,   114,   159,
     164,   154,    92,    42,    42,   164,    45,    45,    98,   600,
     601,   602,   154,   154,   154,   606,   162,   938,   602,   135,
     420,   154,   242,   135,   969,   245,    65,    65,   154,    68,
      68,    70,    70,   164,   154,    28,   154,    31,   154,   162,
      79,    79,   963,   159,   264,   162,   162,   160,   135,   160,
     114,    79,   643,   644,    29,    29,   160,   978,   164,    98,
      98,   552,   282,   159,   539,    31,   541,  1012,  1013,  1014,
    1015,  1016,  1017,   134,    79,   666,   476,   134,   669,   670,
     671,   481,     2,   674,   164,    78,   164,  1008,     3,    82,
     164,    11,   154,   160,   137,   154,   135,   137,   161,   690,
      15,   692,  1023,    23,   129,    25,   697,    22,   137,   700,
     137,   137,   703,   129,   705,   606,   137,   708,   137,   137,
    1041,   129,   137,   162,  1045,   137,    41,   129,   232,   129,
     137,    46,    31,    94,   129,   239,   129,   129,   162,    54,
     162,   134,   733,   136,   137,   135,    61,   160,   141,   733,
      70,   306,   743,    28,   745,   164,   149,   748,   643,   379,
     644,    76,    22,   754,   157,   888,   276,   556,   737,   823,
     755,   888,   883,    88,   715,   758,    96,    92,   589,   196,
     100,  1025,   962,   403,    99,   987,  1018,   407,   292,  1011,
     105,    33,   592,   428,   669,   670,   596,   554,    -1,     2,
      -1,    -1,   306,    78,    -1,    -1,    -1,    82,    11,   800,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   617,    -1,    -1,
      23,   621,    25,   814,   815,    -1,   817,   818,   819,   820,
      -1,    -1,    -1,    -1,   825,   826,    -1,   828,    -1,   830,
     160,   832,   833,    -1,    -1,   836,    -1,   875,   876,    -1,
      -1,    -1,    -1,    -1,   129,   130,   656,   132,   133,   134,
      -1,   136,   137,   854,   855,    -1,   141,    70,    -1,   860,
      -1,   862,   376,   848,   149,   866,    -1,    23,    24,    -1,
     155,   156,   157,   874,    -1,    -1,    -1,    -1,    34,    35,
      -1,    -1,    -1,    96,   398,    24,    -1,   100,    44,    -1,
     404,   892,   893,   894,   895,   896,   897,   898,   899,    -1,
      -1,    -1,   232,    42,   714,    -1,    45,   717,   909,   239,
      66,    -1,    68,   914,    -1,    -1,    -1,    -1,   919,    -1,
     914,    -1,   923,    79,    -1,    -1,    65,   737,    -1,    68,
      -1,    70,   562,   563,   919,    -1,    -1,    -1,   568,   569,
      79,    -1,    -1,    -1,    -1,   755,    -1,   160,   104,   463,
     580,    -1,    -1,   467,   955,   956,   957,   958,    -1,    98,
      -1,   475,   292,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     780,    -1,    -1,    -1,    -1,    -1,   306,   978,   963,   980,
     981,   982,    -1,    -1,    -1,    -1,    -1,   617,   982,    -1,
     991,   992,   993,   994,   995,   996,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1007,  1008,     2,  1010,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    11,    -1,   232,
      -1,    -1,    -1,  1008,    -1,    -1,   239,    -1,    -1,    23,
      -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,    19,    -1,
    1041,    -1,    23,    24,  1045,    -1,   376,    -1,    -1,   679,
     680,    32,    -1,    34,    35,    -1,    -1,   687,    39,   689,
    1045,    -1,    -1,    44,    -1,   579,   696,    -1,   398,   699,
      -1,    -1,   702,    -1,   404,    -1,    70,    -1,   888,   292,
      74,    75,   412,    -1,    -1,    66,    -1,    68,    -1,    70,
      -1,    72,    -1,   306,    75,    -1,    77,    -1,    79,    -1,
      -1,    -1,    96,    -1,    -1,    -1,   100,    -1,    -1,    -1,
     740,    -1,    -1,    -1,    -1,   629,    -1,    98,    -1,    -1,
     101,   635,    -1,   104,    -1,    -1,    -1,     2,    -1,    -1,
      -1,    -1,    -1,   463,    -1,    -1,    11,   467,    28,    -1,
      -1,    -1,    -1,    -1,    -1,   475,    -1,    -1,    23,    -1,
      25,    -1,    -1,    -1,    -1,    19,    -1,    -1,    -1,    23,
      24,    -1,    -1,   376,    -1,    -1,   160,    -1,    32,    -1,
      34,    35,    -1,   154,    -1,    39,   690,    -1,   692,   160,
      44,    -1,    -1,   697,    -1,   398,   700,    -1,    78,    -1,
      -1,   404,    82,   707,    -1,    70,   710,    -1,    -1,   412,
      -1,    -1,    66,     2,    68,   535,    70,    -1,    72,    -1,
      -1,    75,    11,    77,    -1,    79,    -1,    42,   732,    -1,
      -1,    96,    -1,    -1,    23,   100,    25,    52,   858,   743,
      -1,   745,    -1,    -1,    98,    -1,    -1,   101,   232,   129,
     104,    -1,    -1,    -1,   134,   239,   136,   137,    -1,   579,
     463,   141,    -1,    -1,   467,    -1,    81,    -1,    -1,   149,
      -1,    -1,   475,    -1,    -1,   155,   156,   157,    -1,    -1,
      28,    70,    -1,   903,   904,    -1,    -1,   907,   908,    -1,
      -1,    -1,   107,    -1,    -1,   160,    -1,    -1,    -1,   114,
     154,    -1,    -1,    -1,   924,    -1,   160,    96,   292,   629,
     930,   100,   932,    -1,   934,   635,    -1,    -1,    -1,    -1,
     135,    -1,   306,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      78,    -1,    -1,    -1,    82,    -1,   656,    -1,    -1,   154,
     844,    -1,    -1,    -1,   159,    -1,    -1,   162,    -1,   669,
     670,    -1,   856,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   865,    -1,    -1,    -1,   869,    -1,   232,    -1,    -1,
     690,   160,   692,    -1,   239,    -1,   579,   697,    -1,    -1,
     700,   129,   130,    -1,   132,   133,   134,   707,   136,   137,
     710,    -1,   376,   141,    -1,    -1,    -1,    -1,    -1,    -1,
     148,   149,    -1,    -1,   152,  1025,   910,   155,   156,   157,
      -1,    -1,   732,    -1,   398,    -1,    -1,    -1,    -1,    -1,
     404,    -1,    -1,   743,    -1,   745,   629,   292,   412,    -1,
      -1,    -1,   635,    -1,    -1,    -1,    -1,    -1,    10,    -1,
      -1,   306,    -1,   232,    -1,    17,    -1,    -1,    -1,    -1,
     239,    -1,    -1,    -1,     2,    -1,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    23,    -1,    25,    -1,   463,
      -1,    -1,    -1,   467,    -1,    -1,    -1,   690,    -1,   692,
      -1,   475,    -1,    -1,   697,    -1,    -1,   700,    -1,    -1,
      -1,    -1,    -1,   292,   707,   825,    78,   710,    -1,    -1,
      82,   376,   832,    -1,    -1,    -1,    -1,   306,    -1,    -1,
      -1,    -1,    70,    -1,   844,    -1,    -1,    -1,    -1,   732,
      -1,    -1,    -1,   398,    -1,    -1,   856,   109,    -1,   404,
     743,   113,   745,    -1,    -1,   865,    -1,   412,    96,   869,
      -1,    -1,   100,    -1,    -1,    -1,    -1,   129,   130,    -1,
     132,   133,   134,    -1,   136,   137,   138,    28,   140,   141,
     142,   143,   144,    -1,   146,   147,   148,   149,   150,   151,
     152,    -1,    -1,   155,   156,   157,    -1,   376,    -1,    -1,
     910,    -1,   164,    -1,    -1,   579,    -1,    -1,   463,    -1,
      -1,    -1,   467,    -1,    -1,    -1,    -1,    -1,    -1,   398,
     475,    -1,   160,    -1,    -1,   404,    -1,    78,    -1,    -1,
      -1,    82,   825,   412,    -1,    -1,    -1,    -1,    -1,   832,
      -1,    -1,    -1,    -1,    -1,   955,   956,   957,   958,    -1,
      -1,   844,    -1,    -1,    -1,   629,    -1,    -1,    -1,    -1,
      -1,   635,    -1,   856,    -1,    -1,    -1,    -1,    -1,    -1,
     980,   981,   865,    -1,    -1,    -1,   869,    -1,   129,   130,
      -1,    -1,   133,   134,   463,   136,   137,    -1,   467,    -1,
     141,    -1,    -1,    28,   232,    -1,   475,    -1,   149,    -1,
      -1,   239,    -1,    -1,   155,   156,   157,    -1,    -1,    -1,
      -1,    42,    -1,    -1,    -1,    -1,   690,   910,   692,    -1,
      -1,    52,    -1,   697,   579,    -1,   700,    -1,    -1,    -1,
      -1,    -1,    -1,   707,    -1,    -1,   710,    -1,    -1,    -1,
      -1,    -1,    64,    78,    -1,    -1,    -1,    82,    -1,    -1,
      81,    -1,    -1,    -1,   292,    -1,    -1,    -1,   732,    -1,
      -1,    -1,   955,   956,   957,   958,    -1,    -1,   306,   743,
      -1,   745,    -1,    -1,   629,    -1,   107,    -1,    -1,    -1,
     635,    -1,    -1,   114,    -1,    -1,    -1,   980,   981,     2,
      -1,    -1,    -1,    -1,   129,   130,    -1,    -1,    11,   134,
     579,   136,   137,    -1,   135,    -1,   141,    -1,    -1,    -1,
      23,    -1,    25,    -1,   149,    -1,    -1,    -1,    -1,    -1,
     155,   156,   157,   154,    -1,    -1,    -1,    -1,   159,    -1,
      -1,   162,    -1,    -1,    -1,   690,    -1,   692,   376,    -1,
      -1,    -1,   697,    -1,    -1,   700,    -1,    -1,    -1,    -1,
     629,   825,   707,    -1,    -1,   710,   635,    70,   832,    -1,
     398,    -1,    -1,    -1,    -1,    -1,   404,    -1,    -1,    -1,
     844,    -1,    -1,    -1,   412,    -1,    -1,   732,   200,   201,
     202,   203,   856,    96,    -1,    -1,    -1,   100,   743,    -1,
     745,   865,    -1,    -1,    -1,   869,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   690,    -1,   692,    -1,    -1,    -1,    -1,   697,    -1,
     242,   700,    -1,   245,    -1,   463,    -1,    -1,   707,   467,
      -1,   710,    -1,    -1,     2,    -1,   910,   475,    -1,    -1,
      -1,    -1,   264,    11,    -1,    -1,    -1,   160,    -1,    -1,
      -1,    -1,    -1,   732,    -1,    23,    -1,    25,    -1,    -1,
     282,    -1,    -1,    -1,   743,    -1,   745,    -1,    -1,    -1,
     825,    -1,    -1,    -1,    -1,    -1,    -1,   832,    -1,    23,
      24,   955,   956,   957,   958,    -1,    -1,    -1,    -1,   844,
      34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      44,   856,    70,    47,    -1,    -1,   980,   981,    -1,    -1,
     865,    -1,    -1,    -1,   869,    -1,    -1,    -1,    -1,   232,
      -1,    -1,    66,    -1,    68,    -1,   239,    -1,    96,    73,
      -1,     3,   100,    -1,    -1,    79,    -1,    -1,    -1,    -1,
      -1,   579,    -1,    15,    16,    -1,   825,    -1,    -1,    -1,
      22,    -1,    -1,   832,    -1,   910,    -1,   379,    30,   103,
     104,    -1,    -1,    -1,    36,   844,    -1,    -1,    -1,    41,
      -1,    43,    -1,    -1,    46,    -1,    -1,   856,    -1,   292,
      -1,   403,    54,    -1,    -1,   407,   865,    -1,    60,    61,
     869,   629,   160,   306,    -1,    67,    -1,   635,    -1,    -1,
     955,   956,   957,   958,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    85,    86,    -1,    -1,    -1,    90,    -1,
      92,    -1,    -1,    95,    -1,   980,   981,    99,   100,    -1,
     102,   910,    -1,   105,    -1,    -1,    -1,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   690,    -1,   692,    -1,    -1,    -1,    -1,   697,
      -1,    -1,   700,   376,   232,    -1,    -1,    -1,   145,   707,
      -1,   239,   710,    -1,    -1,    -1,   955,   956,   957,   958,
      -1,   158,    -1,    -1,   161,   398,   163,    -1,    -1,   161,
      -1,   404,    -1,    -1,   732,    -1,    -1,    -1,    -1,   412,
      -1,   980,   981,    -1,    -1,   743,    -1,   745,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,   292,    -1,    -1,    12,    -1,    -1,
      15,    16,    -1,    -1,    -1,    -1,    -1,    22,   306,    -1,
     562,   563,    -1,    -1,    -1,    30,   568,   569,    -1,    -1,
     463,    36,    37,    38,   467,    40,    41,    -1,    43,    -1,
      -1,    46,   475,    -1,    -1,    50,    51,    52,    -1,    54,
      55,    -1,    57,    58,    -1,    60,    61,    -1,    -1,    -1,
      -1,    -1,    67,    -1,    69,    -1,    71,   825,    -1,    -1,
      -1,    76,    -1,    -1,   832,    -1,    81,    -1,    -1,    -1,
      85,    86,    87,    88,    89,    90,   844,    92,   376,    94,
      95,    -1,    -1,    -1,    99,    -1,    -1,   102,   856,    -1,
     105,    -1,   107,    -1,    -1,    -1,    -1,   865,    -1,    -1,
     398,   869,    -1,    -1,    -1,    -1,   404,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   412,    -1,   131,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   679,   680,    -1,
      -1,    -1,    -1,     1,    -1,   687,   579,    -1,    -1,   154,
      -1,    -1,   910,    -1,   159,    -1,   161,   699,   163,    -1,
     702,    19,    -1,    -1,    -1,    23,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    32,   463,    34,    35,    -1,   467,
      -1,    39,    23,    24,    -1,    -1,    44,   475,    -1,    47,
      -1,    -1,    -1,    34,    35,    -1,   629,   955,   956,   957,
     958,    -1,   635,    44,    -1,    -1,    47,    -1,    66,    -1,
      68,    -1,    70,    -1,    72,    73,    -1,    75,    -1,    77,
      -1,    79,   980,   981,    -1,    66,    -1,    68,    -1,    -1,
      -1,    -1,    73,    -1,    -1,    -1,    -1,    -1,    79,    -1,
      98,    -1,    -1,   101,    -1,    -1,   104,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   690,    -1,   692,
      -1,    -1,   103,   104,   697,    -1,    -1,   700,    -1,    -1,
      -1,    -1,    -1,    -1,   707,    -1,    -1,   710,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,
      -1,   579,    -1,    -1,    -1,    -1,   154,    -1,    -1,   732,
      -1,    -1,   160,    -1,    19,    -1,    -1,    -1,    23,    24,
     743,    -1,   745,    -1,    -1,    -1,   858,    32,    19,    34,
      35,    -1,    23,    24,    39,    -1,    -1,    -1,    -1,    44,
      -1,    32,    47,    34,    35,    -1,    -1,    -1,    39,    -1,
      -1,   629,    -1,    44,    -1,    -1,    -1,   635,    -1,    -1,
      -1,    66,    -1,    68,    -1,    70,    -1,    72,    73,    -1,
      75,    -1,    77,    -1,    79,    66,    -1,    68,    -1,    70,
      -1,    72,    -1,    -1,    75,    -1,    77,    -1,    79,    -1,
      -1,    -1,    -1,    98,    -1,    -1,   101,    -1,    -1,   104,
      -1,    -1,   825,    -1,    -1,    -1,    -1,    98,    -1,   832,
     101,    -1,   690,   104,   692,    -1,    -1,    -1,    -1,   697,
      -1,   844,   700,    -1,    -1,    -1,    -1,    -1,    -1,   707,
      -1,    -1,   710,   856,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   865,    -1,    -1,    -1,   869,    -1,    -1,   154,
      -1,    -1,    -1,    -1,   732,   160,    -1,     3,     4,     5,
       6,     7,     8,   154,    -1,   743,    12,   745,    -1,    15,
      16,    -1,    -1,    -1,    -1,    -1,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    -1,    -1,   910,    -1,    -1,
      36,    37,    38,    -1,    40,    41,    -1,    43,    -1,    -1,
      46,    -1,    -1,    -1,    50,    51,    -1,    -1,    54,    55,
      -1,    57,    58,    -1,    60,    61,    -1,    -1,    -1,    -1,
      10,    67,    -1,    69,    -1,    71,    -1,    17,    -1,    -1,
      76,    -1,   955,   956,   957,   958,    -1,    -1,    28,    85,
      86,    87,    88,    89,    90,    -1,    92,   825,    -1,    95,
      -1,    -1,    -1,    99,   832,    -1,   102,   980,   981,   105,
      -1,    -1,    -1,    -1,    -1,    -1,   844,    -1,   114,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   856,    -1,
      -1,    -1,    -1,    -1,    -1,   131,    -1,   865,    78,   135,
      -1,   869,    82,   139,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   153,    -1,    -1,
      -1,    -1,    -1,   159,    -1,   161,   162,   163,    -1,    -1,
      -1,    -1,    -1,   113,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   910,    -1,    -1,    -1,    -1,    -1,    -1,   129,
     130,    -1,   132,   133,   134,    -1,   136,   137,   138,    -1,
     140,   141,   142,   143,   144,    -1,   146,   147,   148,   149,
     150,   151,   152,    -1,    -1,   155,   156,   157,    -1,    -1,
      -1,    -1,    -1,    -1,   164,    -1,    -1,   955,   956,   957,
     958,    -1,    -1,    -1,    -1,     0,     1,    -1,     3,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    12,    13,    14,
      15,    16,   980,   981,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    29,    30,    -1,    32,    -1,    34,
      35,    36,    37,    38,    39,    40,    41,    -1,    43,    44,
      -1,    46,    47,    -1,    49,    50,    51,    -1,    53,    54,
      55,    56,    57,    58,    -1,    60,    61,    62,    -1,    -1,
      -1,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    -1,    79,    80,    81,    -1,    83,    84,
      85,    86,    87,    88,    89,    90,    -1,    92,    93,    -1,
      95,    96,    97,    98,    99,    -1,   101,   102,   103,   104,
     105,    -1,    -1,   108,    -1,   110,    -1,    -1,   113,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   129,   130,   131,   132,   133,    -1,
      -1,    -1,    -1,   138,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   148,    -1,    -1,   151,   152,    -1,   154,
      -1,    -1,   157,    -1,   159,    -1,   161,     1,   163,     3,
       4,     5,     6,     7,     8,    -1,    -1,    -1,    12,    -1,
      -1,    15,    16,    -1,    -1,    -1,    -1,    -1,    22,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,
      -1,    -1,    36,    37,    38,    -1,    40,    41,    -1,    43,
      -1,    -1,    46,    -1,    -1,    -1,    50,    51,    -1,    -1,
      54,    55,    -1,    57,    58,    -1,    60,    61,    -1,    -1,
      -1,    -1,    -1,    67,    -1,    69,    -1,    71,    -1,    -1,
      -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    85,    86,    87,    88,    89,    90,    -1,    92,    -1,
      -1,    95,    -1,    -1,    -1,    99,    -1,    -1,   102,    -1,
      -1,   105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   113,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   129,   130,   131,   132,   133,
      -1,    -1,    -1,    -1,   138,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   148,    -1,    -1,   151,   152,   153,
      -1,    -1,    -1,   157,    -1,   159,    -1,   161,    -1,   163,
     164,     1,    -1,     3,     4,     5,     6,     7,     8,    -1,
      10,    -1,    12,    13,    14,    15,    16,    17,    -1,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    -1,    34,    35,    36,    37,    38,    39,
      40,    41,    -1,    43,    44,    -1,    46,    47,    -1,    49,
      50,    51,    -1,    53,    54,    55,    56,    57,    58,    -1,
      60,    61,    62,    -1,    -1,    -1,    66,    67,    68,    69,
      -1,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    -1,    92,    93,    -1,    95,    96,    97,    98,    99,
      -1,   101,   102,   103,   104,   105,    -1,    -1,   108,    -1,
     110,    -1,    -1,   113,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,    -1,
     140,   141,   142,   143,   144,    -1,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,    -1,   159,
     160,   161,     1,   163,     3,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    12,    13,    14,    15,    16,    -1,    -1,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    -1,
      29,    30,    -1,    32,    -1,    34,    35,    36,    37,    38,
      39,    40,    41,    -1,    43,    44,    -1,    46,    47,    -1,
      49,    50,    51,    -1,    53,    54,    55,    56,    57,    58,
      -1,    60,    61,    62,    -1,    -1,    -1,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    -1,
      79,    80,    81,    -1,    83,    84,    85,    86,    87,    88,
      89,    90,    -1,    92,    93,    -1,    95,    96,    97,    98,
      99,    -1,   101,   102,   103,   104,   105,    -1,    -1,   108,
      -1,   110,    -1,    -1,   113,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     129,   130,   131,   132,   133,    -1,    -1,    -1,    -1,   138,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   148,
      -1,    -1,   151,   152,   153,   154,    -1,    -1,   157,    -1,
     159,   160,   161,     1,   163,     3,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    12,    13,    14,    15,    16,    -1,
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      -1,    29,    30,    -1,    32,    -1,    34,    35,    36,    37,
      38,    39,    40,    41,    -1,    43,    44,    -1,    46,    47,
      -1,    49,    50,    51,    -1,    53,    54,    55,    56,    57,
      58,    -1,    60,    61,    62,    -1,    -1,    -1,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      -1,    79,    80,    81,    -1,    83,    84,    85,    86,    87,
      88,    89,    90,    -1,    92,    93,    -1,    95,    96,    97,
      98,    99,    -1,   101,   102,   103,   104,   105,    -1,    -1,
     108,    -1,   110,    -1,    -1,   113,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   129,   130,   131,   132,   133,    -1,    -1,    -1,    -1,
     138,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     148,    -1,    -1,   151,   152,    -1,   154,    -1,    -1,   157,
      -1,   159,   160,   161,     1,   163,     3,     4,     5,     6,
       7,     8,    -1,    -1,    -1,    12,    13,    14,    15,    16,
      -1,    -1,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    -1,    29,    30,    -1,    32,    -1,    34,    35,    36,
      37,    38,    39,    40,    41,    -1,    43,    44,    -1,    46,
      47,    -1,    49,    50,    51,    -1,    53,    54,    55,    56,
      57,    58,    -1,    60,    61,    62,    -1,    -1,    -1,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    -1,    79,    80,    81,    -1,    83,    84,    85,    86,
      87,    88,    89,    90,    -1,    92,    93,    -1,    95,    96,
      97,    98,    99,    -1,   101,   102,   103,   104,   105,    -1,
      -1,   108,    -1,   110,    -1,    -1,   113,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   129,   130,   131,   132,   133,    -1,    -1,    -1,
      -1,   138,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   148,    -1,    -1,   151,   152,    -1,   154,    -1,    -1,
     157,    -1,   159,   160,   161,     1,   163,     3,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    12,    13,    14,    15,
      16,    -1,    -1,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    -1,    29,    30,    -1,    32,    -1,    34,    35,
      36,    37,    38,    39,    40,    41,    -1,    43,    44,    -1,
      46,    47,    -1,    49,    50,    51,    -1,    53,    54,    55,
      56,    57,    58,    -1,    60,    61,    62,    -1,    -1,    -1,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    -1,    79,    80,    81,    -1,    83,    84,    85,
      86,    87,    88,    89,    90,    -1,    92,    93,    -1,    95,
      96,    97,    98,    99,    -1,   101,   102,   103,   104,   105,
      -1,    -1,   108,    -1,   110,    -1,    -1,   113,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   129,   130,   131,   132,   133,    -1,    -1,
      -1,    -1,   138,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   148,    -1,    -1,   151,   152,    -1,   154,    -1,
      -1,   157,    -1,   159,   160,   161,     1,   163,     3,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    12,    13,    14,
      15,    16,    -1,    -1,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    29,    30,    -1,    32,    -1,    34,
      35,    36,    37,    38,    39,    40,    41,    -1,    43,    44,
      -1,    46,    47,    -1,    49,    50,    51,    -1,    53,    54,
      55,    56,    57,    58,    -1,    60,    61,    62,    -1,    -1,
      -1,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    -1,    79,    80,    81,    -1,    83,    84,
      85,    86,    87,    88,    89,    90,    -1,    92,    93,    -1,
      95,    96,    97,    98,    99,    -1,   101,   102,   103,   104,
     105,    -1,    -1,   108,    -1,   110,    -1,    -1,   113,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   129,   130,   131,   132,   133,    -1,
      -1,    -1,    -1,   138,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   148,    -1,    -1,   151,   152,    -1,   154,
      -1,    -1,   157,    -1,   159,   160,   161,     1,   163,     3,
       4,     5,     6,     7,     8,    -1,    -1,    -1,    12,    13,
      14,    15,    16,    -1,    -1,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    -1,    29,    30,    -1,    32,    -1,
      34,    35,    36,    37,    38,    39,    40,    41,    -1,    43,
      44,    -1,    46,    47,    -1,    49,    50,    51,    -1,    53,
      54,    55,    56,    57,    58,    -1,    60,    61,    62,    -1,
      -1,    -1,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    -1,    79,    80,    81,    -1,    83,
      84,    85,    86,    87,    88,    89,    90,    -1,    92,    93,
      -1,    95,    96,    97,    98,    99,    -1,   101,   102,   103,
     104,   105,    -1,    -1,   108,    -1,   110,    -1,    -1,   113,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   129,   130,   131,   132,   133,
      -1,    -1,    -1,    -1,   138,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   148,    -1,    -1,   151,   152,    -1,
     154,    -1,    -1,   157,    -1,   159,    -1,   161,     1,   163,
       3,     4,     5,     6,     7,     8,    -1,    -1,    -1,    12,
      13,    14,    15,    16,    -1,    -1,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    -1,    29,    30,    -1,    32,
      -1,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      43,    44,    -1,    46,    47,    -1,    49,    50,    51,    -1,
      53,    54,    55,    56,    57,    58,    -1,    60,    61,    62,
      -1,    -1,    -1,    66,    67,    68,    69,    -1,    71,    72,
      73,    74,    75,    76,    77,    -1,    79,    80,    81,    -1,
      83,    84,    85,    86,    87,    88,    89,    90,    -1,    92,
      93,    -1,    95,    96,    97,    98,    99,    -1,   101,   102,
     103,   104,   105,    -1,    -1,   108,    -1,   110,    -1,    -1,
     113,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   129,   130,   131,   132,
     133,    -1,    -1,    -1,    -1,   138,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   148,    -1,    -1,   151,   152,
      -1,   154,    -1,    -1,   157,    -1,   159,    -1,   161,     1,
     163,     3,     4,     5,     6,     7,     8,    -1,    -1,    -1,
      12,    13,    14,    15,    16,    -1,    -1,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    -1,    29,    30,    -1,
      32,    -1,    34,    35,    36,    37,    38,    39,    40,    41,
      -1,    43,    44,    -1,    46,    47,    -1,    49,    50,    51,
      -1,    53,    54,    55,    56,    57,    58,    -1,    60,    61,
      62,    -1,    -1,    -1,    66,    67,    68,    69,    -1,    71,
      72,    73,    74,    75,    76,    77,    -1,    79,    80,    81,
      -1,    83,    84,    85,    86,    87,    88,    89,    90,    -1,
      92,    93,    -1,    95,    96,    97,    98,    99,    -1,   101,
     102,   103,   104,   105,    -1,    -1,   108,    -1,   110,    -1,
      -1,   113,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,   130,   131,
     132,   133,    -1,    -1,    -1,    -1,   138,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   148,    -1,    -1,   151,
     152,    -1,   154,    -1,    -1,   157,    -1,   159,    -1,   161,
       1,   163,     3,     4,     5,     6,     7,     8,    -1,    -1,
      -1,    12,    13,    14,    15,    16,    -1,    -1,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    -1,    29,    30,
      -1,    32,    -1,    34,    35,    36,    37,    38,    39,    40,
      41,    -1,    43,    44,    -1,    46,    47,    -1,    49,    50,
      51,    -1,    53,    54,    55,    56,    57,    58,    -1,    60,
      61,    62,    -1,    -1,    -1,    66,    67,    68,    69,    -1,
      71,    72,    73,    74,    75,    76,    77,    -1,    79,    80,
      81,    -1,    83,    84,    85,    86,    87,    88,    89,    90,
      -1,    92,    93,    -1,    95,    96,    97,    98,    99,    -1,
     101,   102,   103,   104,   105,    -1,    -1,   108,    -1,   110,
      -1,    -1,   113,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,   130,
     131,   132,   133,    -1,    -1,    -1,    -1,   138,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   148,    -1,    -1,
     151,   152,    -1,   154,    -1,    -1,   157,    -1,   159,    -1,
     161,     1,   163,     3,     4,     5,     6,     7,     8,    -1,
      -1,    -1,    12,    13,    14,    15,    16,    -1,    -1,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    -1,    29,
      30,    -1,    32,    -1,    34,    35,    36,    37,    38,    39,
      40,    41,    -1,    43,    44,    -1,    46,    47,    -1,    49,
      50,    51,    -1,    53,    54,    55,    56,    57,    58,    -1,
      60,    61,    62,    -1,    -1,    -1,    66,    67,    68,    69,
      -1,    71,    72,    73,    74,    75,    76,    77,    -1,    79,
      80,    81,    -1,    83,    84,    85,    86,    87,    88,    89,
      90,    -1,    92,    93,    -1,    95,    96,    97,    98,    99,
      -1,   101,   102,   103,   104,   105,    -1,    -1,   108,    -1,
     110,    -1,    -1,   113,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,
     130,   131,   132,   133,    -1,    -1,    -1,    -1,   138,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   148,    -1,
      -1,   151,   152,    -1,   154,    -1,    -1,   157,    -1,   159,
      -1,   161,     1,   163,     3,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    12,    13,    14,    15,    16,    -1,    -1,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    -1,
      29,    30,    -1,    32,    -1,    34,    35,    36,    37,    38,
      39,    40,    41,    -1,    43,    44,    -1,    46,    47,    -1,
      49,    50,    51,    -1,    53,    54,    55,    56,    57,    58,
      -1,    60,    61,    62,    -1,    -1,    -1,    66,    67,    68,
      69,    -1,    71,    72,    73,    74,    75,    76,    77,    -1,
      79,    80,    81,    -1,    83,    84,    85,    86,    87,    88,
      89,    90,    -1,    92,    93,    -1,    95,    96,    97,    98,
      99,    -1,   101,   102,   103,   104,   105,    -1,    -1,   108,
      -1,   110,    -1,    -1,   113,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     129,   130,   131,   132,   133,    -1,    -1,    -1,    -1,   138,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   148,
      -1,    -1,   151,   152,    -1,   154,    -1,    -1,   157,    -1,
     159,    -1,   161,     1,   163,     3,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    12,    13,    14,    15,    16,    -1,
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      -1,    29,    30,    -1,    32,    -1,    34,    35,    36,    37,
      38,    39,    40,    41,    -1,    43,    44,    -1,    46,    47,
      -1,    49,    50,    51,    -1,    53,    54,    55,    56,    57,
      58,    -1,    60,    61,    62,    -1,    -1,    -1,    66,    67,
      68,    69,    -1,    71,    72,    73,    74,    75,    76,    77,
      -1,    79,    80,    81,    -1,    83,    84,    85,    86,    87,
      88,    89,    90,    -1,    92,    93,    -1,    95,    96,    97,
      98,    99,    -1,   101,   102,   103,   104,   105,    -1,    -1,
     108,    -1,   110,    -1,    -1,   113,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   129,   130,   131,   132,   133,    -1,    -1,    -1,    -1,
     138,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     148,    -1,    -1,   151,   152,    -1,   154,    -1,    -1,   157,
      -1,   159,    -1,   161,     1,   163,     3,     4,     5,     6,
       7,     8,    -1,    -1,    -1,    12,    13,    14,    15,    16,
      -1,    -1,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    -1,    29,    30,    -1,    32,    -1,    34,    35,    36,
      37,    38,    39,    40,    41,    -1,    43,    44,    -1,    46,
      47,    -1,    49,    50,    51,    -1,    53,    54,    55,    56,
      57,    58,    -1,    60,    61,    62,    -1,    -1,    -1,    66,
      67,    68,    69,    -1,    71,    72,    73,    74,    75,    76,
      77,    -1,    79,    80,    81,    -1,    83,    84,    85,    86,
      87,    88,    89,    90,    -1,    92,    93,    -1,    95,    96,
      97,    98,    99,    -1,   101,   102,   103,   104,   105,    -1,
      -1,   108,    -1,   110,    -1,    -1,   113,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   129,   130,   131,   132,   133,    -1,    -1,    -1,
      -1,   138,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   148,    -1,    -1,   151,   152,    -1,   154,    -1,    -1,
     157,    -1,   159,    -1,   161,     1,   163,     3,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    12,    13,    14,    15,
      16,    -1,    -1,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    -1,    29,    30,    -1,    32,    -1,    34,    35,
      36,    37,    38,    39,    40,    41,    -1,    43,    44,    -1,
      46,    47,    -1,    49,    50,    51,    -1,    53,    54,    55,
      56,    57,    58,    -1,    60,    61,    62,    -1,    -1,    -1,
      66,    67,    68,    69,    -1,    71,    72,    73,    74,    75,
      76,    77,    -1,    79,    80,    81,    -1,    83,    84,    85,
      86,    87,    88,    89,    90,    -1,    92,    93,    -1,    95,
      96,    97,    98,    99,    -1,   101,   102,   103,   104,   105,
      -1,    -1,   108,    -1,   110,    -1,    -1,   113,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   129,   130,   131,   132,   133,    -1,    -1,
      -1,    -1,   138,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   148,    -1,    -1,   151,   152,    -1,   154,    -1,
      -1,   157,    -1,   159,    -1,   161,     1,   163,     3,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    12,    13,    14,
      15,    16,    -1,    -1,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    29,    30,    -1,    32,    -1,    34,
      35,    36,    37,    38,    39,    40,    41,    -1,    43,    44,
      -1,    46,    47,    -1,    49,    50,    51,    -1,    53,    54,
      55,    56,    57,    58,    -1,    60,    61,    62,    -1,    -1,
      -1,    66,    67,    68,    69,    -1,    71,    72,    73,    74,
      75,    76,    77,    -1,    79,    80,    81,    -1,    83,    84,
      85,    86,    87,    88,    89,    90,    -1,    92,    93,    -1,
      95,    96,    97,    98,    99,    -1,   101,   102,   103,   104,
     105,    -1,    -1,   108,    -1,   110,    -1,    -1,   113,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   129,   130,   131,   132,   133,    -1,
      -1,    -1,    -1,   138,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   148,    -1,    -1,   151,   152,    -1,   154,
      -1,    -1,   157,    -1,   159,    -1,   161,     1,   163,     3,
       4,     5,     6,     7,     8,    -1,    -1,    -1,    12,    13,
      14,    15,    16,    -1,    -1,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    -1,    29,    30,    -1,    32,    -1,
      34,    35,    36,    37,    38,    39,    40,    41,    -1,    43,
      44,    -1,    46,    47,    -1,    49,    50,    51,    -1,    53,
      54,    55,    56,    57,    58,    -1,    60,    61,    62,    -1,
      -1,    -1,    66,    67,    68,    69,    -1,    71,    72,    73,
      74,    75,    76,    77,    -1,    79,    80,    81,    -1,    83,
      84,    85,    86,    87,    88,    89,    90,    -1,    92,    93,
      -1,    95,    96,    97,    98,    99,    -1,   101,   102,   103,
     104,   105,    -1,    -1,   108,    -1,   110,    -1,    -1,   113,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   129,   130,   131,   132,   133,
      -1,    -1,    -1,    -1,   138,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   148,    -1,    -1,   151,   152,    -1,
     154,    -1,    -1,   157,    -1,   159,    -1,   161,     1,   163,
       3,     4,     5,     6,     7,     8,    -1,    -1,    -1,    12,
      -1,    -1,    15,    16,    -1,    -1,    -1,    -1,    -1,    22,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,
      -1,    -1,    -1,    36,    37,    38,    -1,    40,    41,    -1,
      43,    -1,    -1,    46,    -1,    -1,    -1,    50,    51,    -1,
      -1,    54,    55,    -1,    57,    58,    -1,    60,    61,    -1,
      -1,    -1,    -1,    -1,    67,    -1,    69,    -1,    71,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    85,    86,    87,    88,    89,    90,    -1,    92,
      -1,    -1,    95,    -1,    -1,    -1,    99,    -1,    -1,   102,
      -1,    -1,   105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     113,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   129,   130,   131,   132,
     133,    -1,    -1,    -1,    -1,   138,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   148,    -1,    -1,   151,   152,
     153,    -1,    -1,    -1,   157,    -1,   159,    -1,   161,    -1,
     163,     3,     4,     5,     6,     7,     8,    -1,    -1,    -1,
      12,    -1,    -1,    15,    16,    -1,    -1,    -1,    -1,    -1,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,
      -1,    -1,    -1,    -1,    36,    37,    38,    -1,    40,    41,
      -1,    43,    -1,    -1,    46,    -1,    -1,    -1,    50,    51,
      -1,    -1,    54,    55,    -1,    57,    58,    -1,    60,    61,
      -1,    -1,    -1,    -1,    -1,    67,    -1,    69,    -1,    71,
      -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    85,    86,    87,    88,    89,    90,    -1,
      92,    -1,    -1,    95,    -1,    -1,    -1,    99,    -1,    -1,
     102,    -1,    -1,   105,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   113,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,   130,   131,
     132,   133,    -1,    -1,    -1,    -1,   138,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   148,    -1,    -1,   151,
     152,   153,    -1,    -1,    -1,   157,    -1,   159,    -1,   161,
      -1,   163,   164,     3,     4,     5,     6,     7,     8,    -1,
      -1,    -1,    12,    -1,    -1,    15,    16,    -1,    -1,    -1,
      -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    -1,    -1,    -1,    -1,    -1,    36,    37,    38,    -1,
      40,    41,    -1,    43,    -1,    -1,    46,    -1,    -1,    -1,
      50,    51,    -1,    -1,    54,    55,    -1,    57,    58,    -1,
      60,    61,    -1,    -1,    -1,    -1,    -1,    67,    -1,    69,
      -1,    71,    -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    85,    86,    87,    88,    89,
      90,    -1,    92,    -1,    -1,    95,    -1,    -1,    -1,    99,
      -1,    -1,   102,    -1,    -1,   105,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   113,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,
     130,   131,   132,   133,    -1,    -1,    -1,    -1,   138,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   148,    -1,
      -1,   151,   152,   153,    -1,    -1,    -1,   157,    -1,   159,
      -1,   161,    -1,   163,   164,     3,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    12,    -1,    -1,    15,    16,    -1,
      -1,    -1,    -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,    36,    37,
      38,    -1,    40,    41,    -1,    43,    -1,    -1,    46,    -1,
      -1,    -1,    50,    51,    -1,    -1,    54,    55,    -1,    57,
      58,    -1,    60,    61,    -1,    -1,    -1,    -1,    -1,    67,
      -1,    69,    -1,    71,    -1,    -1,    -1,    -1,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,    86,    87,
      88,    89,    90,    -1,    92,    -1,    -1,    95,    -1,    -1,
      -1,    99,    -1,    -1,   102,    -1,    -1,   105,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   113,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,     3,
      -1,   129,   130,   131,   132,   133,    10,    -1,    -1,    -1,
     138,    15,    16,    17,    -1,    -1,    -1,    -1,    22,    -1,
     148,    -1,    -1,   151,   152,    -1,    30,    -1,    -1,   157,
      -1,   159,    36,   161,    -1,   163,   164,    41,    -1,    43,
      -1,    -1,    46,    -1,    48,    -1,    -1,    -1,    -1,    -1,
      54,    -1,    -1,    -1,    -1,    -1,    60,    61,    -1,    -1,
      -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    85,    86,    -1,    88,    -1,    90,    -1,    92,    -1,
      -1,    95,    -1,    -1,    -1,    99,    -1,    -1,   102,    -1,
      -1,   105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     114,   115,   116,   117,   118,   119,    -1,    -1,   122,   123,
     124,   125,    -1,   127,   128,   129,   130,   131,   132,   133,
      -1,    -1,   136,    -1,    -1,    -1,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,    -1,   152,    -1,
      -1,   155,   156,   157,   158,    -1,    -1,   161,     3,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    12,    -1,    -1,
      15,    16,    -1,    -1,    -1,    -1,    -1,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    -1,    43,    -1,
      -1,    46,    -1,    -1,    -1,    50,    51,    -1,    -1,    54,
      55,    -1,    57,    58,    -1,    60,    61,    -1,    -1,    -1,
      -1,    -1,    67,    68,    69,    -1,    71,    -1,    -1,    -1,
      -1,    76,    -1,    -1,    79,    -1,    -1,    -1,    -1,    -1,
      85,    86,    87,    88,    89,    90,    -1,    92,    -1,    -1,
      95,    -1,    -1,    -1,    99,    -1,    -1,   102,    -1,   104,
     105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   113,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   129,   130,   131,   132,   133,    -1,
      -1,    -1,    -1,   138,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   148,    -1,    -1,   151,   152,    -1,    -1,
      -1,    -1,   157,    -1,   159,    -1,   161,    -1,   163,     3,
       4,     5,     6,     7,     8,     9,    -1,    -1,    12,    -1,
      -1,    15,    16,    -1,    -1,    19,    -1,    -1,    22,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,
      -1,    -1,    36,    37,    38,    -1,    40,    41,    -1,    43,
      -1,    -1,    46,    -1,    -1,    -1,    50,    51,    -1,    -1,
      54,    55,    -1,    57,    58,    -1,    60,    61,    -1,    -1,
      -1,    -1,    -1,    67,    -1,    69,    -1,    71,    -1,    -1,
      -1,    -1,    76,    77,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    85,    86,    87,    88,    89,    90,    -1,    92,    -1,
      -1,    95,    -1,    -1,    98,    99,    -1,   101,   102,    -1,
      -1,   105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   113,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   129,   130,   131,   132,   133,
      -1,    -1,    -1,    -1,   138,    -1,    -1,     3,     4,     5,
       6,     7,     8,    -1,   148,    -1,    12,   151,   152,    15,
      16,    -1,    -1,   157,    -1,   159,    22,   161,    -1,   163,
      -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,
      36,    37,    38,    -1,    40,    41,    -1,    43,    -1,    -1,
      46,    -1,    -1,    -1,    50,    51,    -1,    -1,    54,    55,
      -1,    57,    58,    -1,    60,    61,    -1,    -1,    -1,    -1,
      -1,    67,    -1,    69,    -1,    71,    -1,    -1,    -1,    -1,
      76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,
      86,    87,    88,    89,    90,    -1,    92,    -1,    -1,    95,
      96,    97,    -1,    99,   100,    -1,   102,    -1,    -1,   105,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   113,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   129,   130,   131,   132,   133,    -1,    -1,
      -1,    -1,   138,   139,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   148,    -1,    -1,   151,   152,   153,    -1,    -1,
      -1,   157,    -1,   159,    -1,   161,    -1,   163,     3,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    12,    -1,    -1,
      15,    16,    -1,    -1,    -1,    -1,    -1,    22,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    -1,
      -1,    36,    37,    38,    -1,    40,    41,    -1,    43,    -1,
      -1,    46,    -1,    -1,    -1,    50,    51,    -1,    -1,    54,
      55,    -1,    57,    58,    -1,    60,    61,    -1,    -1,    -1,
      -1,    -1,    67,    -1,    69,    -1,    71,    -1,    -1,    -1,
      -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      85,    86,    87,    88,    89,    90,    -1,    92,    -1,    -1,
      95,    96,    97,    -1,    99,   100,    -1,   102,    -1,    -1,
     105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   113,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   129,   130,   131,   132,   133,    -1,
      -1,    -1,    -1,   138,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   148,    -1,    -1,   151,   152,   153,    -1,
      -1,    -1,   157,    -1,   159,    -1,   161,   162,   163,     3,
       4,     5,     6,     7,     8,    -1,    -1,    -1,    12,    -1,
      -1,    15,    16,    -1,    -1,    -1,    -1,    -1,    22,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,
      -1,    -1,    36,    37,    38,    -1,    40,    41,    -1,    43,
      -1,    -1,    46,    -1,    -1,    -1,    50,    51,    -1,    -1,
      54,    55,    -1,    57,    58,    -1,    60,    61,    -1,    -1,
      -1,    -1,    -1,    67,    -1,    69,    -1,    71,    -1,    -1,
      -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    85,    86,    87,    88,    89,    90,    -1,    92,    -1,
      -1,    95,    96,    97,    -1,    99,   100,    -1,   102,    -1,
      -1,   105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   113,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   129,   130,   131,   132,   133,
      -1,    -1,    -1,    -1,   138,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   148,    -1,    -1,   151,   152,   153,
      -1,    -1,    -1,   157,    -1,   159,    -1,   161,   162,   163,
       3,     4,     5,     6,     7,     8,    -1,    -1,    -1,    12,
      -1,    -1,    15,    16,    -1,    -1,    -1,    -1,    -1,    22,
      -1,    24,    -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,
      -1,    -1,    -1,    36,    37,    38,    -1,    40,    41,    42,
      43,    -1,    -1,    46,    -1,    -1,    -1,    50,    51,    -1,
      -1,    54,    55,    -1,    57,    58,    -1,    60,    61,    -1,
      -1,    -1,    -1,    -1,    67,    -1,    69,    -1,    71,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    79,    -1,    -1,    -1,
      -1,    -1,    85,    86,    87,    88,    89,    90,    -1,    92,
      -1,    -1,    95,    -1,    -1,    -1,    99,    -1,    -1,   102,
      -1,   104,   105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     113,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   129,   130,   131,   132,
     133,    -1,    -1,    -1,    -1,   138,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   148,    -1,    -1,   151,   152,
      -1,    -1,    -1,    -1,   157,    -1,   159,    -1,   161,    -1,
     163,     3,     4,     5,     6,     7,     8,    -1,    -1,    -1,
      12,    -1,    -1,    15,    16,    -1,    -1,    19,    -1,    -1,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,
      -1,    -1,    -1,    -1,    36,    37,    38,    -1,    40,    41,
      -1,    43,    -1,    -1,    46,    -1,    -1,    -1,    50,    51,
      -1,    -1,    54,    55,    -1,    57,    58,    -1,    60,    61,
      -1,    -1,    -1,    -1,    -1,    67,    -1,    69,    -1,    71,
      -1,    -1,    -1,    -1,    76,    77,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    85,    86,    87,    88,    89,    90,    -1,
      92,    -1,    -1,    95,    -1,    -1,    98,    99,    -1,   101,
     102,    -1,    -1,   105,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   113,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,   130,   131,
     132,   133,    -1,    -1,    -1,    -1,   138,    -1,    -1,     3,
       4,     5,     6,     7,     8,    -1,   148,    -1,    12,   151,
     152,    15,    16,    -1,    -1,   157,    -1,   159,    22,   161,
      -1,   163,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,
      -1,    -1,    36,    37,    38,    -1,    40,    41,    -1,    43,
      -1,    -1,    46,    -1,    -1,    -1,    50,    51,    -1,    -1,
      54,    55,    -1,    57,    58,    -1,    60,    61,    -1,    -1,
      -1,    -1,    -1,    67,    -1,    69,    -1,    71,    -1,    -1,
      -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    85,    86,    87,    88,    89,    90,    -1,    92,    -1,
      -1,    95,    96,    97,    -1,    99,    -1,    -1,   102,    -1,
      -1,   105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   113,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   129,   130,   131,   132,   133,
      -1,    -1,    -1,    -1,   138,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   148,    -1,    -1,   151,   152,    -1,
     154,    -1,    -1,   157,    -1,   159,    -1,   161,    -1,   163,
       3,     4,     5,     6,     7,     8,    -1,    -1,    -1,    12,
      -1,    -1,    15,    16,    -1,    -1,    -1,    -1,    -1,    22,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,
      -1,    -1,    -1,    36,    37,    38,    -1,    40,    41,    -1,
      43,    -1,    -1,    46,    -1,    -1,    -1,    50,    51,    -1,
      -1,    54,    55,    -1,    57,    58,    -1,    60,    61,    -1,
      -1,    -1,    -1,    -1,    67,    -1,    69,    -1,    71,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    85,    86,    87,    88,    89,    90,    -1,    92,
      -1,    -1,    95,    96,    97,    -1,    99,    -1,    -1,   102,
      -1,    -1,   105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     113,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   129,   130,   131,   132,
     133,    -1,    -1,    -1,    -1,   138,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   148,    -1,    -1,   151,   152,
     153,    -1,    -1,    -1,   157,    -1,   159,    -1,   161,    -1,
     163,     3,     4,     5,     6,     7,     8,    -1,    -1,    -1,
      12,    -1,    -1,    15,    16,    -1,    -1,    -1,    -1,    -1,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,
      -1,    -1,    -1,    -1,    36,    37,    38,    -1,    40,    41,
      -1,    43,    -1,    -1,    46,    -1,    -1,    -1,    50,    51,
      -1,    -1,    54,    55,    -1,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    -1,    67,    -1,    69,    -1,    71,
      -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    85,    86,    87,    88,    89,    90,    -1,
      92,    -1,    -1,    95,    96,    97,    -1,    99,    -1,    -1,
     102,    -1,    -1,   105,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   113,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,   130,   131,
     132,   133,    -1,    -1,    -1,    -1,   138,    -1,    -1,     3,
       4,     5,     6,     7,     8,    -1,   148,    -1,    12,   151,
     152,    15,    16,    -1,    -1,   157,    -1,   159,    22,   161,
      -1,   163,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,
      -1,    -1,    36,    37,    38,    -1,    40,    41,    -1,    43,
      -1,    -1,    46,    -1,    -1,    -1,    50,    51,    -1,    -1,
      54,    55,    -1,    57,    58,    -1,    60,    61,    -1,    -1,
      -1,    -1,    -1,    67,    68,    69,    -1,    71,    -1,    -1,
      -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    85,    86,    87,    88,    89,    90,    -1,    92,    -1,
      -1,    95,    -1,    -1,    -1,    99,    -1,    -1,   102,    -1,
      -1,   105,    -1,    -1,    -1,    -1,    -1,   111,    -1,   113,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   129,   130,   131,   132,   133,
      -1,    -1,    -1,    -1,   138,    -1,    -1,     3,     4,     5,
       6,     7,     8,    -1,   148,    -1,    12,   151,   152,    15,
      16,    -1,    -1,   157,    -1,   159,    22,   161,    -1,   163,
      -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,
      36,    37,    38,    -1,    40,    41,    -1,    43,    -1,    -1,
      46,    -1,    -1,    -1,    50,    51,    -1,    -1,    54,    55,
      -1,    57,    58,    -1,    60,    61,    -1,    -1,    -1,    -1,
      -1,    67,    -1,    69,    -1,    71,    -1,    -1,    -1,    -1,
      76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,
      86,    87,    88,    89,    90,    -1,    92,    -1,    -1,    95,
      -1,    -1,    -1,    99,    -1,    -1,   102,    -1,    -1,   105,
      -1,    -1,    -1,    -1,    -1,   111,    -1,   113,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   129,   130,   131,   132,   133,    -1,    -1,
      -1,    -1,   138,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   148,    -1,    -1,   151,   152,   153,    -1,    -1,
      -1,   157,    -1,   159,    -1,   161,    -1,   163,     3,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    12,    -1,    -1,
      15,    16,    -1,    -1,    -1,    -1,    -1,    22,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    -1,
      -1,    36,    37,    38,    -1,    40,    41,    -1,    43,    -1,
      -1,    46,    -1,    -1,    -1,    50,    51,    -1,    -1,    54,
      55,    -1,    57,    58,    -1,    60,    61,    -1,    -1,    -1,
      -1,    -1,    67,    -1,    69,    -1,    71,    -1,    -1,    -1,
      -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      85,    86,    87,    88,    89,    90,    -1,    92,    -1,    -1,
      95,    96,    97,    -1,    99,    -1,    -1,   102,    -1,    -1,
     105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   113,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   129,   130,   131,   132,   133,    -1,
      -1,    -1,    -1,   138,    -1,    -1,     3,     4,     5,     6,
       7,     8,    -1,   148,    -1,    12,   151,   152,    15,    16,
      -1,    -1,   157,    -1,   159,    22,   161,    -1,   163,    -1,
      -1,    -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,    36,
      37,    38,    -1,    40,    41,    -1,    43,    -1,    -1,    46,
      -1,    -1,    -1,    50,    51,    -1,    -1,    54,    55,    -1,
      57,    58,    -1,    60,    61,    -1,    -1,    -1,    -1,    -1,
      67,    -1,    69,    -1,    71,    -1,    -1,    -1,    -1,    76,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,    86,
      87,    88,    89,    90,    -1,    92,    -1,    -1,    95,    -1,
      -1,    -1,    99,    -1,    -1,   102,    -1,    -1,   105,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   113,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   129,   130,   131,   132,   133,    -1,    -1,    -1,
      -1,   138,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   148,    -1,    -1,   151,   152,   153,    -1,    -1,    -1,
     157,    -1,   159,   160,   161,    -1,   163,     3,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    12,    -1,    -1,    15,
      16,    -1,    -1,    -1,    -1,    -1,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,
      36,    37,    38,    -1,    40,    41,    -1,    43,    -1,    -1,
      46,    -1,    -1,    -1,    50,    51,    -1,    -1,    54,    55,
      -1,    57,    58,    -1,    60,    61,    -1,    -1,    -1,    -1,
      -1,    67,    -1,    69,    -1,    71,    -1,    -1,    -1,    -1,
      76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,
      86,    87,    88,    89,    90,    -1,    92,    -1,    -1,    95,
      -1,    -1,    -1,    99,    -1,    -1,   102,    -1,    -1,   105,
      -1,    -1,    -1,    -1,    -1,   111,    -1,   113,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   129,   130,   131,   132,   133,    -1,    -1,
      -1,    -1,   138,    -1,    -1,     3,     4,     5,     6,     7,
       8,    -1,   148,    -1,    12,   151,   152,    15,    16,    -1,
      -1,   157,    -1,   159,    22,   161,    -1,   163,    -1,    -1,
      -1,    29,    30,    -1,    -1,    -1,    -1,    -1,    36,    37,
      38,    -1,    40,    41,    -1,    43,    -1,    -1,    46,    -1,
      -1,    -1,    50,    51,    -1,    -1,    54,    55,    -1,    57,
      58,    -1,    60,    61,    -1,    -1,    -1,    -1,    -1,    67,
      -1,    69,    -1,    71,    -1,    -1,    -1,    -1,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,    86,    87,
      88,    89,    90,    -1,    92,    -1,    -1,    95,    -1,    -1,
      -1,    99,    -1,    -1,   102,    -1,    -1,   105,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   113,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   129,   130,   131,   132,   133,    -1,    -1,    -1,    -1,
     138,    -1,    -1,     3,     4,     5,     6,     7,     8,    -1,
     148,    -1,    12,   151,   152,    15,    16,    -1,    -1,   157,
      -1,   159,    22,   161,    -1,   163,    -1,    -1,    -1,    -1,
      30,    -1,    -1,    -1,    -1,    -1,    36,    37,    38,    -1,
      40,    41,    -1,    43,    -1,    -1,    46,    -1,    -1,    -1,
      50,    51,    -1,    -1,    54,    55,    -1,    57,    58,    -1,
      60,    61,    -1,    -1,    -1,    -1,    -1,    67,    -1,    69,
      -1,    71,    -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    85,    86,    87,    88,    89,
      90,    -1,    92,    -1,    -1,    95,    -1,    -1,    -1,    99,
      -1,    -1,   102,    -1,    -1,   105,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   113,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,
     130,   131,   132,   133,    -1,    -1,    -1,    -1,   138,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   148,    -1,
      -1,   151,   152,   153,    -1,    -1,    -1,   157,    -1,   159,
      -1,   161,    -1,   163,     3,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    12,    -1,    -1,    15,    16,    -1,    -1,
      -1,    -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    -1,    -1,    -1,    -1,    -1,    36,    37,    38,
      -1,    40,    41,    -1,    43,    -1,    -1,    46,    -1,    -1,
      -1,    50,    51,    -1,    -1,    54,    55,    -1,    57,    58,
      -1,    60,    61,    -1,    -1,    -1,    -1,    -1,    67,    -1,
      69,    -1,    71,    -1,    -1,    -1,    -1,    76,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    85,    86,    87,    88,
      89,    90,    -1,    92,    -1,    -1,    95,    -1,    -1,    -1,
      99,    -1,    -1,   102,    -1,    -1,   105,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   113,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     129,   130,   131,   132,   133,    -1,    -1,    -1,    -1,   138,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   148,
      -1,    -1,   151,   152,   153,    -1,    -1,    -1,   157,    -1,
     159,    -1,   161,    -1,   163,     3,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    12,    -1,    -1,    15,    16,    -1,
      -1,    -1,    -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,    36,    37,
      38,    -1,    40,    41,    -1,    43,    -1,    -1,    46,    -1,
      -1,    -1,    50,    51,    -1,    -1,    54,    55,    -1,    57,
      58,    -1,    60,    61,    -1,    -1,    -1,    -1,    -1,    67,
      -1,    69,    -1,    71,    -1,    -1,    -1,    -1,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,    86,    87,
      88,    89,    90,    -1,    92,    -1,    -1,    95,    -1,    -1,
      -1,    99,    -1,    -1,   102,    -1,    -1,   105,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   113,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   129,   130,   131,   132,   133,    -1,    -1,    -1,    -1,
     138,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     148,    -1,    -1,   151,   152,   153,    -1,    -1,    -1,   157,
      -1,   159,    -1,   161,    -1,   163,     3,     4,     5,     6,
       7,     8,    -1,    -1,    -1,    12,    -1,    -1,    15,    16,
      -1,    -1,    -1,    -1,    -1,    22,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,    36,
      37,    38,    -1,    40,    41,    -1,    43,    -1,    -1,    46,
      -1,    -1,    -1,    50,    51,    -1,    -1,    54,    55,    -1,
      57,    58,    -1,    60,    61,    -1,    -1,    -1,    -1,    -1,
      67,    -1,    69,    -1,    71,    -1,    -1,    -1,    -1,    76,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,    86,
      87,    88,    89,    90,    -1,    92,    -1,    -1,    95,    -1,
      -1,    -1,    99,    -1,    -1,   102,    -1,    -1,   105,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   113,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   129,   130,   131,   132,   133,    -1,    -1,    -1,
      -1,   138,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   148,    -1,    -1,   151,   152,   153,    -1,    -1,    -1,
     157,    -1,   159,    -1,   161,    -1,   163,     3,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    12,    -1,    -1,    15,
      16,    -1,    -1,    -1,    -1,    -1,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,
      36,    37,    38,    -1,    40,    41,    -1,    43,    -1,    -1,
      46,    -1,    -1,    -1,    50,    51,    -1,    -1,    54,    55,
      -1,    57,    58,    -1,    60,    61,    -1,    -1,    -1,    -1,
      -1,    67,    -1,    69,    -1,    71,    -1,    -1,    -1,    -1,
      76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,
      86,    87,    88,    89,    90,    -1,    92,    -1,    -1,    95,
      -1,    -1,    -1,    99,    -1,    -1,   102,    -1,    -1,   105,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   113,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   129,   130,   131,   132,   133,    -1,    -1,
      -1,    -1,   138,    -1,    -1,     3,     4,     5,     6,     7,
       8,    -1,   148,    -1,    12,   151,   152,    15,    16,    -1,
      -1,   157,    -1,   159,    22,   161,    -1,   163,    -1,    -1,
      -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,    36,    37,
      38,    -1,    40,    41,    -1,    43,    -1,    -1,    46,    -1,
      -1,    -1,    50,    51,    -1,    -1,    54,    55,    -1,    57,
      58,    -1,    60,    61,    -1,    -1,    -1,    -1,    -1,    67,
      -1,    69,    -1,    71,    -1,    -1,    -1,    -1,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,    86,    87,
      88,    89,    90,    -1,    92,    -1,    -1,    95,    -1,    -1,
      -1,    99,    -1,    -1,   102,    -1,    -1,   105,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   113,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   129,   130,   131,   132,   133,    -1,    -1,    -1,    -1,
     138,    -1,    -1,     3,     4,     5,     6,     7,     8,    -1,
     148,    -1,    12,   151,   152,    15,    16,    -1,    -1,   157,
      -1,   159,    22,   161,    -1,   163,    -1,    -1,    -1,    -1,
      30,    -1,    -1,    -1,    -1,    -1,    36,    37,    38,    -1,
      40,    41,    -1,    43,    -1,    -1,    46,    -1,    -1,    -1,
      50,    51,    -1,    -1,    54,    55,    -1,    57,    58,    -1,
      60,    61,    -1,    -1,    -1,    -1,    -1,    67,    -1,    69,
      -1,    71,    -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    85,    86,    87,    88,    89,
      90,    -1,    92,    -1,    -1,    95,    -1,    -1,    -1,    99,
      -1,    -1,   102,    -1,    -1,   105,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   113,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,
     130,   131,   132,   133,    -1,    -1,    -1,    -1,   138,    -1,
      -1,     3,     4,     5,     6,     7,     8,    -1,   148,    -1,
      12,   151,   152,    15,    16,    -1,    -1,   157,    -1,   159,
      22,   161,    -1,   163,    -1,    -1,    -1,    -1,    30,    -1,
      -1,    -1,    -1,    -1,    36,    37,    38,    -1,    40,    41,
      -1,    43,    -1,    -1,    46,    -1,    -1,    -1,    50,    51,
      -1,    -1,    54,    55,    -1,    57,    58,    -1,    60,    61,
      -1,    -1,    -1,    -1,    -1,    67,    -1,    69,    -1,    71,
      -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    85,    86,    87,    88,    89,    90,    -1,
      92,    -1,    -1,    95,    -1,    -1,    -1,    99,    -1,    -1,
     102,    -1,    -1,   105,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   113,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,   130,   131,
     132,   133,    -1,    -1,    -1,    -1,   138,    -1,    -1,     3,
       4,     5,     6,     7,     8,    -1,   148,    -1,    12,   151,
     152,    15,    16,    -1,    -1,   157,    -1,   159,    22,   161,
      -1,   163,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,
      -1,    -1,    36,    37,    38,    -1,    40,    41,    -1,    43,
      -1,    -1,    46,    -1,    -1,    -1,    50,    51,    -1,    -1,
      54,    55,    -1,    57,    58,    -1,    60,    61,    -1,    -1,
      -1,    -1,    -1,    67,    -1,    69,    -1,    71,    -1,    -1,
      -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    85,    86,    87,    88,    89,    90,    -1,    92,    -1,
      -1,    95,    -1,    -1,    -1,    99,    -1,    -1,   102,    -1,
      -1,   105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   113,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   129,   130,   131,   132,   133,
      -1,    -1,    -1,    -1,   138,    -1,    -1,     3,     4,     5,
       6,     7,     8,    -1,   148,    -1,    12,   151,   152,    15,
      16,    -1,    -1,   157,    -1,   159,    22,   161,    -1,   163,
      -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,
      36,    37,    38,    -1,    40,    41,    -1,    43,    -1,    -1,
      46,    -1,    -1,    -1,    50,    51,    -1,    -1,    54,    55,
      -1,    57,    58,    -1,    60,    61,    -1,    -1,    -1,    -1,
      -1,    67,    -1,    69,    -1,    71,    -1,    -1,    -1,    -1,
      76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,
      86,    87,    88,    89,    90,    -1,    92,    -1,    -1,    95,
      -1,    -1,    -1,    99,    -1,    -1,   102,    -1,    -1,   105,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   113,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   129,   130,   131,   132,   133,    -1,    -1,
      -1,    -1,   138,    -1,    -1,     3,     4,     5,     6,     7,
       8,    -1,   148,    -1,    12,   151,   152,    15,    16,    -1,
      -1,   157,    -1,   159,    22,   161,    -1,   163,    -1,    -1,
      -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,    36,    37,
      38,    -1,    40,    41,    -1,    43,    -1,    -1,    46,    -1,
      -1,    -1,    50,    51,    -1,    -1,    54,    55,    -1,    57,
      58,    -1,    60,    61,    -1,    -1,    -1,    -1,    -1,    67,
      -1,    69,    -1,    71,    -1,    -1,    -1,    -1,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,    86,    87,
      88,    89,    90,    -1,    92,    -1,    -1,    95,    -1,    -1,
      -1,    99,    -1,    -1,   102,    -1,    -1,   105,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   113,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   129,   130,   131,   132,   133,    -1,    -1,    -1,    -1,
     138,    -1,    -1,     3,     4,     5,     6,     7,     8,    -1,
     148,    -1,    12,   151,   152,    15,    16,    -1,    -1,   157,
      -1,   159,    22,   161,    -1,   163,    -1,    -1,    -1,    -1,
      30,    -1,    -1,    -1,    -1,    -1,    36,    37,    38,    -1,
      40,    41,    -1,    43,    -1,    -1,    46,    -1,    -1,    -1,
      50,    51,    -1,    -1,    54,    55,    -1,    57,    58,    -1,
      60,    61,    -1,    -1,    -1,    -1,    -1,    67,    -1,    69,
      -1,    71,    -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    85,    86,    87,    88,    89,
      90,    -1,    92,    -1,    -1,    95,    -1,    -1,    -1,    99,
      -1,    -1,   102,    -1,    -1,   105,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   113,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,
     130,   131,   132,   133,    -1,    -1,    -1,    -1,   138,    -1,
      -1,     3,     4,     5,     6,     7,     8,    -1,   148,    -1,
      12,   151,   152,    15,    16,    -1,    -1,   157,    -1,   159,
      22,   161,    -1,   163,    -1,    -1,    -1,    -1,    30,    -1,
      -1,    -1,    -1,    -1,    36,    37,    38,    -1,    40,    41,
      -1,    43,    -1,    -1,    46,    -1,    -1,    -1,    50,    51,
      -1,    -1,    54,    55,    -1,    57,    58,    -1,    60,    61,
      -1,    -1,    -1,    -1,    -1,    67,    -1,    69,    -1,    71,
      -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    85,    86,    87,    88,    89,    90,    -1,
      92,    -1,    -1,    95,    -1,    -1,    -1,    99,    -1,    -1,
     102,    -1,    -1,   105,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   113,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,   130,   131,
     132,   133,    -1,    -1,    -1,    -1,   138,    -1,    -1,     3,
       4,     5,     6,     7,     8,    -1,   148,    -1,    12,   151,
     152,    15,    16,    -1,    -1,   157,    -1,   159,    22,   161,
      -1,   163,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,
      -1,    -1,    36,    37,    38,    -1,    40,    41,    -1,    43,
      -1,    -1,    46,    -1,    -1,    -1,    50,    51,    -1,    -1,
      54,    55,    -1,    57,    58,    -1,    60,    61,    -1,    -1,
      -1,    -1,    -1,    67,    -1,    69,    -1,    71,    -1,    -1,
      -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    85,    86,    87,    88,    89,    90,    -1,    92,    -1,
      -1,    95,    -1,    -1,    -1,    99,    -1,    -1,   102,    -1,
      -1,   105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   113,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   129,   130,   131,   132,   133,
      -1,    -1,    -1,    -1,   138,    -1,    -1,     3,     4,     5,
       6,     7,     8,    -1,   148,    -1,    12,   151,   152,    15,
      16,    -1,    -1,   157,    -1,   159,    22,   161,    -1,   163,
      -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,
      36,    37,    38,    -1,    40,    41,    -1,    43,    -1,    -1,
      46,    -1,    -1,    -1,    50,    51,    -1,    -1,    54,    55,
      -1,    57,    58,    -1,    60,    61,    -1,    -1,    -1,    -1,
      -1,    67,    -1,    69,    -1,    71,    -1,    -1,    -1,    -1,
      76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,
      86,    87,    88,    89,    90,    -1,    92,    -1,    -1,    95,
      -1,    -1,    -1,    99,    -1,    -1,   102,    -1,    -1,   105,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   113,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   129,   130,   131,   132,   133,    -1,    -1,
      -1,    -1,   138,    -1,    -1,     3,     4,     5,     6,     7,
       8,    -1,   148,    -1,    12,   151,   152,    15,    16,    -1,
      -1,   157,    -1,   159,    22,   161,    -1,   163,    -1,    -1,
      -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,    36,    37,
      38,    -1,    40,    41,    -1,    43,    -1,    -1,    46,    -1,
      -1,    -1,    50,    51,    -1,    -1,    54,    55,    -1,    57,
      58,    -1,    60,    61,    -1,    -1,    -1,    -1,    -1,    67,
      -1,    69,    -1,    71,    -1,    -1,    -1,    -1,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,    86,    87,
      88,    89,    90,    -1,    92,    -1,    -1,    95,    -1,    -1,
      -1,    99,    -1,    -1,   102,    -1,    -1,   105,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   113,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   129,   130,   131,   132,   133,    -1,    -1,    -1,    -1,
     138,    -1,    -1,     3,     4,     5,     6,     7,     8,    -1,
     148,    -1,    12,   151,   152,    15,    16,    -1,    -1,   157,
      -1,   159,    22,   161,    -1,   163,    -1,    -1,    -1,    -1,
      30,    -1,    -1,    -1,    -1,    -1,    36,    37,    38,    -1,
      40,    41,    -1,    43,    -1,    -1,    46,    -1,    -1,    -1,
      50,    51,    -1,    -1,    54,    55,    -1,    57,    58,    -1,
      60,    61,    -1,    -1,    -1,    -1,    -1,    67,    -1,    69,
      -1,    71,    -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    85,    86,    87,    88,    89,
      90,    -1,    92,    -1,    -1,    95,    -1,    -1,    -1,    99,
      -1,    -1,   102,    -1,    -1,   105,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   113,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,
     130,   131,   132,   133,    -1,    -1,    -1,    -1,   138,    -1,
      -1,     3,     4,     5,     6,     7,     8,    -1,   148,    -1,
      12,   151,   152,    15,    16,    -1,    -1,   157,    -1,   159,
      22,   161,    -1,   163,    -1,    -1,    -1,    -1,    30,    -1,
      -1,    -1,    -1,    -1,    36,    37,    38,    -1,    40,    41,
      -1,    43,    -1,    -1,    46,    -1,    -1,    -1,    50,    51,
      -1,    -1,    54,    55,    -1,    57,    58,    -1,    60,    61,
      -1,    -1,    -1,    -1,    -1,    67,    -1,    69,    -1,    71,
      -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    85,    86,    87,    88,    89,    90,    -1,
      92,    -1,    -1,    95,    -1,    -1,    -1,    99,    -1,    -1,
     102,    -1,    -1,   105,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   113,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,   130,   131,
     132,   133,    -1,    -1,    -1,    -1,   138,    -1,    -1,     3,
       4,     5,     6,     7,     8,    -1,   148,    -1,    12,   151,
     152,    15,    16,    -1,    -1,   157,    -1,   159,    22,   161,
      -1,   163,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,
      -1,    -1,    36,    37,    38,    -1,    40,    41,    -1,    43,
      -1,    -1,    46,    -1,    -1,    -1,    50,    51,    -1,    -1,
      54,    55,    -1,    57,    58,    -1,    60,    61,    -1,    -1,
      -1,    -1,    -1,    67,    -1,    69,    -1,    71,    -1,    -1,
      -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    85,    86,    87,    88,    89,    90,    -1,    92,    -1,
      -1,    95,    -1,    -1,    -1,    99,    -1,    -1,   102,    -1,
      -1,   105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   113,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   129,   130,   131,   132,   133,
      -1,    -1,    -1,    -1,   138,    -1,    -1,     3,     4,     5,
       6,     7,     8,    -1,   148,    -1,    12,   151,   152,    15,
      16,    -1,    -1,   157,    -1,    -1,    22,   161,    -1,   163,
      -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,
      36,    37,    38,    -1,    40,    41,    -1,    43,    -1,    -1,
      46,    -1,    -1,    -1,    50,    51,    -1,    -1,    54,    55,
      -1,    57,    58,    -1,    60,    61,    -1,    -1,    -1,    -1,
      -1,    67,    -1,    69,    -1,    71,    -1,    -1,    -1,    -1,
      76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,
      86,    87,    88,    89,    90,    -1,    92,    -1,    -1,    95,
      -1,    -1,    -1,    99,    -1,    -1,   102,    -1,    -1,   105,
      -1,    -1,    -1,    -1,    -1,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
      -1,    -1,    -1,   129,   130,   131,   132,   133,    -1,    -1,
      -1,     3,     4,     5,     6,     7,     8,    -1,    -1,    -1,
      12,    -1,   148,    15,    16,    -1,   152,    -1,    -1,   158,
      22,   157,   161,   159,   163,   161,    -1,   163,    30,    -1,
      -1,    -1,    -1,    -1,    36,    37,    38,    -1,    40,    41,
      -1,    43,    -1,    -1,    46,    -1,    -1,    -1,    50,    51,
      -1,    -1,    54,    55,    -1,    57,    58,    -1,    60,    61,
      -1,    -1,    -1,    -1,    -1,    67,    -1,    69,    -1,    71,
      -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    85,    86,    87,    88,    89,    90,    -1,
      92,    -1,    -1,    95,    -1,    -1,    -1,    99,    -1,    -1,
     102,    -1,    -1,   105,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    12,    -1,    -1,    15,    16,   131,
      -1,    -1,    -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,    36,    37,
      38,    -1,    40,    41,    -1,    43,    -1,   159,    46,   161,
      -1,   163,    50,    51,    -1,    -1,    54,    55,    -1,    57,
      58,    -1,    60,    61,    -1,    -1,    -1,    -1,    -1,    67,
      -1,    69,    -1,    71,    -1,    -1,    -1,    -1,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,    86,    87,
      88,    89,    90,    -1,    92,    -1,    -1,    95,    -1,    -1,
      -1,    99,    -1,    -1,   102,    -1,    -1,   105,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,    -1,    -1,    -1,    12,    -1,
      -1,    15,    16,   131,    -1,    -1,    -1,    -1,    22,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,
      -1,    -1,    36,    37,    38,    -1,    40,    41,    -1,    43,
      -1,   159,    46,   161,    -1,   163,    50,    51,    -1,    -1,
      54,    55,    -1,    57,    58,    -1,    60,    61,    -1,    -1,
      -1,    -1,    -1,    67,    -1,    69,    -1,    71,    -1,    -1,
      -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,    85,    86,    87,    88,    89,    90,    -1,    92,    -1,
      -1,    95,    15,    16,    -1,    99,    -1,    -1,   102,    22,
      -1,   105,    -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,
      -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,    41,    -1,
      43,    -1,    -1,    46,    -1,    -1,    -1,   131,    -1,    -1,
      -1,    54,    -1,    -1,    -1,    -1,    -1,    60,    61,    -1,
      -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    -1,   161,     3,   163,
      -1,    -1,    85,    86,    -1,    -1,    -1,    90,    -1,    92,
      15,    16,    95,    -1,    -1,    -1,    99,    22,    -1,   102,
      -1,    -1,   105,    -1,    -1,    30,    -1,    -1,    -1,    -1,
      -1,    36,    -1,    -1,    -1,    -1,    41,    -1,    43,    -1,
      -1,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      -1,    -1,    -1,    -1,    -1,    60,    61,    -1,    -1,    -1,
      -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    76,    -1,    -1,    -1,    -1,   159,    -1,   161,     3,
      85,    86,    -1,    -1,    -1,    90,    -1,    92,    -1,    -1,
      95,    15,    16,    -1,    99,    -1,    -1,   102,    22,    -1,
     105,    -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,
      -1,    -1,    36,    -1,    -1,    -1,    -1,    41,    -1,    43,
      -1,    -1,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    -1,    -1,    -1,    -1,    -1,    60,    61,    -1,    -1,
      -1,    -1,    -1,    67,    -1,    -1,     3,    -1,    -1,    -1,
      -1,    -1,    76,    10,    -1,    -1,   161,    -1,    15,    16,
      17,    85,    86,    -1,    -1,    22,    90,    -1,    92,    -1,
      -1,    95,    -1,    30,    -1,    99,    -1,    -1,   102,    36,
      -1,   105,    -1,    -1,    41,    -1,    43,    -1,    -1,    46,
      -1,    48,    -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,
      -1,    -1,    -1,    60,    61,    -1,    -1,    -1,    -1,    10,
      67,    -1,    -1,    -1,    -1,    -1,    17,    -1,    -1,    76,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    85,    86,
      -1,    88,    -1,    90,    -1,    92,    -1,   161,    95,    -1,
      -1,    -1,    99,    -1,    -1,   102,    -1,    -1,   105,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   114,   115,   116,
     117,   118,   119,    -1,    -1,   122,   123,   124,   125,    -1,
     127,   128,   129,   130,   131,   132,   133,    78,    -1,   136,
      -1,    82,    -1,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,    -1,   152,    10,    -1,   155,   156,
     157,   158,    -1,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   113,    -1,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,   130,
      -1,   132,   133,   134,    -1,   136,   137,   138,    -1,   140,
     141,   142,   143,   144,    -1,   146,   147,   148,   149,   150,
     151,   152,    -1,    10,   155,   156,   157,    -1,    -1,    -1,
      17,    -1,    -1,   164,    78,    -1,    -1,    -1,    82,    -1,
      -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    10,    -1,    -1,    -1,    -1,    -1,   113,
      17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    -1,    -1,    -1,   129,   130,    -1,   132,   133,
     134,    78,   136,   137,   138,    82,   140,   141,   142,   143,
     144,    -1,   146,   147,   148,   149,   150,   151,   152,    -1,
      -1,   155,   156,   157,    -1,    -1,    -1,    -1,    -1,    -1,
     164,    -1,    -1,    -1,    -1,    -1,   113,    -1,    -1,    -1,
      -1,    78,    -1,    -1,    -1,    82,    -1,    -1,    -1,    -1,
      -1,    -1,   129,   130,    -1,   132,   133,   134,    -1,   136,
     137,   138,    -1,   140,   141,   142,   143,   144,    -1,   146,
     147,   148,   149,   150,   151,   152,   113,    -1,   155,   156,
     157,    -1,    -1,    -1,    10,   162,    -1,    -1,    -1,    -1,
      -1,    17,   129,   130,    -1,   132,   133,   134,    -1,   136,
     137,   138,    28,   140,   141,   142,   143,   144,    -1,   146,
     147,   148,   149,   150,   151,   152,    -1,    -1,   155,   156,
     157,    -1,    -1,    -1,    -1,   162,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    78,    -1,    -1,    -1,    82,    -1,    -1,    -1,
      10,    -1,    -1,    -1,    -1,    91,    -1,    17,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   113,   114,   115,
     116,   117,   118,   119,    -1,    -1,   122,   123,   124,   125,
      -1,   127,   128,   129,   130,    -1,   132,   133,   134,    -1,
     136,   137,   138,    -1,   140,   141,   142,   143,   144,    -1,
     146,   147,   148,   149,   150,   151,   152,    -1,    78,   155,
     156,   157,    82,   159,    -1,    -1,    10,    -1,    -1,    -1,
      -1,    91,    -1,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   113,   114,   115,   116,   117,   118,   119,
      -1,    -1,   122,   123,   124,   125,    -1,   127,   128,   129,
     130,    -1,   132,   133,   134,    -1,   136,   137,   138,    -1,
     140,   141,   142,   143,   144,    -1,   146,   147,   148,   149,
     150,   151,   152,    -1,    78,   155,   156,   157,    82,   159,
      -1,    -1,    10,    -1,    -1,    -1,    -1,    91,    -1,    17,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   113,
     114,   115,   116,   117,   118,   119,    -1,    -1,   122,   123,
     124,   125,    -1,   127,   128,   129,   130,    -1,   132,   133,
     134,    -1,   136,   137,   138,    -1,   140,   141,   142,   143,
     144,    -1,   146,   147,   148,   149,   150,   151,   152,    -1,
      78,   155,   156,   157,    82,   159,    -1,    -1,    10,    -1,
      -1,    -1,    -1,    91,    -1,    17,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   113,   114,   115,   116,   117,
     118,   119,    -1,    -1,   122,   123,   124,   125,    -1,   127,
     128,   129,   130,    -1,   132,   133,   134,    -1,   136,   137,
     138,    -1,   140,   141,   142,   143,   144,    -1,   146,   147,
     148,   149,   150,   151,   152,    -1,    78,   155,   156,   157,
      82,   159,    -1,    -1,    10,    -1,    -1,    -1,    -1,    91,
      -1,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   113,   114,   115,   116,   117,   118,   119,    -1,    -1,
     122,   123,   124,   125,    -1,   127,   128,   129,   130,    -1,
     132,   133,   134,    -1,   136,   137,   138,    -1,   140,   141,
     142,   143,   144,    -1,   146,   147,   148,   149,   150,   151,
     152,    -1,    78,   155,   156,   157,    82,   159,    -1,    -1,
      10,    -1,    -1,    -1,    -1,    91,    -1,    17,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   113,   114,   115,
     116,   117,   118,   119,    -1,    -1,   122,   123,   124,   125,
      -1,   127,   128,   129,   130,    -1,   132,   133,   134,    -1,
     136,   137,   138,    -1,   140,   141,   142,   143,   144,    -1,
     146,   147,   148,   149,   150,   151,   152,    -1,    78,   155,
     156,   157,    82,   159,    -1,    -1,    10,    -1,    -1,    -1,
      -1,    91,    -1,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   113,   114,   115,   116,   117,   118,   119,
      -1,    -1,   122,   123,   124,   125,    -1,   127,   128,   129,
     130,    -1,   132,   133,   134,    -1,   136,   137,   138,    -1,
     140,   141,   142,   143,   144,    -1,   146,   147,   148,   149,
     150,   151,   152,    -1,    78,   155,   156,   157,    82,   159,
      -1,    -1,    10,    -1,    -1,    -1,    -1,    91,    -1,    17,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   113,
     114,   115,   116,   117,   118,   119,    -1,    -1,   122,   123,
     124,   125,    -1,   127,   128,   129,   130,    -1,   132,   133,
     134,    -1,   136,   137,   138,    -1,   140,   141,   142,   143,
     144,    -1,   146,   147,   148,   149,   150,   151,   152,    -1,
      78,   155,   156,   157,    82,   159,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    91,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   113,   114,   115,   116,   117,
     118,   119,    -1,    -1,   122,   123,   124,   125,    -1,   127,
     128,   129,   130,    -1,   132,   133,   134,    -1,   136,   137,
     138,    -1,   140,   141,   142,   143,   144,    -1,   146,   147,
     148,   149,   150,   151,   152,    10,    -1,   155,   156,   157,
      -1,   159,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    29,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    10,    -1,    -1,    -1,
      -1,    -1,    -1,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    29,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    78,    -1,    -1,    -1,    82,    42,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    10,    -1,    -1,    -1,    -1,    -1,    -1,    17,    -1,
      -1,    -1,    -1,    -1,   109,    -1,    -1,    -1,   113,    28,
      29,    -1,    -1,    -1,    78,    -1,    -1,    -1,    82,    -1,
      -1,    -1,    -1,    -1,   129,   130,    -1,   132,   133,   134,
      -1,   136,   137,   138,    -1,   140,   141,   142,   143,   144,
      -1,   146,   147,   148,   149,   150,   151,   152,    -1,   113,
     155,   156,   157,    -1,   159,    -1,    -1,    -1,    -1,    78,
      -1,    -1,    28,    82,    -1,   129,   130,    -1,   132,   133,
     134,    -1,   136,   137,   138,    -1,   140,   141,   142,   143,
     144,    -1,   146,   147,   148,   149,   150,   151,   152,    10,
     109,   155,   156,   157,   113,   159,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    -1,
     129,   130,    78,   132,   133,   134,    82,   136,   137,   138,
      -1,   140,   141,   142,   143,   144,    -1,   146,   147,   148,
     149,   150,   151,   152,    10,    -1,   155,   156,   157,    -1,
     159,    17,    -1,    -1,    -1,    -1,    -1,   113,    -1,    -1,
      -1,    -1,    28,    29,    -1,    -1,    -1,    78,    -1,    -1,
      -1,    82,    -1,   129,   130,    -1,   132,   133,   134,    -1,
     136,   137,   138,    -1,   140,   141,   142,   143,    -1,    -1,
     146,   147,   148,   149,   150,   151,   152,    -1,    -1,   155,
     156,   157,   113,    -1,    -1,    -1,    -1,    28,    -1,    -1,
      -1,    -1,    78,    -1,    -1,    -1,    82,    -1,   129,   130,
      -1,   132,   133,   134,    -1,   136,   137,   138,    -1,   140,
     141,   142,   143,   144,    -1,   146,   147,   148,   149,   150,
     151,   152,    10,    -1,   155,   156,   157,   113,   159,    17,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    -1,    -1,
      28,    82,    -1,   129,   130,    -1,   132,   133,   134,    -1,
     136,   137,   138,    -1,   140,   141,   142,   143,   144,    -1,
     146,   147,   148,   149,   150,   151,   152,    10,    -1,   155,
     156,   157,   113,   159,    17,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,   129,   130,
      78,   132,   133,   134,    82,   136,   137,   138,    -1,   140,
     141,   142,   143,    91,    -1,   146,   147,   148,   149,   150,
      -1,   152,    -1,    -1,   155,   156,   157,    -1,    -1,    -1,
      10,    -1,    -1,    -1,    -1,   113,    -1,    17,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    78,    -1,    -1,    28,    82,
      -1,   129,   130,    33,   132,   133,   134,    -1,   136,   137,
     138,    -1,   140,   141,   142,   143,   144,    -1,   146,   147,
     148,   149,   150,   151,   152,    -1,    -1,   155,   156,   157,
     113,   159,    -1,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   129,   130,    78,   132,
     133,   134,    82,   136,   137,   138,    -1,   140,   141,   142,
     143,   144,    -1,   146,   147,   148,   149,   150,   151,   152,
      -1,    -1,   155,   156,   157,    -1,   159,    10,    -1,    -1,
      -1,    -1,    -1,   113,    17,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,   129,
     130,    -1,   132,   133,   134,    -1,   136,   137,   138,    42,
     140,   141,   142,   143,   144,    -1,   146,   147,   148,   149,
     150,   151,   152,    10,   154,   155,   156,   157,    -1,    -1,
      17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    29,    -1,    -1,    78,    -1,    -1,    -1,    82,
      -1,    -1,    -1,    -1,    -1,    42,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   109,    -1,    -1,    -1,
     113,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    78,    -1,    -1,    -1,    82,   129,   130,    -1,   132,
     133,   134,    -1,   136,   137,   138,    -1,   140,   141,   142,
     143,   144,    -1,   146,   147,   148,   149,   150,   151,   152,
      10,    -1,   155,   156,   157,    -1,   113,    17,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,
      -1,    -1,   129,   130,    -1,   132,   133,   134,    -1,   136,
     137,   138,    42,   140,   141,   142,   143,   144,    -1,   146,
     147,   148,   149,   150,   151,   152,    10,    -1,   155,   156,
     157,    -1,    -1,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    78,    33,
      -1,    -1,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    10,    -1,    -1,    -1,
      -1,    -1,    -1,    17,    -1,    -1,    -1,    -1,    -1,    63,
      -1,    -1,    -1,   113,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,    82,   129,
     130,    -1,   132,   133,   134,    -1,   136,   137,   138,    -1,
     140,   141,   142,   143,   144,    -1,   146,   147,   148,   149,
     150,   151,   152,    10,    -1,   155,   156,   157,    -1,   113,
      17,    -1,    -1,    -1,    78,    -1,    -1,    -1,    82,    -1,
      -1,    28,    -1,    -1,    -1,   129,   130,    -1,   132,   133,
     134,    -1,   136,   137,   138,    -1,   140,   141,   142,   143,
     144,    -1,   146,   147,   148,   149,   150,   151,   152,   113,
      -1,   155,   156,   157,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    -1,    -1,    -1,   129,   130,    -1,   132,   133,
     134,    78,   136,   137,   138,    82,   140,   141,   142,   143,
     144,    -1,   146,   147,   148,   149,   150,   151,   152,    10,
     154,   155,   156,   157,    -1,    -1,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   113,    28,    -1,    -1,
      -1,    78,    -1,    -1,    -1,    82,    -1,    -1,    -1,    -1,
      -1,    -1,   129,   130,    -1,   132,   133,   134,    -1,   136,
     137,   138,    -1,   140,   141,   142,   143,   144,    -1,   146,
     147,   148,   149,   150,   151,   152,    10,   154,   155,   156,
     157,    -1,    -1,    17,    -1,    -1,    -1,    78,    -1,    -1,
      -1,    82,   129,   130,    28,   132,   133,   134,    -1,   136,
     137,   138,    -1,   140,   141,   142,   143,    -1,    -1,   146,
     147,   148,   149,   150,    -1,   152,    10,    -1,   155,   156,
     157,    -1,   113,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,   129,   130,
      -1,   132,   133,   134,    78,   136,   137,   138,    82,   140,
     141,   142,   143,   144,    -1,   146,   147,   148,   149,   150,
     151,   152,    10,   154,   155,   156,   157,    -1,    -1,    17,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   113,
      28,    -1,    -1,    -1,    78,    -1,    -1,    -1,    82,    -1,
      -1,    -1,    -1,    -1,    -1,   129,   130,    91,   132,   133,
     134,    -1,   136,   137,   138,    -1,   140,   141,   142,   143,
     144,    -1,   146,   147,   148,   149,   150,   151,   152,   113,
     154,   155,   156,   157,    -1,    -1,    -1,    -1,    -1,    -1,
      78,    -1,    -1,    -1,    82,   129,   130,    28,   132,   133,
     134,    -1,   136,   137,   138,    -1,   140,   141,   142,   143,
     144,    -1,   146,   147,   148,   149,   150,   151,   152,    10,
      -1,   155,   156,   157,   112,   113,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,
      -1,   129,   130,    -1,   132,   133,   134,    78,   136,   137,
     138,    82,   140,   141,   142,   143,   144,    -1,   146,   147,
     148,   149,   150,   151,   152,    -1,    -1,   155,   156,   157,
      -1,    -1,    10,    -1,    -1,    -1,    -1,    -1,    -1,    17,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    -1,    -1,
      28,    82,    -1,    -1,    -1,    -1,    -1,    -1,   129,   130,
      -1,   132,   133,   134,    -1,   136,   137,   138,    -1,    -1,
     141,    -1,    10,    -1,    -1,    -1,    -1,   148,   149,    17,
      -1,   152,   113,    -1,   155,   156,   157,    -1,    -1,    -1,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,   130,
      78,   132,   133,   134,    82,   136,   137,   138,    -1,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,    -1,    -1,   155,   156,   157,    -1,    -1,    10,
      11,   109,    -1,    -1,    -1,   113,    17,    -1,    -1,    -1,
      78,    -1,    -1,    -1,    82,    -1,    -1,    28,    -1,    -1,
      -1,   129,   130,    -1,   132,   133,   134,    -1,   136,   137,
     138,    -1,   140,   141,   142,   143,   144,    -1,   146,   147,
     148,   149,   150,   151,   152,   113,    -1,   155,   156,   157,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   129,   130,    -1,   132,   133,   134,    78,   136,   137,
     138,    82,   140,   141,   142,   143,   144,    -1,   146,   147,
     148,   149,   150,   151,   152,    10,   154,   155,   156,   157,
      -1,    -1,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   113,    28,    -1,    -1,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,   130,
      -1,   132,   133,   134,    -1,   136,   137,   138,    -1,   140,
     141,   142,   143,   144,    -1,   146,   147,   148,   149,   150,
     151,   152,    10,    -1,   155,   156,   157,    -1,    -1,    17,
      -1,    -1,    -1,    78,    -1,    -1,    -1,    82,    -1,    -1,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    10,    -1,    -1,    -1,    -1,    -1,
      -1,    17,    -1,    -1,    -1,    -1,    -1,    -1,   113,    -1,
      -1,    -1,    28,    29,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   129,   130,    -1,   132,   133,   134,
      78,   136,   137,   138,    82,   140,   141,   142,   143,   144,
      -1,   146,   147,   148,   149,   150,   151,   152,    -1,    -1,
     155,   156,   157,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    78,    -1,   112,   113,    82,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   129,   130,    -1,   132,   133,   134,    -1,   136,   137,
     138,    -1,   140,   141,   142,   143,   144,   113,   146,   147,
     148,   149,   150,   151,   152,    10,    -1,   155,   156,   157,
      -1,    78,    17,   129,   130,    82,   132,   133,   134,    -1,
     136,   137,   138,    28,   140,   141,   142,   143,   144,    -1,
     146,   147,   148,   149,   150,   151,   152,    10,    -1,   155,
     156,   157,    -1,    -1,    17,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    29,    -1,    -1,    -1,
      -1,    -1,   129,   130,    -1,   132,   133,   134,    -1,   136,
     137,   138,    -1,    78,   141,   142,   143,    82,    -1,   146,
     147,   148,   149,    -1,    -1,   152,    91,    -1,   155,   156,
     157,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    78,    -1,    -1,   113,    82,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   129,   130,    -1,   132,   133,   134,
      -1,   136,   137,   138,    -1,   140,   141,   142,   143,   144,
     113,   146,   147,   148,   149,   150,   151,   152,    10,    -1,
     155,   156,   157,    -1,    -1,    17,   129,   130,    -1,   132,
     133,   134,    -1,   136,   137,   138,    28,   140,   141,   142,
     143,   144,    -1,   146,   147,   148,   149,   150,   151,   152,
      10,    11,   155,   156,   157,    -1,    -1,    17,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,
      82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    -1,
      -1,   113,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,   130,    -1,
     132,   133,   134,    -1,   136,   137,   138,    -1,   140,   141,
     142,   143,   144,   113,   146,   147,   148,   149,   150,   151,
     152,    10,    -1,   155,   156,   157,    -1,    -1,    17,   129,
     130,    -1,   132,   133,   134,    -1,   136,   137,   138,    28,
     140,   141,   142,   143,   144,    -1,   146,   147,   148,   149,
     150,   151,   152,    10,    -1,   155,   156,   157,    -1,    -1,
      17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,
      -1,    -1,    -1,    82,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    78,    -1,    -1,   113,    82,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    91,    -1,    -1,    -1,    -1,    -1,
     129,   130,    -1,   132,   133,   134,    -1,   136,   137,   138,
      -1,   140,   141,   142,   143,   144,   113,   146,   147,   148,
     149,   150,   151,   152,    10,    -1,   155,   156,   157,    -1,
      -1,    17,   129,   130,    -1,   132,   133,   134,    -1,   136,
     137,   138,    28,   140,   141,   142,   143,   144,    -1,   146,
     147,   148,   149,   150,   151,   152,    10,    -1,   155,   156,
     157,    -1,    -1,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    78,    -1,    -1,    -1,    82,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    78,    -1,    -1,   113,    82,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,
      -1,    -1,    -1,   129,   130,    -1,   132,   133,   134,    -1,
     136,   137,   138,    -1,   140,   141,   142,   143,   144,   113,
     146,   147,   148,   149,   150,   151,   152,    10,    -1,   155,
     156,   157,    -1,    -1,    17,   129,   130,    -1,   132,   133,
     134,    -1,   136,   137,   138,    28,   140,   141,   142,   143,
     144,    -1,   146,   147,   148,   149,   150,   151,   152,    10,
      -1,   155,   156,   157,    -1,    -1,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,    82,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    -1,    -1,
     113,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      91,    -1,    -1,    -1,    -1,    -1,   129,   130,    -1,   132,
     133,   134,    -1,   136,   137,   138,    -1,   140,   141,   142,
     143,   144,   113,   146,   147,   148,   149,   150,   151,   152,
      10,    -1,   155,   156,   157,    -1,    -1,    17,   129,   130,
      -1,   132,   133,   134,    -1,   136,   137,   138,    28,   140,
     141,   142,   143,   144,    -1,   146,   147,   148,   149,   150,
     151,   152,    10,    -1,   155,   156,   157,    -1,    -1,    17,
      -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    -1,
      -1,    -1,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    10,    -1,    -1,    -1,    -1,    -1,    -1,    17,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      78,    -1,    -1,   113,    82,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,
     130,    -1,   132,   133,   134,    -1,   136,   137,   138,    -1,
     140,   141,   142,   143,   144,   113,   146,   147,   148,   149,
     150,   151,   152,    -1,    -1,   155,   156,   157,    -1,    78,
      -1,   129,   130,    82,   132,   133,   134,    -1,   136,   137,
     138,    -1,   140,   141,   142,   143,   144,    -1,   146,   147,
     148,   149,   150,   151,   152,    -1,    -1,   155,   156,   157,
      -1,    -1,    -1,    -1,   113,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     129,   130,    -1,   132,   133,   134,    -1,   136,   137,   138,
      -1,   140,   141,   142,   143,   144,    -1,   146,   147,   148,
     149,   150,   151,   152,    -1,    -1,   155,   156,   157,     1,
      -1,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    15,    16,    -1,    -1,    -1,    -1,    -1,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,
      -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,    41,
      -1,    43,    -1,    -1,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,    60,    61,
      -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,     3,    -1,
      -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,
      15,    16,    -1,    85,    86,    -1,    -1,    22,    90,    -1,
      92,    -1,    -1,    95,    -1,    30,    -1,    99,    -1,    -1,
     102,    36,    -1,   105,    -1,    -1,    41,    -1,    43,    -1,
      -1,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      -1,    -1,    -1,    -1,    -1,    60,    61,    -1,    -1,    -1,
      -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      85,    86,    -1,    -1,    -1,    90,    -1,    92,    -1,    -1,
      95,    -1,    -1,    -1,    99,    -1,    -1,   102,    -1,    -1,
     105
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   169,   170,     0,     1,     3,     4,     5,     6,     7,
       8,    12,    13,    14,    15,    16,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    29,    30,    32,    34,    35,
      36,    37,    38,    39,    40,    41,    43,    44,    46,    49,
      50,    51,    53,    54,    55,    57,    58,    60,    61,    62,
      66,    67,    68,    69,    70,    71,    72,    75,    76,    77,
      79,    80,    81,    83,    84,    85,    86,    87,    88,    89,
      90,    92,    93,    95,    96,    97,    98,    99,   101,   102,
     104,   105,   108,   110,   113,   129,   130,   131,   132,   133,
     138,   148,   151,   152,   154,   157,   159,   161,   163,   171,
     172,   173,   174,   175,   176,   178,   183,   184,   185,   186,
     190,   193,   197,   198,   199,   200,   201,   202,   204,   205,
     206,   210,   211,   214,   215,   218,   219,   222,   225,   226,
     252,   255,   256,   276,   277,   278,   279,   280,   281,   282,
     290,   291,   292,   293,   296,   297,   298,   299,   300,   301,
     302,   304,   305,   306,   307,   308,   154,   173,   293,   109,
     283,   284,     3,   187,    12,    37,    38,    40,    90,   159,
     163,   222,   276,   281,   291,   292,   293,   296,   298,   299,
     283,   293,    98,   255,    79,   187,   173,   270,   293,   173,
     161,   293,   294,     7,     9,    98,   195,   294,    68,   111,
     203,   293,   203,   293,    23,    35,   256,   293,   293,   161,
       3,    15,    16,    22,    30,    36,    41,    43,    46,    54,
      60,    61,    67,    76,    85,    86,    90,    92,    95,    99,
     102,   105,   189,   191,   223,   161,   189,   257,   258,    29,
     178,   196,   293,   293,   293,   293,   293,   293,     7,   161,
      35,   199,   199,   153,   245,   269,   293,    96,    97,   154,
     293,   295,   293,   196,   293,   293,   293,    89,   161,   173,
     293,   293,   178,   186,   293,   296,   178,   186,   293,   189,
     253,   293,   293,   293,   293,   293,   293,   293,   293,     1,
     160,   171,   179,   269,   100,   139,   245,   271,   272,   295,
     203,   269,   293,   303,    70,   173,   159,    74,   177,   103,
     189,   189,    47,    73,   240,   257,   153,   154,   145,    10,
      17,    28,    78,    82,   113,   129,   130,   132,   133,   134,
     136,   137,   138,   140,   141,   142,   143,   144,   146,   147,
     148,   149,   150,   151,   152,   155,   156,   157,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   158,   232,   161,   163,    78,    82,   161,
     173,   154,   293,   293,   293,   269,   159,   178,    42,   283,
     253,   257,   154,   135,   154,   108,   190,   245,   273,   274,
     275,   295,   253,   215,   255,   189,   161,   196,    29,    42,
     196,   109,   196,   286,    29,    42,   196,   286,   294,    33,
      63,   154,    91,   178,   232,   273,   173,   161,   234,   100,
     161,   189,   259,   260,     1,   134,   264,    42,   135,   173,
     196,   196,   273,   189,   135,   154,   293,   293,   154,   159,
     196,   161,   273,   154,   207,   154,   207,   154,   114,   254,
     154,   196,   154,   160,   160,   171,   135,   160,   293,   135,
     162,   135,   162,   164,   286,    42,   135,   164,   286,   112,
     135,   164,     7,     1,   160,   179,    56,   269,   293,   134,
     216,   159,   227,   154,   293,   293,   293,   293,   203,   293,
     203,   293,   293,   293,   293,   293,   293,   293,    30,    54,
      98,   190,   293,   293,   293,   293,   293,   293,   293,   293,
     293,   293,   293,   293,   293,   293,   293,   293,   295,   295,
     295,   295,   295,   273,   273,   203,   293,   203,   293,    24,
      42,    79,   104,   285,   288,   289,   293,   308,    29,    42,
      29,    42,    91,    42,   164,   203,   293,   196,   154,   154,
     293,   293,   114,   162,   135,   154,   189,   257,    42,   269,
      40,   293,   203,   293,   161,   196,    40,   293,   203,   293,
     196,   157,   180,   182,   293,   180,   181,   173,   293,    31,
     293,   162,    24,    42,    45,    65,    68,    79,    98,   172,
     235,   236,   237,   238,   224,   260,   135,   162,    30,    43,
      86,    90,   163,   194,   265,   277,   114,   261,   293,   258,
     162,   245,   293,     1,   212,   273,   162,    18,   208,   265,
     277,   135,   160,   162,   162,   271,   162,   271,   173,   164,
     203,   293,   164,   173,   293,   164,   293,   164,   293,   160,
     160,   189,   154,    33,    63,   269,   159,     1,   189,   220,
     221,    24,    68,    79,    98,   229,   239,   154,   154,   154,
     154,   154,   162,   164,    42,    79,   135,   162,   276,    78,
      78,    40,   203,   293,    40,   203,   293,   203,   293,   283,
     283,   154,   245,   295,   275,   216,   154,   293,   162,   293,
      29,   196,    29,   196,   287,   288,   293,    29,   196,   286,
      29,   196,   286,   135,   154,    11,   154,    31,    31,   173,
      91,   178,    42,    79,   237,   135,   162,   161,   189,    24,
      68,    79,    98,   241,   162,   260,   264,     1,   269,    59,
     295,   160,    64,   106,   160,   213,   162,   161,   178,   189,
     209,   253,   173,   164,   286,   164,   286,   173,   112,   182,
     181,     1,   217,   160,   114,   135,   160,    79,   228,     1,
       3,    10,    15,    17,    22,    36,    41,    46,    48,    54,
      60,    61,    76,    88,    92,    95,    99,   105,   129,   130,
     131,   132,   133,   136,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   152,   155,   156,   157,   158,
     161,   188,   189,   191,   192,   230,   231,   232,   276,   288,
     264,   276,   276,   293,    29,    29,   293,    29,    29,   164,
     164,   196,   196,   159,   196,    91,    40,   293,    40,   293,
     135,   162,    91,    40,   293,   196,    40,   293,   196,   293,
     293,   173,   293,   173,    31,   189,   236,   260,   134,   268,
      79,   264,   261,   164,    42,   164,    29,   173,   269,   209,
     134,   178,    40,   173,   293,   164,    40,   173,   293,   164,
     293,   154,   154,   160,    35,    72,    75,   160,   172,   198,
     293,   221,   241,   161,   233,   189,   293,   129,   137,   233,
     233,   261,    91,    40,    40,    91,    40,    40,    40,    40,
       1,   217,   293,   293,   293,   288,   293,   293,   293,    11,
      31,   173,   268,   162,   163,   194,   245,   267,   277,   139,
     247,   261,    52,   107,   248,   293,   265,   277,   173,   196,
     162,   293,   293,   173,   293,   173,   198,     1,   134,   263,
     235,   162,     3,    88,    92,   231,   232,   293,   293,   293,
     293,   293,   293,   160,   160,    91,    91,    91,    91,   293,
     173,   261,   268,   164,   269,   245,   246,   293,     3,    81,
      92,   249,   250,   251,   293,   178,   197,   244,   164,   178,
      91,    91,   163,   194,   262,   277,    94,   242,   162,   233,
     233,    91,    91,    91,    91,    91,    91,   293,   293,   293,
     293,   247,   261,   245,   266,   267,   277,    42,   164,   251,
     107,   135,   114,   140,   142,   143,   146,   147,    52,   277,
     293,   293,     1,   164,   269,   248,   293,   266,   267,   293,
     250,   251,   251,   251,   251,   251,   251,   249,   164,   262,
     277,   164,   154,   243,   244,   164,   262,   277,   266
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   168,   169,   170,   170,   171,   171,   172,   172,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   174,
     175,   175,   175,   176,   176,   176,   177,   177,   178,   178,
     178,   179,   179,   180,   180,   180,   180,   181,   181,   182,
     182,   183,   183,   183,   184,   184,   184,   185,   186,   186,
     186,   186,   186,   187,   187,   188,   188,   188,   188,   188,
     188,   188,   189,   189,   189,   189,   189,   189,   190,   190,
     191,   191,   191,   191,   191,   191,   191,   191,   191,   191,
     191,   191,   191,   191,   191,   191,   191,   192,   193,   193,
     193,   193,   193,   193,   193,   193,   193,   193,   194,   194,
     194,   194,   195,   195,   196,   196,   197,   197,   198,   198,
     198,   198,   198,   198,   198,   198,   199,   199,   200,   200,
     200,   200,   201,   202,   202,   202,   202,   202,   202,   202,
     202,   202,   202,   202,   202,   202,   202,   202,   202,   202,
     202,   202,   202,   202,   202,   202,   202,   202,   202,   203,
     204,   204,   204,   204,   204,   204,   204,   204,   205,   206,
     206,   206,   206,   206,   206,   207,   207,   208,   208,   208,
     209,   209,   210,   211,   211,   212,   212,   213,   213,   213,
     214,   214,   214,   214,   215,   215,   215,   216,   216,   217,
     217,   217,   218,   218,   219,   220,   220,   220,   221,   221,
     223,   224,   222,   225,   225,   225,   225,   225,   227,   228,
     226,   229,   229,   229,   229,   229,   230,   230,   231,   231,
     231,   231,   231,   231,   231,   231,   231,   231,   231,   231,
     231,   231,   231,   231,   231,   231,   231,   231,   231,   231,
     231,   231,   231,   231,   231,   231,   232,   232,   232,   232,
     232,   232,   232,   232,   232,   232,   232,   232,   233,   233,
     234,   235,   235,   235,   236,   236,   236,   236,   236,   237,
     237,   238,   238,   238,   238,   238,   238,   238,   238,   238,
     239,   239,   239,   239,   239,   239,   240,   240,   241,   241,
     241,   241,   241,   241,   242,   242,   243,   243,   244,   244,
     245,   245,   246,   246,   247,   247,   248,   248,   248,   248,
     248,   249,   249,   250,   250,   250,   250,   250,   250,   250,
     251,   251,   252,   252,   252,   253,   253,   254,   254,   254,
     255,   255,   255,   255,   255,   256,   256,   256,   257,   257,
     258,   258,   259,   259,   259,   260,   260,   260,   261,   261,
     261,   262,   262,   262,   262,   262,   262,   262,   263,   263,
     263,   263,   263,   264,   264,   264,   264,   264,   265,   265,
     265,   265,   266,   266,   266,   267,   267,   267,   267,   267,
     268,   268,   268,   268,   268,   269,   269,   269,   269,   270,
     270,   271,   271,   271,   272,   272,   273,   273,   274,   274,
     275,   275,   275,   275,   276,   276,   277,   277,   278,   278,
     278,   278,   278,   278,   278,   278,   278,   278,   278,   278,
     278,   278,   278,   278,   278,   278,   278,   278,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   280,   281,   282,   282,   282,
     282,   282,   282,   282,   282,   283,   283,   284,   285,   285,
     286,   287,   287,   288,   288,   288,   289,   289,   289,   289,
     289,   289,   290,   290,   291,   292,   293,   293,   293,   293,
     293,   293,   293,   293,   293,   293,   293,   293,   293,   293,
     294,   294,   295,   295,   295,   296,   296,   296,   296,   297,
     297,   297,   298,   298,   298,   299,   299,   299,   299,   300,
     300,   300,   300,   301,   301,   302,   302,   302,   302,   302,
     302,   302,   302,   302,   302,   302,   302,   302,   303,   303,
     304,   304,   304,   304,   304,   304,   304,   304,   304,   304,
     304,   304,   304,   304,   304,   304,   304,   304,   304,   304,
     304,   304,   304,   305,   305,   305,   305,   305,   305,   305,
     306,   306,   306,   306,   307,   307,   307,   307,   308,   308,
     308,   308,   308,   308,   308
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     2,     2,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     3,     3,     3,     3,     3,
       3,     3,     2,     3,     3,     2,     2,     3,     2,     4,
       3,     4,     4,     0,     1,     1,     0,     1,     2,     3,
       3,     1,     2,     1,     3,     3,     5,     0,     1,     1,
       1,     0,     1,     1,     4,     6,     6,     3,     4,     4,
       4,     4,     4,     0,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     1,     2,     1,     2,     3,     1,     1,
       2,     2,     1,     1,     1,     1,     1,     1,     3,     5,
       5,     2,     2,     5,     3,     6,     6,     4,     5,     5,
       3,     3,     6,     5,     6,     5,     6,     3,     4,     3,
       4,     6,     7,     6,     7,     4,     5,     4,     5,     4,
       4,     3,     6,     5,     6,     5,     8,     7,     2,     3,
       3,     2,     2,     3,     3,     0,     2,     2,     3,     5,
       1,     3,     3,     5,     5,     0,     2,     3,     2,     3,
       6,     8,     6,     8,     1,     1,     1,     0,     2,     0,
       2,     3,     5,     5,     1,     1,     2,     3,     1,     3,
       0,     0,     8,     0,     1,     2,     2,     1,     0,     0,
      10,     3,     3,     5,     5,     3,     1,     3,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     3,
       3,     0,     1,     3,     4,     5,     4,     6,     6,     0,
       1,     1,     1,     1,     1,     2,     2,     1,     1,     1,
       0,     1,     1,     2,     1,     1,     1,     1,     0,     1,
       2,     1,     1,     1,     0,     1,     1,     1,     1,     1,
       2,     1,     0,     1,     2,     2,     0,     2,     2,     4,
       4,     1,     3,     3,     3,     3,     3,     3,     3,     2,
       1,     1,     3,     4,     4,     2,     4,     0,     2,     2,
       1,     1,     1,     2,     1,     4,     5,     3,     1,     3,
       3,     5,     1,     1,     3,     1,     2,     3,     0,     2,
       2,     3,     2,     4,     3,     3,     4,     3,     0,     2,
       2,     2,     1,     0,     2,     2,     2,     1,     4,     4,
       6,     3,     0,     1,     1,     3,     4,     3,     4,     6,
       0,     2,     2,     2,     2,     1,     1,     3,     3,     1,
       3,     1,     1,     1,     3,     3,     0,     1,     1,     3,
       3,     3,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     2,     4,     4,     4,     5,     2,     2,
       1,     2,     1,     2,     1,     2,     1,     2,     6,     6,
       4,     9,     9,     7,     6,     6,     4,     9,     9,     7,
       4,     6,     6,     9,     9,     6,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     1,     4,     1,     3,
       4,     1,     3,     4,     3,     3,     1,     1,     2,     1,
       2,     1,     1,     3,     2,     4,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     3,     3,     2,     2,     1,
       0,     1,     2,     2,     1,     1,     1,     1,     1,     1,
       2,     1,     4,     4,     4,     3,     3,     3,     3,     3,
       4,     3,     4,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     4,     3,     4,     3,     4,     3,     5,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     2,     2,     2,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     1,
       1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      yyerror (&yylloc, context, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
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

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, context); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, ParserContext* context)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  YYUSE (context);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, ParserContext* context)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, context);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, ParserContext* context)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , context);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, context); \
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, ParserContext* context)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (context);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}



struct yypstate
  {
    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;
    /* Used to determine if this is the first time this instance has
       been used.  */
    int yynew;
  };

/* Initialize the parser data structure.  */
yypstate *
yypstate_new (void)
{
  yypstate *yyps;
  yyps = (yypstate *) malloc (sizeof *yyps);
  if (!yyps)
    return YY_NULLPTR;
  yyps->yynew = 1;
  return yyps;
}

void
yypstate_delete (yypstate *yyps)
{
#ifndef yyoverflow
  /* If the stack was reallocated but the parse did not complete, then the
     stack still needs to be freed.  */
  if (!yyps->yynew && yyps->yyss != yyps->yyssa)
    YYSTACK_FREE (yyps->yyss);
#endif
  free (yyps);
}

#define yynerrs yyps->yynerrs
#define yystate yyps->yystate
#define yyerrstatus yyps->yyerrstatus
#define yyssa yyps->yyssa
#define yyss yyps->yyss
#define yyssp yyps->yyssp
#define yyvsa yyps->yyvsa
#define yyvs yyps->yyvs
#define yyvsp yyps->yyvsp
#define yylsa yyps->yylsa
#define yyls yyps->yyls
#define yylsp yyps->yylsp
#define yyerror_range yyps->yyerror_range
#define yystacksize yyps->yystacksize


/*---------------.
| yypush_parse.  |
`---------------*/

int
yypush_parse (yypstate *yyps, int yypushed_char, YYSTYPE const *yypushed_val, YYLTYPE *yypushed_loc, ParserContext* context)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  if (!yyps->yynew)
    {
      yyn = yypact[yystate];
      goto yyread_pushed_token;
    }

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = *yypushed_loc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
      if (!yyps->yynew)
        {
          YYDPRINTF ((stderr, "Return for a new token:\n"));
          yyresult = YYPUSH_MORE;
          goto yypushreturn;
        }
      yyps->yynew = 0;
yyread_pushed_token:
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yypushed_char;
      if (yypushed_val)
        yylval = *yypushed_val;
      if (yypushed_loc)
        yylloc = *yypushed_loc;
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 489 "chapel.ypp" /* yacc.c:1663  */
    { yyblock = (yyval.pblockstmt); }
#line 5609 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 3:
#line 494 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = new BlockStmt(); resetTempID(); }
#line 5615 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 4:
#line 495 "chapel.ypp" /* yacc.c:1663  */
    { (yyvsp[-1].pblockstmt)->appendChapelStmt((yyvsp[0].pblockstmt)); context->generatedStmt = (yyvsp[-1].pblockstmt); resetTempID(); }
#line 5621 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 6:
#line 502 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildPragmaStmt( (yyvsp[-1].vpch), (yyvsp[0].pblockstmt) ); }
#line 5627 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 7:
#line 507 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.vpch) = new Vec<const char*>(); (yyval.vpch)->add(astr((yyvsp[0].pch))); }
#line 5633 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 8:
#line 508 "chapel.ypp" /* yacc.c:1663  */
    { (yyvsp[-2].vpch)->add(astr((yyvsp[0].pch))); }
#line 5639 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 23:
#line 527 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildChapelStmt((yyvsp[-1].pexpr)); }
#line 5645 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 24:
#line 528 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildAtomicStmt((yyvsp[0].pblockstmt)); }
#line 5651 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 25:
#line 529 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildBeginStmt((yyvsp[-1].pcallexpr), (yyvsp[0].pblockstmt)); }
#line 5657 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 26:
#line 530 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildGotoStmt(GOTO_BREAK, (yyvsp[-1].pch)); }
#line 5663 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 27:
#line 531 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildCobeginStmt((yyvsp[-1].pcallexpr), (yyvsp[0].pblockstmt));  }
#line 5669 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 28:
#line 532 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildGotoStmt(GOTO_CONTINUE, (yyvsp[-1].pch)); }
#line 5675 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 29:
#line 533 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildDeleteStmt((yyvsp[-1].pcallexpr)); }
#line 5681 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 30:
#line 534 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildLabelStmt((yyvsp[-1].pch), (yyvsp[0].pblockstmt)); }
#line 5687 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 31:
#line 535 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildLocalStmt((yyvsp[-1].pexpr), (yyvsp[0].pblockstmt)); }
#line 5693 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 32:
#line 536 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildLocalStmt((yyvsp[0].pblockstmt)); }
#line 5699 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 33:
#line 537 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildOnStmt((yyvsp[-1].pexpr), (yyvsp[0].pblockstmt)); }
#line 5705 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 34:
#line 538 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildSerialStmt((yyvsp[-1].pexpr), (yyvsp[0].pblockstmt)); }
#line 5711 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 35:
#line 539 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildSerialStmt(new SymExpr(gTrue), (yyvsp[0].pblockstmt)); }
#line 5717 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 36:
#line 540 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildSyncStmt((yyvsp[0].pblockstmt)); }
#line 5723 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 37:
#line 541 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildPrimitiveStmt(PRIM_YIELD, (yyvsp[-1].pexpr)); }
#line 5729 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 38:
#line 542 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildErrorStandin(); }
#line 5735 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 39:
#line 547 "chapel.ypp" /* yacc.c:1663  */
    {
      (yyval.pmodsymbol) = buildModule((yyvsp[0].pch), currentModuleType, NULL, yyfilename, (yyvsp[-3].b), (yyvsp[-2].b), (yylsp[-3]).comment);
      // store previous module name in order to restore it once we're
      // done with this module in module_decl_stmt below.  Ultimately,
      // we will need to store a stack of module names in order to
      // support full module path resolution of -s config flags.
      (yyloc).prevModule = currentModuleName;
      currentModuleName = (yyvsp[0].pch);
    }
#line 5749 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 40:
#line 560 "chapel.ypp" /* yacc.c:1663  */
    { (yyvsp[-2].pmodsymbol)->block = new BlockStmt();
      (yyval.pblockstmt) = buildChapelStmt(new DefExpr((yyvsp[-2].pmodsymbol)));
      currentModuleName = (yylsp[-2]).prevModule;  // restore previous module name
    }
#line 5758 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 41:
#line 565 "chapel.ypp" /* yacc.c:1663  */
    { (yyvsp[-3].pmodsymbol)->block = (yyvsp[-1].pblockstmt);
      (yyval.pblockstmt) = buildChapelStmt(new DefExpr((yyvsp[-3].pmodsymbol)));
      currentModuleName = (yylsp[-3]).prevModule;  // restore previous module name
    }
#line 5767 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 42:
#line 570 "chapel.ypp" /* yacc.c:1663  */
    { (yyvsp[-3].pmodsymbol)->block = buildErrorStandin();
      (yyval.pblockstmt) = buildChapelStmt(new DefExpr((yyvsp[-3].pmodsymbol)));
      currentModuleName = (yylsp[-3]).prevModule;  // restore previous module name
    }
#line 5776 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 43:
#line 577 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.b) = false; (yyloc).comment = context->latestComment; context->latestComment = NULL; }
#line 5782 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 44:
#line 578 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.b) = false; (yyloc).comment = context->latestComment; context->latestComment = NULL; }
#line 5788 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 45:
#line 579 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.b) = true; (yyloc).comment = context->latestComment; context->latestComment = NULL; }
#line 5794 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 46:
#line 583 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.b) = false; }
#line 5800 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 47:
#line 584 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.b) = true;  }
#line 5806 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 48:
#line 597 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = new BlockStmt(); }
#line 5812 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 49:
#line 598 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = (yyvsp[-1].pblockstmt);              }
#line 5818 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 50:
#line 599 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildErrorStandin(); }
#line 5824 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 51:
#line 604 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = new BlockStmt(); (yyval.pblockstmt)->appendChapelStmt((yyvsp[0].pblockstmt)); }
#line 5830 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 52:
#line 605 "chapel.ypp" /* yacc.c:1663  */
    { (yyvsp[-1].pblockstmt)->appendChapelStmt((yyvsp[0].pblockstmt)); }
#line 5836 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 53:
#line 610 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.ponlylist) = new std::vector<OnlyRename*>();
                                         OnlyRename* cur = new OnlyRename();
                                         cur->tag = OnlyRename::SINGLE;
                                         cur->elem = (yyvsp[0].pexpr);
                                         (yyval.ponlylist)->push_back(cur); }
#line 5846 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 54:
#line 615 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.ponlylist) = new std::vector<OnlyRename*>();
                                         OnlyRename* cur = new OnlyRename();
                                         cur->tag = OnlyRename::DOUBLE;
                                         cur->renamed = new std::pair<Expr*, Expr*>((yyvsp[-2].pexpr), (yyvsp[0].pexpr));
                                         (yyval.ponlylist)->push_back(cur); }
#line 5856 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 55:
#line 620 "chapel.ypp" /* yacc.c:1663  */
    { OnlyRename* cur = new OnlyRename();
                                         cur->tag = OnlyRename::SINGLE;
                                         cur->elem = (yyvsp[0].pexpr);
                                         (yyvsp[-2].ponlylist)->push_back(cur); }
#line 5865 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 56:
#line 624 "chapel.ypp" /* yacc.c:1663  */
    { OnlyRename* cur = new OnlyRename();
                                         cur->tag = OnlyRename::DOUBLE;
                                         cur->renamed = new std::pair<Expr*, Expr*>((yyvsp[-2].pexpr), (yyvsp[0].pexpr));
                                         (yyvsp[-4].ponlylist)->push_back(cur); }
#line 5874 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 57:
#line 631 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.ponlylist) = new std::vector<OnlyRename*>();
                                         OnlyRename* cur = new OnlyRename();
                                         cur->tag = OnlyRename::SINGLE;
                                         cur->elem = new UnresolvedSymExpr("");
                                         (yyval.ponlylist)->push_back(cur); }
#line 5884 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 59:
#line 640 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.ponlylist) = new std::vector<OnlyRename*>();
                                         OnlyRename* cur = new OnlyRename();
                                         cur->tag = OnlyRename::SINGLE;
                                         cur->elem = new UnresolvedSymExpr("");
                                         (yyval.ponlylist)->push_back(cur); }
#line 5894 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 61:
#line 649 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.b) = false; }
#line 5900 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 62:
#line 650 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.b) = false; }
#line 5906 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 63:
#line 651 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.b) = true; }
#line 5912 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 64:
#line 655 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildUseStmt((yyvsp[-1].pcallexpr), (yyvsp[-3].b)); }
#line 5918 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 65:
#line 656 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildUseStmt((yyvsp[-3].pexpr), (yyvsp[-1].ponlylist), true, (yyvsp[-5].b)); }
#line 5924 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 66:
#line 657 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildUseStmt((yyvsp[-3].pexpr), (yyvsp[-1].ponlylist), false, (yyvsp[-5].b)); }
#line 5930 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 67:
#line 661 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildRequireStmt((yyvsp[-1].pcallexpr)); }
#line 5936 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 68:
#line 666 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildAssignment((yyvsp[-3].pexpr), (yyvsp[-1].pexpr), (yyvsp[-2].pch));   }
#line 5942 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 69:
#line 668 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildAssignment((yyvsp[-3].pexpr), (yyvsp[-1].pexpr), "<=>"); }
#line 5948 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 70:
#line 670 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildAssignment((yyvsp[-3].pexpr), (yyvsp[-1].pexpr), PRIM_REDUCE_ASSIGN); }
#line 5954 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 71:
#line 672 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildLAndAssignment((yyvsp[-3].pexpr), (yyvsp[-1].pexpr));    }
#line 5960 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 72:
#line 674 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildLOrAssignment((yyvsp[-3].pexpr), (yyvsp[-1].pexpr));     }
#line 5966 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 73:
#line 680 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = NULL; }
#line 5972 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 74:
#line 681 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = (yyvsp[0].pch); }
#line 5978 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 75:
#line 685 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = (yyvsp[0].pch); }
#line 5984 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 76:
#line 686 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "none"; redefiningReservedWordError((yyval.pch)); }
#line 5990 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 77:
#line 687 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "this"; }
#line 5996 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 78:
#line 688 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "false"; redefiningReservedWordError((yyval.pch)); }
#line 6002 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 79:
#line 689 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "true"; redefiningReservedWordError((yyval.pch)); }
#line 6008 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 80:
#line 690 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = (yyvsp[0].pch); }
#line 6014 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 81:
#line 691 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = (yyvsp[0].pch); redefiningReservedTypeError((yyvsp[0].pch)); }
#line 6020 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 82:
#line 694 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = (yyvsp[0].pch); }
#line 6026 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 83:
#line 695 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "none"; redefiningReservedWordError((yyval.pch)); }
#line 6032 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 84:
#line 696 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "this"; redefiningReservedWordError((yyval.pch)); }
#line 6038 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 85:
#line 697 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "false"; redefiningReservedWordError((yyval.pch)); }
#line 6044 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 86:
#line 698 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "true"; redefiningReservedWordError((yyval.pch)); }
#line 6050 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 87:
#line 699 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = (yyvsp[0].pch); redefiningReservedTypeError((yyvsp[0].pch)); }
#line 6056 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 88:
#line 711 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = (yyvsp[0].pch); }
#line 6062 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 89:
#line 712 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "this"; }
#line 6068 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 90:
#line 723 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "bool"; }
#line 6074 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 91:
#line 724 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "int"; }
#line 6080 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 92:
#line 725 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "uint"; }
#line 6086 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 93:
#line 726 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "real"; }
#line 6092 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 94:
#line 727 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "imag"; }
#line 6098 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 95:
#line 728 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "complex"; }
#line 6104 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 96:
#line 729 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "sync"; }
#line 6110 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 97:
#line 730 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "single"; }
#line 6116 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 98:
#line 731 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "owned"; }
#line 6122 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 99:
#line 732 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "shared"; }
#line 6128 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 100:
#line 733 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "borrowed"; }
#line 6134 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 101:
#line 734 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "unmanaged"; }
#line 6140 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 102:
#line 735 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "domain"; }
#line 6146 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 103:
#line 736 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "index"; }
#line 6152 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 104:
#line 737 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "locale"; }
#line 6158 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 105:
#line 738 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "nothing"; }
#line 6164 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 106:
#line 739 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "void"; }
#line 6170 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 107:
#line 743 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "string"; }
#line 6176 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 108:
#line 747 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new SymExpr(dtBools[BOOL_SIZE_DEFAULT]->symbol); }
#line 6182 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 109:
#line 748 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new SymExpr(dtInt[INT_SIZE_DEFAULT]->symbol); }
#line 6188 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 110:
#line 749 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new SymExpr(dtUInt[INT_SIZE_DEFAULT]->symbol); }
#line 6194 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 111:
#line 750 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new SymExpr(dtReal[FLOAT_SIZE_DEFAULT]->symbol); }
#line 6200 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 112:
#line 751 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new SymExpr(dtImag[FLOAT_SIZE_DEFAULT]->symbol); }
#line 6206 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 113:
#line 752 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new SymExpr(dtComplex[COMPLEX_SIZE_DEFAULT]->symbol); }
#line 6212 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 114:
#line 753 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new SymExpr(dtString->symbol); }
#line 6218 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 115:
#line 754 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new SymExpr(dtLocale->symbol); }
#line 6224 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 116:
#line 755 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new SymExpr(dtNothing->symbol); }
#line 6230 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 117:
#line 756 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new SymExpr(dtVoid->symbol); }
#line 6236 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 118:
#line 767 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "_syncvar"; }
#line 6242 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 119:
#line 768 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "_singlevar"; }
#line 6248 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 120:
#line 773 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "_domain"; }
#line 6254 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 121:
#line 774 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "_index"; }
#line 6260 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 122:
#line 779 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = NULL; }
#line 6266 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 123:
#line 780 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = (yyvsp[0].pch); }
#line 6272 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 124:
#line 784 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = (yyvsp[0].pblockstmt); }
#line 6278 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 125:
#line 785 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = (yyvsp[0].pblockstmt); }
#line 6284 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 126:
#line 789 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildPrimitiveStmt(PRIM_RETURN); }
#line 6290 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 127:
#line 790 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildPrimitiveStmt(PRIM_RETURN, (yyvsp[-1].pexpr)); }
#line 6296 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 128:
#line 794 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildChapelStmt(new BlockStmt()); }
#line 6302 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 130:
#line 796 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = (yyvsp[0].pblockstmt); }
#line 6308 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 131:
#line 797 "chapel.ypp" /* yacc.c:1663  */
    { applyPrivateToBlock((yyvsp[0].pblockstmt)); (yyval.pblockstmt) = (yyvsp[0].pblockstmt); }
#line 6314 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 138:
#line 810 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildForwardingStmt((yyvsp[-1].pexpr)); }
#line 6320 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 139:
#line 811 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildForwardingStmt((yyvsp[-3].pexpr), (yyvsp[-1].ponlylist), true); }
#line 6326 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 140:
#line 812 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildForwardingStmt((yyvsp[-3].pexpr), (yyvsp[-1].ponlylist), false); }
#line 6332 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 141:
#line 813 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildForwardingDeclStmt((yyvsp[0].pblockstmt)); }
#line 6338 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 142:
#line 818 "chapel.ypp" /* yacc.c:1663  */
    {
      (yyval.pblockstmt) = buildExternBlockStmt(astr((yyvsp[0].pch)));
    }
#line 6346 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 143:
#line 824 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = DoWhileStmt::build((yyvsp[-1].pexpr), (yyvsp[-3].pblockstmt)); }
#line 6352 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 144:
#line 825 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = WhileDoStmt::build((yyvsp[-1].pexpr), (yyvsp[0].pblockstmt)); }
#line 6358 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 145:
#line 826 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildCoforallLoopStmt((yyvsp[-4].pexpr), (yyvsp[-2].pexpr), (yyvsp[-1].pcallexpr), (yyvsp[0].pblockstmt));       }
#line 6364 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 146:
#line 827 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildCoforallLoopStmt((yyvsp[-4].pexpr), (yyvsp[-2].pcallexpr), (yyvsp[-1].pcallexpr), (yyvsp[0].pblockstmt), true); }
#line 6370 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 147:
#line 828 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildCoforallLoopStmt(NULL, (yyvsp[-2].pexpr), (yyvsp[-1].pcallexpr), (yyvsp[0].pblockstmt));     }
#line 6376 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 148:
#line 829 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = ForLoop::buildForLoop(  (yyvsp[-3].pexpr), (yyvsp[-1].pexpr), (yyvsp[0].pblockstmt), false, false); }
#line 6382 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 149:
#line 830 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = ForLoop::buildForLoop(  (yyvsp[-3].pexpr), (yyvsp[-1].pcallexpr), (yyvsp[0].pblockstmt), false,  true); }
#line 6388 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 150:
#line 831 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = ForLoop::buildForLoop(NULL, (yyvsp[-1].pexpr), (yyvsp[0].pblockstmt), false, false); }
#line 6394 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 151:
#line 832 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = ForLoop::buildForLoop(NULL, (yyvsp[-1].pcallexpr), (yyvsp[0].pblockstmt), false,  true); }
#line 6400 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 152:
#line 833 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildParamForLoopStmt((yyvsp[-3].pch), (yyvsp[-1].pexpr), (yyvsp[0].pblockstmt)); }
#line 6406 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 153:
#line 834 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = ForallStmt::build((yyvsp[-3].pexpr),   (yyvsp[-1].pexpr), NULL, (yyvsp[0].pblockstmt), false, false); }
#line 6412 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 154:
#line 835 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = ForallStmt::build((yyvsp[-4].pexpr),   (yyvsp[-2].pexpr), (yyvsp[-1].pcallexpr),   (yyvsp[0].pblockstmt), false, false); }
#line 6418 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 155:
#line 836 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = ForallStmt::build((yyvsp[-3].pexpr),   (yyvsp[-1].pcallexpr), NULL, (yyvsp[0].pblockstmt), true,  false); }
#line 6424 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 156:
#line 837 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = ForallStmt::build((yyvsp[-4].pexpr),   (yyvsp[-2].pcallexpr), (yyvsp[-1].pcallexpr),   (yyvsp[0].pblockstmt), true,  false); }
#line 6430 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 157:
#line 838 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = ForallStmt::build(NULL, (yyvsp[-1].pexpr), NULL, (yyvsp[0].pblockstmt), false, false); }
#line 6436 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 158:
#line 839 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = ForallStmt::build(NULL, (yyvsp[-2].pexpr), (yyvsp[-1].pcallexpr),   (yyvsp[0].pblockstmt), false, false); }
#line 6442 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 159:
#line 840 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = ForallStmt::build(NULL, (yyvsp[-1].pcallexpr), NULL, (yyvsp[0].pblockstmt), true,  false); }
#line 6448 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 160:
#line 841 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = ForallStmt::build(NULL, (yyvsp[-2].pcallexpr), (yyvsp[-1].pcallexpr),   (yyvsp[0].pblockstmt), true,  false); }
#line 6454 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 161:
#line 843 "chapel.ypp" /* yacc.c:1663  */
    {
      if ((yyvsp[-4].pcallexpr)->argList.length != 1)
        USR_FATAL((yyvsp[-2].pexpr), "invalid index expression");
      (yyval.pblockstmt) = ForallStmt::build((yyvsp[-4].pcallexpr)->get(1)->remove(), (yyvsp[-2].pexpr), NULL, new BlockStmt((yyvsp[0].pblockstmt)), false, true);
    }
#line 6464 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 162:
#line 849 "chapel.ypp" /* yacc.c:1663  */
    {
      if ((yyvsp[-5].pcallexpr)->argList.length != 1)
        USR_FATAL((yyvsp[-3].pexpr), "invalid index expression");
      (yyval.pblockstmt) = ForallStmt::build((yyvsp[-5].pcallexpr)->get(1)->remove(), (yyvsp[-3].pexpr), (yyvsp[-2].pcallexpr),   new BlockStmt((yyvsp[0].pblockstmt)), false, true);
    }
#line 6474 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 163:
#line 855 "chapel.ypp" /* yacc.c:1663  */
    {
      if ((yyvsp[-4].pcallexpr)->argList.length != 1)
        USR_FATAL((yyvsp[-2].pcallexpr), "invalid index expression");
      (yyval.pblockstmt) = ForallStmt::build((yyvsp[-4].pcallexpr)->get(1)->remove(), (yyvsp[-2].pcallexpr), NULL, new BlockStmt((yyvsp[0].pblockstmt)), true,  true);
    }
#line 6484 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 164:
#line 861 "chapel.ypp" /* yacc.c:1663  */
    {
      if ((yyvsp[-5].pcallexpr)->argList.length != 1)
        USR_FATAL((yyvsp[-3].pcallexpr), "invalid index expression");
      (yyval.pblockstmt) = ForallStmt::build((yyvsp[-5].pcallexpr)->get(1)->remove(), (yyvsp[-3].pcallexpr), (yyvsp[-2].pcallexpr),   new BlockStmt((yyvsp[0].pblockstmt)), true,  true);
    }
#line 6494 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 165:
#line 867 "chapel.ypp" /* yacc.c:1663  */
    {
      if ((yyvsp[-2].pcallexpr)->argList.length > 1)
        (yyval.pblockstmt) = ForallStmt::build(NULL, new CallExpr("chpl__ensureDomainExpr", (yyvsp[-2].pcallexpr)), NULL, new BlockStmt((yyvsp[0].pblockstmt)), false, true);
      else
        (yyval.pblockstmt) = ForallStmt::build(NULL, (yyvsp[-2].pcallexpr)->get(1)->remove(),                       NULL, new BlockStmt((yyvsp[0].pblockstmt)), false, true);
    }
#line 6505 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 166:
#line 874 "chapel.ypp" /* yacc.c:1663  */
    {
      if ((yyvsp[-3].pcallexpr)->argList.length > 1)
        (yyval.pblockstmt) = ForallStmt::build(NULL, new CallExpr("chpl__ensureDomainExpr", (yyvsp[-3].pcallexpr)), (yyvsp[-2].pcallexpr), new BlockStmt((yyvsp[0].pblockstmt)), false, true);
      else
        (yyval.pblockstmt) = ForallStmt::build(NULL, (yyvsp[-3].pcallexpr)->get(1)->remove(),                       (yyvsp[-2].pcallexpr), new BlockStmt((yyvsp[0].pblockstmt)), false, true);
    }
#line 6516 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 167:
#line 881 "chapel.ypp" /* yacc.c:1663  */
    {
      (yyval.pblockstmt) = ForallStmt::build(NULL, (yyvsp[-2].pcallexpr), NULL, new BlockStmt((yyvsp[0].pblockstmt)), true,  true);
    }
#line 6524 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 168:
#line 885 "chapel.ypp" /* yacc.c:1663  */
    {
      (yyval.pblockstmt) = ForallStmt::build(NULL, (yyvsp[-3].pcallexpr), (yyvsp[-2].pcallexpr),   new BlockStmt((yyvsp[0].pblockstmt)), true,  true);
    }
#line 6532 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 169:
#line 891 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pcallexpr) = new CallExpr(PRIM_ZIP, (yyvsp[-1].pcallexpr)); }
#line 6538 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 170:
#line 895 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildIfStmt((yyvsp[-2].pexpr), (yyvsp[0].pblockstmt)); }
#line 6544 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 171:
#line 896 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildIfStmt((yyvsp[-1].pexpr), (yyvsp[0].pblockstmt)); }
#line 6550 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 172:
#line 897 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildIfStmt((yyvsp[-4].pexpr), (yyvsp[-2].pblockstmt), (yyvsp[0].pblockstmt)); }
#line 6556 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 173:
#line 898 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildIfStmt((yyvsp[-3].pexpr), (yyvsp[-2].pblockstmt), (yyvsp[0].pblockstmt)); }
#line 6562 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 174:
#line 899 "chapel.ypp" /* yacc.c:1663  */
    {
(yyval.pblockstmt) = buildIfStmt(convertAssignmentAndWarn((yyvsp[-4].pexpr),(yyvsp[-3].pch),(yyvsp[-2].pexpr)), (yyvsp[0].pblockstmt)); }
#line 6569 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 175:
#line 901 "chapel.ypp" /* yacc.c:1663  */
    {
(yyval.pblockstmt) = buildIfStmt(convertAssignmentAndWarn((yyvsp[-3].pexpr),(yyvsp[-2].pch),(yyvsp[-1].pexpr)), (yyvsp[0].pblockstmt)); }
#line 6576 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 176:
#line 903 "chapel.ypp" /* yacc.c:1663  */
    {
(yyval.pblockstmt) = buildIfStmt(convertAssignmentAndWarn((yyvsp[-6].pexpr),(yyvsp[-5].pch),(yyvsp[-4].pexpr)), (yyvsp[-2].pblockstmt), (yyvsp[0].pblockstmt)); }
#line 6583 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 177:
#line 905 "chapel.ypp" /* yacc.c:1663  */
    {
(yyval.pblockstmt) = buildIfStmt(convertAssignmentAndWarn((yyvsp[-5].pexpr),(yyvsp[-4].pch),(yyvsp[-3].pexpr)), (yyvsp[-2].pblockstmt), (yyvsp[0].pblockstmt)); }
#line 6590 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 178:
#line 910 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = DeferStmt::build((yyvsp[0].pblockstmt)); }
#line 6596 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 179:
#line 913 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = TryStmt::build(false, (yyvsp[-1].pexpr)); }
#line 6602 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 180:
#line 914 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = TryStmt::build(true,  (yyvsp[-1].pexpr)); }
#line 6608 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 181:
#line 915 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = TryStmt::build(false, (yyvsp[0].pblockstmt)); }
#line 6614 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 182:
#line 916 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = TryStmt::build(true,  (yyvsp[0].pblockstmt)); }
#line 6620 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 183:
#line 917 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = TryStmt::build(false, (yyvsp[-1].pblockstmt), (yyvsp[0].pblockstmt)); }
#line 6626 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 184:
#line 918 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = TryStmt::build(true,  (yyvsp[-1].pblockstmt), (yyvsp[0].pblockstmt)); }
#line 6632 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 185:
#line 922 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildChapelStmt(); }
#line 6638 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 186:
#line 923 "chapel.ypp" /* yacc.c:1663  */
    { (yyvsp[-1].pblockstmt)->insertAtTail((yyvsp[0].pexpr)); }
#line 6644 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 187:
#line 927 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = CatchStmt::build((yyvsp[0].pblockstmt)); }
#line 6650 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 188:
#line 928 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = CatchStmt::build((yyvsp[-1].pdefexpr), (yyvsp[0].pblockstmt)); }
#line 6656 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 189:
#line 929 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = CatchStmt::build((yyvsp[-2].pdefexpr), (yyvsp[0].pblockstmt)); }
#line 6662 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 190:
#line 933 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pdefexpr) = new DefExpr(new VarSymbol((yyvsp[0].pch)), NULL, new UnresolvedSymExpr("Error")); }
#line 6668 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 191:
#line 934 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pdefexpr) = new DefExpr(new VarSymbol((yyvsp[-2].pch)), NULL, (yyvsp[0].pexpr));   }
#line 6674 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 192:
#line 938 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildPrimitiveStmt(PRIM_THROW, (yyvsp[-1].pexpr)); }
#line 6680 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 193:
#line 942 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildChapelStmt(buildSelectStmt((yyvsp[-3].pexpr), (yyvsp[-1].pblockstmt))); }
#line 6686 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 194:
#line 944 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildErrorStandin(); }
#line 6692 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 195:
#line 948 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildChapelStmt(); }
#line 6698 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 196:
#line 949 "chapel.ypp" /* yacc.c:1663  */
    { (yyvsp[-1].pblockstmt)->insertAtTail((yyvsp[0].pexpr)); }
#line 6704 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 197:
#line 954 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CondStmt(new CallExpr(PRIM_WHEN, (yyvsp[-1].pcallexpr)), (yyvsp[0].pblockstmt)); }
#line 6710 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 198:
#line 956 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CondStmt(new CallExpr(PRIM_WHEN), (yyvsp[0].pblockstmt)); }
#line 6716 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 199:
#line 958 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CondStmt(new CallExpr(PRIM_WHEN), (yyvsp[0].pblockstmt)); }
#line 6722 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 200:
#line 965 "chapel.ypp" /* yacc.c:1663  */
    {
      (yyval.pblockstmt) = buildChapelStmt(buildClassDefExpr((yyvsp[-4].pch),
                                             NULL,
                                             (yyvsp[-5].aggrTag),
                                             (yyvsp[-3].pcallexpr),
                                             (yyvsp[-1].pblockstmt),
                                             FLAG_UNKNOWN,
                                             (yylsp[-5]).comment));
    }
#line 6736 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 201:
#line 975 "chapel.ypp" /* yacc.c:1663  */
    {
      (yyval.pblockstmt) = buildChapelStmt(buildClassDefExpr((yyvsp[-4].pch),
                                             (yyvsp[-6].pch),
                                             (yyvsp[-5].aggrTag),
                                             (yyvsp[-3].pcallexpr),
                                             (yyvsp[-1].pblockstmt),
                                             FLAG_EXTERN,
                                             (yylsp[-5]).comment));
    }
#line 6750 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 202:
#line 985 "chapel.ypp" /* yacc.c:1663  */
    {
      (yyval.pblockstmt) = buildChapelStmt(buildClassDefExpr((yyvsp[-4].pch),
                                             NULL,
                                             (yyvsp[-5].aggrTag),
                                             (yyvsp[-3].pcallexpr),
                                             new BlockStmt(),
                                             FLAG_UNKNOWN,
                                             (yylsp[-5]).comment));
    }
#line 6764 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 203:
#line 995 "chapel.ypp" /* yacc.c:1663  */
    {
      (yyval.pblockstmt) = buildChapelStmt(buildClassDefExpr((yyvsp[-4].pch),
                                             (yyvsp[-6].pch),
                                             (yyvsp[-5].aggrTag),
                                             (yyvsp[-3].pcallexpr),
                                             new BlockStmt(),
                                             FLAG_EXTERN,
                                             (yylsp[-5]).comment));
    }
#line 6778 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 204:
#line 1007 "chapel.ypp" /* yacc.c:1663  */
    {
             (yyval.aggrTag)                     = AGGREGATE_CLASS;
             (yyloc).comment             = context->latestComment;
             context->latestComment = NULL;
           }
#line 6788 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 205:
#line 1012 "chapel.ypp" /* yacc.c:1663  */
    {
             (yyval.aggrTag)                     = AGGREGATE_RECORD;
             (yyloc).comment             = context->latestComment;
             context->latestComment = NULL;
           }
#line 6798 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 206:
#line 1017 "chapel.ypp" /* yacc.c:1663  */
    {
             (yyval.aggrTag)                     = AGGREGATE_UNION;
             (yyloc).comment             = context->latestComment;
             context->latestComment = NULL;
           }
#line 6808 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 207:
#line 1025 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pcallexpr) = NULL; }
#line 6814 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 208:
#line 1026 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pcallexpr) = (yyvsp[0].pcallexpr); }
#line 6820 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 209:
#line 1031 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = new BlockStmt(); }
#line 6826 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 210:
#line 1033 "chapel.ypp" /* yacc.c:1663  */
    { (yyvsp[-1].pblockstmt)->insertAtTail((yyvsp[0].pblockstmt)); }
#line 6832 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 211:
#line 1035 "chapel.ypp" /* yacc.c:1663  */
    { (yyvsp[-2].pblockstmt)->insertAtTail(buildPragmaStmt((yyvsp[-1].vpch), (yyvsp[0].pblockstmt))); }
#line 6838 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 212:
#line 1040 "chapel.ypp" /* yacc.c:1663  */
    {
      EnumType* pdt = (yyvsp[-4].penumtype);
      for_vector(DefExpr, ec, *(yyvsp[-1].pvecOfDefs)) {
        ec->sym->type = pdt;
        pdt->constants.insertAtTail(ec);
        if (pdt->defaultValue == NULL) {
          pdt->defaultValue = ec->sym;
        }
      }
      delete (yyvsp[-1].pvecOfDefs);
      pdt->doc = (yylsp[-4]).comment;
      TypeSymbol* pst = new TypeSymbol((yyvsp[-3].pch), pdt);
      (yyvsp[-4].penumtype)->symbol = pst;
      (yyval.pblockstmt) = buildChapelStmt(new DefExpr(pst));
    }
#line 6858 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 213:
#line 1056 "chapel.ypp" /* yacc.c:1663  */
    {
      (yyval.pblockstmt) = buildErrorStandin();
    }
#line 6866 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 214:
#line 1063 "chapel.ypp" /* yacc.c:1663  */
    {
      (yyval.penumtype) = new EnumType();
      (yyloc).comment = context->latestComment;
      context->latestComment = NULL;
    }
#line 6876 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 215:
#line 1072 "chapel.ypp" /* yacc.c:1663  */
    {
      (yyval.pvecOfDefs) = new std::vector<DefExpr*>();
      (yyval.pvecOfDefs)->push_back((yyvsp[0].pdefexpr));
      //$$->doc = context->latestComment;
      // start here for enabling documentation of enum constants
      //context->latestComment = NULL;
    }
#line 6888 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 216:
#line 1080 "chapel.ypp" /* yacc.c:1663  */
    {
      (yyval.pvecOfDefs) = (yyvsp[-1].pvecOfDefs);
    }
#line 6896 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 217:
#line 1084 "chapel.ypp" /* yacc.c:1663  */
    {
      (yyvsp[-2].pvecOfDefs)->push_back((yyvsp[0].pdefexpr));
    }
#line 6904 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 218:
#line 1090 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pdefexpr) = new DefExpr(new EnumSymbol((yyvsp[0].pch))); }
#line 6910 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 219:
#line 1091 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pdefexpr) = new DefExpr(new EnumSymbol((yyvsp[-2].pch)), (yyvsp[0].pexpr)); }
#line 6916 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 220:
#line 1096 "chapel.ypp" /* yacc.c:1663  */
    {
      captureTokens = 1;
      captureString.clear();
    }
#line 6925 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 221:
#line 1101 "chapel.ypp" /* yacc.c:1663  */
    {
      captureTokens = 0;
      (yyvsp[0].pfnsymbol)->userString = astr(captureString);
    }
#line 6934 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 222:
#line 1106 "chapel.ypp" /* yacc.c:1663  */
    {
      (yyvsp[-5].pfnsymbol)->retTag = (yyvsp[-3].retTag);
      if ((yyvsp[-3].retTag) == RET_REF || (yyvsp[-3].retTag) == RET_CONST_REF)
        USR_FATAL("'ref' return types are not allowed in lambdas");
      if ((yyvsp[-3].retTag) == RET_PARAM)
        USR_FATAL("'param' return types are not allowed in lambdas");
      if ((yyvsp[-3].retTag) == RET_TYPE)
        USR_FATAL("'type' return types are not allowed in lambdas");
      if ((yyvsp[-2].pexpr))
        (yyvsp[-5].pfnsymbol)->retExprType = new BlockStmt((yyvsp[-2].pexpr), BLOCK_SCOPELESS);
      if ((yyvsp[-1].lifetimeAndWhere).where)
        (yyvsp[-5].pfnsymbol)->where = new BlockStmt((yyvsp[-1].lifetimeAndWhere).where);
      if ((yyvsp[-1].lifetimeAndWhere).lifetime)
        (yyvsp[-5].pfnsymbol)->lifetimeConstraints = new BlockStmt((yyvsp[-1].lifetimeAndWhere).lifetime);
      (yyvsp[-5].pfnsymbol)->insertAtTail((yyvsp[0].pblockstmt));
      (yyval.pexpr) = new DefExpr(buildLambda((yyvsp[-5].pfnsymbol)));
    }
#line 6956 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 223:
#line 1128 "chapel.ypp" /* yacc.c:1663  */
    {
                  (yyval.pfnsymbol) = new FnSymbol("");

                  (yyloc).comment             = context->latestComment;
                  context->latestComment = NULL;
                }
#line 6967 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 224:
#line 1134 "chapel.ypp" /* yacc.c:1663  */
    {
                  (yyval.pfnsymbol) = new FnSymbol("");
                  (yyval.pfnsymbol)->addFlag(FLAG_INLINE);

                  (yyloc).comment             = context->latestComment;
                  context->latestComment = NULL;
                }
#line 6979 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 225:
#line 1141 "chapel.ypp" /* yacc.c:1663  */
    {
                  (yyval.pfnsymbol) = buildLinkageFn(FLAG_EXPORT, (yyvsp[0].pexpr));

                  (yyloc).comment             = context->latestComment;
                  context->latestComment = NULL;
                }
#line 6990 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 226:
#line 1147 "chapel.ypp" /* yacc.c:1663  */
    {
                  (yyval.pfnsymbol) = buildLinkageFn(FLAG_EXTERN, (yyvsp[0].pexpr));

                  (yyloc).comment             = context->latestComment;
                  context->latestComment = NULL;
                }
#line 7001 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 227:
#line 1153 "chapel.ypp" /* yacc.c:1663  */
    {
                  (yyval.pfnsymbol) = new FnSymbol("");
                  (yyval.pfnsymbol)->addFlag(FLAG_OVERRIDE);

                  (yyloc).comment             = context->latestComment;
                  context->latestComment = NULL;
                }
#line 7013 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 228:
#line 1164 "chapel.ypp" /* yacc.c:1663  */
    {
      // Sets up to capture tokens while parsing the next grammar nonterminal.
      captureTokens = 1;
      captureString.clear();
    }
#line 7023 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 229:
#line 1170 "chapel.ypp" /* yacc.c:1663  */
    {
      // Stop capturing and save the result.
      captureTokens = 0;

      (yyvsp[0].pfnsymbol)->userString = astr(captureString);
    }
#line 7034 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 230:
#line 1177 "chapel.ypp" /* yacc.c:1663  */
    {
      FnSymbol* fn = (yyvsp[-6].pfnsymbol);
      FnSymbol* linkageFn = (yyvsp[-9].pfnsymbol);

      fn->copyFlags((yyvsp[-9].pfnsymbol));
      if (*linkageFn->name)
        // The user explicitly named this function (controls mangling).
        fn->cname = linkageFn->name;
      else if (linkageFn->numFormals() == 1)
        // cname should be set based upon param
        fn->insertFormalAtTail(linkageFn->getFormal(1));

      if ((yyvsp[-8].procIter) == ProcIter_ITER)
      {
        if (fn->hasFlag(FLAG_EXTERN))
          USR_FATAL_CONT(fn, "'iter' is not legal with 'extern'");
        fn->addFlag(FLAG_ITERATOR_FN);
      }

      (yyval.pblockstmt) = buildFunctionDecl((yyvsp[-6].pfnsymbol), (yyvsp[-4].retTag), (yyvsp[-3].pexpr), (yyvsp[-2].b), (yyvsp[-1].lifetimeAndWhere).where, (yyvsp[-1].lifetimeAndWhere).lifetime, (yyvsp[0].pblockstmt), (yylsp[-9]).comment);
      context->latestComment = NULL;
    }
#line 7061 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 231:
#line 1203 "chapel.ypp" /* yacc.c:1663  */
    {
      (yyval.pfnsymbol) = buildFunctionSymbol((yyvsp[0].pfnsymbol), (yyvsp[-1].pch), (yyvsp[-2].pt), NULL);
    }
#line 7069 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 232:
#line 1207 "chapel.ypp" /* yacc.c:1663  */
    {
      (yyval.pfnsymbol) = buildFunctionSymbol((yyvsp[0].pfnsymbol), (yyvsp[-1].pch), (yyvsp[-2].pt), NULL);
      (yyval.pfnsymbol)->addFlag(FLAG_ASSIGNOP);
    }
#line 7078 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 233:
#line 1212 "chapel.ypp" /* yacc.c:1663  */
    {
      (yyval.pfnsymbol) = buildFunctionSymbol((yyvsp[0].pfnsymbol), (yyvsp[-1].pch), (yyvsp[-4].pt), (yyvsp[-3].pexpr));
    }
#line 7086 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 234:
#line 1216 "chapel.ypp" /* yacc.c:1663  */
    {
      (yyval.pfnsymbol) = buildFunctionSymbol((yyvsp[0].pfnsymbol), (yyvsp[-1].pch), (yyvsp[-4].pt), (yyvsp[-3].pexpr));
      (yyval.pfnsymbol)->addFlag(FLAG_ASSIGNOP);
    }
#line 7095 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 235:
#line 1221 "chapel.ypp" /* yacc.c:1663  */
    {
      (yyval.pfnsymbol) = buildFunctionSymbol((yyvsp[0].pfnsymbol), "dummy", INTENT_BLANK, NULL);
    }
#line 7103 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 237:
#line 1228 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = (yyvsp[-1].pexpr); }
#line 7109 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 238:
#line 1232 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = (yyvsp[0].pch); }
#line 7115 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 239:
#line 1233 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = astr("~", (yyvsp[0].pch)); }
#line 7121 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 240:
#line 1234 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "&"; }
#line 7127 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 241:
#line 1235 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "|"; }
#line 7133 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 242:
#line 1236 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "^"; }
#line 7139 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 243:
#line 1237 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "~"; }
#line 7145 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 244:
#line 1238 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "=="; }
#line 7151 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 245:
#line 1239 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "!="; }
#line 7157 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 246:
#line 1240 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "<="; }
#line 7163 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 247:
#line 1241 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = ">="; }
#line 7169 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 248:
#line 1242 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "<"; }
#line 7175 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 249:
#line 1243 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = ">"; }
#line 7181 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 250:
#line 1244 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "+"; }
#line 7187 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 251:
#line 1245 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "-"; }
#line 7193 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 252:
#line 1246 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "*"; }
#line 7199 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 253:
#line 1247 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "/"; }
#line 7205 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 254:
#line 1248 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "<<"; }
#line 7211 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 255:
#line 1249 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = ">>"; }
#line 7217 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 256:
#line 1250 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "%"; }
#line 7223 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 257:
#line 1251 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "**"; }
#line 7229 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 258:
#line 1252 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "!"; }
#line 7235 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 259:
#line 1253 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "chpl_by"; }
#line 7241 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 260:
#line 1254 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "#"; }
#line 7247 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 261:
#line 1255 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "chpl_align"; }
#line 7253 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 262:
#line 1256 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "<=>"; }
#line 7259 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 263:
#line 1257 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "<~>"; }
#line 7265 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 264:
#line 1258 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "init="; }
#line 7271 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 265:
#line 1259 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = astr((yyvsp[-1].pch), "!"); }
#line 7277 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 266:
#line 1263 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "="; }
#line 7283 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 267:
#line 1264 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "+="; }
#line 7289 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 268:
#line 1265 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "-="; }
#line 7295 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 269:
#line 1266 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "*="; }
#line 7301 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 270:
#line 1267 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "/="; }
#line 7307 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 271:
#line 1268 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "%="; }
#line 7313 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 272:
#line 1269 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "**="; }
#line 7319 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 273:
#line 1270 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "&="; }
#line 7325 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 274:
#line 1271 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "|="; }
#line 7331 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 275:
#line 1272 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "^="; }
#line 7337 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 276:
#line 1273 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = ">>="; }
#line 7343 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 277:
#line 1274 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pch) = "<<="; }
#line 7349 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 278:
#line 1278 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pfnsymbol) = new FnSymbol("_"); (yyval.pfnsymbol)->addFlag(FLAG_NO_PARENS); }
#line 7355 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 279:
#line 1279 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pfnsymbol) = (yyvsp[-1].pfnsymbol); }
#line 7361 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 280:
#line 1283 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pfnsymbol) = (yyvsp[-1].pfnsymbol); }
#line 7367 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 281:
#line 1287 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pfnsymbol) = buildFunctionFormal(NULL, NULL); }
#line 7373 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 282:
#line 1288 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pfnsymbol) = buildFunctionFormal(NULL, (yyvsp[0].pdefexpr)); }
#line 7379 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 283:
#line 1289 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pfnsymbol) = buildFunctionFormal((yyvsp[-2].pfnsymbol), (yyvsp[0].pdefexpr)); }
#line 7385 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 284:
#line 1294 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pdefexpr) = buildArgDefExpr((yyvsp[-3].pt), (yyvsp[-2].pch), (yyvsp[-1].pexpr), (yyvsp[0].pexpr), NULL); }
#line 7391 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 285:
#line 1296 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pdefexpr) = buildPragmaDefExpr((yyvsp[-4].vpch), buildArgDefExpr((yyvsp[-3].pt), (yyvsp[-2].pch), (yyvsp[-1].pexpr), (yyvsp[0].pexpr), NULL)); }
#line 7397 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 286:
#line 1298 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pdefexpr) = buildArgDefExpr((yyvsp[-3].pt), (yyvsp[-2].pch), (yyvsp[-1].pexpr), NULL, (yyvsp[0].pexpr)); }
#line 7403 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 287:
#line 1300 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pdefexpr) = buildTupleArgDefExpr((yyvsp[-5].pt), (yyvsp[-3].pblockstmt), (yyvsp[-1].pexpr), (yyvsp[0].pexpr)); }
#line 7409 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 288:
#line 1302 "chapel.ypp" /* yacc.c:1663  */
    { USR_FATAL("variable-length argument may not be grouped in a tuple"); }
#line 7415 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 289:
#line 1306 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pt) = INTENT_BLANK; }
#line 7421 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 290:
#line 1307 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pt) = (yyvsp[0].pt); }
#line 7427 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 291:
#line 1311 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pt) = INTENT_IN; }
#line 7433 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 292:
#line 1312 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pt) = INTENT_INOUT; }
#line 7439 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 293:
#line 1313 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pt) = INTENT_OUT; }
#line 7445 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 294:
#line 1314 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pt) = INTENT_CONST; }
#line 7451 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 295:
#line 1315 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pt) = INTENT_CONST_IN; }
#line 7457 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 296:
#line 1316 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pt) = INTENT_CONST_REF; }
#line 7463 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 297:
#line 1317 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pt) = INTENT_PARAM; }
#line 7469 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 298:
#line 1318 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pt) = INTENT_REF; }
#line 7475 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 299:
#line 1319 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pt) = INTENT_TYPE; }
#line 7481 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 300:
#line 1323 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pt) = INTENT_BLANK; }
#line 7487 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 301:
#line 1324 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pt) = INTENT_PARAM; }
#line 7493 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 302:
#line 1325 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pt) = INTENT_REF;   }
#line 7499 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 303:
#line 1326 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pt) = INTENT_CONST_REF;   }
#line 7505 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 304:
#line 1327 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pt) = INTENT_CONST;   }
#line 7511 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 305:
#line 1328 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pt) = INTENT_TYPE;  }
#line 7517 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 306:
#line 1332 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.procIter) = ProcIter_PROC; }
#line 7523 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 307:
#line 1333 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.procIter) = ProcIter_ITER; }
#line 7529 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 308:
#line 1337 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.retTag) = RET_VALUE; }
#line 7535 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 309:
#line 1338 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.retTag) = RET_VALUE; }
#line 7541 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 310:
#line 1339 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.retTag) = RET_CONST_REF; }
#line 7547 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 311:
#line 1340 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.retTag) = RET_REF; }
#line 7553 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 312:
#line 1341 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.retTag) = RET_PARAM; }
#line 7559 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 313:
#line 1342 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.retTag) = RET_TYPE; }
#line 7565 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 314:
#line 1346 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.b) = false; }
#line 7571 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 315:
#line 1347 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.b) = true;  }
#line 7577 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 316:
#line 1350 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = NULL; }
#line 7583 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 319:
#line 1356 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = new BlockStmt((yyvsp[0].pblockstmt)); }
#line 7589 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 320:
#line 1361 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pdefexpr) = new DefExpr(new VarSymbol((yyvsp[0].pch))); }
#line 7595 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 321:
#line 1363 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pdefexpr) = new DefExpr(new VarSymbol(astr("chpl__query", istr(query_uid++)))); }
#line 7601 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 322:
#line 1367 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pdefexpr) = new DefExpr(new VarSymbol(astr("chpl__query", istr(query_uid++)))); }
#line 7607 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 324:
#line 1372 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = (yyvsp[0].pexpr); }
#line 7613 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 325:
#line 1373 "chapel.ypp" /* yacc.c:1663  */
    { (yyvsp[0].pdefexpr)->sym->addFlag(FLAG_PARAM); (yyval.pexpr) = (yyvsp[0].pdefexpr); }
#line 7619 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 326:
#line 1377 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.lifetimeAndWhere) = makeWhereAndLifetime(NULL, NULL); }
#line 7625 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 327:
#line 1379 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.lifetimeAndWhere) = makeWhereAndLifetime((yyvsp[0].pexpr), NULL); }
#line 7631 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 328:
#line 1381 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.lifetimeAndWhere) = makeWhereAndLifetime(NULL, (yyvsp[0].pexpr)); }
#line 7637 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 329:
#line 1383 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.lifetimeAndWhere) = makeWhereAndLifetime((yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7643 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 330:
#line 1385 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.lifetimeAndWhere) = makeWhereAndLifetime((yyvsp[0].pexpr), (yyvsp[-2].pexpr)); }
#line 7649 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 331:
#line 1389 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = (yyvsp[0].pexpr); }
#line 7655 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 332:
#line 1390 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr(",", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7661 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 333:
#line 1393 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("=", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7667 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 334:
#line 1394 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("<", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7673 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 335:
#line 1395 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("<=", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7679 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 336:
#line 1396 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("==", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7685 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 337:
#line 1397 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr(">", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7691 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 338:
#line 1398 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr(">=", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7697 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 339:
#line 1399 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr(PRIM_RETURN, (yyvsp[0].pexpr)); }
#line 7703 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 340:
#line 1402 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr(PRIM_LIFETIME_OF, new UnresolvedSymExpr((yyvsp[0].pch))); }
#line 7709 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 341:
#line 1403 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr(PRIM_LIFETIME_OF, new UnresolvedSymExpr("this")); }
#line 7715 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 342:
#line 1407 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = (yyvsp[-1].pblockstmt); }
#line 7721 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 343:
#line 1409 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = handleConfigTypes((yyvsp[-1].pblockstmt)); }
#line 7727 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 344:
#line 1411 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = convertTypesToExtern((yyvsp[-1].pblockstmt)); }
#line 7733 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 345:
#line 1416 "chapel.ypp" /* yacc.c:1663  */
    {
      VarSymbol* var = new VarSymbol((yyvsp[-1].pch));

      var->addFlag(FLAG_TYPE_VARIABLE);

      var->doc               = context->latestComment;
      context->latestComment = NULL;

      DefExpr* def = new DefExpr(var, (yyvsp[0].pexpr));

      (yyval.pblockstmt) = buildChapelStmt(def);
    }
#line 7750 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 346:
#line 1429 "chapel.ypp" /* yacc.c:1663  */
    {
      VarSymbol* var = new VarSymbol((yyvsp[-3].pch));

      var->addFlag(FLAG_TYPE_VARIABLE);

      var->doc               = context->latestComment;
      context->latestComment = NULL;

      DefExpr* def = new DefExpr(var, (yyvsp[-2].pexpr));

      (yyvsp[0].pblockstmt)->insertAtHead(def);
      (yyval.pblockstmt) = buildChapelStmt((yyvsp[0].pblockstmt));
    }
#line 7768 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 347:
#line 1445 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = NULL; }
#line 7774 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 348:
#line 1447 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = (yyvsp[0].pexpr); }
#line 7780 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 349:
#line 1449 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildForallLoopExprFromArrayType((yyvsp[0].pcallexpr)); }
#line 7786 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 350:
#line 1453 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pflagset) = buildVarDeclFlags(FLAG_PARAM); }
#line 7792 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 351:
#line 1454 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pflagset) = buildVarDeclFlags(FLAG_CONST); }
#line 7798 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 352:
#line 1455 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pflagset) = buildVarDeclFlags(FLAG_REF_VAR); }
#line 7804 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 353:
#line 1456 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pflagset) = buildVarDeclFlags(FLAG_CONST, FLAG_REF_VAR); }
#line 7810 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 354:
#line 1457 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pflagset) = buildVarDeclFlags(); }
#line 7816 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 355:
#line 1462 "chapel.ypp" /* yacc.c:1663  */
    {
      (yyvsp[-2].pflagset)->insert(FLAG_CONFIG);
      (yyval.pblockstmt) = buildVarDecls((yyvsp[-1].pblockstmt), context->latestComment, (yyvsp[-2].pflagset));
      context->latestComment = NULL;
    }
#line 7826 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 356:
#line 1468 "chapel.ypp" /* yacc.c:1663  */
    {
      (yyvsp[-2].pflagset)->insert(FLAG_EXTERN);
      (yyval.pblockstmt) = buildVarDecls((yyvsp[-1].pblockstmt), context->latestComment, (yyvsp[-2].pflagset), (yyvsp[-3].pexpr));
      context->latestComment = NULL;
    }
#line 7836 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 357:
#line 1474 "chapel.ypp" /* yacc.c:1663  */
    {
      (yyval.pblockstmt) = buildVarDecls((yyvsp[-1].pblockstmt), context->latestComment, (yyvsp[-2].pflagset));
      context->latestComment = NULL;
    }
#line 7845 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 359:
#line 1483 "chapel.ypp" /* yacc.c:1663  */
    {
      for_alist(expr, (yyvsp[0].pblockstmt)->body)
        (yyvsp[-2].pblockstmt)->insertAtTail(expr->remove());
    }
#line 7854 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 360:
#line 1491 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildChapelStmt(new DefExpr(new VarSymbol((yyvsp[-2].pch)), (yyvsp[0].pexpr), (yyvsp[-1].pexpr))); }
#line 7860 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 361:
#line 1493 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildTupleVarDeclStmt((yyvsp[-3].pblockstmt), (yyvsp[-1].pexpr), (yyvsp[0].pexpr)); }
#line 7866 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 362:
#line 1498 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new DefExpr(new VarSymbol("chpl__tuple_blank")); }
#line 7872 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 363:
#line 1500 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new DefExpr(new VarSymbol((yyvsp[0].pch))); }
#line 7878 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 364:
#line 1502 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = (yyvsp[-1].pblockstmt); }
#line 7884 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 365:
#line 1507 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildChapelStmt((yyvsp[0].pexpr)); }
#line 7890 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 366:
#line 1509 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = buildChapelStmt((yyvsp[-1].pexpr)); }
#line 7896 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 367:
#line 1511 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pblockstmt) = ((yyvsp[0].pblockstmt)->insertAtHead((yyvsp[-2].pexpr)), (yyvsp[0].pblockstmt)); }
#line 7902 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 368:
#line 1517 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = NULL; }
#line 7908 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 369:
#line 1518 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new SymExpr(gNoInit); }
#line 7914 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 370:
#line 1519 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = (yyvsp[0].pexpr); }
#line 7920 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 371:
#line 1525 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("chpl__buildArrayRuntimeType", gNil, (yyvsp[0].pexpr)); }
#line 7926 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 372:
#line 1527 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("chpl__buildArrayRuntimeType", gNil, NULL); }
#line 7932 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 373:
#line 1529 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("chpl__buildArrayRuntimeType",
             new CallExpr("chpl__ensureDomainExpr", (yyvsp[-2].pcallexpr)), (yyvsp[0].pexpr));
    }
#line 7940 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 374:
#line 1533 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("chpl__buildArrayRuntimeType",
             new CallExpr("chpl__ensureDomainExpr", (yyvsp[-1].pcallexpr)), NULL);
    }
#line 7948 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 375:
#line 1537 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("chpl__buildArrayRuntimeType", gNil, (yyvsp[0].pexpr)); }
#line 7954 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 376:
#line 1539 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("chpl__buildArrayRuntimeType",
             new CallExpr("chpl__ensureDomainExpr", (yyvsp[-2].pcallexpr)), (yyvsp[0].pexpr));
    }
#line 7962 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 377:
#line 1543 "chapel.ypp" /* yacc.c:1663  */
    {
      (yyval.pexpr) = new CallExpr(PRIM_ERROR);
    }
#line 7970 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 378:
#line 1550 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = NULL; }
#line 7976 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 379:
#line 1551 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = (yyvsp[0].pexpr); }
#line 7982 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 380:
#line 1552 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = (yyvsp[0].pexpr); }
#line 7988 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 381:
#line 1553 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new UnresolvedSymExpr((yyvsp[0].pch)); }
#line 7994 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 382:
#line 1554 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = NULL; }
#line 8000 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 383:
#line 1559 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = NULL; }
#line 8006 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 384:
#line 1560 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = (yyvsp[0].pexpr); }
#line 8012 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 385:
#line 1561 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = (yyvsp[0].pcallexpr); }
#line 8018 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 386:
#line 1562 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new UnresolvedSymExpr((yyvsp[0].pch)); }
#line 8024 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 387:
#line 1563 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = NULL; }
#line 8030 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 388:
#line 1584 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pcallexpr) = new CallExpr("chpl__buildArrayRuntimeType",
             new CallExpr("chpl__ensureDomainExpr", (yyvsp[-2].pcallexpr)), (yyvsp[0].pexpr));
    }
#line 8038 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 389:
#line 1588 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pcallexpr) = new CallExpr("chpl__buildArrayRuntimeType",
             new CallExpr("chpl__ensureDomainExpr", (yyvsp[-2].pcallexpr)), (yyvsp[0].pcallexpr));
    }
#line 8046 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 390:
#line 1592 "chapel.ypp" /* yacc.c:1663  */
    {
      if ((yyvsp[-4].pcallexpr)->argList.length != 1)
        USR_FATAL((yyvsp[-2].pexpr), "invalid index expression");
      (yyval.pcallexpr) = new CallExpr("chpl__buildArrayRuntimeType",
             new CallExpr("chpl__ensureDomainExpr", (yyvsp[-2].pexpr)), (yyvsp[0].pexpr), (yyvsp[-4].pcallexpr)->get(1)->remove(),
             new CallExpr("chpl__ensureDomainExpr", (yyvsp[-2].pexpr)->copy()));
    }
#line 8058 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 391:
#line 1600 "chapel.ypp" /* yacc.c:1663  */
    {
      (yyval.pcallexpr) = new CallExpr(PRIM_ERROR);
    }
#line 8066 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 392:
#line 1606 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = NULL; }
#line 8072 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 393:
#line 1607 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = (yyvsp[0].pexpr); }
#line 8078 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 394:
#line 1608 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = (yyvsp[0].pdefexpr); }
#line 8084 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 395:
#line 1613 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("chpl__buildArrayRuntimeType", gNil, (yyvsp[0].pexpr)); }
#line 8090 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 396:
#line 1615 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildFormalArrayType((yyvsp[-2].pcallexpr), (yyvsp[0].pexpr)); }
#line 8096 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 397:
#line 1621 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("chpl__buildArrayRuntimeType", gNil, (yyvsp[0].pexpr)); }
#line 8102 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 398:
#line 1623 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildFormalArrayType((yyvsp[-2].pcallexpr), (yyvsp[0].pexpr)); }
#line 8108 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 399:
#line 1625 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildFormalArrayType((yyvsp[-2].pexpr), (yyvsp[0].pexpr), (yyvsp[-4].pcallexpr)); }
#line 8114 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 400:
#line 1629 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = NULL; }
#line 8120 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 401:
#line 1630 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = (yyvsp[0].pexpr); }
#line 8126 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 402:
#line 1631 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = (yyvsp[0].pdefexpr); }
#line 8132 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 403:
#line 1632 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new UnresolvedSymExpr((yyvsp[0].pch)); }
#line 8138 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 404:
#line 1633 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = (yyvsp[0].pexpr); }
#line 8144 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 405:
#line 1639 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pcallexpr) = new CallExpr(PRIM_ACTUALS_LIST, (yyvsp[0].pexpr)); }
#line 8150 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 406:
#line 1640 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pcallexpr) = new CallExpr(PRIM_ACTUALS_LIST, (yyvsp[0].pdefexpr)); }
#line 8156 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 407:
#line 1641 "chapel.ypp" /* yacc.c:1663  */
    { (yyvsp[-2].pcallexpr)->insertAtTail((yyvsp[0].pexpr)); }
#line 8162 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 408:
#line 1642 "chapel.ypp" /* yacc.c:1663  */
    { (yyvsp[-2].pcallexpr)->insertAtTail((yyvsp[0].pdefexpr)); }
#line 8168 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 409:
#line 1646 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pcallexpr) = new CallExpr(PRIM_ACTUALS_LIST, (yyvsp[0].pexpr));}
#line 8174 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 410:
#line 1647 "chapel.ypp" /* yacc.c:1663  */
    { (yyvsp[-2].pcallexpr)->insertAtTail((yyvsp[0].pexpr)); }
#line 8180 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 411:
#line 1651 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new UnresolvedSymExpr("chpl__tuple_blank"); }
#line 8186 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 412:
#line 1652 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = (yyvsp[0].pexpr); }
#line 8192 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 413:
#line 1653 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = (yyvsp[0].pdefexpr); }
#line 8198 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 414:
#line 1657 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pcallexpr) = new CallExpr(PRIM_ACTUALS_LIST, (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 8204 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 415:
#line 1658 "chapel.ypp" /* yacc.c:1663  */
    { (yyvsp[-2].pcallexpr)->insertAtTail((yyvsp[0].pexpr)); }
#line 8210 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 416:
#line 1662 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pcallexpr) = new CallExpr(PRIM_ACTUALS_LIST); }
#line 8216 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 418:
#line 1667 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pcallexpr) = new CallExpr(PRIM_ACTUALS_LIST, (yyvsp[0].pexpr)); }
#line 8222 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 419:
#line 1668 "chapel.ypp" /* yacc.c:1663  */
    { (yyvsp[-2].pcallexpr)->insertAtTail((yyvsp[0].pexpr)); }
#line 8228 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 420:
#line 1672 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildNamedActual((yyvsp[-2].pch), (yyvsp[0].pdefexpr)); }
#line 8234 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 421:
#line 1673 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildNamedActual((yyvsp[-2].pch), (yyvsp[0].pexpr)); }
#line 8240 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 422:
#line 1674 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = (yyvsp[0].pdefexpr); }
#line 8246 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 423:
#line 1675 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = (yyvsp[0].pexpr); }
#line 8252 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 424:
#line 1679 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new UnresolvedSymExpr((yyvsp[0].pch)); }
#line 8258 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 425:
#line 1680 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = (yyvsp[0].pexpr); }
#line 8264 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 426:
#line 1692 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = (yyvsp[0].pexpr); }
#line 8270 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 427:
#line 1694 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr( PRIM_TO_NILABLE_CLASS, (yyvsp[-1].pexpr)); }
#line 8276 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 433:
#line 1704 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr( "_singlevar", (yyvsp[0].pexpr)); }
#line 8282 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 434:
#line 1706 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("chpl__buildIndexType", (yyvsp[-1].pcallexpr)); }
#line 8288 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 435:
#line 1708 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("chpl__buildDomainRuntimeType", new UnresolvedSymExpr("defaultDist"), (yyvsp[-1].pcallexpr)); }
#line 8294 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 436:
#line 1710 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("chpl__buildSubDomainType", (yyvsp[-1].pcallexpr)); }
#line 8300 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 437:
#line 1712 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("chpl__buildSparseDomainRuntimeType", buildDotExpr((yyvsp[-1].pcallexpr)->copy(), "defaultSparseDist"), (yyvsp[-1].pcallexpr)); }
#line 8306 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 438:
#line 1714 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("chpl__atomicType", (yyvsp[0].pexpr)); }
#line 8312 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 439:
#line 1716 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr( "_syncvar", (yyvsp[0].pexpr)); }
#line 8318 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 440:
#line 1719 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new UnresolvedSymExpr("_owned"); }
#line 8324 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 441:
#line 1721 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr( "_owned", (yyvsp[0].pexpr)); }
#line 8330 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 442:
#line 1723 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new UnresolvedSymExpr("_unmanaged"); }
#line 8336 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 443:
#line 1725 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr( PRIM_TO_UNMANAGED_CLASS, (yyvsp[0].pexpr)); }
#line 8342 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 444:
#line 1727 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new UnresolvedSymExpr("_shared"); }
#line 8348 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 445:
#line 1729 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr( "_shared", (yyvsp[0].pexpr)); }
#line 8354 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 446:
#line 1731 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new UnresolvedSymExpr("_borrowed"); }
#line 8360 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 447:
#line 1733 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr( PRIM_TO_BORROWED_CLASS, (yyvsp[0].pexpr)); }
#line 8366 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 448:
#line 1738 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildForLoopExpr((yyvsp[-4].pexpr), (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 8372 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 449:
#line 1740 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildForLoopExpr((yyvsp[-4].pexpr), (yyvsp[-2].pcallexpr), (yyvsp[0].pexpr), NULL, false, true); }
#line 8378 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 450:
#line 1742 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildForLoopExpr(NULL, (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 8384 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 451:
#line 1744 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildForLoopExpr((yyvsp[-7].pexpr), (yyvsp[-5].pexpr), (yyvsp[0].pexpr), (yyvsp[-2].pexpr)); }
#line 8390 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 452:
#line 1746 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildForLoopExpr((yyvsp[-7].pexpr), (yyvsp[-5].pcallexpr), (yyvsp[0].pexpr), (yyvsp[-2].pexpr), false, true); }
#line 8396 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 453:
#line 1748 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildForLoopExpr(NULL, (yyvsp[-5].pexpr), (yyvsp[0].pexpr), (yyvsp[-2].pexpr)); }
#line 8402 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 454:
#line 1750 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildForallLoopExpr((yyvsp[-4].pexpr), (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 8408 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 455:
#line 1752 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildForallLoopExpr((yyvsp[-4].pexpr), (yyvsp[-2].pcallexpr), (yyvsp[0].pexpr), NULL, false, true); }
#line 8414 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 456:
#line 1754 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildForallLoopExpr(NULL, (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 8420 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 457:
#line 1756 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildForallLoopExpr((yyvsp[-7].pexpr), (yyvsp[-5].pexpr), (yyvsp[0].pexpr), (yyvsp[-2].pexpr)); }
#line 8426 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 458:
#line 1758 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildForallLoopExpr((yyvsp[-7].pexpr), (yyvsp[-5].pcallexpr), (yyvsp[0].pexpr), (yyvsp[-2].pexpr), false, true); }
#line 8432 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 459:
#line 1760 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildForallLoopExpr(NULL, (yyvsp[-5].pexpr), (yyvsp[0].pexpr), (yyvsp[-2].pexpr)); }
#line 8438 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 460:
#line 1762 "chapel.ypp" /* yacc.c:1663  */
    {
      if ((yyvsp[-2].pcallexpr)->argList.length > 1)
        (yyval.pexpr) = buildForallLoopExpr(NULL, new CallExpr("chpl__ensureDomainExpr", (yyvsp[-2].pcallexpr)), (yyvsp[0].pexpr), NULL, true);
      else
        (yyval.pexpr) = buildForallLoopExpr(NULL, (yyvsp[-2].pcallexpr)->get(1)->remove(), (yyvsp[0].pexpr), NULL, true);
    }
#line 8449 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 461:
#line 1769 "chapel.ypp" /* yacc.c:1663  */
    {
      if ((yyvsp[-4].pcallexpr)->argList.length != 1)
        USR_FATAL((yyvsp[-2].pexpr), "invalid index expression");
      (yyval.pexpr) = buildForallLoopExpr((yyvsp[-4].pcallexpr)->get(1)->remove(), (yyvsp[-2].pexpr), (yyvsp[0].pexpr), NULL, true);
    }
#line 8459 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 462:
#line 1775 "chapel.ypp" /* yacc.c:1663  */
    {
      if ((yyvsp[-4].pcallexpr)->argList.length != 1)
        USR_FATAL((yyvsp[-2].pcallexpr), "invalid index expression");
      (yyval.pexpr) = buildForallLoopExpr((yyvsp[-4].pcallexpr)->get(1)->remove(), (yyvsp[-2].pcallexpr), (yyvsp[0].pexpr), NULL, false, true);
    }
#line 8469 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 463:
#line 1781 "chapel.ypp" /* yacc.c:1663  */
    {
      if ((yyvsp[-7].pcallexpr)->argList.length != 1)
        USR_FATAL((yyvsp[-5].pexpr), "invalid index expression");
      (yyval.pexpr) = buildForallLoopExpr((yyvsp[-7].pcallexpr)->get(1)->remove(), (yyvsp[-5].pexpr), (yyvsp[0].pexpr), (yyvsp[-2].pexpr));
    }
#line 8479 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 464:
#line 1787 "chapel.ypp" /* yacc.c:1663  */
    {
      if ((yyvsp[-7].pcallexpr)->argList.length != 1)
        USR_FATAL((yyvsp[-5].pcallexpr), "invalid index expression");
      (yyval.pexpr) = buildForallLoopExpr((yyvsp[-7].pcallexpr)->get(1)->remove(), (yyvsp[-5].pcallexpr), (yyvsp[0].pexpr), (yyvsp[-2].pexpr), false, true);
    }
#line 8489 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 465:
#line 1796 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new IfExpr((yyvsp[-4].pexpr), (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 8495 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 466:
#line 1805 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new SymExpr(gNil); }
#line 8501 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 474:
#line 1821 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("<~>", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 8507 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 475:
#line 1825 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pcallexpr) = NULL; }
#line 8513 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 477:
#line 1830 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pcallexpr) = (yyvsp[-1].pcallexpr); }
#line 8519 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 478:
#line 1834 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pcallexpr) = new CallExpr(PRIM_ACTUALS_LIST); addTaskIntent((yyval.pcallexpr), (yyvsp[0].pShadowVar)); }
#line 8525 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 479:
#line 1835 "chapel.ypp" /* yacc.c:1663  */
    { addTaskIntent((yyvsp[-2].pcallexpr), (yyvsp[0].pShadowVar)); }
#line 8531 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 480:
#line 1839 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pcallexpr) = (yyvsp[-1].pcallexpr); }
#line 8537 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 481:
#line 1843 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pcallexpr) = new CallExpr(PRIM_ACTUALS_LIST); addForallIntent((yyval.pcallexpr), (yyvsp[0].pShadowVar)); }
#line 8543 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 482:
#line 1844 "chapel.ypp" /* yacc.c:1663  */
    { addForallIntent((yyvsp[-2].pcallexpr), (yyvsp[0].pShadowVar)); }
#line 8549 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 483:
#line 1849 "chapel.ypp" /* yacc.c:1663  */
    {
      (yyval.pShadowVar) = ShadowVarSymbol::buildForPrefix((yyvsp[-3].pShadowVarPref), (yyvsp[-2].pexpr), (yyvsp[-1].pexpr), (yyvsp[0].pexpr));
    }
#line 8557 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 484:
#line 1853 "chapel.ypp" /* yacc.c:1663  */
    {
      (yyval.pShadowVar) = ShadowVarSymbol::buildFromReduceIntent((yyvsp[0].pexpr), (yyvsp[-2].pexpr));
    }
#line 8565 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 485:
#line 1857 "chapel.ypp" /* yacc.c:1663  */
    {
      (yyval.pShadowVar) = ShadowVarSymbol::buildFromReduceIntent((yyvsp[0].pexpr), (yyvsp[-2].pexpr));
    }
#line 8573 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 486:
#line 1863 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pShadowVarPref) = SVP_CONST;     }
#line 8579 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 487:
#line 1864 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pShadowVarPref) = SVP_IN;        }
#line 8585 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 488:
#line 1865 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pShadowVarPref) = SVP_CONST_IN;  }
#line 8591 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 489:
#line 1866 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pShadowVarPref) = SVP_REF;       }
#line 8597 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 490:
#line 1867 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pShadowVarPref) = SVP_CONST_REF; }
#line 8603 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 491:
#line 1868 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pShadowVarPref) = SVP_VAR;       }
#line 8609 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 493:
#line 1874 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("<~>", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 8615 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 494:
#line 1879 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr(PRIM_NEW, (yyvsp[0].pexpr)); }
#line 8621 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 495:
#line 1884 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildLetExpr((yyvsp[-2].pblockstmt), (yyvsp[0].pexpr)); }
#line 8627 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 504:
#line 1900 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr(PRIM_TUPLE_EXPAND, (yyvsp[-1].pexpr)); }
#line 8633 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 505:
#line 1902 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = createCast((yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 8639 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 506:
#line 1904 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("chpl_build_bounded_range", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 8645 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 507:
#line 1906 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("chpl_build_low_bounded_range", (yyvsp[-1].pexpr)); }
#line 8651 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 508:
#line 1908 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("chpl_build_high_bounded_range", (yyvsp[0].pexpr)); }
#line 8657 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 509:
#line 1910 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("chpl_build_unbounded_range"); }
#line 8663 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 510:
#line 1914 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = NULL; }
#line 8669 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 511:
#line 1915 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = (yyvsp[0].pexpr); }
#line 8675 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 512:
#line 1918 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = tryExpr((yyvsp[0].pexpr)); }
#line 8681 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 513:
#line 1919 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = tryBangExpr((yyvsp[0].pexpr)); }
#line 8687 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 514:
#line 1920 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = (yyvsp[0].pexpr); }
#line 8693 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 519:
#line 1937 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = (yyvsp[0].pexpr); }
#line 8699 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 520:
#line 1938 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("postfix!", (yyvsp[-1].pexpr)); }
#line 8705 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 521:
#line 1939 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = (yyvsp[0].pexpr); }
#line 8711 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 522:
#line 1943 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr((yyvsp[-3].pexpr), (yyvsp[-1].pcallexpr)); }
#line 8717 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 523:
#line 1944 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildSquareCallExpr((yyvsp[-3].pexpr), (yyvsp[-1].pcallexpr)); }
#line 8723 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 524:
#line 1945 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildPrimitiveExpr((yyvsp[-1].pcallexpr)); }
#line 8729 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 525:
#line 1949 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildDotExpr((yyvsp[-2].pexpr), (yyvsp[0].pch)); }
#line 8735 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 526:
#line 1950 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr(PRIM_TYPEOF, (yyvsp[-2].pexpr)); }
#line 8741 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 527:
#line 1951 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildDotExpr((yyvsp[-2].pexpr), "_dom"); }
#line 8747 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 528:
#line 1952 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildDotExpr((yyvsp[-2].pexpr), "locale"); }
#line 8753 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 529:
#line 1960 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = (yyvsp[-1].pexpr); }
#line 8759 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 530:
#line 1961 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildOneTuple((yyvsp[-2].pexpr)); }
#line 8765 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 531:
#line 1962 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildTuple((yyvsp[-1].pcallexpr)); }
#line 8771 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 532:
#line 1963 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildTuple((yyvsp[-2].pcallexpr)); }
#line 8777 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 533:
#line 1967 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new SymExpr(gFalse); }
#line 8783 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 534:
#line 1968 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new SymExpr(gTrue); }
#line 8789 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 536:
#line 1973 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildIntLiteral((yyvsp[0].pch), yyfilename, chplLineno);    }
#line 8795 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 537:
#line 1974 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildRealLiteral((yyvsp[0].pch));   }
#line 8801 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 538:
#line 1975 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildImagLiteral((yyvsp[0].pch));   }
#line 8807 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 539:
#line 1976 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildStringLiteral((yyvsp[0].pch)); }
#line 8813 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 540:
#line 1977 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildCStringLiteral((yyvsp[0].pch)); }
#line 8819 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 541:
#line 1978 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new SymExpr(gNone); }
#line 8825 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 542:
#line 1979 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("chpl__buildDomainExpr", (yyvsp[-1].pcallexpr)); }
#line 8831 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 543:
#line 1980 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("chpl__buildDomainExpr", (yyvsp[-2].pcallexpr)); }
#line 8837 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 544:
#line 1981 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("chpl__buildArrayExpr",  (yyvsp[-1].pcallexpr)); }
#line 8843 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 545:
#line 1982 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("chpl__buildArrayExpr",  (yyvsp[-2].pcallexpr)); }
#line 8849 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 546:
#line 1984 "chapel.ypp" /* yacc.c:1663  */
    {
      (yyval.pexpr) = new CallExpr("chpl__buildAssociativeArrayExpr", (yyvsp[-1].pcallexpr));
    }
#line 8857 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 547:
#line 1988 "chapel.ypp" /* yacc.c:1663  */
    {
      (yyval.pexpr) = new CallExpr("chpl__buildAssociativeArrayExpr", (yyvsp[-2].pcallexpr));
    }
#line 8865 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 548:
#line 1995 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pcallexpr) = new CallExpr(PRIM_ACTUALS_LIST, (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 8871 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 549:
#line 1996 "chapel.ypp" /* yacc.c:1663  */
    { (yyvsp[-4].pcallexpr)->insertAtTail((yyvsp[-2].pexpr)); (yyvsp[-4].pcallexpr)->insertAtTail((yyvsp[0].pexpr)); }
#line 8877 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 550:
#line 2000 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("+", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 8883 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 551:
#line 2001 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("-", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 8889 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 552:
#line 2002 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("*", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 8895 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 553:
#line 2003 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("/", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 8901 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 554:
#line 2004 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("<<", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 8907 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 555:
#line 2005 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr(">>", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 8913 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 556:
#line 2006 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("%", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 8919 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 557:
#line 2007 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("==", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 8925 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 558:
#line 2008 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("!=", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 8931 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 559:
#line 2009 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("<=", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 8937 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 560:
#line 2010 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr(">=", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 8943 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 561:
#line 2011 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("<", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 8949 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 562:
#line 2012 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr(">", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 8955 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 563:
#line 2013 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("&", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 8961 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 564:
#line 2014 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("|", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 8967 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 565:
#line 2015 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("^", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 8973 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 566:
#line 2016 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("&&", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 8979 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 567:
#line 2017 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("||", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 8985 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 568:
#line 2018 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("**", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 8991 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 569:
#line 2019 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("chpl_by", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 8997 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 570:
#line 2020 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("chpl_align", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 9003 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 571:
#line 2021 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("#", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 9009 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 572:
#line 2022 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("chpl__distributed", (yyvsp[0].pexpr), (yyvsp[-2].pexpr)); }
#line 9015 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 573:
#line 2026 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("+", (yyvsp[0].pexpr)); }
#line 9021 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 574:
#line 2027 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("-", (yyvsp[0].pexpr)); }
#line 9027 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 575:
#line 2028 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildPreDecIncWarning((yyvsp[0].pexpr), '-'); }
#line 9033 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 576:
#line 2029 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildPreDecIncWarning((yyvsp[0].pexpr), '+'); }
#line 9039 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 577:
#line 2030 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("!", (yyvsp[0].pexpr)); }
#line 9045 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 578:
#line 2031 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("postfix!", (yyvsp[-1].pexpr)); }
#line 9051 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 579:
#line 2032 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new CallExpr("~", (yyvsp[0].pexpr)); }
#line 9057 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 580:
#line 2036 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildReduceExpr((yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 9063 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 581:
#line 2037 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildReduceExpr((yyvsp[-2].pexpr), (yyvsp[0].pcallexpr), true); }
#line 9069 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 582:
#line 2038 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildReduceExpr((yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 9075 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 583:
#line 2039 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildReduceExpr((yyvsp[-2].pexpr), (yyvsp[0].pcallexpr), true); }
#line 9081 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 584:
#line 2043 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildScanExpr((yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 9087 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 585:
#line 2044 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildScanExpr((yyvsp[-2].pexpr), (yyvsp[0].pcallexpr), true); }
#line 9093 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 586:
#line 2045 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildScanExpr((yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 9099 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 587:
#line 2046 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = buildScanExpr((yyvsp[-2].pexpr), (yyvsp[0].pcallexpr), true); }
#line 9105 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 588:
#line 2051 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new UnresolvedSymExpr("SumReduceScanOp"); }
#line 9111 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 589:
#line 2052 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new UnresolvedSymExpr("ProductReduceScanOp"); }
#line 9117 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 590:
#line 2053 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new UnresolvedSymExpr("LogicalAndReduceScanOp"); }
#line 9123 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 591:
#line 2054 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new UnresolvedSymExpr("LogicalOrReduceScanOp"); }
#line 9129 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 592:
#line 2055 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new UnresolvedSymExpr("BitwiseAndReduceScanOp"); }
#line 9135 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 593:
#line 2056 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new UnresolvedSymExpr("BitwiseOrReduceScanOp"); }
#line 9141 "bison-chapel.cpp" /* yacc.c:1663  */
    break;

  case 594:
#line 2057 "chapel.ypp" /* yacc.c:1663  */
    { (yyval.pexpr) = new UnresolvedSymExpr("BitwiseXorReduceScanOp"); }
#line 9147 "bison-chapel.cpp" /* yacc.c:1663  */
    break;


#line 9151 "bison-chapel.cpp" /* yacc.c:1663  */
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
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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
      yyerror (&yylloc, context, YY_("syntax error"));
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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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
        yyerror (&yylloc, context, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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
                      yytoken, &yylval, &yylloc, context);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp, context);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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
  yyerror (&yylloc, context, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, context);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp, context);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  yyps->yynew = 1;

yypushreturn:
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
