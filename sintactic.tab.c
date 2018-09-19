
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 14 "sintactic.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "sintactic.tab.h"
#include "symtab.h"
#include "cua.h"

typedef struct t_cadenaRegistreActivacio {
   char * nom;    
   int tam_tipus;
   int tipus;
   int es_array;
   long tam_array;
   long tam_total;
   long offset;
   struct t_cadenaRegistreActivacio * seguent;
} t_cadenaRegistreActivacio;

typedef struct t_registreActivacio {
    char * nom_registre;  
    long currentOffset; 
	int num_llista_parametres, num_llista_locals, num_llista_temporals;
	
	t_cadenaRegistreActivacio * primer_llista_parametres, * primer_llista_locals, * primer_llista_temporals;
	t_cadenaRegistreActivacio * ultim_llista_parametres, * ultim_llista_locals, * ultim_llista_temporals;
} t_registreActivacio;

typedef struct t_registreC3A {
	int num_quadruples;
	Cua * quadrupleC3A;
} t_registreC3A;

typedef struct t_quadrupleC3A {
	int num_sentencia;
	char * sentenciaC3A;
} t_quadrupleC3A;

FILE * fRegActivacio, * fCodi3A;
extern FILE * yyout;
extern int numFila;
extern int yyleng;
extern void yyerror(char * explanation);

int init_analisi_sintactic_O(char * fileOutput, char * nomFitxerRA, char * nomFitxerC3A);
int end_analisi_sintactic_O();
void init_analisi_sintactic(char * nomFitxerRA);
int analisi_semantic();
void printErrorSintactic(Boolean err, char * errorDesc, ...);
void printInfoSintactic(char * desc, ...);
int comprovacioTipusDades(Tipus_Dades t1, Tipus_Dades t2, int vsituacio);
Boolean identificadorDeclarat(char * idSimbol);
Boolean identificadorDeclaratMateixAmbit(char * idSimbol);
void printSimbolInfo(char * idSimbol);
char * tipusDadesID(int idTipus, int espais);
int checkOperadorIncDec(struct t_infoBison p1);
int esTipus(char * nom);
int campExisteixStruct(char * nomStruct, char * campStruct);
int campStructEsArray(char * nomStruct, char * campStruct);

int iniRegistreActivacio(t_registreActivacio * pRegistreActivacio, char * nom_registre);
int iniRegistreActivacioFuncions(char * nom_registre);
int iniC3A(t_registreC3A * pC3A);
int iniC3AFuncions();
void afegirParamRA(t_registreActivacio * pRegistreActivacio, char * nom_var, int tipus_var, int es_array, long tam_array);
void afegirVarLocalRA(t_registreActivacio * pRegistreActivacio, char * nom_var, struct t_simbol * simbol);
char * afegirVarTemporalRA(t_registreActivacio * pRegistreActivacio, int tipusVarTemp);
void printRegistreActivacio(t_registreActivacio * pRegistreActivacio);
void printRegistreActivacioGlobal(t_registreActivacio * pRegistreActivacio);
void printC3AFuncions(t_registreC3A * pC3A, char * nom_funcio);
int tamanyStruct(struct t_simbol * p1);
int tamanyStructbyInfoBison(struct t_infoBison * p1);
int offsetCampStruct(struct t_simbol * p1, char * nomCamp);
int tamanyTipusVar(int tipus);
int operacioC3A(Tipus_Dades t1, Tipus_Dades t2, int operacio);
void emet_cridaC3A(char * nom_funcio, struct t_infoBison * parametres, int tipus_retorn, struct t_infoBison * paramResult);
void emet_condicioC3A(struct t_infoBison * param1, struct t_infoBison * paramResult);
void emet_operacioC3A(struct t_infoBison * param1, struct t_infoBison * param2, struct t_infoBison * paramResult, int operacio);
void emet_operacioCanviSigneC3A(struct t_infoBison * param1, struct t_infoBison * paramResult);
void emet_arrayC3A(struct t_infoBison * paramResult, struct t_infoBison * paramArray, struct t_infoBison * paramArrayIndex);
void emet_structC3A(struct t_infoBison * paramStruct);
void emet_saltC3A(int num_linia);
void emet_retornFuncioC3A(struct t_infoBison * param1);
void completar_llista(Cua * llista, int seguent);

char * idSimbol;
char * nom_fitxerRA, * nom_fitxerC3A;
struct t_simbol simbol, simbol_tmp;
int currentScope;
long long tmpValor;
Boolean arrayDeclaracio = FALSE;
struct t_infoBison * pparam;
struct t_infoBison * pcamp;
struct t_infoBison * recordsetParam;
struct t_infoBison * recordsetCamp;
struct t_infoBison * tmpCondicio;
int num_errors;
int tipus_var_funcio_retorn;
char * valor_retorn;
struct Cua * llista_seguents_funcio_retorn;
int count;
int funcioDeclaradaCorrecte = FALSE;
Boolean errFuncDeclaration = FALSE;
t_registreActivacio * registreActivacioGlobal, * registreActivacioFuncions;
t_registreC3A * C3AGlobal, * C3AFuncions;
char strCastingC3A[4], strOperacioC3A[5];
t_quadrupleC3A * quadrupleC3A;
int conditional_if_while_for;
int tipus_var_tmp;


/* Line 189 of yacc.c  */
#line 186 "sintactic.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID_AUTO = 258,
     ID_BREAK = 259,
     ID_CASE = 260,
     ID_CHAR = 261,
     ID_CONST = 262,
     ID_CONTINUE = 263,
     ID_DEFAULT = 264,
     ID_DO = 265,
     ID_DOUBLE = 266,
     ID_ELSE = 267,
     ID_ENUM = 268,
     ID_EXTERN = 269,
     ID_FLOAT = 270,
     ID_FOR = 271,
     ID_GOTO = 272,
     ID_IF = 273,
     ID_INT = 274,
     ID_LONG = 275,
     ID_REGISTER = 276,
     ID_RETURN = 277,
     ID_SHORT = 278,
     ID_SIGNED = 279,
     ID_SIZEOF = 280,
     ID_STATIC = 281,
     ID_STRUCT = 282,
     ID_SWITCH = 283,
     ID_TYPEDEF = 284,
     ID_UNION = 285,
     ID_UNSIGNED = 286,
     ID_VOID = 287,
     ID_VOLATILE = 288,
     ID_WHILE = 289,
     ID_INC_OP = 290,
     ID_DEC_OP = 291,
     ID_LE_OP = 292,
     ID_GE_OP = 293,
     ID_EQ_OP = 294,
     ID_NE_OP = 295,
     ID_AND_OP = 296,
     ID_OR_OP = 297,
     ID_MUL_ASSIG = 298,
     ID_DIV_ASSIG = 299,
     ID_MOD_ASSIG = 300,
     ID_ADD_ASSIG = 301,
     ID_SUB_ASSIG = 302,
     ID_IDENTIFICADOR = 303,
     ID_TYPEDEF_IDENTIFIER = 304,
     ID_CHARACTER_CONSTANT = 305,
     ID_INTEGER_CONSTANT = 306,
     ID_FLOATING_CONSTANT = 307,
     ID_STRING = 308
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 146 "sintactic.y"
 	   
    struct t_infoBison {   
       char * valor;
       char * valorC3A;
       int constant;      
       int tipus_var;
       int array;
       long tam_array;
       int array_indexat;
       char * array_indexat_offset;
       int camp_struct_indexat;
       int offset_camp_struct_indexat;
       int funcio;
       int num_funcio_parametres;
       int num_struct_camps;
       struct t_infoBison * seguent_param_funcio;
       struct t_infoBison * seguent_camp_struct;
	   struct Cua * llista_certs;       
  	   struct Cua * llista_falsos;
	   struct Cua * llista_seguents;
	   int punter_quadruple;
       void * no_definit;	
    } infoBison;



/* Line 214 of yacc.c  */
#line 302 "sintactic.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 314 "sintactic.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  38
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1081

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  70
/* YYNRULES -- Number of rules.  */
#define YYNRULES  179
/* YYNRULES -- Number of states.  */
#define YYNSTATES  352

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   308

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    65,     2,     2,     2,    66,     2,     2,
      59,    60,    57,    55,    64,    56,    63,    58,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    70,    71,
      67,    54,    68,    69,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    61,     2,    62,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    72,     2,    73,     2,     2,     2,     2,
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
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    13,    15,    17,    19,
      21,    26,    30,    35,    39,    42,    45,    47,    51,    53,
      56,    59,    62,    65,    70,    72,    74,    76,    78,    83,
      85,    89,    93,    97,    99,   103,   107,   109,   113,   117,
     121,   125,   127,   131,   135,   137,   142,   144,   149,   151,
     157,   159,   161,   165,   167,   169,   171,   173,   175,   177,
     179,   183,   186,   190,   195,   197,   199,   203,   205,   209,
     211,   213,   215,   217,   219,   221,   223,   225,   227,   229,
     235,   240,   242,   244,   246,   249,   253,   255,   259,   261,
     263,   267,   272,   277,   282,   286,   288,   292,   295,   298,
     300,   302,   306,   308,   311,   314,   316,   320,   324,   329,
     332,   336,   340,   345,   347,   351,   356,   358,   362,   364,
     366,   368,   370,   372,   374,   379,   383,   386,   390,   394,
     399,   401,   405,   407,   410,   412,   417,   419,   423,   431,
     437,   438,   439,   449,   450,   461,   462,   477,   478,   492,
     493,   506,   507,   517,   518,   532,   533,   544,   545,   556,
     557,   569,   581,   584,   587,   590,   594,   596,   599,   601,
     603,   604,   609,   614,   615,   621,   625,   627,   630,   631
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     136,     0,    -1,    48,    -1,    76,    -1,    53,    -1,    59,
      92,    60,    -1,    51,    -1,    50,    -1,    52,    -1,    75,
      -1,    77,    61,    92,    62,    -1,    77,    59,    60,    -1,
      77,    59,    78,    60,    -1,    77,    63,    48,    -1,    77,
      35,    -1,    77,    36,    -1,    90,    -1,    78,    64,    90,
      -1,    77,    -1,    35,    79,    -1,    36,    79,    -1,    80,
      81,    -1,    25,    79,    -1,    25,    59,   109,    60,    -1,
      55,    -1,    56,    -1,    65,    -1,    79,    -1,    59,   109,
      60,    81,    -1,    81,    -1,    82,    57,    81,    -1,    82,
      58,    81,    -1,    82,    66,    81,    -1,    82,    -1,    83,
      55,    82,    -1,    83,    56,    82,    -1,    83,    -1,    84,
      67,    83,    -1,    84,    68,    83,    -1,    84,    37,    83,
      -1,    84,    38,    83,    -1,    84,    -1,    85,    39,    84,
      -1,    85,    40,    84,    -1,    85,    -1,    86,    41,   142,
      85,    -1,    86,    -1,    87,    42,   142,    86,    -1,    87,
      -1,    87,    69,    92,    70,    88,    -1,    88,    -1,    88,
      -1,    79,    91,    90,    -1,    54,    -1,    43,    -1,    44,
      -1,    45,    -1,    46,    -1,    47,    -1,    90,    -1,    92,
      64,    90,    -1,    94,    71,    -1,    94,    95,    71,    -1,
      29,    94,   105,    71,    -1,    97,    -1,    96,    -1,    95,
      64,    96,    -1,   105,    -1,   105,    54,   112,    -1,    32,
      -1,     6,    -1,    23,    -1,    19,    -1,    20,    -1,    15,
      -1,    11,    -1,    99,    -1,    98,    -1,    49,    -1,   100,
      48,    72,   101,    73,    -1,   100,    72,   101,    73,    -1,
      27,    -1,    30,    -1,   102,    -1,   101,   102,    -1,   110,
     103,    71,    -1,   104,    -1,   103,    64,   104,    -1,   105,
      -1,    48,    -1,    59,   105,    60,    -1,   105,    61,    51,
      62,    -1,   105,    59,   106,    60,    -1,   105,    59,   108,
      60,    -1,   105,    59,    60,    -1,   107,    -1,   106,    64,
     107,    -1,    94,   105,    -1,    94,   111,    -1,    94,    -1,
      48,    -1,   108,    64,    48,    -1,   110,    -1,   110,   111,
      -1,    97,   110,    -1,    97,    -1,    59,   111,    60,    -1,
      61,    51,    62,    -1,   111,    61,    51,    62,    -1,    59,
      60,    -1,    59,   106,    60,    -1,   111,    59,    60,    -1,
     111,    59,   106,    60,    -1,    90,    -1,    72,   113,    73,
      -1,    72,   113,    64,    73,    -1,   112,    -1,   113,    64,
     112,    -1,   115,    -1,   116,    -1,   118,    -1,   122,    -1,
     123,    -1,   135,    -1,     5,    89,    70,   114,    -1,     9,
      70,   114,    -1,    72,    73,    -1,    72,   141,    73,    -1,
      72,   117,    73,    -1,    72,   141,   117,    73,    -1,   114,
      -1,   117,   142,   114,    -1,    71,    -1,    92,    71,    -1,
      18,    -1,   119,    59,    92,    60,    -1,    16,    -1,   120,
     142,   114,    -1,   120,   142,   114,    12,   143,   142,   114,
      -1,    28,    59,    92,    60,   114,    -1,    -1,    -1,    34,
     124,    59,   142,    92,    60,   125,   142,   114,    -1,    -1,
      10,   142,   114,    34,   126,    59,   142,    92,    60,    71,
      -1,    -1,   121,    59,    92,    71,   142,    92,    71,   127,
     142,    92,    60,   143,   142,   114,    -1,    -1,   121,    59,
      71,   142,    92,    71,   128,   142,    92,    60,   143,   142,
     114,    -1,    -1,   121,    59,    71,   142,    71,   129,   142,
      92,    60,   143,   142,   114,    -1,    -1,   121,    59,    71,
     142,    71,   130,    60,   142,   114,    -1,    -1,   121,    59,
      92,    71,   142,    71,   131,   142,    92,    60,   143,   142,
     114,    -1,    -1,   121,    59,    92,    71,   142,    71,   132,
      60,   142,   114,    -1,    -1,   121,    59,    71,   142,    92,
      71,   133,    60,   142,   114,    -1,    -1,   121,    59,    92,
      71,   142,    92,    71,   134,    60,   142,   114,    -1,   121,
      59,    97,    92,     1,    71,     1,    71,     1,    60,   114,
      -1,     8,    71,    -1,     4,    71,    -1,    22,    71,    -1,
      22,    92,    71,    -1,   137,    -1,   136,   137,    -1,   138,
      -1,    93,    -1,    -1,   105,   139,   116,   142,    -1,    94,
     105,   141,   116,    -1,    -1,    94,   105,   140,   116,   142,
      -1,   105,   141,   116,    -1,    93,    -1,   141,    93,    -1,
      -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   208,   208,   214,   221,   230,   241,   248,   255,   268,
     288,   326,   352,   429,   461,   487,   519,   531,   553,   558,
     585,   611,   629,   635,   647,   650,   653,   662,   667,   676,
     681,   698,   723,   746,   751,   768,   791,   796,   815,   834,
     853,   878,   883,   902,   927,   932,   950,   955,   973,   978,
     989,  1000,  1005,  1085,  1090,  1095,  1100,  1105,  1110,  1121,
    1125,  1134,  1137,  1140,  1196,  1208,  1335,  1468,  1474,  1525,
    1530,  1535,  1540,  1545,  1550,  1555,  1560,  1566,  1577,  1611,
    1619,  1632,  1635,  1644,  1649,  1667,  1678,  1692,  1714,  1725,
    1731,  1736,  1751,  1759,  1767,  1781,  1794,  1816,  1822,  1825,
    1836,  1849,  1871,  1874,  1883,  1886,  1895,  1900,  1905,  1910,
    1913,  1918,  1923,  1934,  1939,  1942,  1951,  1956,  1967,  1971,
    1975,  1979,  1983,  1987,  1997,  2000,  2009,  2012,  2016,  2020,
    2030,  2034,  2045,  2048,  2057,  2064,  2074,  2081,  2087,  2094,
    2103,  2103,  2103,  2114,  2114,  2124,  2124,  2137,  2137,  2151,
    2151,  2174,  2174,  2195,  2195,  2218,  2218,  2239,  2239,  2250,
    2250,  2261,  2271,  2274,  2277,  2280,  2295,  2298,  2307,  2310,
    2319,  2319,  2506,  2509,  2509,  2707,  2716,  2719,  2727,  2734
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID_AUTO", "ID_BREAK", "ID_CASE",
  "ID_CHAR", "ID_CONST", "ID_CONTINUE", "ID_DEFAULT", "ID_DO", "ID_DOUBLE",
  "ID_ELSE", "ID_ENUM", "ID_EXTERN", "ID_FLOAT", "ID_FOR", "ID_GOTO",
  "ID_IF", "ID_INT", "ID_LONG", "ID_REGISTER", "ID_RETURN", "ID_SHORT",
  "ID_SIGNED", "ID_SIZEOF", "ID_STATIC", "ID_STRUCT", "ID_SWITCH",
  "ID_TYPEDEF", "ID_UNION", "ID_UNSIGNED", "ID_VOID", "ID_VOLATILE",
  "ID_WHILE", "ID_INC_OP", "ID_DEC_OP", "ID_LE_OP", "ID_GE_OP", "ID_EQ_OP",
  "ID_NE_OP", "ID_AND_OP", "ID_OR_OP", "ID_MUL_ASSIG", "ID_DIV_ASSIG",
  "ID_MOD_ASSIG", "ID_ADD_ASSIG", "ID_SUB_ASSIG", "ID_IDENTIFICADOR",
  "ID_TYPEDEF_IDENTIFIER", "ID_CHARACTER_CONSTANT", "ID_INTEGER_CONSTANT",
  "ID_FLOATING_CONSTANT", "ID_STRING", "'='", "'+'", "'-'", "'*'", "'/'",
  "'('", "')'", "'['", "']'", "'.'", "','", "'!'", "'%'", "'<'", "'>'",
  "'?'", "':'", "';'", "'{'", "'}'", "$accept", "primary_expression",
  "constant", "postfix_expression", "argument_expression_list",
  "unary_expression", "unary_operator", "cast_expression",
  "multiplicative_expression", "additive_expression",
  "relational_expression", "equality_expression", "logical_AND_expression",
  "logical_OR_expression", "conditional_expression", "constant_expression",
  "assignment_expression", "assignment_operator", "expression",
  "declaration", "declaration_specifiers", "init_declarator_list",
  "init_declarator", "type_specifier", "typedef_name",
  "struct_or_union_specifier", "struct_or_union",
  "struct_declaration_list", "struct_declaration",
  "struct_declarator_list", "struct_declarator", "declarator",
  "parameter_list", "parameter_declaration", "identifier_list",
  "type_name", "specifier_qualifier_list", "abstract_declarator",
  "initializer", "initializer_list", "statement", "labeled_statement",
  "compound_statement", "statement_list", "expression_statement",
  "if_token", "if_cond_header", "for_token", "selection_statement",
  "iteration_statement", "$@1", "$@2", "$@3", "$@4", "$@5", "$@6", "$@7",
  "$@8", "$@9", "$@10", "$@11", "jump_statement", "translation_unit",
  "external_declaration", "function_definition", "@12", "@13",
  "declaration_list", "M", "N", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,    61,    43,    45,    42,    47,    40,
      41,    91,    93,    46,    44,    33,    37,    60,    62,    63,
      58,    59,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    74,    75,    75,    75,    75,    76,    76,    76,    77,
      77,    77,    77,    77,    77,    77,    78,    78,    79,    79,
      79,    79,    79,    79,    80,    80,    80,    81,    81,    82,
      82,    82,    82,    83,    83,    83,    84,    84,    84,    84,
      84,    85,    85,    85,    86,    86,    87,    87,    88,    88,
      89,    90,    90,    91,    91,    91,    91,    91,    91,    92,
      92,    93,    93,    93,    94,    95,    95,    96,    96,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    98,    99,
      99,   100,   100,   101,   101,   102,   103,   103,   104,   105,
     105,   105,   105,   105,   105,   106,   106,   107,   107,   107,
     108,   108,   109,   109,   110,   110,   111,   111,   111,   111,
     111,   111,   111,   112,   112,   112,   113,   113,   114,   114,
     114,   114,   114,   114,   115,   115,   116,   116,   116,   116,
     117,   117,   118,   118,   119,   120,   121,   122,   122,   122,
     124,   125,   123,   126,   123,   127,   123,   128,   123,   129,
     123,   130,   123,   131,   123,   132,   123,   133,   123,   134,
     123,   123,   135,   135,   135,   135,   136,   136,   137,   137,
     139,   138,   138,   140,   138,   138,   141,   141,   142,   143
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     3,     1,     1,     1,     1,
       4,     3,     4,     3,     2,     2,     1,     3,     1,     2,
       2,     2,     2,     4,     1,     1,     1,     1,     4,     1,
       3,     3,     3,     1,     3,     3,     1,     3,     3,     3,
       3,     1,     3,     3,     1,     4,     1,     4,     1,     5,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     3,     4,     1,     1,     3,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     5,
       4,     1,     1,     1,     2,     3,     1,     3,     1,     1,
       3,     4,     4,     4,     3,     1,     3,     2,     2,     1,
       1,     3,     1,     2,     2,     1,     3,     3,     4,     2,
       3,     3,     4,     1,     3,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     4,     3,     2,     3,     3,     4,
       1,     3,     1,     2,     1,     4,     1,     3,     7,     5,
       0,     0,     9,     0,    10,     0,    14,     0,    13,     0,
      12,     0,     9,     0,    13,     0,    10,     0,    10,     0,
      11,    11,     2,     2,     2,     3,     1,     2,     1,     1,
       0,     4,     4,     0,     5,     3,     1,     2,     0,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    70,    75,    74,    72,    73,    71,    81,     0,    82,
      69,    89,    78,     0,   169,     0,    64,    77,    76,     0,
     170,     0,   166,   168,     0,     0,    61,     0,    65,    67,
       0,     0,     0,     0,   176,     0,     0,     0,     1,   167,
       0,    90,     0,    62,     0,     0,     0,     0,   105,     0,
      83,     0,   100,    94,    99,     0,    95,     0,     0,    67,
       0,   178,   177,   175,    63,    66,     0,     0,     0,     2,
       7,     6,     8,     4,    24,    25,     0,    26,     0,     9,
       3,    18,    27,     0,    29,    33,    36,    41,    44,    46,
      48,    51,   113,    68,   178,   172,     0,   104,    80,    84,
       0,    86,    88,     0,     0,    97,    98,    92,     0,    93,
       0,    91,     0,     0,     0,     0,   178,   136,   134,     0,
       0,   140,   132,   126,    59,     0,   130,   118,   119,   178,
     120,     0,   178,     0,   121,   122,   123,     0,   171,     0,
      22,     0,    19,    20,     0,     0,   102,   116,     0,    14,
      15,     0,     0,     0,    54,    55,    56,    57,    58,    53,
       0,    27,    21,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   178,   178,     0,   174,    79,     0,
      85,   109,     0,     0,     0,     0,     0,    96,   101,   163,
      50,     0,   162,     0,     0,   164,     0,     0,     0,     0,
     133,   128,     0,     0,     0,     0,   127,   178,     0,     5,
       0,     0,   103,     0,   114,    11,     0,    16,     0,    13,
      52,    30,    31,    32,    34,    35,    39,    40,    37,    38,
      42,    43,     0,     0,     0,    87,   110,   106,   107,   111,
       0,     0,     0,   125,     0,   165,     0,   178,    60,   131,
       0,   137,   178,     0,     0,   129,    23,    28,   115,   117,
      12,     0,    10,    45,    47,     0,   112,   108,   124,   143,
       0,     0,   135,   179,     0,   178,     0,    17,    49,     0,
     139,     0,   178,   149,     0,     0,     0,   178,   141,     0,
     178,     0,   147,   153,     0,     0,     0,   178,   138,     0,
     178,   178,     0,   178,     0,   145,     0,     0,     0,     0,
       0,     0,   178,     0,   178,   178,     0,     0,     0,   142,
     179,   152,     0,     0,     0,     0,     0,   178,     0,   144,
     178,   179,   158,   179,   156,     0,     0,     0,     0,   178,
     178,   179,   160,   161,   150,     0,     0,   178,   148,   154,
       0,   146
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    79,    80,    81,   216,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,   191,   124,   160,   125,    34,
      35,    27,    28,    16,    17,    18,    19,    49,    50,   100,
     101,    20,   182,    56,    57,   145,    51,   183,    93,   148,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     198,   297,   279,   315,   301,   290,   291,   303,   304,   302,
     316,   136,    21,    22,    23,    36,    45,    37,   202,   282
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -262
static const yytype_int16 yypact[] =
{
     832,  -262,  -262,  -262,  -262,  -262,  -262,  -262,   917,  -262,
    -262,  -262,  -262,    -1,  -262,   -20,  -262,  -262,  -262,   -22,
     729,   336,  -262,  -262,    -1,   189,  -262,    25,  -262,   589,
     -35,   917,   780,    52,  -262,   -20,    34,   153,  -262,  -262,
      23,  -262,    -1,  -262,   874,    34,   153,   917,   917,   253,
    -262,    -1,  -262,  -262,    15,    56,  -262,   101,    79,    67,
     406,  -262,  -262,  -262,  -262,  -262,   972,   994,   994,  -262,
    -262,  -262,  -262,  -262,  -262,  -262,   672,  -262,   874,  -262,
    -262,     6,    55,  1016,  -262,    61,   -33,    -7,    85,   111,
     -25,  -262,  -262,  -262,  -262,  -262,   297,  -262,  -262,  -262,
      33,  -262,     5,   723,   130,     5,    24,  -262,   917,  -262,
     136,  -262,   -31,  1016,   116,   137,  -262,  -262,  -262,    98,
     142,  -262,  -262,  -262,  -262,    58,  -262,  -262,  -262,   125,
    -262,   158,  -262,   172,  -262,  -262,  -262,   476,  -262,   672,
    -262,  1016,  -262,  -262,   102,   162,   131,  -262,    17,  -262,
    -262,   950,  1016,   190,  -262,  -262,  -262,  -262,  -262,  -262,
    1016,  -262,  -262,  1016,  1016,  1016,  1016,  1016,  1016,  1016,
    1016,  1016,  1016,  1016,  -262,  -262,  1016,  -262,  -262,    -1,
    -262,  -262,   114,   202,   175,   826,   192,  -262,  -262,  -262,
    -262,   174,  -262,   534,   534,  -262,    71,  1016,   187,  1016,
    -262,  -262,   534,  1016,   534,   617,  -262,   179,   195,  -262,
    1016,   774,    24,   842,  -262,  -262,   115,  -262,    68,  -262,
    -262,  -262,  -262,  -262,    61,    61,   -33,   -33,   -33,   -33,
      -7,    -7,  1016,  1016,   -32,  -262,  -262,  -262,  -262,  -262,
     133,   196,   534,  -262,   236,  -262,   139,  -262,  -262,  -262,
     140,   259,  -262,    72,  1016,  -262,  -262,  -262,  -262,  -262,
    -262,  1016,  -262,    85,   111,  1016,  -262,  -262,  -262,  -262,
     534,  1016,  -262,  -262,   906,  -262,    13,  -262,  -262,   215,
    -262,   146,  -262,   217,    76,   928,   204,  -262,  -262,   534,
    -262,   221,   222,   224,    96,   303,  1016,  -262,  -262,  1016,
    -262,  -262,   246,  -262,   247,   249,   239,   149,   534,   152,
     534,  1016,  -262,  1016,  -262,  -262,   251,   312,   243,  -262,
    -262,  -262,   160,   534,   163,   534,  1016,  -262,   255,  -262,
    -262,  -262,  -262,  -262,  -262,   168,   534,   534,   534,  -262,
    -262,  -262,  -262,  -262,  -262,   534,   534,  -262,  -262,  -262,
     534,  -262
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -262,  -262,  -262,  -262,  -262,   128,  -262,   -72,  -110,   119,
      62,    86,    88,  -262,  -107,  -262,   -43,  -262,   -66,     8,
       4,  -262,   277,   -28,  -262,  -262,  -262,   275,   -34,  -262,
     144,    -8,   -30,   220,  -262,   186,   -24,   -41,   -69,  -262,
      63,  -262,    42,   193,  -262,  -262,  -262,  -262,  -262,  -262,
    -262,  -262,  -262,  -262,  -262,  -262,  -262,  -262,  -262,  -262,
    -262,  -262,  -262,   310,  -262,  -262,  -262,   -11,   -61,  -261
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -174
static const yytype_int16 yytable[] =
{
     138,    92,    55,    48,    15,    25,   190,    29,    14,   147,
     144,   162,    24,   106,   286,    99,    40,   175,    46,    48,
      48,    48,   166,   167,    97,    15,    30,    59,    11,    14,
     168,   169,   199,   177,    59,    92,    54,    47,   265,    13,
     189,   149,   150,   102,   176,    62,   105,    11,    48,   137,
      31,    26,   146,   196,    62,   194,   224,   225,    13,   330,
     170,   171,    99,    11,    32,   151,    33,   152,    48,   153,
     339,   204,   340,   144,   103,   144,   104,   199,    61,    63,
     347,   213,    32,   185,    33,   186,   218,    94,    95,    42,
     214,   221,   222,   223,    64,    25,    43,   179,   154,   155,
     156,   157,   158,    58,   180,   212,    60,    54,   217,   159,
     234,    48,    54,   232,   233,   146,   107,   220,   163,   164,
     108,    44,   199,    66,   172,   173,    32,   165,    33,   200,
     262,   246,   199,    67,    68,   199,   199,   250,   257,   253,
     199,   111,   245,   275,   259,    62,    69,   292,    70,    71,
      72,    73,   174,    74,    75,   240,   248,    76,   278,     1,
     199,   109,   209,    77,     2,   110,   199,   305,     3,   195,
      92,   102,     4,     5,   236,   260,     6,   254,   108,   261,
       7,   184,     8,     9,   188,    10,   271,   192,   276,    54,
     211,   274,   104,   266,   140,   142,   143,   108,   201,   270,
     272,   197,    12,   199,   199,   281,   288,   193,   284,   318,
     199,   161,   320,   199,   285,    54,   199,   203,   277,   294,
     331,   289,   210,   333,   199,    60,   296,   199,   341,   299,
     307,   205,   199,   309,   230,   231,   308,   238,   219,   310,
     311,   161,   313,   241,   242,   322,   247,   324,    32,    41,
      33,   323,   255,   325,   326,   256,   243,   244,   267,     1,
     335,   185,   237,   186,     2,   249,   336,   251,     3,   338,
     269,   273,     4,     5,   287,   295,     6,  -151,   345,   346,
       7,   300,  -157,     9,  -155,    10,   350,   226,   227,   228,
     229,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     161,   161,    12,     1,   306,   268,   312,   314,     2,  -159,
     317,   327,     3,   328,   329,   337,     4,     5,   263,    65,
       6,   264,    96,   235,     7,   208,    98,     9,   187,    10,
     207,    39,     0,   280,     0,     0,    38,     0,   161,     0,
       0,     0,     1,     0,     0,     0,    12,     2,     0,     0,
       0,     3,   298,     0,     0,     4,     5,     0,     0,     6,
     161,   161,     0,     7,     0,     8,     9,     0,    10,     0,
     178,   319,     0,   321,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    11,    12,   332,     0,   334,     0,
       0,     0,     0,   161,     0,    13,     0,     0,     0,   342,
     343,   344,     0,     0,     0,     0,     0,     0,   348,   349,
     112,   113,     1,   351,   114,   115,   116,     2,     0,     0,
       0,     3,   117,     0,   118,     4,     5,     0,   119,     6,
       0,    66,     0,     7,   120,     8,     9,     0,    10,     0,
     121,    67,    68,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    69,    12,    70,    71,    72,    73,
       0,    74,    75,     0,     0,    76,     0,     0,     0,     0,
       0,    77,     0,     0,     0,     0,     0,   122,    60,   123,
     112,   113,     1,     0,   114,   115,   116,     2,     0,     0,
       0,     3,   117,     0,   118,     4,     5,     0,   119,     6,
       0,    66,     0,     7,   120,     8,     9,     0,    10,     0,
     121,    67,    68,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    69,    12,    70,    71,    72,    73,
       0,    74,    75,     0,     0,    76,     0,     0,   112,   113,
       0,    77,   114,   115,   116,     0,     0,   122,    60,   206,
     117,     0,   118,     0,     0,     0,   119,     0,     0,    66,
       0,     0,   120,     0,     0,     0,     0,     0,   121,    67,
      68,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    69,     0,    70,    71,    72,    73,     0,    74,
      75,     0,     0,    76,     0,     1,     0,     0,     0,    77,
       2,     0,     0,     0,     3,   122,    60,     0,     4,     5,
       0,     0,     6,     0,     0,     0,     7,     0,     8,     9,
       0,    10,     0,     1,     0,     0,     0,     0,     2,     0,
       0,     0,     3,     0,     0,     0,     4,     5,    12,     0,
       6,     0,    66,    44,     7,     0,     0,     9,    32,    10,
      33,     0,    67,    68,     0,     0,     0,     0,     0,     0,
       0,  -173,     0,     0,     0,    69,    12,    70,    71,    72,
      73,     0,    74,    75,     0,     0,    76,     0,     1,     0,
       0,     0,    77,     2,     0,     0,     0,     3,   252,     0,
       0,     4,     5,     0,     0,     6,     0,    66,     0,     7,
       0,     0,     9,     0,    10,     0,     0,    67,    68,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      69,    12,    70,    71,    72,    73,     0,    74,    75,     1,
       0,    76,     0,     0,     2,     1,     0,    77,     3,     0,
       2,     0,     4,     5,     3,     0,     6,     0,     4,     5,
       7,     0,     6,     9,     0,    10,     7,     0,     8,     9,
       0,    10,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    11,    12,     0,     0,     0,     0,     0,    12,     0,
       1,     0,   103,   181,   104,     2,     1,     0,    32,     3,
      33,     2,     0,     4,     5,     3,     0,     6,     0,     4,
       5,     7,     0,     6,     9,     0,    10,     7,     0,     0,
       9,     0,    10,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    12,     0,     0,     0,     0,    52,    12,
       0,     0,     1,   211,   181,   104,     0,     2,     1,     0,
      53,     3,     0,     2,     0,     4,     5,     3,     0,     6,
       0,     4,     5,     7,     0,     6,     9,     0,    10,     7,
       0,     8,     9,     0,    10,     0,     0,    66,     0,     0,
       0,     0,     0,     0,     0,    12,     0,    67,    68,     0,
      11,    12,     0,     0,     0,     0,   239,     0,     0,     0,
      69,    13,    70,    71,    72,    73,     0,    74,    75,    66,
       0,    76,     0,     0,     0,     0,     0,    77,     0,    67,
      68,     0,     0,     0,    78,   258,     0,     0,     0,     0,
       0,     0,    69,     1,    70,    71,    72,    73,     2,    74,
      75,    66,     3,    76,     0,     0,     4,     5,     0,    77,
       6,    67,    68,     0,     7,     0,    78,     9,     0,    10,
       0,     0,     0,    66,    69,     0,    70,    71,    72,    73,
       0,    74,    75,    67,    68,    76,    12,     0,     0,     0,
       0,    77,     0,     0,     0,    66,    69,   283,    70,    71,
      72,    73,     0,    74,    75,    67,    68,    76,     0,     0,
       0,     0,     0,    77,     0,     0,     0,    66,    69,   293,
      70,    71,    72,    73,     0,    74,    75,    67,    68,    76,
     215,     0,     0,     0,     0,    77,     0,     0,     0,    66,
      69,     0,    70,    71,    72,    73,     0,    74,    75,    67,
      68,   139,     0,     0,     0,     0,     0,    77,     0,     0,
       0,    66,    69,     0,    70,    71,    72,    73,     0,    74,
      75,    67,    68,   141,     0,     0,     0,     0,     0,    77,
       0,     0,     0,     0,    69,     0,    70,    71,    72,    73,
       0,    74,    75,     0,     0,    76,     0,     0,     0,     0,
       0,    77
};

static const yytype_int16 yycheck[] =
{
      61,    44,    32,    31,     0,    13,   113,    15,     0,    78,
      76,    83,     8,    54,     1,    49,    24,    42,    29,    47,
      48,    49,    55,    56,    48,    21,    48,    35,    48,    21,
      37,    38,    64,    94,    42,    78,    32,    72,    70,    59,
      71,    35,    36,    51,    69,    37,    54,    48,    76,    60,
      72,    71,    76,   119,    46,   116,   166,   167,    59,   320,
      67,    68,    96,    48,    59,    59,    61,    61,    96,    63,
     331,   132,   333,   139,    59,   141,    61,    64,    36,    37,
     341,    64,    59,    59,    61,    61,   152,    45,    46,    64,
      73,   163,   164,   165,    71,   103,    71,    64,    43,    44,
      45,    46,    47,    51,    71,   146,    72,   103,   151,    54,
     176,   139,   108,   174,   175,   139,    60,   160,    57,    58,
      64,    54,    64,    25,    39,    40,    59,    66,    61,    71,
      62,   197,    64,    35,    36,    64,    64,   203,   210,   205,
      64,    62,    71,    71,   213,   137,    48,    71,    50,    51,
      52,    53,    41,    55,    56,   185,   199,    59,   265,     6,
      64,    60,    60,    65,    11,    64,    64,    71,    15,    71,
     213,   179,    19,    20,    60,    60,    23,   205,    64,    64,
      27,    51,    29,    30,    48,    32,   247,    71,   254,   185,
      59,   252,    61,    60,    66,    67,    68,    64,    73,    60,
      60,    59,    49,    64,    64,   271,    60,    70,   274,    60,
      64,    83,    60,    64,   275,   211,    64,    59,   261,   285,
      60,   282,    60,    60,    64,    72,   287,    64,    60,   290,
     296,    59,    64,   299,   172,   173,   297,    62,    48,   300,
     301,   113,   303,    51,    70,   311,    59,   313,    59,    60,
      61,   312,    73,   314,   315,    60,   193,   194,    62,     6,
     326,    59,    60,    61,    11,   202,   327,   204,    15,   330,
      34,    12,    19,    20,    59,    71,    23,    60,   339,   340,
      27,    60,    60,    30,    60,    32,   347,   168,   169,   170,
     171,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,    49,     6,     1,   242,    60,    60,    11,    60,
      71,    60,    15,     1,    71,    60,    19,    20,   232,    42,
      23,   233,    47,   179,    27,   139,    73,    30,   108,    32,
     137,    21,    -1,   270,    -1,    -1,     0,    -1,   210,    -1,
      -1,    -1,     6,    -1,    -1,    -1,    49,    11,    -1,    -1,
      -1,    15,   289,    -1,    -1,    19,    20,    -1,    -1,    23,
     232,   233,    -1,    27,    -1,    29,    30,    -1,    32,    -1,
      73,   308,    -1,   310,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    49,   323,    -1,   325,    -1,
      -1,    -1,    -1,   265,    -1,    59,    -1,    -1,    -1,   336,
     337,   338,    -1,    -1,    -1,    -1,    -1,    -1,   345,   346,
       4,     5,     6,   350,     8,     9,    10,    11,    -1,    -1,
      -1,    15,    16,    -1,    18,    19,    20,    -1,    22,    23,
      -1,    25,    -1,    27,    28,    29,    30,    -1,    32,    -1,
      34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    49,    50,    51,    52,    53,
      -1,    55,    56,    -1,    -1,    59,    -1,    -1,    -1,    -1,
      -1,    65,    -1,    -1,    -1,    -1,    -1,    71,    72,    73,
       4,     5,     6,    -1,     8,     9,    10,    11,    -1,    -1,
      -1,    15,    16,    -1,    18,    19,    20,    -1,    22,    23,
      -1,    25,    -1,    27,    28,    29,    30,    -1,    32,    -1,
      34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    49,    50,    51,    52,    53,
      -1,    55,    56,    -1,    -1,    59,    -1,    -1,     4,     5,
      -1,    65,     8,     9,    10,    -1,    -1,    71,    72,    73,
      16,    -1,    18,    -1,    -1,    -1,    22,    -1,    -1,    25,
      -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,    34,    35,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    -1,    50,    51,    52,    53,    -1,    55,
      56,    -1,    -1,    59,    -1,     6,    -1,    -1,    -1,    65,
      11,    -1,    -1,    -1,    15,    71,    72,    -1,    19,    20,
      -1,    -1,    23,    -1,    -1,    -1,    27,    -1,    29,    30,
      -1,    32,    -1,     6,    -1,    -1,    -1,    -1,    11,    -1,
      -1,    -1,    15,    -1,    -1,    -1,    19,    20,    49,    -1,
      23,    -1,    25,    54,    27,    -1,    -1,    30,    59,    32,
      61,    -1,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    72,    -1,    -1,    -1,    48,    49,    50,    51,    52,
      53,    -1,    55,    56,    -1,    -1,    59,    -1,     6,    -1,
      -1,    -1,    65,    11,    -1,    -1,    -1,    15,    71,    -1,
      -1,    19,    20,    -1,    -1,    23,    -1,    25,    -1,    27,
      -1,    -1,    30,    -1,    32,    -1,    -1,    35,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    49,    50,    51,    52,    53,    -1,    55,    56,     6,
      -1,    59,    -1,    -1,    11,     6,    -1,    65,    15,    -1,
      11,    -1,    19,    20,    15,    -1,    23,    -1,    19,    20,
      27,    -1,    23,    30,    -1,    32,    27,    -1,    29,    30,
      -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    49,    -1,    -1,    -1,    -1,    -1,    49,    -1,
       6,    -1,    59,    60,    61,    11,     6,    -1,    59,    15,
      61,    11,    -1,    19,    20,    15,    -1,    23,    -1,    19,
      20,    27,    -1,    23,    30,    -1,    32,    27,    -1,    -1,
      30,    -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,    48,    49,
      -1,    -1,     6,    59,    60,    61,    -1,    11,     6,    -1,
      60,    15,    -1,    11,    -1,    19,    20,    15,    -1,    23,
      -1,    19,    20,    27,    -1,    23,    30,    -1,    32,    27,
      -1,    29,    30,    -1,    32,    -1,    -1,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    49,    -1,    35,    36,    -1,
      48,    49,    -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,
      48,    59,    50,    51,    52,    53,    -1,    55,    56,    25,
      -1,    59,    -1,    -1,    -1,    -1,    -1,    65,    -1,    35,
      36,    -1,    -1,    -1,    72,    73,    -1,    -1,    -1,    -1,
      -1,    -1,    48,     6,    50,    51,    52,    53,    11,    55,
      56,    25,    15,    59,    -1,    -1,    19,    20,    -1,    65,
      23,    35,    36,    -1,    27,    -1,    72,    30,    -1,    32,
      -1,    -1,    -1,    25,    48,    -1,    50,    51,    52,    53,
      -1,    55,    56,    35,    36,    59,    49,    -1,    -1,    -1,
      -1,    65,    -1,    -1,    -1,    25,    48,    71,    50,    51,
      52,    53,    -1,    55,    56,    35,    36,    59,    -1,    -1,
      -1,    -1,    -1,    65,    -1,    -1,    -1,    25,    48,    71,
      50,    51,    52,    53,    -1,    55,    56,    35,    36,    59,
      60,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    25,
      48,    -1,    50,    51,    52,    53,    -1,    55,    56,    35,
      36,    59,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,
      -1,    25,    48,    -1,    50,    51,    52,    53,    -1,    55,
      56,    35,    36,    59,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    -1,    -1,    -1,    48,    -1,    50,    51,    52,    53,
      -1,    55,    56,    -1,    -1,    59,    -1,    -1,    -1,    -1,
      -1,    65
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,    11,    15,    19,    20,    23,    27,    29,    30,
      32,    48,    49,    59,    93,    94,    97,    98,    99,   100,
     105,   136,   137,   138,    94,   105,    71,    95,    96,   105,
      48,    72,    59,    61,    93,    94,   139,   141,     0,   137,
     105,    60,    64,    71,    54,   140,   141,    72,    97,   101,
     102,   110,    48,    60,    94,   106,   107,   108,    51,   105,
      72,   116,    93,   116,    71,    96,    25,    35,    36,    48,
      50,    51,    52,    53,    55,    56,    59,    65,    72,    75,
      76,    77,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    90,   112,   116,   116,   101,   110,    73,   102,
     103,   104,   105,    59,    61,   105,   111,    60,    64,    60,
      64,    62,     4,     5,     8,     9,    10,    16,    18,    22,
      28,    34,    71,    73,    90,    92,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   135,   141,   142,    59,
      79,    59,    79,    79,    92,   109,   110,   112,   113,    35,
      36,    59,    61,    63,    43,    44,    45,    46,    47,    54,
      91,    79,    81,    57,    58,    66,    55,    56,    37,    38,
      67,    68,    39,    40,    41,    42,    69,   142,    73,    64,
      71,    60,   106,   111,    51,    59,    61,   107,    48,    71,
      88,    89,    71,    70,   142,    71,    92,    59,   124,    64,
      71,    73,   142,    59,   142,    59,    73,   117,   109,    60,
      60,    59,   111,    64,    73,    60,    78,    90,    92,    48,
      90,    81,    81,    81,    82,    82,    83,    83,    83,    83,
      84,    84,   142,   142,    92,   104,    60,    60,    62,    60,
     106,    51,    70,   114,   114,    71,    92,    59,    90,   114,
      92,   114,    71,    92,    97,    73,    60,    81,    73,   112,
      60,    64,    62,    85,    86,    70,    60,    62,   114,    34,
      60,   142,    60,    12,   142,    71,    92,    90,    88,   126,
     114,    92,   143,    71,    92,   142,     1,    59,    60,   142,
     129,   130,    71,    71,    92,    71,   142,   125,   114,   142,
      60,   128,   133,   131,   132,    71,     1,    92,   142,    92,
     142,   142,    60,   142,    60,   127,   134,    71,    60,   114,
      60,   114,    92,   142,    92,   142,   142,    60,     1,    71,
     143,    60,   114,    60,   114,    92,   142,    60,   142,   143,
     143,    60,   114,   114,   114,   142,   142,   143,   114,   114,
     142,   114
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

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
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;

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
     `$$ = $1'.

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

/* Line 1455 of yacc.c  */
#line 208 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      (yyval.infoBison).funcio = FALSE; 
      
      fprintf(yyout, ">>> linia %i: ID_IDENTIFICADOR -> [%s] REDUCE TO primary_expression\n", numFila, (yyvsp[(1) - (1)].infoBison).valor);     
   ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 214 "sintactic.y"
    { 
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      (yyval.infoBison).array = FALSE;
      (yyval.infoBison).tam_array = 0;
      
      fprintf(yyout, ">>> linia %i: constant REDUCE TO primary_expression\n", numFila); 
   ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 221 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      (yyval.infoBison).constant = TRUE;       
      (yyval.infoBison).tipus_var = TIPUS_STRING;
      (yyval.infoBison).array = FALSE;
      (yyval.infoBison).tam_array = 0;
            
      fprintf(yyout, ">>> linia %i: ID_STRING -> [%s] REDUCE TO primary_expression\n", numFila, (yyvsp[(1) - (1)].infoBison).valor);
   ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 230 "sintactic.y"
    { 
      (yyval.infoBison) = (yyvsp[(2) - (3)].infoBison);

      fprintf(yyout, ">>> linia %i: (expression) REDUCE TO primary_expression\n", numFila);
   ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 241 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      (yyval.infoBison).constant = TRUE;       
      (yyval.infoBison).tipus_var = TIPUS_INTEGER;
          
      fprintf(yyout, ">>> linia %i: ID_INTEGER_CONSTANT -> [%s] REDUCE TO constant\n", numFila, (yyvsp[(1) - (1)].infoBison).valor);    
   ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 248 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);                     
      (yyval.infoBison).constant = TRUE;       
      (yyval.infoBison).tipus_var = TIPUS_CHARACTER;
            
      fprintf(yyout, ">>> linia %i: ID_CHARACTER_CONSTANT -> [%s] REDUCE TO constant\n", numFila, (yyvsp[(1) - (1)].infoBison).valor);
   ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 255 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      (yyval.infoBison).constant = TRUE;       
      (yyval.infoBison).tipus_var = TIPUS_FLOAT;
      
      fprintf(yyout, ">>> linia %i: ID_FLOATING_CONSTANT -> [%s] REDUCE TO constant\n", numFila, (yyvsp[(1) - (1)].infoBison).valor);
   ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 268 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      
      if ((yyvsp[(1) - (1)].infoBison).constant != TRUE) {
         if (!identificadorDeclarat((yyvsp[(1) - (1)].infoBison).valor)) {
            (yyval.infoBison).tipus_var = TIPUS_NULL;
            if ((yyvsp[(1) - (1)].infoBison).funcio == TRUE) { num_errors++; printErrorSintactic(TRUE, ERR_NO_DECLARADA_FUNC_VAR, "funcio", (yyvsp[(1) - (1)].infoBison).valor); }               
            else { num_errors++; printErrorSintactic(TRUE, ERR_NO_DECLARADA_FUNC_VAR, "variable", (yyvsp[(1) - (1)].infoBison).valor); }
         }
         else {
            (yyval.infoBison).tipus_var = (yyvsp[(1) - (1)].infoBison).tipus_var;
            
            if (simbol.funcio == TRUE) printInfoSintactic(OK_CONSULTA_TAULA_SIMBOL_FUN_VAR, "funcio", (yyvsp[(1) - (1)].infoBison).valor);
            else printInfoSintactic(OK_CONSULTA_TAULA_SIMBOL_FUN_VAR, "variable", (yyvsp[(1) - (1)].infoBison).valor);
         }
      }
      else (yyval.infoBison).tipus_var = (yyvsp[(1) - (1)].infoBison).tipus_var;
         
      fprintf(yyout, ">>> linia %i: primary_expression REDUCE TO postfix_expression\n", numFila);
   ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 288 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (4)].infoBison);
      (yyval.infoBison).array = TRUE;
      (yyval.infoBison).tipus_var = TIPUS_NULL;
      
      if ((yyvsp[(1) - (4)].infoBison).constant != TRUE) {
         if (identificadorDeclarat((yyvsp[(1) - (4)].infoBison).valor)) {
            if (simbol.array == TRUE) {
               if ((yyvsp[(3) - (4)].infoBison).tipus_var < 5) {
                  if (atol((yyvsp[(3) - (4)].infoBison).valor) >= simbol.tam_array) {
                     num_errors++; printErrorSintactic(TRUE, ERR_INDEX_ARRAY_FORA_RANG, (yyvsp[(1) - (4)].infoBison).valor);
                  }
                  else { 
                     (yyval.infoBison).tipus_var = simbol.tipus_var; 
                     
                     if ((yyvsp[(1) - (4)].infoBison).valorC3A == NULL) {
                        (yyvsp[(1) - (4)].infoBison).valorC3A = malloc(strlen((yyvsp[(1) - (4)].infoBison).valor) + 1); 
                        strcpy((yyvsp[(1) - (4)].infoBison).valorC3A, (yyvsp[(1) - (4)].infoBison).valor);
                     }
                     if ((yyvsp[(3) - (4)].infoBison).valorC3A == NULL) {
                        (yyvsp[(3) - (4)].infoBison).valorC3A = malloc(strlen((yyvsp[(3) - (4)].infoBison).valor) + 1); 
                        strcpy((yyvsp[(3) - (4)].infoBison).valorC3A, (yyvsp[(3) - (4)].infoBison).valor);
                     }
                              
                     emet_arrayC3A(&(yyval.infoBison), &(yyvsp[(1) - (4)].infoBison), &(yyvsp[(3) - (4)].infoBison));
                     
                     printInfoSintactic(OK_INDEX_ARRAY, (yyvsp[(1) - (4)].infoBison).valor, (yyvsp[(3) - (4)].infoBison).valor);
                  }
               }
               else { num_errors++; printErrorSintactic(TRUE, ERR_INDEX_ARRAY_NO_INT, (yyvsp[(1) - (4)].infoBison).valor); }   
            }   
            else { num_errors++; printErrorSintactic(TRUE, ERR_VARIABLE_NO_ARRAY, (yyvsp[(1) - (4)].infoBison).valor); }
         }
      }
      else { num_errors++; printErrorSintactic(TRUE, ERR_CONSTANT_NO_VARIABLE, (yyvsp[(1) - (4)].infoBison).valor, "ARRAY"); }
      
      fprintf(yyout, ">>> linia %i: postfix_expression[expression] REDUCE TO postfix_expression\n", numFila);
   ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 326 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (3)].infoBison);                  
      (yyval.infoBison).funcio = TRUE;
      (yyval.infoBison).tipus_var = TIPUS_NULL;
      
      if ((yyvsp[(1) - (3)].infoBison).constant != TRUE) {
         if (identificadorDeclarat((yyvsp[(1) - (3)].infoBison).valor)) {
            if (simbol.funcio == TRUE) {
               if (simbol.num_funcio_parametres == 0) {
                  (yyval.infoBison).tipus_var = simbol.tipus_var;
                  
                  emet_cridaC3A((yyvsp[(1) - (3)].infoBison).valor, NULL, simbol.tipus_var, &(yyval.infoBison));
                  printInfoSintactic(OK_CRIDA_FUNCIO, (yyvsp[(1) - (3)].infoBison).valor);
               }
               else {
                  num_errors++;  
                  printErrorSintactic(TRUE, ERR_FUNCIO_PARAMS_INSUFICIENTS, (yyvsp[(1) - (3)].infoBison).valor);   
               }                   
            }
            else { num_errors++; printErrorSintactic(TRUE, ERR_VARIABLE_NO_FUNCIO, (yyvsp[(1) - (3)].infoBison).valor); }
         }
      }
      else { num_errors++; printErrorSintactic(TRUE, ERR_CONSTANT_NO_VARIABLE, (yyvsp[(1) - (3)].infoBison).valor, "FUNCIO"); }
      
      fprintf(yyout, ">>> linia %i: postfix_expression() REDUCE TO postfix_expression\n", numFila);
   ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 352 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (4)].infoBison);                  
      (yyval.infoBison).funcio = TRUE;
      (yyval.infoBison).tipus_var = TIPUS_NULL;
      
      funcioDeclaradaCorrecte = TRUE;
      if ((yyvsp[(1) - (4)].infoBison).constant != TRUE) {
         if (identificadorDeclarat((yyvsp[(1) - (4)].infoBison).valor)) {
            if (simbol.funcio == TRUE) {
               if (simbol.num_funcio_parametres == 0) {
                  num_errors++;                              
                  printErrorSintactic(TRUE, ERR_FUNCIO_PARAMS_EXCESIUS, (yyvsp[(1) - (4)].infoBison).valor);
               }
               else {
                  if (simbol.num_funcio_parametres != (yyvsp[(3) - (4)].infoBison).num_funcio_parametres) {
                     num_errors++;
                     printErrorSintactic(TRUE, ERR_FUNCIO_NUM_PARAMS_DIFERENTS, (yyvsp[(1) - (4)].infoBison).valor);  
                  }
                  else {
                     /* Numero de parametres correctes per cridar la funcio */
                     recordsetParam = (yyvsp[(3) - (4)].infoBison).seguent_param_funcio; 
                     for (count = 0; count < (yyvsp[(3) - (4)].infoBison).num_funcio_parametres; count++) {
                        if ((recordsetParam -> constant == FALSE) && (sym_lookup(recordsetParam -> valor, &simbol_tmp) != SYMTAB_OK)) {
                           funcioDeclaradaCorrecte = FALSE;
                        }
                        else {
                           if ((simbol.funcio_params[count].tipus_var != TIPUS_NULL) && (recordsetParam -> tipus_var != TIPUS_NULL)) {
                              if (recordsetParam -> constant == FALSE) {
                                 /* Si ens han passat una variable declarada => comprovacio de tipus i d'arrays */
                                 if ((simbol_tmp.array != TRUE) && (simbol.funcio_params[count].array == TRUE)) {
                                    num_errors++; funcioDeclaradaCorrecte = FALSE; printErrorSintactic(TRUE, ERR_FUNCIO_PARAM_ES_ARRAY, count + 1, (yyvsp[(1) - (4)].infoBison).valor);
                                 }
                                 /* Variable que ens passen es un array i la declaracio de la funcio no ho és: es poden donar 2 casos, que l'array s'accedeixi de forma indexada o no. */
                                 /* Forma no indexada es incorrecte */
                                 else if ((simbol_tmp.array == TRUE) && (simbol.funcio_params[count].array != TRUE) && (recordsetParam -> array != TRUE)) {
                                    num_errors++; funcioDeclaradaCorrecte = FALSE; printErrorSintactic(TRUE, ERR_FUNCIO_PARAM_NO_ES_ARRAY, count + 1, (yyvsp[(1) - (4)].infoBison).valor);
                                 }
                                 /* Forma en que els 2 casos son arrays, pero s'indexa => error */
                                 else if ((simbol_tmp.array == TRUE) && (simbol.funcio_params[count].array == TRUE) && (recordsetParam -> array == TRUE)) {
                                    num_errors++; funcioDeclaradaCorrecte = FALSE; printErrorSintactic(TRUE, ERR_FUNCIO_PARAM_ARRAY_METODE_ACCESS, count + 1, (yyvsp[(1) - (4)].infoBison).valor);
                                 }
                                 else {
                                    comprovacioTipusDades(simbol.funcio_params[count].tipus_var, recordsetParam -> tipus_var, ID_SITUACIO_FUNCIO);
                                 }
                              }
                              else {
                                 /* Si ens han passat una constant => comprovacio de tipus i d'array en la funcio */
                                 if (simbol.funcio_params[count].array == TRUE) {
                                    num_errors++; funcioDeclaradaCorrecte = FALSE; printErrorSintactic(TRUE, ERR_FUNCIO_PARAM_ES_ARRAY, count + 1, (yyvsp[(1) - (4)].infoBison).valor);   
                                 }
                                 else {
                                    comprovacioTipusDades(simbol.funcio_params[count].tipus_var, recordsetParam -> tipus_var, ID_SITUACIO_FUNCIO);
                                 }
                              }
                           }
                           else if (recordsetParam -> tipus_var == TIPUS_NULL) {
                              funcioDeclaradaCorrecte = FALSE;
                           }      
                        }
                        recordsetParam = recordsetParam -> seguent_param_funcio;
                     }
                     if (funcioDeclaradaCorrecte) {
                        (yyval.infoBison).tipus_var = simbol.tipus_var;
                        
                        emet_cridaC3A((yyvsp[(1) - (4)].infoBison).valor, &(yyvsp[(3) - (4)].infoBison), simbol.tipus_var, &(yyval.infoBison));
                        printInfoSintactic(OK_CRIDA_FUNCIO, (yyvsp[(1) - (4)].infoBison).valor);   
                     }
                     else { num_errors++; printErrorSintactic(TRUE, ERR_CRIDA_FUNCIO, (yyvsp[(1) - (4)].infoBison).valor); }
                  }
               }
            }
            else { num_errors++; printErrorSintactic(TRUE, ERR_VARIABLE_NO_FUNCIO, (yyvsp[(1) - (4)].infoBison).valor); }
         }                           
      }
      
      fprintf(yyout, ">>> linia %i: postfix_expression(argument_expression_list) REDUCE TO postfix_expression\n", numFila);
   ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 429 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (3)].infoBison);
      (yyval.infoBison).tipus_var = TIPUS_NULL;
      
      if ((yyvsp[(1) - (3)].infoBison).constant == TRUE) {
         num_errors++;                        
         printErrorSintactic(TRUE, ERR_STRUCT_CONSTANT);
      }
      else {
         if (identificadorDeclarat((yyvsp[(1) - (3)].infoBison).valor)) {
            if (simbol.tipus_var != TIPUS_STRUCT) {
               num_errors++;                  
               printErrorSintactic(TRUE, ERR_STRUCT_TIPUS_DIFERENT, (yyvsp[(1) - (3)].infoBison).valor);
            }
            else {
               (yyval.infoBison).tipus_var = campExisteixStruct((yyvsp[(1) - (3)].infoBison).valor, (yyvsp[(3) - (3)].infoBison).valor);
               if ((yyval.infoBison).tipus_var == TIPUS_NULL) {
                  num_errors++;
                  printErrorSintactic(TRUE, ERR_CAMP_NO_EXISTEIX_STRUCT, (yyvsp[(3) - (3)].infoBison).valor, (yyvsp[(1) - (3)].infoBison).valor);
               }
               else {
                  (yyval.infoBison).offset_camp_struct_indexat = offsetCampStruct(&simbol, (yyvsp[(3) - (3)].infoBison).valor);
                  (yyval.infoBison).camp_struct_indexat = TRUE;
                  
                  printInfoSintactic(OK_CAMP_EXISTEIX_STRUCT, (yyvsp[(3) - (3)].infoBison).valor, (yyvsp[(1) - (3)].infoBison).valor);
               }
            }
         }
      }
      
      fprintf(yyout, ">>> linia %i: postfix_expression.ID_IDENTIFICADOR -> [%s] REDUCE TO postfix_expression\n", numFila, (yyvsp[(3) - (3)].infoBison).valor);
   ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 461 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (2)].infoBison);
      (yyval.infoBison).tipus_var = TIPUS_NULL;
      
      if ((yyvsp[(1) - (2)].infoBison).constant == TRUE) {
         num_errors++;
         printErrorSintactic(TRUE, ERR_DEC_O_INC_CONSTANT, "incrementar");
      }
      else { 
         (yyval.infoBison).tipus_var = checkOperadorIncDec((yyvsp[(1) - (2)].infoBison));
         (yyvsp[(2) - (2)].infoBison).valorC3A = malloc(2); strcpy((yyvsp[(2) - (2)].infoBison).valorC3A, "1");
         
         if ((yyvsp[(1) - (2)].infoBison).valorC3A == NULL) {
            (yyvsp[(1) - (2)].infoBison).valorC3A = malloc(strlen((yyvsp[(1) - (2)].infoBison).valor) + 1); 
            strcpy((yyvsp[(1) - (2)].infoBison).valorC3A, (yyvsp[(1) - (2)].infoBison).valor);
         }
         (yyvsp[(2) - (2)].infoBison).constant = TRUE;
         (yyvsp[(2) - (2)].infoBison).tipus_var = TIPUS_INTEGER;     
         (yyvsp[(2) - (2)].infoBison).array_indexat = FALSE;
         (yyvsp[(2) - (2)].infoBison).camp_struct_indexat = FALSE;
             
         emet_operacioC3A(&(yyvsp[(1) - (2)].infoBison), &(yyvsp[(2) - (2)].infoBison), &(yyval.infoBison), '+');
         emet_operacioC3A(&(yyval.infoBison), NULL, &(yyvsp[(1) - (2)].infoBison), '=');
      }
      fprintf(yyout, ">>> linia %i: postfix_expression++ REDUCE TO postfix_expression\n", numFila);
   ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 487 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (2)].infoBison);
      (yyval.infoBison).tipus_var = TIPUS_NULL;
      
      if ((yyvsp[(1) - (2)].infoBison).constant == TRUE) {
         num_errors++;
         printErrorSintactic(TRUE, ERR_DEC_O_INC_CONSTANT, "decrementar");
      }
      else {
         (yyval.infoBison).tipus_var = checkOperadorIncDec((yyvsp[(1) - (2)].infoBison));
         (yyvsp[(2) - (2)].infoBison).valorC3A = malloc(2); strcpy((yyvsp[(2) - (2)].infoBison).valorC3A, "1");
         
         if ((yyvsp[(1) - (2)].infoBison).valorC3A == NULL) {
            (yyvsp[(1) - (2)].infoBison).valorC3A = malloc(strlen((yyvsp[(1) - (2)].infoBison).valor) + 1); 
            strcpy((yyvsp[(1) - (2)].infoBison).valorC3A, (yyvsp[(1) - (2)].infoBison).valor);
         }
         (yyvsp[(2) - (2)].infoBison).constant = TRUE;
         (yyvsp[(2) - (2)].infoBison).tipus_var = TIPUS_INTEGER;     
         (yyvsp[(2) - (2)].infoBison).array_indexat = FALSE;
         (yyvsp[(2) - (2)].infoBison).camp_struct_indexat = FALSE;
             
         emet_operacioC3A(&(yyvsp[(1) - (2)].infoBison), &(yyvsp[(2) - (2)].infoBison), &(yyval.infoBison), '-');
         emet_operacioC3A(&(yyval.infoBison), NULL, &(yyvsp[(1) - (2)].infoBison), '=');
      }
      fprintf(yyout, ">>> linia %i: postfix_expression-- REDUCE TO postfix_expression\n", numFila);
   ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 519 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      pparam = (struct t_infoBison *) malloc(sizeof(struct t_infoBison));
      *pparam = (yyvsp[(1) - (1)].infoBison);
      pparam->tipus_var = (yyvsp[(1) - (1)].infoBison).tipus_var;
      pparam->seguent_param_funcio = NULL;
      
      (yyval.infoBison).seguent_param_funcio = pparam;
      (yyval.infoBison).num_funcio_parametres = 1;
      
      fprintf(yyout, ">>> linia %i: assignment_expression REDUCE TO argument_expression_list\n", numFila);      
   ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 531 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (3)].infoBison);
      pparam = (struct t_infoBison *) malloc(sizeof(struct t_infoBison));
      *pparam = (yyvsp[(3) - (3)].infoBison);
      pparam->seguent_param_funcio = NULL;
      pparam->tipus_var = (yyvsp[(3) - (3)].infoBison).tipus_var;
      
      recordsetParam = (yyval.infoBison).seguent_param_funcio; 
      for (count = 1; count < (yyval.infoBison).num_funcio_parametres; count++) {
         recordsetParam = recordsetParam -> seguent_param_funcio;
      }
      recordsetParam -> seguent_param_funcio = pparam;
      (yyval.infoBison).num_funcio_parametres++;
      
      fprintf(yyout, ">>> linia %i: argument_expression_list,assignment_expression REDUCE TO argument_expression_list\n", numFila);  
   ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 553 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
       
      fprintf(yyout, ">>> linia %i: postfix_expression REDUCE TO unary_expression\n", numFila);    
   ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 558 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(2) - (2)].infoBison);
      (yyval.infoBison).tipus_var = TIPUS_NULL;
      
      if ((yyvsp[(2) - (2)].infoBison).constant == TRUE) {
         num_errors++;
         printErrorSintactic(TRUE, ERR_DEC_O_INC_CONSTANT, "incrementar");
      }
      else {
         (yyval.infoBison).tipus_var = checkOperadorIncDec((yyvsp[(2) - (2)].infoBison));
         (yyvsp[(1) - (2)].infoBison).valorC3A = malloc(2); strcpy((yyvsp[(1) - (2)].infoBison).valorC3A, "1");
         
         if ((yyvsp[(2) - (2)].infoBison).valorC3A == NULL) {
            (yyvsp[(2) - (2)].infoBison).valorC3A = malloc(strlen((yyvsp[(2) - (2)].infoBison).valor) + 1); 
            strcpy((yyvsp[(2) - (2)].infoBison).valorC3A, (yyvsp[(2) - (2)].infoBison).valor);
         }
         (yyvsp[(1) - (2)].infoBison).constant = TRUE;
         (yyvsp[(1) - (2)].infoBison).tipus_var = TIPUS_INTEGER;     
         (yyvsp[(1) - (2)].infoBison).array_indexat = FALSE;
         (yyvsp[(1) - (2)].infoBison).camp_struct_indexat = FALSE;
             
         emet_operacioC3A(&(yyvsp[(2) - (2)].infoBison), &(yyvsp[(1) - (2)].infoBison), &(yyval.infoBison), '+');
         emet_operacioC3A(&(yyval.infoBison), NULL, &(yyvsp[(2) - (2)].infoBison), '=');
      }
            
      fprintf(yyout, ">>> linia %i: ++unary_expression REDUCE TO unary_expression\n", numFila);      
   ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 585 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(2) - (2)].infoBison);
      (yyval.infoBison).tipus_var = TIPUS_NULL;
      
      if ((yyvsp[(2) - (2)].infoBison).constant == TRUE) {
         num_errors++;
         printErrorSintactic(TRUE, ERR_DEC_O_INC_CONSTANT, "decrementar");
      }
      else {
         (yyval.infoBison).tipus_var = checkOperadorIncDec((yyvsp[(2) - (2)].infoBison));
         (yyvsp[(1) - (2)].infoBison).valorC3A = malloc(2); strcpy((yyvsp[(1) - (2)].infoBison).valorC3A, "1");
         
         if ((yyvsp[(2) - (2)].infoBison).valorC3A == NULL) {
            (yyvsp[(2) - (2)].infoBison).valorC3A = malloc(strlen((yyvsp[(2) - (2)].infoBison).valor) + 1); 
            strcpy((yyvsp[(2) - (2)].infoBison).valorC3A, (yyvsp[(2) - (2)].infoBison).valor);
         }
         (yyvsp[(1) - (2)].infoBison).constant = TRUE;
         (yyvsp[(1) - (2)].infoBison).tipus_var = TIPUS_INTEGER;     
         (yyvsp[(1) - (2)].infoBison).array_indexat = FALSE;
         (yyvsp[(1) - (2)].infoBison).camp_struct_indexat = FALSE;
             
         emet_operacioC3A(&(yyvsp[(2) - (2)].infoBison), &(yyvsp[(1) - (2)].infoBison), &(yyval.infoBison), '-');
         emet_operacioC3A(&(yyval.infoBison), NULL, &(yyvsp[(2) - (2)].infoBison), '=');
      }      
      fprintf(yyout, ">>> linia %i: --unary_expression REDUCE TO unary_expression\n", numFila);
   ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 611 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(2) - (2)].infoBison);
      
      if (strcmp((yyvsp[(1) - (2)].infoBison).valor, "!") == 0) {
         (yyval.infoBison).llista_certs = (yyvsp[(2) - (2)].infoBison).llista_falsos;
         (yyval.infoBison).llista_falsos = (yyvsp[(2) - (2)].infoBison).llista_certs;
      }
      else if (strcmp((yyvsp[(1) - (2)].infoBison).valor, "-") == 0) {
         if ((yyvsp[(2) - (2)].infoBison).valorC3A == NULL) {
            (yyvsp[(2) - (2)].infoBison).valorC3A = malloc(strlen((yyvsp[(2) - (2)].infoBison).valor) + 1); 
            strcpy((yyvsp[(2) - (2)].infoBison).valorC3A, (yyvsp[(2) - (2)].infoBison).valor);
         }
         
         emet_operacioCanviSigneC3A(&(yyvsp[(2) - (2)].infoBison), &(yyval.infoBison));
      }
          
      fprintf(yyout, ">>> linia %i: unary_operator cast_expression REDUCE TO unary_expression\n", numFila);
   ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 629 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(2) - (2)].infoBison);
      (yyval.infoBison).tipus_var = TIPUS_INTEGER;
      
      fprintf(yyout, ">>> linia %i: ID_SIZEOF unary_expression REDUCE TO unary_expression\n", numFila);
   ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 635 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(2) - (4)].infoBison);
      (yyval.infoBison).tipus_var = TIPUS_INTEGER;
      
      fprintf(yyout, ">>> linia %i: ID_SIZEOF (type_name) REDUCE TO unary_expression\n", numFila);
   ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 647 "sintactic.y"
    { 
      fprintf(yyout, ">>> linia %i: '+' REDUCE TO unary_operator\n", numFila);   
   ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 650 "sintactic.y"
    {
      fprintf(yyout, ">>> linia %i: '-' REDUCE TO unary_operator\n", numFila);
   ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 653 "sintactic.y"
    {
      fprintf(yyout, ">>> linia %i: '!' REDUCE TO unary_operator\n", numFila);   
   ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 662 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      
      fprintf(yyout, ">>> linia %i: unary_expression REDUCE TO cast_expression\n", numFila);
   ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 667 "sintactic.y"
    {
      fprintf(yyout, ">>> linia %i: (type_name) cast_expression REDUCE TO cast_expression\n", numFila);
   ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 676 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      
      fprintf(yyout, ">>> linia %i: cast_expression REDUCE TO multiplicative_expression\n", numFila);
   ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 681 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (3)].infoBison); 
      (yyval.infoBison).tipus_var = checkOperadors((yyvsp[(1) - (3)].infoBison), (yyvsp[(3) - (3)].infoBison));  

      if ((yyvsp[(1) - (3)].infoBison).valorC3A == NULL) {
         (yyvsp[(1) - (3)].infoBison).valorC3A = malloc(strlen((yyvsp[(1) - (3)].infoBison).valor) + 1); 
         strcpy((yyvsp[(1) - (3)].infoBison).valorC3A, (yyvsp[(1) - (3)].infoBison).valor);
      }
      if ((yyvsp[(3) - (3)].infoBison).valorC3A == NULL) {
         (yyvsp[(3) - (3)].infoBison).valorC3A = malloc(strlen((yyvsp[(3) - (3)].infoBison).valor) + 1); 
         strcpy((yyvsp[(3) - (3)].infoBison).valorC3A, (yyvsp[(3) - (3)].infoBison).valor);
      }      
         
      emet_operacioC3A(&(yyvsp[(1) - (3)].infoBison), &(yyvsp[(3) - (3)].infoBison), &(yyval.infoBison), '*');
         
      fprintf(yyout, ">>> linia %i: multiplicative_expression '*' cast_expression REDUCE TO multiplicative_expression\n", numFila);
   ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 698 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (3)].infoBison);
      (yyval.infoBison).tipus_var = TIPUS_NULL;
      
      if (strcmp((yyvsp[(3) - (3)].infoBison).valor, "0") == 0) {
         num_errors++;
         printErrorSintactic(TRUE, ERR_DIVISIO_PER_ZERO);
      }
      else {
         (yyval.infoBison).tipus_var = checkOperadors((yyvsp[(1) - (3)].infoBison), (yyvsp[(3) - (3)].infoBison));
         
         if ((yyvsp[(1) - (3)].infoBison).valorC3A == NULL) {
            (yyvsp[(1) - (3)].infoBison).valorC3A = malloc(strlen((yyvsp[(1) - (3)].infoBison).valor) + 1); 
            strcpy((yyvsp[(1) - (3)].infoBison).valorC3A, (yyvsp[(1) - (3)].infoBison).valor);
         }
         if ((yyvsp[(3) - (3)].infoBison).valorC3A == NULL) {
            (yyvsp[(3) - (3)].infoBison).valorC3A = malloc(strlen((yyvsp[(3) - (3)].infoBison).valor) + 1); 
            strcpy((yyvsp[(3) - (3)].infoBison).valorC3A, (yyvsp[(3) - (3)].infoBison).valor);
         }      
         
         emet_operacioC3A(&(yyvsp[(1) - (3)].infoBison), &(yyvsp[(3) - (3)].infoBison), &(yyval.infoBison), '/');
      }
      
      fprintf(yyout, ">>> linia %i: multiplicative_expression '/' cast_expression REDUCE TO multiplicative_expression\n", numFila);
   ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 723 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (3)].infoBison);
      (yyval.infoBison).tipus_var = checkOperadors((yyvsp[(1) - (3)].infoBison), (yyvsp[(3) - (3)].infoBison));

      if ((yyvsp[(1) - (3)].infoBison).valorC3A == NULL) {
         (yyvsp[(1) - (3)].infoBison).valorC3A = malloc(strlen((yyvsp[(1) - (3)].infoBison).valor) + 1); 
         strcpy((yyvsp[(1) - (3)].infoBison).valorC3A, (yyvsp[(1) - (3)].infoBison).valor);
      }
      if ((yyvsp[(3) - (3)].infoBison).valorC3A == NULL) {
         (yyvsp[(3) - (3)].infoBison).valorC3A = malloc(strlen((yyvsp[(3) - (3)].infoBison).valor) + 1); 
         strcpy((yyvsp[(3) - (3)].infoBison).valorC3A, (yyvsp[(3) - (3)].infoBison).valor);
      }      
         
      emet_operacioC3A(&(yyvsp[(1) - (3)].infoBison), &(yyvsp[(3) - (3)].infoBison), &(yyval.infoBison), '%');
      
      fprintf(yyout, ">>> linia %i: multiplicative_expression %% cast_expression REDUCE TO multiplicative_expression\n", numFila);
   ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 746 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      
      fprintf(yyout, ">>> linia %i: multiplicative_expression REDUCE TO additive_expression\n", numFila);   
   ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 751 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (3)].infoBison);
      (yyval.infoBison).tipus_var = checkOperadors((yyvsp[(1) - (3)].infoBison), (yyvsp[(3) - (3)].infoBison));
      
      if ((yyvsp[(1) - (3)].infoBison).valorC3A == NULL) {
         (yyvsp[(1) - (3)].infoBison).valorC3A = malloc(strlen((yyvsp[(1) - (3)].infoBison).valor) + 1); 
         strcpy((yyvsp[(1) - (3)].infoBison).valorC3A, (yyvsp[(1) - (3)].infoBison).valor);
      }
      if ((yyvsp[(3) - (3)].infoBison).valorC3A == NULL) {
         (yyvsp[(3) - (3)].infoBison).valorC3A = malloc(strlen((yyvsp[(3) - (3)].infoBison).valor) + 1); 
         strcpy((yyvsp[(3) - (3)].infoBison).valorC3A, (yyvsp[(3) - (3)].infoBison).valor);
      }      
         
      emet_operacioC3A(&(yyvsp[(1) - (3)].infoBison), &(yyvsp[(3) - (3)].infoBison), &(yyval.infoBison), '+');
      
      fprintf(yyout, ">>> linia %i: additive_expression '+' multiplicative_expression REDUCE TO additive_expression\n", numFila);
   ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 768 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (3)].infoBison);
      (yyval.infoBison).tipus_var = checkOperadors((yyvsp[(1) - (3)].infoBison), (yyvsp[(3) - (3)].infoBison));

      if ((yyvsp[(1) - (3)].infoBison).valorC3A == NULL) {
         (yyvsp[(1) - (3)].infoBison).valorC3A = malloc(strlen((yyvsp[(1) - (3)].infoBison).valor) + 1); 
         strcpy((yyvsp[(1) - (3)].infoBison).valorC3A, (yyvsp[(1) - (3)].infoBison).valor);
      }
      if ((yyvsp[(3) - (3)].infoBison).valorC3A == NULL) {
         (yyvsp[(3) - (3)].infoBison).valorC3A = malloc(strlen((yyvsp[(3) - (3)].infoBison).valor) + 1); 
         strcpy((yyvsp[(3) - (3)].infoBison).valorC3A, (yyvsp[(3) - (3)].infoBison).valor);
      }      
         
      emet_operacioC3A(&(yyvsp[(1) - (3)].infoBison), &(yyvsp[(3) - (3)].infoBison), &(yyval.infoBison), '-');
      
      fprintf(yyout, ">>> linia %i: REDUCE additive_expression '-' multiplicative_expression REDUCE TO additive_expression\n", numFila);
   ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 791 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      
      fprintf(yyout, ">>> linia %i: additive_expression REDUCE TO relational_expression\n", numFila);
   ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 796 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (3)].infoBison);
      (yyval.infoBison).tipus_var = checkOperadors((yyvsp[(1) - (3)].infoBison), (yyvsp[(3) - (3)].infoBison));
      if ((yyval.infoBison).tipus_var != TIPUS_NULL) {
         (yyval.infoBison).tipus_var = TIPUS_INTEGER;
         if ((yyvsp[(1) - (3)].infoBison).valorC3A == NULL) {
            (yyvsp[(1) - (3)].infoBison).valorC3A = malloc(strlen((yyvsp[(1) - (3)].infoBison).valor) + 1); 
            strcpy((yyvsp[(1) - (3)].infoBison).valorC3A, (yyvsp[(1) - (3)].infoBison).valor);
         }
         if ((yyvsp[(3) - (3)].infoBison).valorC3A == NULL) {
            (yyvsp[(3) - (3)].infoBison).valorC3A = malloc(strlen((yyvsp[(3) - (3)].infoBison).valor) + 1); 
            strcpy((yyvsp[(3) - (3)].infoBison).valorC3A, (yyvsp[(3) - (3)].infoBison).valor);
         }

         emet_operacioC3A(&(yyvsp[(1) - (3)].infoBison), &(yyvsp[(3) - (3)].infoBison), &(yyval.infoBison), '<');                                       
         if (conditional_if_while_for == TRUE) emet_condicioC3A(&(yyval.infoBison), &(yyval.infoBison));
      }
      fprintf(yyout, ">>> linia %i: relational_expression '<' additive_expression REDUCE TO relational_expression\n", numFila);
   ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 815 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (3)].infoBison);
      (yyval.infoBison).tipus_var = checkOperadors((yyvsp[(1) - (3)].infoBison), (yyvsp[(3) - (3)].infoBison));
      if ((yyval.infoBison).tipus_var != TIPUS_NULL) {
         (yyval.infoBison).tipus_var = TIPUS_INTEGER;
         if ((yyvsp[(1) - (3)].infoBison).valorC3A == NULL) {
            (yyvsp[(1) - (3)].infoBison).valorC3A = malloc(strlen((yyvsp[(1) - (3)].infoBison).valor) + 1); 
            strcpy((yyvsp[(1) - (3)].infoBison).valorC3A, (yyvsp[(1) - (3)].infoBison).valor);
         }
         if ((yyvsp[(3) - (3)].infoBison).valorC3A == NULL) {
            (yyvsp[(3) - (3)].infoBison).valorC3A = malloc(strlen((yyvsp[(3) - (3)].infoBison).valor) + 1); 
            strcpy((yyvsp[(3) - (3)].infoBison).valorC3A, (yyvsp[(3) - (3)].infoBison).valor);
         }

         emet_operacioC3A(&(yyvsp[(1) - (3)].infoBison), &(yyvsp[(3) - (3)].infoBison), &(yyval.infoBison), '>');
         if (conditional_if_while_for == TRUE) emet_condicioC3A(&(yyval.infoBison), &(yyval.infoBison));     
      }
      fprintf(yyout, ">>> linia %i: relational_expression '>' additive_expression REDUCE TO relational_expression\n", numFila);
   ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 834 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (3)].infoBison);
      (yyval.infoBison).tipus_var = checkOperadors((yyvsp[(1) - (3)].infoBison), (yyvsp[(3) - (3)].infoBison));
      if ((yyval.infoBison).tipus_var != TIPUS_NULL) {
         (yyval.infoBison).tipus_var = TIPUS_INTEGER;
         if ((yyvsp[(1) - (3)].infoBison).valorC3A == NULL) {
            (yyvsp[(1) - (3)].infoBison).valorC3A = malloc(strlen((yyvsp[(1) - (3)].infoBison).valor) + 1); 
            strcpy((yyvsp[(1) - (3)].infoBison).valorC3A, (yyvsp[(1) - (3)].infoBison).valor);
         }
         if ((yyvsp[(3) - (3)].infoBison).valorC3A == NULL) {
            (yyvsp[(3) - (3)].infoBison).valorC3A = malloc(strlen((yyvsp[(3) - (3)].infoBison).valor) + 1); 
            strcpy((yyvsp[(3) - (3)].infoBison).valorC3A, (yyvsp[(3) - (3)].infoBison).valor);
         }

         emet_operacioC3A(&(yyvsp[(1) - (3)].infoBison), &(yyvsp[(3) - (3)].infoBison), &(yyval.infoBison), ID_LE_OP);
         if (conditional_if_while_for == TRUE) emet_condicioC3A(&(yyval.infoBison), &(yyval.infoBison));
      }      
      fprintf(yyout, ">>> linia %i: relational_expression <= additive_expression REDUCE TO relational_expression\n", numFila);
   ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 853 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (3)].infoBison);
      (yyval.infoBison).tipus_var = checkOperadors((yyvsp[(1) - (3)].infoBison), (yyvsp[(3) - (3)].infoBison));
      if ((yyval.infoBison).tipus_var != TIPUS_NULL) {
         (yyval.infoBison).tipus_var = TIPUS_INTEGER;
         if ((yyvsp[(1) - (3)].infoBison).valorC3A == NULL) {
            (yyvsp[(1) - (3)].infoBison).valorC3A = malloc(strlen((yyvsp[(1) - (3)].infoBison).valor) + 1); 
            strcpy((yyvsp[(1) - (3)].infoBison).valorC3A, (yyvsp[(1) - (3)].infoBison).valor);
         }
         if ((yyvsp[(3) - (3)].infoBison).valorC3A == NULL) {
            (yyvsp[(3) - (3)].infoBison).valorC3A = malloc(strlen((yyvsp[(3) - (3)].infoBison).valor) + 1); 
            strcpy((yyvsp[(3) - (3)].infoBison).valorC3A, (yyvsp[(3) - (3)].infoBison).valor);
         }

         emet_operacioC3A(&(yyvsp[(1) - (3)].infoBison), &(yyvsp[(3) - (3)].infoBison), &(yyval.infoBison), ID_GE_OP);
         if (conditional_if_while_for == TRUE) emet_condicioC3A(&(yyval.infoBison), &(yyval.infoBison));
      }      
      fprintf(yyout, ">>> linia %i: relational_expression >= additive_expression REDUCE TO relational_expression\n", numFila);
   ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 878 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
            
      fprintf(yyout, ">>> linia %i: relational_expression REDUCE TO equality_expression\n", numFila);
   ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 883 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (3)].infoBison);
      (yyval.infoBison).tipus_var = checkOperadors((yyvsp[(1) - (3)].infoBison), (yyvsp[(3) - (3)].infoBison));
      if ((yyval.infoBison).tipus_var != TIPUS_NULL) {
         (yyval.infoBison).tipus_var = TIPUS_INTEGER;
         if ((yyvsp[(1) - (3)].infoBison).valorC3A == NULL) {
            (yyvsp[(1) - (3)].infoBison).valorC3A = malloc(strlen((yyvsp[(1) - (3)].infoBison).valor) + 1); 
            strcpy((yyvsp[(1) - (3)].infoBison).valorC3A, (yyvsp[(1) - (3)].infoBison).valor);
         }
         if ((yyvsp[(3) - (3)].infoBison).valorC3A == NULL) {
            (yyvsp[(3) - (3)].infoBison).valorC3A = malloc(strlen((yyvsp[(3) - (3)].infoBison).valor) + 1); 
            strcpy((yyvsp[(3) - (3)].infoBison).valorC3A, (yyvsp[(3) - (3)].infoBison).valor);
         }

         emet_operacioC3A(&(yyvsp[(1) - (3)].infoBison), &(yyvsp[(3) - (3)].infoBison), &(yyval.infoBison), ID_EQ_OP);
         if (conditional_if_while_for == TRUE) emet_condicioC3A(&(yyval.infoBison), &(yyval.infoBison));
      }      
      fprintf(yyout, ">>> linia %i: equality_expression == relational_expression REDUCE TO equality_expression\n", numFila);
   ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 902 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (3)].infoBison);
      (yyval.infoBison).tipus_var = checkOperadors((yyvsp[(1) - (3)].infoBison), (yyvsp[(3) - (3)].infoBison));
      if ((yyval.infoBison).tipus_var != TIPUS_NULL) {
         (yyval.infoBison).tipus_var = TIPUS_INTEGER;
         if ((yyvsp[(1) - (3)].infoBison).valorC3A == NULL) {
            (yyvsp[(1) - (3)].infoBison).valorC3A = malloc(strlen((yyvsp[(1) - (3)].infoBison).valor) + 1); 
            strcpy((yyvsp[(1) - (3)].infoBison).valorC3A, (yyvsp[(1) - (3)].infoBison).valor);
         }
         if ((yyvsp[(3) - (3)].infoBison).valorC3A == NULL) {
            (yyvsp[(3) - (3)].infoBison).valorC3A = malloc(strlen((yyvsp[(3) - (3)].infoBison).valor) + 1); 
            strcpy((yyvsp[(3) - (3)].infoBison).valorC3A, (yyvsp[(3) - (3)].infoBison).valor);
         }

         emet_operacioC3A(&(yyvsp[(1) - (3)].infoBison), &(yyvsp[(3) - (3)].infoBison), &(yyval.infoBison), ID_NE_OP);
         if (conditional_if_while_for == TRUE) emet_condicioC3A(&(yyval.infoBison), &(yyval.infoBison));
      }      
      fprintf(yyout, ">>> linia %i: equality_expression <> relational_expression REDUCE TO equality_expression\n", numFila);
   ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 927 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      
      fprintf(yyout, ">>> linia %i: equality_expression REDUCE TO logical_AND_expression\n", numFila);   
   ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 932 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (4)].infoBison);
      (yyval.infoBison).tipus_var = checkOperadors((yyvsp[(1) - (4)].infoBison), (yyvsp[(4) - (4)].infoBison));
      if ((yyval.infoBison).tipus_var != TIPUS_NULL) {
         (yyval.infoBison).tipus_var = TIPUS_INTEGER;
         
         completar_llista((Cua *) (yyvsp[(1) - (4)].infoBison).llista_certs , (yyvsp[(3) - (4)].infoBison).punter_quadruple);
	     (yyval.infoBison).llista_certs = (yyvsp[(4) - (4)].infoBison).llista_certs;
	     (yyval.infoBison).llista_falsos = (struct Cua *) fusionar_cues(((Cua *) (yyvsp[(1) - (4)].infoBison).llista_falsos), ((Cua *) (yyvsp[(4) - (4)].infoBison).llista_falsos));   
      }
      fprintf(yyout, ">>> linia %i: logical_AND_expression && equality_expression REDUCE TO logical_AND_expression\n", numFila);
   ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 950 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      
      fprintf(yyout, ">>> linia %i: logical_AND_expression REDUCE TO logical_OR_expression\n", numFila);
   ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 955 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (4)].infoBison);
      (yyval.infoBison).tipus_var = checkOperadors((yyvsp[(1) - (4)].infoBison), (yyvsp[(4) - (4)].infoBison));
      if ((yyval.infoBison).tipus_var != TIPUS_NULL) {
         (yyval.infoBison).tipus_var = TIPUS_INTEGER;
         
         completar_llista((Cua *) (yyvsp[(1) - (4)].infoBison).llista_falsos , (yyvsp[(3) - (4)].infoBison).punter_quadruple);
	     (yyval.infoBison).llista_falsos = (yyvsp[(4) - (4)].infoBison).llista_falsos;
	     (yyval.infoBison).llista_certs = (struct Cua *) fusionar_cues(((Cua *) (yyvsp[(1) - (4)].infoBison).llista_certs), ((Cua *) (yyvsp[(4) - (4)].infoBison).llista_certs));
      }
      fprintf(yyout, ">>> linia %i: logical_OR_expression || logical_AND_expression REDUCE TO logical_OR_expression\n", numFila);   
   ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 973 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      
      fprintf(yyout, ">>> linia %i: logical_OR_expression REDUCE TO conditional_expression\n", numFila); 
   ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 978 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (5)].infoBison);
      
      fprintf(yyout, ">>> linia %i: logical_OR_expression '?' expression ':' conditional_expression REDUCE TO conditional_expression\n", numFila);
   ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 989 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      
      fprintf(yyout, ">>> linia %i: conditional_expression REDUCE TO constant_expression\n", numFila);
   ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 1000 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      
      fprintf(yyout, ">>> linia %i: conditional_expression REDUCE TO assignment_expression\n", numFila);
   ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 1005 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (3)].infoBison);
      
      if ((yyvsp[(1) - (3)].infoBison).constant == TRUE) {
         num_errors++;
         printErrorSintactic(TRUE, ERR_ASIGNACIO_CONSTANT, (yyvsp[(1) - (3)].infoBison).valor);   
      }
      else {
         if (identificadorDeclarat((yyvsp[(1) - (3)].infoBison).valor)) {
            if ((simbol.array == TRUE) && ((yyvsp[(1) - (3)].infoBison).array != TRUE)) {
               num_errors++;
               printErrorSintactic(TRUE, ERR_UTILITZACIO_ARRAY, (yyvsp[(1) - (3)].infoBison).valor);   
            }
            else {  
               if ((yyvsp[(3) - (3)].infoBison).constant == TRUE) {
                  if ((yyvsp[(1) - (3)].infoBison).valorC3A == NULL) {
                     (yyvsp[(1) - (3)].infoBison).valorC3A = malloc(strlen((yyvsp[(1) - (3)].infoBison).valor) + 1); 
                     strcpy((yyvsp[(1) - (3)].infoBison).valorC3A, (yyvsp[(1) - (3)].infoBison).valor);
                  }
                  if ((yyvsp[(3) - (3)].infoBison).valorC3A == NULL) {
                     (yyvsp[(3) - (3)].infoBison).valorC3A = malloc(strlen((yyvsp[(3) - (3)].infoBison).valor) + 1); 
                     strcpy((yyvsp[(3) - (3)].infoBison).valorC3A, (yyvsp[(3) - (3)].infoBison).valor);
                  }

                  if (strcmp((yyvsp[(2) - (3)].infoBison).valor, "=") != 0) {
                     emet_operacioC3A(&(yyvsp[(1) - (3)].infoBison), &(yyvsp[(3) - (3)].infoBison), &(yyval.infoBison), ((yyvsp[(2) - (3)].infoBison).valor)[0]);
                     emet_operacioC3A(&(yyval.infoBison), NULL, &(yyvsp[(1) - (3)].infoBison), '=');
                  }
                  else emet_operacioC3A(&(yyvsp[(3) - (3)].infoBison), NULL, &(yyvsp[(1) - (3)].infoBison), '=');
                  
                  if (strlen((yyvsp[(2) - (3)].infoBison).valor) == 1) { 
                     comprovacioTipusDades((yyvsp[(1) - (3)].infoBison).tipus_var, (yyvsp[(3) - (3)].infoBison).tipus_var, ID_SITUACIO_ASSIGNACIO);
                  }
                  else {
                     comprovacioTipusDades((yyvsp[(1) - (3)].infoBison).tipus_var, comprovacioTipusDades((yyvsp[(1) - (3)].infoBison).tipus_var, (yyvsp[(3) - (3)].infoBison).tipus_var, ID_SITUACIO_OPERACIO), ID_SITUACIO_ASSIGNACIO);
                  }
               }
               else {
                  if (identificadorDeclarat((yyvsp[(3) - (3)].infoBison).valor)) {
                     if ((simbol.array == TRUE) && ((yyvsp[(3) - (3)].infoBison).array != TRUE)) {
                        num_errors++;
                        printErrorSintactic(TRUE, ERR_UTILITZACIO_ARRAY, (yyvsp[(3) - (3)].infoBison).valor);   
                     }
                     else {
                        if ((yyvsp[(1) - (3)].infoBison).valorC3A == NULL) {
                           (yyvsp[(1) - (3)].infoBison).valorC3A = malloc(strlen((yyvsp[(1) - (3)].infoBison).valor) + 1); 
                           strcpy((yyvsp[(1) - (3)].infoBison).valorC3A, (yyvsp[(1) - (3)].infoBison).valor);
                        }
                        if ((yyvsp[(3) - (3)].infoBison).valorC3A == NULL) {
                           (yyvsp[(3) - (3)].infoBison).valorC3A = malloc(strlen((yyvsp[(3) - (3)].infoBison).valor) + 1); 
                           strcpy((yyvsp[(3) - (3)].infoBison).valorC3A, (yyvsp[(3) - (3)].infoBison).valor);
                        }
                        
                        if (strcmp((yyvsp[(2) - (3)].infoBison).valor, "=") != 0) {
                           emet_operacioC3A(&(yyvsp[(1) - (3)].infoBison), &(yyvsp[(3) - (3)].infoBison), &(yyval.infoBison), ((yyvsp[(2) - (3)].infoBison).valor)[0]);
                           emet_operacioC3A(&(yyval.infoBison), NULL, &(yyvsp[(1) - (3)].infoBison), '=');
                        }
                        else emet_operacioC3A(&(yyvsp[(3) - (3)].infoBison), NULL, &(yyvsp[(1) - (3)].infoBison), '=');  
                        
                        if (strlen((yyvsp[(2) - (3)].infoBison).valor) == 1) { 
                           comprovacioTipusDades((yyvsp[(1) - (3)].infoBison).tipus_var, (yyvsp[(3) - (3)].infoBison).tipus_var, ID_SITUACIO_ASSIGNACIO);
                        }
                        else {
                           comprovacioTipusDades((yyvsp[(1) - (3)].infoBison).tipus_var, comprovacioTipusDades((yyvsp[(1) - (3)].infoBison).tipus_var, (yyvsp[(3) - (3)].infoBison).tipus_var, ID_SITUACIO_OPERACIO), ID_SITUACIO_ASSIGNACIO);
                        }                     
                     }
                  }
               }
            }
         }
      }
      
      fprintf(yyout, ">>> linia %i: unary_expression assignment_operator assignment_expression REDUCE TO assignment_expression\n", numFila);
   ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 1085 "sintactic.y"
    { 
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      
      fprintf(yyout, ">>> linia %i: '=' REDUCE TO assignment_operator\n", numFila);
   ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 1090 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      
      fprintf(yyout, ">>> linia %i: *= REDUCE TO assignment_operator\n", numFila);
   ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 1095 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      
      fprintf(yyout, ">>> linia %i: /= REDUCE TO assignment_operator\n", numFila);
   ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 1100 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      
      fprintf(yyout, ">>> linia %i: %%= REDUCE TO assignment_operator\n", numFila);
   ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 1105 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      
      fprintf(yyout, ">>> linia %i: += REDUCE TO assignment_operator\n", numFila);
   ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 1110 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      
      fprintf(yyout, ">>> linia %i: -= REDUCE TO assignment_operator\n", numFila);
   ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 1121 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);  
      fprintf(yyout, ">>> linia %i: assignment_expression REDUCE TO expression\n", numFila);
   ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 1125 "sintactic.y"
    {
      fprintf(yyout, ">>> linia %i: expression,assignment_expression REDUCE TO expression\n", numFila);
   ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 1134 "sintactic.y"
    {
      fprintf(yyout, ">>> linia %i: declaration_specifiers; REDUCE TO declaration\n", numFila);
   ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 1137 "sintactic.y"
    {
      fprintf(yyout, ">>> linia %i: declaration_specifiers init_declarator_list; REDUCE TO declaration\n", numFila);
   ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 1140 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(3) - (4)].infoBison);
      (yyval.infoBison).tipus_var = (yyvsp[(2) - (4)].infoBison).tipus_var;
      idSimbol = (char *) malloc(strlen((yyvsp[(3) - (4)].infoBison).valor) + 1);
      strcpy(idSimbol, (yyvsp[(3) - (4)].infoBison).valor); 
      simbol.tipus_var = (yyvsp[(2) - (4)].infoBison).tipus_var;
      simbol.tipus = TIPUS_BASIC;
      simbol.idLexic = ID_TYPEDEF_IDENTIFIER;
      strcpy(simbol.nomLexic, "TYPEDEF_IDENTIFIER");
      currentScope = sym_get_scope();
      simbol.ambit = currentScope;
               
      if ((yyval.infoBison).tipus_var == TIPUS_STRUCT) {
         (yyval.infoBison).num_struct_camps = (yyvsp[(2) - (4)].infoBison).num_struct_camps;
         (yyval.infoBison).seguent_camp_struct = (yyvsp[(2) - (4)].infoBison).seguent_camp_struct;
         simbol.num_struct_camps = (yyvsp[(2) - (4)].infoBison).num_struct_camps;

         if (simbol.num_struct_camps > 0) {
            simbol.struct_camps = malloc(sizeof(struct t_param) * (yyvsp[(2) - (4)].infoBison).num_struct_camps);
          
            recordsetCamp = (yyvsp[(2) - (4)].infoBison).seguent_camp_struct;
            for (count = 0; (count < (yyvsp[(2) - (4)].infoBison).num_struct_camps); count++) {
               simbol.struct_camps[count].valor = malloc(strlen(recordsetCamp -> valor) + 1);
               strcpy(simbol.struct_camps[count].valor, recordsetCamp -> valor); 
            
               simbol.struct_camps[count].tipus_var = recordsetCamp -> tipus_var;
               if (recordsetCamp -> array == TRUE) {
                  simbol.struct_camps[count].array = TRUE;
                  simbol.struct_camps[count].tam_array = recordsetCamp -> tam_array;
               }
               else {
                  simbol.struct_camps[count].array = FALSE;
                  simbol.struct_camps[count].tam_array = 0;
               }
               recordsetCamp = recordsetCamp -> seguent_camp_struct;
            }
         }
      }
             
      if (sym_lookup((yyvsp[(3) - (4)].infoBison).valor, &simbol_tmp) == SYMTAB_OK) {
         num_errors++;
         printErrorSintactic(TRUE, ERR_REDECLARACIO_TIPUS, idSimbol);
      }
      else {
         if (sym_add((char *) idSimbol, &simbol) != SYMTAB_OK) { num_errors++; printErrorSintactic(TRUE, ERR_INTRODUCCIO_TAULA_SIMBOL_TIPUS, idSimbol); }
         else { printInfoSintactic(OK_INTRODUCCIO_TAULA_SIMBOL_TIPUS, idSimbol); printSimbolInfo((char *) idSimbol); }
      }
              
      fprintf(yyout, ">>> linia %i: ID_TYPEDEF declaration_specifiers declarator; REDUCE TO declaration\n", numFila);
   ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 1196 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      tipus_var_tmp = (yyvsp[(1) - (1)].infoBison).tipus_var;
          
      fprintf(yyout, ">>> linia %i: type_specifier REDUCE TO declaration_specifiers\n", numFila);
   ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 1208 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(0) - (1)].infoBison);
      
      errFuncDeclaration = FALSE;
      
      if ((yyvsp[(1) - (1)].infoBison).tipus_var != TIPUS_NULL) comprovacioTipusDades((yyvsp[(0) - (1)].infoBison).tipus_var, (yyvsp[(1) - (1)].infoBison).tipus_var, ID_SITUACIO_ASSIGNACIO);
      
      idSimbol = (char *) malloc(strlen((yyvsp[(1) - (1)].infoBison).valor) + 1);
      strcpy(idSimbol, (yyvsp[(1) - (1)].infoBison).valor);
      simbol.tipus_var = (yyvsp[(0) - (1)].infoBison).tipus_var;
      
      if ((yyvsp[(1) - (1)].infoBison).funcio == TRUE) {
         simbol.tipus = FUNCIO;
         simbol.funcio = TRUE;
         simbol.num_funcio_parametres = (yyvsp[(1) - (1)].infoBison).num_funcio_parametres;
      }
      else {
         simbol.tipus = VARIABLE;
         simbol.funcio = FALSE; 
         simbol.num_funcio_parametres = 0;
         if ((yyvsp[(0) - (1)].infoBison).tipus_var == TIPUS_STRUCT) {      
            simbol.tipus_var = TIPUS_STRUCT;
            simbol.num_struct_camps = (yyvsp[(0) - (1)].infoBison).num_struct_camps;
         }
      }
      
      simbol.idLexic = ID_IDENTIFICADOR;
      strcpy(simbol.nomLexic, "IDENTIFICADOR"); 
      if ((yyvsp[(1) - (1)].infoBison).array == TRUE) {
         simbol.array = TRUE;
         simbol.tam_array = (yyvsp[(1) - (1)].infoBison).tam_array;
      }
      else simbol.array = FALSE;
      
      if (simbol.funcio == TRUE) {
          if ((yyvsp[(1) - (1)].infoBison).num_funcio_parametres == 1) {
             if (((yyvsp[(1) - (1)].infoBison).seguent_param_funcio -> tipus_var == TIPUS_VOID) && (!esTipus((yyvsp[(1) - (1)].infoBison).seguent_param_funcio -> valor))) {
                num_errors++;
                errFuncDeclaration = TRUE;
                printErrorSintactic(TRUE, ERR_PARAMETRE_FUNCIO_VOID);
             }
             else if ((yyvsp[(1) - (1)].infoBison).seguent_param_funcio -> tipus_var == TIPUS_VOID) {
                (yyvsp[(1) - (1)].infoBison).num_funcio_parametres--;
                simbol.num_funcio_parametres = 0;
             }
          }

          if (!errFuncDeclaration) {
             simbol.funcio_params = malloc(sizeof(struct t_param) * (yyvsp[(1) - (1)].infoBison).num_funcio_parametres);
          
             recordsetParam = (yyvsp[(1) - (1)].infoBison).seguent_param_funcio;
             for (count = 0; ((count < (yyvsp[(1) - (1)].infoBison).num_funcio_parametres) && (!errFuncDeclaration)); count++) {
                if (recordsetParam -> tipus_var == TIPUS_VOID) {
                   num_errors++;
                   errFuncDeclaration = TRUE;
                   printErrorSintactic(TRUE, ERR_PARAMETRE_FUNCIO_VOID);
                }
                else {
                   simbol.funcio_params[count].tipus_var = recordsetParam -> tipus_var;
                   if (recordsetParam -> array == TRUE) {
                      simbol.funcio_params[count].array = TRUE;
                      simbol.funcio_params[count].tam_array = recordsetParam -> tam_array;
                   }
                   else {
                      simbol.funcio_params[count].array = FALSE;
                      simbol.funcio_params[count].tam_array = 0;
                   }
                }
                recordsetParam = recordsetParam -> seguent_param_funcio;
             }
          } 
      }
      else if (simbol.tipus_var == TIPUS_STRUCT) {
         simbol.struct_camps = malloc(sizeof(struct t_param) * (yyvsp[(0) - (1)].infoBison).num_struct_camps);
          
         recordsetCamp = (yyvsp[(0) - (1)].infoBison).seguent_camp_struct;
         for (count = 0; (count < (yyvsp[(0) - (1)].infoBison).num_struct_camps); count++) {
            simbol.struct_camps[count].valor = malloc(strlen(recordsetCamp -> valor) + 1); 
            strcpy(simbol.struct_camps[count].valor, recordsetCamp -> valor); 
            
            simbol.struct_camps[count].tipus_var = recordsetCamp -> tipus_var;
            if (recordsetCamp -> array == TRUE) {
               simbol.struct_camps[count].array = TRUE;
               simbol.struct_camps[count].tam_array = recordsetCamp -> tam_array;
            }
            else {
               simbol.struct_camps[count].array = FALSE;
               simbol.struct_camps[count].tam_array = 0;
            }
            recordsetCamp = recordsetCamp -> seguent_camp_struct;
         }
      }          
      
      if (!errFuncDeclaration) {
         if (identificadorDeclaratMateixAmbit((yyvsp[(1) - (1)].infoBison).valor)) {
            if (simbol_tmp.funcio == TRUE) { num_errors++; printErrorSintactic(TRUE, ERR_REDECLARACIO_FUNC_VAR, "funcio", idSimbol); }
            else { num_errors++; printErrorSintactic(TRUE, ERR_REDECLARACIO_FUNC_VAR, "variable", idSimbol); }
         }
         else {
            if (simbol.funcio == TRUE) {
               simbol.ambit = -1;
               if (sym_global_add((char *) idSimbol, &simbol) != SYMTAB_OK) {
                  num_errors++; printErrorSintactic(TRUE, ERR_INTRODUCCIO_TAULA_SIMBOL_FUNC_VAR, "funcio", idSimbol);
               }
               else { 
                  printInfoSintactic(OK_INTRODUCCIO_TAULA_SIMBOL_FUN_VAR, "funcio", idSimbol);
               }
            }
            else {
               currentScope = sym_get_scope();
               simbol.ambit = currentScope;
               if (sym_add((char *) idSimbol, &simbol) != SYMTAB_OK) {
                  num_errors++; printErrorSintactic(TRUE, ERR_INTRODUCCIO_TAULA_SIMBOL_FUNC_VAR, "variable", idSimbol);
               }
               else { 
                  if (currentScope == -1) afegirVarLocalRA(registreActivacioGlobal, idSimbol, &simbol);
                  else afegirVarLocalRA(registreActivacioFuncions, idSimbol, &simbol);

                  printInfoSintactic(OK_INTRODUCCIO_TAULA_SIMBOL_FUN_VAR, "variable", idSimbol);
               }
            }
            printSimbolInfo((char *) idSimbol);
         }
      }
      
      fprintf(yyout, ">>> linia %i: init_declarator REDUCE TO init_declarator_list\n", numFila);
   ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 1335 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (3)].infoBison);
      errFuncDeclaration = FALSE;
      
      if ((yyvsp[(3) - (3)].infoBison).tipus_var != TIPUS_NULL) comprovacioTipusDades((yyvsp[(0) - (3)].infoBison).tipus_var, (yyvsp[(3) - (3)].infoBison).tipus_var, ID_SITUACIO_ASSIGNACIO);
      
      idSimbol = (char *) malloc(strlen((yyvsp[(3) - (3)].infoBison).valor) + 1);
      strcpy(idSimbol, (yyvsp[(3) - (3)].infoBison).valor);
      simbol.tipus_var = (yyvsp[(1) - (3)].infoBison).tipus_var;
      
      if ((yyvsp[(3) - (3)].infoBison).funcio == TRUE) {
         simbol.tipus = FUNCIO;
         simbol.funcio = TRUE;
         simbol.num_funcio_parametres = (yyvsp[(3) - (3)].infoBison).num_funcio_parametres;
      }
      else {
         simbol.tipus = VARIABLE;
         simbol.funcio = FALSE; 
         simbol.num_funcio_parametres = 0;
         if ((yyvsp[(1) - (3)].infoBison).tipus_var == TIPUS_STRUCT) {      
            simbol.tipus_var = TIPUS_STRUCT;
            simbol.num_struct_camps = (yyvsp[(0) - (3)].infoBison).num_struct_camps;
         }
      }
      
      simbol.idLexic = ID_IDENTIFICADOR;
      strcpy(simbol.nomLexic, "IDENTIFICADOR");
      currentScope = sym_get_scope();
      simbol.ambit = currentScope;
      
      if ((yyvsp[(3) - (3)].infoBison).array == TRUE) {
         simbol.array = TRUE;
         simbol.tam_array = (yyvsp[(3) - (3)].infoBison).tam_array;
      }
      else simbol.array = FALSE;
      
      if (simbol.funcio == TRUE) {
          if ((yyvsp[(3) - (3)].infoBison).num_funcio_parametres == 1) {
             if (((yyvsp[(3) - (3)].infoBison).seguent_param_funcio -> tipus_var == TIPUS_VOID) && (!esTipus((yyvsp[(3) - (3)].infoBison).seguent_param_funcio -> valor))) {
                errFuncDeclaration = TRUE;
                num_errors++; printErrorSintactic(TRUE, ERR_PARAMETRE_FUNCIO_VOID);
             }
             else if ((yyvsp[(3) - (3)].infoBison).seguent_param_funcio -> tipus_var == TIPUS_VOID) {
                (yyvsp[(3) - (3)].infoBison).num_funcio_parametres--;
                simbol.num_funcio_parametres = 0;
             }
          }

          if (!errFuncDeclaration) {
             simbol.funcio_params = malloc(sizeof(struct t_param) * (yyvsp[(3) - (3)].infoBison).num_funcio_parametres);
             
             recordsetParam = (yyvsp[(3) - (3)].infoBison).seguent_param_funcio;
             for (count = 0; ((count < (yyvsp[(3) - (3)].infoBison).num_funcio_parametres) && (!errFuncDeclaration)); count++) {
                if (recordsetParam -> tipus_var == TIPUS_VOID) {
                   errFuncDeclaration = TRUE;
                   num_errors++; printErrorSintactic(TRUE, ERR_PARAMETRE_FUNCIO_VOID);
                }
                else {
                   simbol.funcio_params[count].tipus_var = recordsetParam -> tipus_var;
                   if (recordsetParam -> array == TRUE) {
                      simbol.funcio_params[count].array = TRUE;
                      simbol.funcio_params[count].tam_array = recordsetParam -> tam_array;
                   }
                   else {
                      simbol.funcio_params[count].array = FALSE;
                      simbol.funcio_params[count].tam_array = 0;
                   }
                }
                recordsetParam = recordsetParam -> seguent_param_funcio;
             }
          }
      }
      else if (simbol.tipus_var == TIPUS_STRUCT) {
         simbol.struct_camps = malloc(sizeof(struct t_param) * (yyvsp[(0) - (3)].infoBison).num_struct_camps);
          
         recordsetCamp = (yyvsp[(0) - (3)].infoBison).seguent_camp_struct;
         for (count = 0; (count < (yyvsp[(0) - (3)].infoBison).num_struct_camps); count++) {
            simbol.struct_camps[count].valor = malloc(strlen(recordsetCamp -> valor) + 1);
            strcpy(simbol.struct_camps[count].valor, recordsetCamp -> valor); 
            
            simbol.struct_camps[count].tipus_var = recordsetCamp -> tipus_var;
            if (recordsetCamp -> array == TRUE) {
               simbol.struct_camps[count].array = TRUE;
               simbol.struct_camps[count].tam_array = recordsetCamp -> tam_array;
            }
            else {
               simbol.struct_camps[count].array = FALSE;
               simbol.struct_camps[count].tam_array = 0;
            }
            recordsetCamp = recordsetCamp -> seguent_camp_struct;
         }
      }
      
      if (!errFuncDeclaration) {
         if (identificadorDeclaratMateixAmbit((yyvsp[(3) - (3)].infoBison).valor)) {
            if (simbol_tmp.funcio == TRUE) { num_errors++; printErrorSintactic(TRUE, ERR_REDECLARACIO_FUNC_VAR, "funcio", idSimbol); }
            else { num_errors++; printErrorSintactic(TRUE, ERR_REDECLARACIO_FUNC_VAR, "variable", idSimbol); }
         }
         else {
            if (simbol.funcio == TRUE) {
               simbol.ambit = -1;
               if (sym_global_add((char *) idSimbol, &simbol) != SYMTAB_OK) {
                  num_errors++; printErrorSintactic(TRUE, ERR_INTRODUCCIO_TAULA_SIMBOL_FUNC_VAR, "funcio", idSimbol);
               }
               else { 
                  printInfoSintactic(OK_INTRODUCCIO_TAULA_SIMBOL_FUN_VAR, "funcio", idSimbol);
               }
            }
            else {
               currentScope = sym_get_scope();
               simbol.ambit = currentScope;
               if (sym_add((char *) idSimbol, &simbol) != SYMTAB_OK) {
                  num_errors++; printErrorSintactic(TRUE, ERR_INTRODUCCIO_TAULA_SIMBOL_FUNC_VAR, "variable", idSimbol);
               }
               else { 
                  if (currentScope == -1) afegirVarLocalRA(registreActivacioGlobal, idSimbol, &simbol);
                  else afegirVarLocalRA(registreActivacioFuncions, idSimbol, &simbol);
                  
                  printInfoSintactic(OK_INTRODUCCIO_TAULA_SIMBOL_FUN_VAR, "variable", idSimbol);
               }
            }
            printSimbolInfo((char *) idSimbol);
         }
      }
      
      fprintf(yyout, ">>> linia %i: init_declarator_list,init_declarator REDUCE TO init_declarator_list\n", numFila);
   ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 1468 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      (yyval.infoBison).tipus_var = TIPUS_NULL;
      
      fprintf(yyout, ">>> linia %i: declarator REDUCE TO init_declarator\n", numFila);
   ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 1474 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (3)].infoBison);
      (yyval.infoBison).constant = FALSE;
      (yyval.infoBison).tipus_var = tipus_var_tmp;

      (yyvsp[(1) - (3)].infoBison).tipus_var = tipus_var_tmp;
            
      if ((yyvsp[(3) - (3)].infoBison).constant != TRUE) { num_errors++; printErrorSintactic(TRUE, ERR_VALOR_INICIAL_NO_CONST); }
      else if (((yyvsp[(1) - (3)].infoBison).array == TRUE) && ((yyvsp[(3) - (3)].infoBison).tipus_var == TIPUS_STRING) && ((strlen((yyvsp[(3) - (3)].infoBison).valor)) > (yyvsp[(1) - (3)].infoBison).tam_array)) {
         num_errors++; printErrorSintactic(TRUE, ERR_ASSIGNACIO_STRING_ARRAY, strlen((yyvsp[(3) - (3)].infoBison).valor), (yyvsp[(1) - (3)].infoBison).tam_array);    
      }
      else {  
         if (((yyvsp[(1) - (3)].infoBison).array == TRUE) && ((yyvsp[(3) - (3)].infoBison).tipus_var == TIPUS_STRING)) {
            if ((yyvsp[(1) - (3)].infoBison).valorC3A == NULL) {
               (yyvsp[(1) - (3)].infoBison).valorC3A = malloc(strlen((yyvsp[(1) - (3)].infoBison).valor) + 1); 
               strcpy((yyvsp[(1) - (3)].infoBison).valorC3A, (yyvsp[(1) - (3)].infoBison).valor);
            }
            (yyvsp[(1) - (3)].infoBison).array_indexat = TRUE;
            (yyvsp[(1) - (3)].infoBison).array_indexat_offset = (char *) malloc(log10Func(strlen((yyvsp[(3) - (3)].infoBison).valor)) + 1);
            (yyvsp[(3) - (3)].infoBison).valorC3A = (char *) malloc(4);
            for(count = 0; count < strlen((yyvsp[(3) - (3)].infoBison).valor); count++) {
               sprintf((yyvsp[(1) - (3)].infoBison).array_indexat_offset, "%d", count);
               sprintf((yyvsp[(3) - (3)].infoBison).valorC3A, "'%c'", (yyvsp[(3) - (3)].infoBison).valor[count]);  
               
               emet_operacioC3A(&(yyvsp[(3) - (3)].infoBison), NULL, &(yyvsp[(1) - (3)].infoBison), '=');
               
               (yyvsp[(1) - (3)].infoBison).array_indexat = TRUE;
               strcpy((yyvsp[(1) - (3)].infoBison).valorC3A, (yyvsp[(1) - (3)].infoBison).valor);
            }
         }
         else {  
            if ((yyvsp[(1) - (3)].infoBison).valorC3A == NULL) {
               (yyvsp[(1) - (3)].infoBison).valorC3A = malloc(strlen((yyvsp[(1) - (3)].infoBison).valor) + 1); 
               strcpy((yyvsp[(1) - (3)].infoBison).valorC3A, (yyvsp[(1) - (3)].infoBison).valor);
            }
            if ((yyvsp[(3) - (3)].infoBison).valorC3A == NULL) {
               (yyvsp[(3) - (3)].infoBison).valorC3A = malloc(strlen((yyvsp[(3) - (3)].infoBison).valor) + 1); 
               strcpy((yyvsp[(3) - (3)].infoBison).valorC3A, (yyvsp[(3) - (3)].infoBison).valor);
            }
            emet_operacioC3A(&(yyvsp[(3) - (3)].infoBison), NULL, &(yyvsp[(1) - (3)].infoBison), '=');
         }
      }
      
      fprintf(yyout, ">>> linia %i: declarator '=' initializer REDUCE TO init_declarator\n", numFila);
   ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 1525 "sintactic.y"
    {
      (yyval.infoBison).constant = FALSE;
      (yyval.infoBison).tipus_var = TIPUS_VOID;         
      fprintf(yyout, ">>> linia %i: ID_VOID REDUCE TO type_specifier\n", numFila);
   ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 1530 "sintactic.y"
    {
      (yyval.infoBison).constant = FALSE;
      (yyval.infoBison).tipus_var = TIPUS_CHARACTER; 
      fprintf(yyout, ">>> linia %i: ID_CHAR REDUCE TO type_specifier\n", numFila);
   ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 1535 "sintactic.y"
    { 
      (yyval.infoBison).constant = FALSE;
      (yyval.infoBison).tipus_var = TIPUS_SHORT;       
      fprintf(yyout, ">>> linia %i: ID_SHORT REDUCE TO type_specifier\n", numFila);
   ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 1540 "sintactic.y"
    {    
      (yyval.infoBison).constant = FALSE;
      (yyval.infoBison).tipus_var = TIPUS_INTEGER;
      fprintf(yyout, ">>> linia %i: ID_INT REDUCE TO type_specifier\n", numFila);
   ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 1545 "sintactic.y"
    {     
      (yyval.infoBison).constant = FALSE;
      (yyval.infoBison).tipus_var = TIPUS_LONG;
      fprintf(yyout, ">>> linia %i: ID_LONG REDUCE TO type_specifier\n", numFila);
   ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 1550 "sintactic.y"
    {      
      (yyval.infoBison).constant = FALSE;
      (yyval.infoBison).tipus_var = TIPUS_FLOAT;
      fprintf(yyout, ">>> linia %i: ID_FLOAT REDUCE TO type_specifier\n", numFila);           
   ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 1555 "sintactic.y"
    {       
      (yyval.infoBison).constant = FALSE;
      (yyval.infoBison).tipus_var = TIPUS_DOUBLE;
      fprintf(yyout, ">>> linia %i: ID_DOUBLE REDUCE TO type_specifier\n", numFila);
   ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 1560 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      (yyval.infoBison).constant = FALSE;
      (yyval.infoBison).tipus_var = TIPUS_STRUCT;
      fprintf(yyout, ">>> linia %i: struct_or_union_specifier REDUCE TO type_specifier\n", numFila);
   ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 1566 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      (yyval.infoBison).constant = FALSE;
      fprintf(yyout, ">>> linia %i: typedef_name REDUCE TO type_specifier\n", numFila);
   ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 1577 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      
      if ((yyvsp[(1) - (1)].infoBison).tipus_var == TIPUS_STRUCT) {
         if (sym_lookup((yyvsp[(1) - (1)].infoBison).valor, &simbol) == SYMTAB_OK) {
            if (simbol.num_struct_camps > 0) {
               recordsetCamp = (struct t_infoBison *) malloc(sizeof(struct t_infoBison));
               (yyval.infoBison).seguent_camp_struct = recordsetCamp;
               (yyval.infoBison).num_struct_camps = simbol.num_struct_camps;
               recordsetCamp -> seguent_camp_struct = NULL;
            
               for(count = 0; count < simbol.num_struct_camps; count++) {
                  recordsetCamp -> valor = malloc(strlen(simbol.struct_camps[count].valor) + 1);       
                  strcpy(recordsetCamp -> valor, simbol.struct_camps[count].valor);
                  
                  recordsetCamp -> tipus_var = simbol.struct_camps[count].tipus_var;
                  recordsetCamp -> array = simbol.struct_camps[count].array;
                  recordsetCamp -> tam_array = simbol.struct_camps[count].tam_array;
               
                  recordsetCamp -> seguent_camp_struct = (struct t_infoBison *) malloc(sizeof(struct t_infoBison));
                  recordsetCamp = recordsetCamp -> seguent_camp_struct;
               }
            }
         }  
      }

      fprintf(yyout, ">>> linia %i: ID_TYPEDEF_IDENTIFIER REDUCE TO typedef_name\n", numFila);
   ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 1611 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(2) - (5)].infoBison);
      (yyval.infoBison).tipus_var = TIPUS_STRUCT;
      (yyval.infoBison).num_struct_camps = (yyvsp[(4) - (5)].infoBison).num_struct_camps;
      (yyval.infoBison).seguent_camp_struct = (yyvsp[(4) - (5)].infoBison).seguent_camp_struct;
      
      fprintf(yyout, ">>> linia %i: struct_or_union ID_IDENTIFICADOR -> [%s] { struct_declaration_list } REDUCE TO struct_or_union_specifier\n", numFila, (yyvsp[(2) - (5)].infoBison).valor);
   ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 1619 "sintactic.y"
    {  
      (yyval.infoBison).tipus_var = TIPUS_STRUCT;
      (yyval.infoBison).num_struct_camps = (yyvsp[(3) - (4)].infoBison).num_struct_camps;
      (yyval.infoBison).seguent_camp_struct = (yyvsp[(3) - (4)].infoBison).seguent_camp_struct;      
      
      fprintf(yyout, ">>> linia %i: struct_or_union { struct_declaration_list } REDUCE TO struct_or_union_specifier\n", numFila);
   ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 1632 "sintactic.y"
    {
      fprintf(yyout, ">>> linia %i: ID_STRUCT REDUCE TO struct_or_union\n", numFila);
   ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 1635 "sintactic.y"
    {
      fprintf(yyout, ">>> linia %i: ID_UNION REDUCE TO struct_or_union\n", numFila);
   ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 1644 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      
      fprintf(yyout, ">>> linia %i: struct_declaration REDUCE TO struct_declaration_list\n", numFila);
   ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 1649 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (2)].infoBison);
      
      recordsetCamp = (yyval.infoBison).seguent_camp_struct; 
      for (count = 1; count < (yyval.infoBison).num_struct_camps; count++) {   
         recordsetCamp = recordsetCamp -> seguent_camp_struct;
      }
      recordsetCamp -> seguent_camp_struct = (yyvsp[(2) - (2)].infoBison).seguent_camp_struct;
      (yyval.infoBison).num_struct_camps += (yyvsp[(2) - (2)].infoBison).num_struct_camps;
      
      fprintf(yyout, ">>> linia %i: struct_declaration_list struct_declaration REDUCE TO struct_declaration_list\n", numFila);
   ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 1667 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(2) - (3)].infoBison);
      
      fprintf(yyout, ">>> linia %i: specifier_qualifier_list struct_declarator_list; REDUCE TO struct_declaration\n", numFila);
   ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 1678 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      
      pcamp = (struct t_infoBison *) malloc(sizeof(struct t_infoBison));
      *pcamp = (yyvsp[(1) - (1)].infoBison);
      pcamp->tipus_var = (yyvsp[(0) - (1)].infoBison).tipus_var;
      pcamp->seguent_camp_struct = NULL;
      
      (yyval.infoBison).seguent_camp_struct = pcamp;
      (yyval.infoBison).num_struct_camps = 1;
      (yyval.infoBison).tipus_var = (yyvsp[(0) - (1)].infoBison).tipus_var;
      
      fprintf(yyout, ">>> linia %i: struct_declarator REDUCE TO struct_declarator_list\n", numFila);
   ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 1692 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (3)].infoBison);
      pcamp = (struct t_infoBison *) malloc(sizeof(struct t_infoBison));
      *pcamp = (yyvsp[(3) - (3)].infoBison);
      pcamp->seguent_camp_struct = NULL;
      pcamp->tipus_var = (yyvsp[(1) - (3)].infoBison).tipus_var;
      
      recordsetCamp = (yyval.infoBison).seguent_camp_struct; 
      for (count = 1; count < (yyval.infoBison).num_struct_camps; count++) {
         recordsetCamp = recordsetCamp -> seguent_camp_struct;
      }
      recordsetCamp -> seguent_camp_struct = pcamp;
      (yyval.infoBison).num_struct_camps++;
      
      fprintf(yyout, ">>> linia %i: struct_declarator_list,struct_declarator REDUCE TO struct_declarator_list\n", numFila);
   ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 1714 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      
      fprintf(yyout, ">>> linia %i: declarator REDUCE TO struct_declarator\n", numFila);
   ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 1725 "sintactic.y"
    {  
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison); 
      (yyval.infoBison).funcio = FALSE;
             
      fprintf(yyout, ">>> linia %i: ID_IDENTIFICADOR -> [%s] REDUCE TO declarator\n", numFila, (yyvsp[(1) - (1)].infoBison).valor);
   ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 1731 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(2) - (3)].infoBison);
      
      fprintf(yyout, ">>> linia %i: (declarator) REDUCE TO declarator\n", numFila);
   ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 1736 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (4)].infoBison);
      (yyval.infoBison).array = TRUE;
      
      tmpValor = atoll((yyvsp[(3) - (4)].infoBison).valor);
      
      if (tmpValor > 0) {
         if (tmpValor > LONG_MAX) { (yyval.infoBison).tam_array = LONG_MAX; printErrorSintactic(FALSE, WARNING_ARRAY_TAMANY_MAXIM, (yyvsp[(1) - (4)].infoBison).valor, LONG_MAX); }
         else (yyval.infoBison).tam_array = tmpValor;
      }
      else { (yyval.infoBison).tam_array = 0; num_errors++; printErrorSintactic(TRUE, ERR_ARRAY_TAMANY_INCORRECTE, (yyvsp[(3) - (4)].infoBison).valor, (yyvsp[(1) - (4)].infoBison).valor); }
      
      arrayDeclaracio = TRUE;
      fprintf(yyout, ">>> linia %i: declarator[ID_INTEGER_CONSTANT -> [%s]] REDUCE TO declarator\n", numFila, (yyvsp[(3) - (4)].infoBison).valor);
   ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 1751 "sintactic.y"
    { 
      (yyval.infoBison) = (yyvsp[(1) - (4)].infoBison);
      (yyval.infoBison).seguent_param_funcio = (yyvsp[(3) - (4)].infoBison).seguent_param_funcio;
      (yyval.infoBison).num_funcio_parametres = (yyvsp[(3) - (4)].infoBison).num_funcio_parametres;
      (yyval.infoBison).funcio = TRUE;
     
      fprintf(yyout, ">>> linia %i: declarator(parameter_list) REDUCE TO declarator\n", numFila);
   ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 1759 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (4)].infoBison);
      (yyval.infoBison).seguent_param_funcio = (yyvsp[(3) - (4)].infoBison).seguent_param_funcio;
      (yyval.infoBison).num_funcio_parametres = (yyvsp[(3) - (4)].infoBison).num_funcio_parametres;
      (yyval.infoBison).funcio = TRUE;
               
      fprintf(yyout, ">>> linia %i: declarator(identifier_list) REDUCE TO declarator\n", numFila);
   ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 1767 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (3)].infoBison);
      (yyval.infoBison).seguent_param_funcio = NULL;
      (yyval.infoBison).num_funcio_parametres = 0;
      (yyval.infoBison).funcio = TRUE;
      
      fprintf(yyout, ">>> linia %i: declarator() REDUCE TO declarator\n", numFila);
   ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 1781 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      
      pparam = (struct t_infoBison *) malloc(sizeof(struct t_infoBison));
      *pparam = (yyvsp[(1) - (1)].infoBison);
      pparam->tipus_var = (yyvsp[(1) - (1)].infoBison).tipus_var;
      pparam->seguent_param_funcio = NULL;
      
      (yyval.infoBison).seguent_param_funcio = pparam;
      (yyval.infoBison).num_funcio_parametres = 1;
      
      fprintf(yyout, ">>> linia %i: parameter_declaration REDUCE TO parameter_list\n", numFila);
   ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 1794 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (3)].infoBison);
      pparam = (struct t_infoBison *) malloc(sizeof(struct t_infoBison));
      *pparam = (yyvsp[(3) - (3)].infoBison);
      pparam->seguent_param_funcio = NULL;
      pparam->tipus_var = (yyvsp[(3) - (3)].infoBison).tipus_var;
      
      recordsetParam = (yyval.infoBison).seguent_param_funcio; 
      for (count = 1; count < (yyval.infoBison).num_funcio_parametres; count++) {
         recordsetParam = recordsetParam -> seguent_param_funcio;
      }
      recordsetParam -> seguent_param_funcio = pparam;
      (yyval.infoBison).num_funcio_parametres++;

      fprintf(yyout, ">>> linia %i: parameter_list,parameter_declaration REDUCE TO parameter_list\n", numFila);   
   ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 1816 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(2) - (2)].infoBison);
      (yyval.infoBison).tipus_var = (yyvsp[(1) - (2)].infoBison).tipus_var;
      
      fprintf(yyout, ">>> linia %i: declaration_specifiers declarator REDUCE TO parameter_declaration\n", numFila);
   ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 1822 "sintactic.y"
    {
      fprintf(yyout, ">>> linia %i: declaration_specifiers abstract_declarator REDUCE TO parameter_declaration\n", numFila);
   ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 1825 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      
      fprintf(yyout, ">>> linia %i: declaration_specifiers REDUCE TO parameter_declaration\n", numFila);
   ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 1836 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      
      pparam = (struct t_infoBison *) malloc(sizeof(struct t_infoBison));
      *pparam = (yyvsp[(1) - (1)].infoBison);
      pparam->tipus_var = TIPUS_NULL;
      pparam->seguent_param_funcio = NULL;
      
      (yyval.infoBison).seguent_param_funcio = pparam;
      (yyval.infoBison).num_funcio_parametres = 1;
      
      fprintf(yyout, ">>> linia %i: ID_IDENTIFICADOR -> [%s] REDUCE TO identifier_list\n", numFila, (yyvsp[(1) - (1)].infoBison).valor);   
   ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 1849 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (3)].infoBison);
      pparam = (struct t_infoBison *) malloc(sizeof(struct t_infoBison));
      *pparam = (yyvsp[(3) - (3)].infoBison);
      pparam->seguent_param_funcio = NULL;
      pparam->tipus_var = TIPUS_NULL;
      
      recordsetParam = (yyval.infoBison).seguent_param_funcio; 
      for (count = 1; count < (yyval.infoBison).num_funcio_parametres; count++) {
         recordsetParam = recordsetParam -> seguent_param_funcio;
      }
      recordsetParam -> seguent_param_funcio = pparam;
      (yyval.infoBison).num_funcio_parametres++;
      
      fprintf(yyout, ">>> linia %i: identifier_list,ID_IDENTIFICADOR -> [%s] REDUCE TO identifier_list\n", numFila, (yyvsp[(3) - (3)].infoBison).valor);
   ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 1871 "sintactic.y"
    {
      fprintf(yyout, ">>> linia %i: specifier_qualifier_list REDUCE TO type_name\n", numFila);
   ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 1874 "sintactic.y"
    {
      fprintf(yyout, ">>> linia %i: specifier_qualifier_list abstract_declarator REDUCE TO type_name\n", numFila);
   ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 1883 "sintactic.y"
    {
      fprintf(yyout, ">>> linia %i: type_specifier specifier_qualifier_list REDUCE TO specifier_qualifier_list\n", numFila);
   ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 1886 "sintactic.y"
    {
      fprintf(yyout, ">>> linia %i: type_specifier REDUCE TO specifier_qualifier_list\n", numFila);
   ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 1895 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(2) - (3)].infoBison);
      
      fprintf(yyout, ">>> linia %i: (abstract_declarator) REDUCE TO abstract_declarator\n", numFila);
   ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 1900 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(2) - (3)].infoBison);
      
      fprintf(yyout, ">>> linia %i: [ID_INTEGER_CONSTANT -> [%s]] REDUCE TO abstract_declarator\n", numFila, (yyvsp[(2) - (3)].infoBison).valor);
   ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 1905 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (4)].infoBison);
      
      fprintf(yyout, ">>> linia %i: abstract_declarator [ID_INTEGER_CONSTANT -> [%s]] REDUCE TO abstract_declarator\n", numFila, (yyvsp[(3) - (4)].infoBison).valor);
   ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 1910 "sintactic.y"
    {
      fprintf(yyout, ">>> linia %i: () REDUCE TO abstract_declarator\n", numFila);
   ;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 1913 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(2) - (3)].infoBison);
      
      fprintf(yyout, ">>> linia %i: (parameter_list) REDUCE TO abstract_declarator\n", numFila);
   ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 1918 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (3)].infoBison);
      
      fprintf(yyout, ">>> linia %i: abstract_declarator() REDUCE TO abstract_declarator\n", numFila);
   ;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 1923 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (4)].infoBison);
      
      fprintf(yyout, ">>> linia %i: abstract_declarator(parameter_list) REDUCE TO abstract_declarator\n", numFila);
   ;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 1934 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      
      fprintf(yyout, ">>> linia %i: assignment_expression REDUCE TO initializer\n", numFila);   
   ;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 1939 "sintactic.y"
    {
      fprintf(yyout, ">>> linia %i: {initializer_list} REDUCE TO initializer\n", numFila);
   ;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 1942 "sintactic.y"
    {
      fprintf(yyout, ">>> linia %i: {initializer_list,} REDUCE TO initializer\n", numFila);
   ;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 1951 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      
      fprintf(yyout, ">>> linia %i: initializer REDUCE TO initializer_list\n", numFila);
   ;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 1956 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (3)].infoBison);
      
      fprintf(yyout, ">>> linia %i: initializer_list , initializer  REDUCE TO initializer_list\n", numFila);
   ;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 1967 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      fprintf(yyout, ">>> linia %i: labeled_statement REDUCE TO statement\n", numFila);
   ;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 1971 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      fprintf(yyout, ">>> linia %i: compound_statement REDUCE TO statement\n", numFila);
   ;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 1975 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      fprintf(yyout, ">>> linia %i: expression_statement REDUCE TO statement\n", numFila);
   ;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 1979 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      fprintf(yyout, ">>> linia %i: selection_statement REDUCE TO statement\n", numFila);
   ;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 1983 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      fprintf(yyout, ">>> linia %i: iteration_statement REDUCE TO statement\n", numFila);
   ;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 1987 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      fprintf(yyout, ">>> linia %i: jump_statement REDUCE TO statement\n", numFila);
   ;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 1997 "sintactic.y"
    {
      fprintf(yyout, ">>> linia %i: ID_CASE constant_expression ':' statement REDUCE TO labeled_statement\n", numFila);
   ;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 2000 "sintactic.y"
    {
      fprintf(yyout, ">>> linia %i: ID_DEFAULT ':' statement REDUCE TO statement\n", numFila);
   ;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 2009 "sintactic.y"
    {
      fprintf(yyout, ">>> linia %i: { } REDUCE TO compound_statement\n", numFila);
   ;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 2012 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(2) - (3)].infoBison);
      fprintf(yyout, ">>> linia %i: { declaration_list } REDUCE TO compound_statement\n", numFila);
   ;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 2016 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(2) - (3)].infoBison);
      fprintf(yyout, ">>> linia %i: { statement_list } REDUCE TO compound_statement\n", numFila);
   ;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 2020 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(3) - (4)].infoBison);
      fprintf(yyout, ">>> linia %i: { declaration_list statement_list } REDUCE TO compound_statement\n", numFila);
   ;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 2030 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);
      fprintf(yyout, ">>> linia %i: statement REDUCE TO statement_list\n", numFila);
   ;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 2034 "sintactic.y"
    {
	  (yyval.infoBison) = (yyvsp[(3) - (3)].infoBison);
	  completar_llista((Cua *) (yyvsp[(1) - (3)].infoBison).llista_seguents, (yyvsp[(2) - (3)].infoBison).punter_quadruple);
      fprintf(yyout, ">>> linia %i: statement_list statement REDUCE TO statement_list\n", numFila);
   ;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 2045 "sintactic.y"
    {
      fprintf(yyout, ">>> linia %i: ';' REDUCE TO expression_statement\n", numFila);
   ;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 2048 "sintactic.y"
    {
      fprintf(yyout, ">>> linia %i: expression; REDUCE TO expression_statement\n", numFila);
   ;}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 2057 "sintactic.y"
    { conditional_if_while_for = TRUE; ;}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 2064 "sintactic.y"
    { 
      conditional_if_while_for = FALSE;
      (yyval.infoBison) = (yyvsp[(3) - (4)].infoBison); 
   ;}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 2074 "sintactic.y"
    { conditional_if_while_for = TRUE; ;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 2081 "sintactic.y"
    {
      completar_llista((Cua *) (yyvsp[(1) - (3)].infoBison).llista_certs, (yyvsp[(2) - (3)].infoBison).punter_quadruple);
      (yyval.infoBison).llista_seguents = (void *) fusionar_cues((Cua *) (yyvsp[(3) - (3)].infoBison).llista_seguents, (Cua *) (yyvsp[(1) - (3)].infoBison).llista_falsos);
  
      fprintf(yyout, ">>> linia %i: ID_IF (expression) statement REDUCE TO selection_statement\n", numFila);
   ;}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 2087 "sintactic.y"
    {
      completar_llista((Cua *) (yyvsp[(1) - (7)].infoBison).llista_certs, (yyvsp[(2) - (7)].infoBison).punter_quadruple);
      completar_llista((Cua *) (yyvsp[(1) - (7)].infoBison).llista_falsos, (yyvsp[(6) - (7)].infoBison).punter_quadruple);
      (yyval.infoBison).llista_seguents = (void *) fusionar_cues((Cua *) (yyvsp[(7) - (7)].infoBison).llista_seguents, (Cua *) fusionar_cues((Cua *) (yyvsp[(3) - (7)].infoBison).llista_seguents ,(Cua *) (yyvsp[(5) - (7)].infoBison).llista_seguents));
		
      fprintf(yyout, ">>> linia %i: ID_IF (expression) statement ID_ELSE statement REDUCE TO selection_statement\n", numFila);
   ;}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 2094 "sintactic.y"
    {
      fprintf(yyout, ">>> linia %i: ID_SWITCH (expression) statement REDUCE TO selection_statement\n", numFila);
   ;}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 2103 "sintactic.y"
    { conditional_if_while_for = TRUE ;}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 2103 "sintactic.y"
    { conditional_if_while_for = FALSE; 
   ;}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 2104 "sintactic.y"
    {
      completar_llista((Cua *) (yyvsp[(5) - (9)].infoBison).llista_certs, (yyvsp[(8) - (9)].infoBison).punter_quadruple);
	  completar_llista((Cua *) (yyvsp[(9) - (9)].infoBison).llista_seguents, (yyvsp[(4) - (9)].infoBison).punter_quadruple);
	
      (yyval.infoBison) = (yyvsp[(5) - (9)].infoBison);
      (yyval.infoBison).llista_seguents = (yyvsp[(5) - (9)].infoBison).llista_falsos;
      
      emet_saltC3A((yyvsp[(4) - (9)].infoBison).punter_quadruple);       
      fprintf(yyout, ">>> linia %i: ID_WHILE (expression) statement REDUCE TO iteration_statement\n", numFila);
   ;}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 2114 "sintactic.y"
    { conditional_if_while_for = TRUE 
   ;}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 2115 "sintactic.y"
    {
      conditional_if_while_for = FALSE;

      completar_llista((Cua *) (yyvsp[(8) - (10)].infoBison).llista_certs, (yyvsp[(2) - (10)].infoBison).punter_quadruple);
      completar_llista((Cua *) (yyvsp[(3) - (10)].infoBison).llista_seguents, (yyvsp[(7) - (10)].infoBison).punter_quadruple);
      
      (yyval.infoBison).llista_seguents = (yyvsp[(8) - (10)].infoBison).llista_falsos;  
      fprintf(yyout, ">>> linia %i: ID_DO statement ID_WHILE (expression); REDUCE TO iteration_statement\n", numFila);
   ;}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 2124 "sintactic.y"
    {
      conditional_if_while_for = FALSE;
   
   ;}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 2127 "sintactic.y"
    {
      completar_llista((Cua *) (yyvsp[(6) - (14)].infoBison).llista_certs, (yyvsp[(13) - (14)].infoBison).punter_quadruple);
	  completar_llista((Cua *) (yyvsp[(12) - (14)].infoBison).llista_seguents, (yyvsp[(5) - (14)].infoBison).punter_quadruple);
      completar_llista((Cua *) (yyvsp[(14) - (14)].infoBison).llista_seguents, (yyvsp[(9) - (14)].infoBison).punter_quadruple);
		
	  (yyval.infoBison).llista_seguents = (yyvsp[(6) - (14)].infoBison).llista_falsos;
	  emet_saltC3A((yyvsp[(9) - (14)].infoBison).punter_quadruple);
		
      fprintf(yyout, ">>> linia %i: ID_FOR (expression; expression; expression) REDUCE TO iteration_statement\n", numFila);
   ;}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 2137 "sintactic.y"
    {
      conditional_if_while_for = FALSE;
      
   ;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 2140 "sintactic.y"
    {
      completar_llista((Cua *) (yyvsp[(5) - (13)].infoBison).llista_certs, (yyvsp[(12) - (13)].infoBison).punter_quadruple);
	  completar_llista((Cua *) (yyvsp[(11) - (13)].infoBison).llista_seguents, (yyvsp[(4) - (13)].infoBison).punter_quadruple);
      completar_llista((Cua *) (yyvsp[(13) - (13)].infoBison).llista_seguents, (yyvsp[(8) - (13)].infoBison).punter_quadruple);
		
	  (yyval.infoBison).llista_seguents = (yyvsp[(5) - (13)].infoBison).llista_falsos;
	  emet_saltC3A((yyvsp[(8) - (13)].infoBison).punter_quadruple);
       
      fprintf(yyout, ">>> linia %i: ID_FOR (;expression;expression) statement REDUCE TO iteration_statement\n", numFila);
   ;}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 2151 "sintactic.y"
    {
      conditional_if_while_for = FALSE;         
      tmpCondicio = (struct t_infoBison *) malloc(sizeof(struct t_infoBison));      
      
      tmpCondicio -> valorC3A = malloc(2); 
      strcpy(tmpCondicio -> valorC3A, "1");
      tmpCondicio -> tipus_var = TIPUS_INTEGER;
      tmpCondicio -> array = FALSE;
      tmpCondicio -> array_indexat = FALSE;
      tmpCondicio -> camp_struct_indexat = FALSE;
      
      emet_condicioC3A(tmpCondicio, tmpCondicio);
      
   ;}
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 2164 "sintactic.y"
    {
      completar_llista((Cua *) tmpCondicio -> llista_certs, (yyvsp[(11) - (12)].infoBison).punter_quadruple);
	  completar_llista((Cua *) (yyvsp[(10) - (12)].infoBison).llista_seguents, (yyvsp[(4) - (12)].infoBison).punter_quadruple);
      completar_llista((Cua *) (yyvsp[(12) - (12)].infoBison).llista_seguents, (yyvsp[(7) - (12)].infoBison).punter_quadruple);
		
	  (yyval.infoBison).llista_seguents = tmpCondicio -> llista_falsos;
	  emet_saltC3A((yyvsp[(7) - (12)].infoBison).punter_quadruple);
       
      fprintf(yyout, ">>> linia %i: ID_FOR (;;expression) statement REDUCE TO iteration_statement\n", numFila);
   ;}
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 2174 "sintactic.y"
    {
      conditional_if_while_for = FALSE;         
      tmpCondicio = (struct t_infoBison *) malloc(sizeof(struct t_infoBison));      
      
      tmpCondicio -> valorC3A = malloc(2); 
      strcpy(tmpCondicio -> valorC3A, "1");
      tmpCondicio -> tipus_var = TIPUS_INTEGER;
      tmpCondicio -> array = FALSE;
      tmpCondicio -> array_indexat = FALSE;
      tmpCondicio -> camp_struct_indexat = FALSE;
      
      emet_condicioC3A(tmpCondicio, tmpCondicio);
      
   ;}
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 2187 "sintactic.y"
    {
      completar_llista((Cua *) tmpCondicio -> llista_certs, (yyvsp[(8) - (9)].infoBison).punter_quadruple);
		
	  (yyval.infoBison).llista_seguents = tmpCondicio -> llista_falsos;
	  emet_saltC3A((yyvsp[(4) - (9)].infoBison).punter_quadruple);
	  
      fprintf(yyout, ">>> linia %i: ID_FOR (;;) statement REDUCE TO iteration_statement\n", numFila);
   ;}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 2195 "sintactic.y"
    {
      conditional_if_while_for = FALSE;         
      tmpCondicio = (struct t_infoBison *) malloc(sizeof(struct t_infoBison));      
      
      tmpCondicio -> valorC3A = malloc(2); 
      strcpy(tmpCondicio -> valorC3A, "1");
      tmpCondicio -> tipus_var = TIPUS_INTEGER;
      tmpCondicio -> array = FALSE;
      tmpCondicio -> array_indexat = FALSE;
      tmpCondicio -> camp_struct_indexat = FALSE;
      
      emet_condicioC3A(tmpCondicio, tmpCondicio);
      
   ;}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 2208 "sintactic.y"
    {
      completar_llista((Cua *) tmpCondicio -> llista_certs, (yyvsp[(12) - (13)].infoBison).punter_quadruple);
	  completar_llista((Cua *) (yyvsp[(11) - (13)].infoBison).llista_seguents, (yyvsp[(5) - (13)].infoBison).punter_quadruple);
      completar_llista((Cua *) (yyvsp[(13) - (13)].infoBison).llista_seguents, (yyvsp[(8) - (13)].infoBison).punter_quadruple);
		
	  (yyval.infoBison).llista_seguents = tmpCondicio -> llista_falsos;
	  emet_saltC3A((yyvsp[(8) - (13)].infoBison).punter_quadruple);
       
      fprintf(yyout, ">>> linia %i: ID_FOR (expression;;expression) REDUCE TO iteration_statement\n", numFila);
   ;}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 2218 "sintactic.y"
    {
      conditional_if_while_for = FALSE;         
      tmpCondicio = (struct t_infoBison *) malloc(sizeof(struct t_infoBison));      
      
      tmpCondicio -> valorC3A = malloc(2); 
      strcpy(tmpCondicio -> valorC3A, "1");
      tmpCondicio -> tipus_var = TIPUS_INTEGER;
      tmpCondicio -> array = FALSE;
      tmpCondicio -> array_indexat = FALSE;
      tmpCondicio -> camp_struct_indexat = FALSE;
      
      emet_condicioC3A(tmpCondicio, tmpCondicio);
      
   ;}
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 2231 "sintactic.y"
    {
      completar_llista((Cua *) tmpCondicio -> llista_certs, (yyvsp[(9) - (10)].infoBison).punter_quadruple);
		
	  (yyval.infoBison).llista_seguents = tmpCondicio -> llista_falsos;
	  emet_saltC3A((yyvsp[(5) - (10)].infoBison).punter_quadruple);
	  
      fprintf(yyout, ">>> linia %i: ID_FOR (expression;;) statement REDUCE TO iteration_statement\n", numFila);
   ;}
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 2239 "sintactic.y"
    {               
      conditional_if_while_for = FALSE;
      
   ;}
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 2242 "sintactic.y"
    {
      completar_llista((Cua *) (yyvsp[(5) - (10)].infoBison).llista_certs, (yyvsp[(9) - (10)].infoBison).punter_quadruple);
		
	  (yyval.infoBison).llista_seguents = (yyvsp[(5) - (10)].infoBison).llista_falsos;
	  emet_saltC3A((yyvsp[(4) - (10)].infoBison).punter_quadruple);
	  
      fprintf(yyout, ">>> linia %i: ID_FOR (;expression;) statement REDUCE TO iteration_statement\n", numFila);
   ;}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 2250 "sintactic.y"
    {
      conditional_if_while_for = FALSE;
      
   ;}
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 2253 "sintactic.y"
    {
      completar_llista((Cua *) (yyvsp[(6) - (11)].infoBison).llista_certs, (yyvsp[(10) - (11)].infoBison).punter_quadruple);
		
	  (yyval.infoBison).llista_seguents = (yyvsp[(6) - (11)].infoBison).llista_falsos;
	  emet_saltC3A((yyvsp[(5) - (11)].infoBison).punter_quadruple);
	  
      fprintf(yyout, ">>> linia %i: ID_FOR (expression;expression;) statement REDUCE TO iteration_statement\n", numFila);
   ;}
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 2261 "sintactic.y"
    {
      num_errors++; printErrorSintactic(TRUE, ERR_FOR_DECLARACIO_VARIABLES);
      yyerrok;
   ;}
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 2271 "sintactic.y"
    {
      fprintf(yyout, ">>> linia %i: ID_CONTINUE; REDUCE TO jump_statement\n", numFila);   
   ;}
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 2274 "sintactic.y"
    {
      fprintf(yyout, ">>> linia %i: ID_BREAK; REDUCE TO jump_statement\n", numFila);
   ;}
    break;

  case 164:

/* Line 1455 of yacc.c  */
#line 2277 "sintactic.y"
    {
      fprintf(yyout, ">>> linia %i: ID_RETURN; REDUCE TO jump_statement\n", numFila);
   ;}
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 2280 "sintactic.y"
    {
      if ((yyvsp[(2) - (3)].infoBison).valorC3A == NULL) {
         (yyvsp[(2) - (3)].infoBison).valorC3A = malloc(strlen((yyvsp[(2) - (3)].infoBison).valor) + 1); 
         strcpy((yyvsp[(2) - (3)].infoBison).valorC3A, (yyvsp[(2) - (3)].infoBison).valor);
      }
      emet_retornFuncioC3A(&(yyvsp[(2) - (3)].infoBison));
      
      fprintf(yyout, ">>> linia %i: ID_RETURN expression; REDUCE TO jump_statement\n", numFila);
   ;}
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 2295 "sintactic.y"
    {
      fprintf(yyout, ">>> linia %i: external_declaration REDUCE TO translation_unit\n", numFila);
   ;}
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 2298 "sintactic.y"
    {
      fprintf(yyout, ">>> linia %i: translation_unit external_declaration REDUCE TO translation_unit\n", numFila);
   ;}
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 2307 "sintactic.y"
    {
      fprintf(yyout, ">>> linia %i: function_definition REDUCE TO external_declaration\n", numFila);
   ;}
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 2310 "sintactic.y"
    {
      fprintf(yyout, ">>> linia %i: declaration REDUCE external_declaration\n", numFila);
   ;}
    break;

  case 170:

/* Line 1455 of yacc.c  */
#line 2319 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(1) - (1)].infoBison);                  
      (yyval.infoBison).tipus_var = TIPUS_VOID;
      
      tipus_var_funcio_retorn = TIPUS_VOID;
      valor_retorn = NULL;
      llista_seguents_funcio_retorn = (void *) crear_cua();
      
      funcioDeclaradaCorrecte = TRUE;
      sym_push_scope();
      currentScope = sym_get_scope();
      printInfoSintactic(OK_INCREMENT_AMBIT, currentScope);
      
      if (identificadorDeclarat((yyvsp[(1) - (1)].infoBison).valor)) {
         if (simbol.funcio == TRUE) {
            printInfoSintactic(OK_CONSULTA_TAULA_SIMBOL_FUN_VAR, "funcio", (yyvsp[(1) - (1)].infoBison).valor);
            (yyval.infoBison).tipus_var = simbol.tipus_var;
          
            if ((yyvsp[(1) - (1)].infoBison).num_funcio_parametres == 1) {
               if (((yyvsp[(1) - (1)].infoBison).seguent_param_funcio -> tipus_var == TIPUS_VOID) && (!esTipus((yyvsp[(1) - (1)].infoBison).seguent_param_funcio -> valor))) {
                  funcioDeclaradaCorrecte = FALSE;
                  num_errors++; printErrorSintactic(TRUE, ERR_PARAMETRE_FUNCIO_VOID);
               }
               else if ((yyvsp[(1) - (1)].infoBison).seguent_param_funcio -> tipus_var == TIPUS_VOID) {
                  (yyvsp[(1) - (1)].infoBison).num_funcio_parametres--;
               }
            }
          
            if (funcioDeclaradaCorrecte) {
               if (simbol.num_funcio_parametres != (yyvsp[(1) - (1)].infoBison).num_funcio_parametres) {
                  funcioDeclaradaCorrecte = FALSE;
                  num_errors++; printErrorSintactic(TRUE, ERR_DEF_FUNCIO_NUM_PARAMS_DIFERENTS, (yyvsp[(1) - (1)].infoBison).valor);  
               }
               else {
                  /* Numero de parametres correctes per definir la funcio */
                  recordsetParam = (yyvsp[(1) - (1)].infoBison).seguent_param_funcio;
                  for (count = 0; count < (yyvsp[(1) - (1)].infoBison).num_funcio_parametres; count++) {
                     if ((recordsetParam -> array != TRUE) && (simbol.funcio_params[count].array == TRUE)) {
                        funcioDeclaradaCorrecte = FALSE; num_errors++; printErrorSintactic(TRUE, ERR_FUNCIO_PARAM_ES_ARRAY, count + 1, (yyvsp[(1) - (1)].infoBison).valor);
                     }
                     else if ((recordsetParam -> array == TRUE) && (simbol.funcio_params[count].array != TRUE)) {
                        funcioDeclaradaCorrecte = FALSE; num_errors++; printErrorSintactic(TRUE, ERR_FUNCIO_PARAM_NO_ES_ARRAY, count + 1, (yyvsp[(1) - (1)].infoBison).valor);
                     }
                     else {
                        if (simbol.funcio_params[count].tipus_var != recordsetParam -> tipus_var) {
                           funcioDeclaradaCorrecte = FALSE;
                           num_errors++; printErrorSintactic(TRUE, ERR_PARAM_FUNCIO_DEFINICIO, count + 1, (yyvsp[(1) - (1)].infoBison).valor, tipusDadesID(simbol.funcio_params[count].tipus_var, 0), tipusDadesID(recordsetParam -> tipus_var, 0));
                        }
                     }
                     recordsetParam = recordsetParam -> seguent_param_funcio;
                  }
                  if (funcioDeclaradaCorrecte) {
                     printInfoSintactic(OK_DEFINICIO_FUNCIO, (yyvsp[(1) - (1)].infoBison).valor);   
                  }   
               }
            }             
         }
         else { funcioDeclaradaCorrecte = FALSE; num_errors++; printErrorSintactic(TRUE, ERR_VARIABLE_NO_FUNCIO, (yyvsp[(1) - (1)].infoBison).valor); }
      }
      else {

         idSimbol = (char *) malloc(strlen((yyvsp[(1) - (1)].infoBison).valor) + 1);
         strcpy(idSimbol, (yyvsp[(1) - (1)].infoBison).valor);
         simbol.tipus_var = TIPUS_VOID;
         simbol.tipus = FUNCIO;
         simbol.funcio = TRUE;
         simbol.num_funcio_parametres = (yyvsp[(1) - (1)].infoBison).num_funcio_parametres;
      
         simbol.idLexic = ID_IDENTIFICADOR;
         strcpy(simbol.nomLexic, "IDENTIFICADOR");
         simbol.ambit = -1; 

         if ((yyvsp[(1) - (1)].infoBison).num_funcio_parametres == 1) {
            if (((yyvsp[(1) - (1)].infoBison).seguent_param_funcio -> tipus_var == TIPUS_VOID) && (!esTipus((yyvsp[(1) - (1)].infoBison).seguent_param_funcio -> valor))) {
               funcioDeclaradaCorrecte = FALSE;
               num_errors++; printErrorSintactic(TRUE, ERR_PARAMETRE_FUNCIO_VOID);
            }
            else if ((yyvsp[(1) - (1)].infoBison).seguent_param_funcio -> tipus_var == TIPUS_VOID) {
               (yyvsp[(1) - (1)].infoBison).num_funcio_parametres--;
               simbol.num_funcio_parametres = 0;
            }
         }
         
         if (funcioDeclaradaCorrecte) { 
            simbol.funcio_params = malloc(sizeof(struct t_param) * (yyvsp[(1) - (1)].infoBison).num_funcio_parametres);
          
            recordsetParam = (yyvsp[(1) - (1)].infoBison).seguent_param_funcio;
            for (count = 0; (count < (yyvsp[(1) - (1)].infoBison).num_funcio_parametres); count++) {
               if (recordsetParam -> tipus_var == TIPUS_VOID) {
                  funcioDeclaradaCorrecte = FALSE;
                  num_errors++; printErrorSintactic(TRUE, ERR_PARAMETRE_FUNCIO_VOID);
               }
               else {               
                  simbol.funcio_params[count].tipus_var = recordsetParam -> tipus_var;
                  if (recordsetParam -> array == TRUE) {
                     simbol.funcio_params[count].array = TRUE;
                     simbol.funcio_params[count].tam_array = recordsetParam -> tam_array;
                  }
                  else {
                     simbol.funcio_params[count].array = FALSE;
                     simbol.funcio_params[count].tam_array = 0;
                  }
               }
               recordsetParam = recordsetParam -> seguent_param_funcio;
            } 
            
            if (funcioDeclaradaCorrecte) {
               if (sym_global_add((char *) idSimbol, &simbol) != SYMTAB_OK) {
                  funcioDeclaradaCorrecte = FALSE;
                  num_errors++; printErrorSintactic(TRUE, ERR_INTRODUCCIO_TAULA_SIMBOL_FUNC_VAR, "funcio", idSimbol);
               }
               else { 
                  printInfoSintactic(OK_INTRODUCCIO_TAULA_SIMBOL_FUN_VAR, "funcio", idSimbol);
               }
         
               printSimbolInfo((char *) idSimbol); 
            }
         }
      }
      
      if (funcioDeclaradaCorrecte) {
         iniRegistreActivacioFuncions((yyvsp[(1) - (1)].infoBison).valor);    
         iniC3AFuncions();

         quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
         quadrupleC3A -> num_sentencia = C3AFuncions -> num_quadruples + 1;
         quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen((yyvsp[(1) - (1)].infoBison).valor) + 7);
         sprintf(quadrupleC3A -> sentenciaC3A, "START %s", (yyvsp[(1) - (1)].infoBison).valor);
          
         encuar(C3AFuncions -> quadrupleC3A, (void *) quadrupleC3A);
         C3AFuncions -> num_quadruples++;
                            
         recordsetParam = (yyvsp[(1) - (1)].infoBison).seguent_param_funcio;
         for (count = 0; count < (yyvsp[(1) - (1)].infoBison).num_funcio_parametres; count++) {
            if (esTipus(recordsetParam -> valor) == FALSE) {               
               idSimbol = (char *) malloc(strlen(recordsetParam -> valor) + 1);
               strcpy(idSimbol, recordsetParam -> valor);
               simbol.tipus_var = recordsetParam -> tipus_var;
               simbol.tipus = VARIABLE;
               simbol.funcio = FALSE;
               simbol.num_funcio_parametres = 0;
      
               if (recordsetParam -> array == TRUE) {
                 simbol.array = TRUE;
                 simbol.tam_array = recordsetParam -> tam_array;
               }
               else simbol.array = FALSE;
        
               simbol.idLexic = ID_IDENTIFICADOR;
               strcpy(simbol.nomLexic, "IDENTIFICADOR");
               simbol.ambit = sym_get_scope(); 

               simbol.funcio_params = NULL;
         
               if (sym_add((char *) idSimbol, &simbol) != SYMTAB_OK) { num_errors++; printErrorSintactic(TRUE, ERR_PARAMETRES_LOCALS_FUNCIO, idSimbol); }
               else {
                  afegirParamRA(registreActivacioFuncions, recordsetParam -> valor, recordsetParam -> tipus_var, recordsetParam -> array, recordsetParam -> tam_array);
                  printInfoSintactic(OK_PARAMETRES_LOCALS_FUNCIO, idSimbol);
               }
            }
            else printErrorSintactic(FALSE, WARNING_NOM_PARAMETRE_FUNCIO_NO_DEC, count + 1, idSimbol);
           
            recordsetParam = recordsetParam -> seguent_param_funcio;
         }  
      }
   ;}
    break;

  case 171:

/* Line 1455 of yacc.c  */
#line 2485 "sintactic.y"
    { 
      currentScope = sym_get_scope();
      sym_pop_scope();
      printInfoSintactic(OK_DECREMENT_AMBIT, currentScope);
      if (funcioDeclaradaCorrecte) { 
         quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
         quadrupleC3A -> num_sentencia = C3AFuncions -> num_quadruples + 1;
         encuar(C3AFuncions -> quadrupleC3A, (void *) quadrupleC3A);
         C3AFuncions -> num_quadruples++;

         quadrupleC3A -> sentenciaC3A = (char * ) malloc(strlen("RETURN") + 1);
         sprintf(quadrupleC3A -> sentenciaC3A, "RETURN"); 
   
         completar_llista((Cua *) llista_seguents_funcio_retorn, (yyvsp[(4) - (4)].infoBison).punter_quadruple);
         completar_llista((Cua *) (yyvsp[(3) - (4)].infoBison).llista_seguents, (yyvsp[(4) - (4)].infoBison).punter_quadruple);                          
         printRegistreActivacio(registreActivacioFuncions);
         printC3AFuncions(C3AFuncions, (yyvsp[(1) - (4)].infoBison).valor);
      }

      fprintf(yyout, ">>> linia %i: declarator compound_statement REDUCE TO function_definition\n", numFila);
   ;}
    break;

  case 172:

/* Line 1455 of yacc.c  */
#line 2506 "sintactic.y"
    {
      fprintf(yyout, ">>> linia %i: declaration_specifiers declarator declaration_list compound_statement REDUCE TO function_definition\n", numFila);
   ;}
    break;

  case 173:

/* Line 1455 of yacc.c  */
#line 2509 "sintactic.y"
    {
      (yyval.infoBison) = (yyvsp[(2) - (2)].infoBison); 
      
      tipus_var_funcio_retorn = TIPUS_VOID;
      valor_retorn = NULL;
      llista_seguents_funcio_retorn = (void *) crear_cua();
      
      funcioDeclaradaCorrecte = TRUE;
      sym_push_scope();
      currentScope = sym_get_scope();
      printInfoSintactic(OK_INCREMENT_AMBIT, currentScope);
      
      if (identificadorDeclarat((yyvsp[(2) - (2)].infoBison).valor)) {
         if (simbol.funcio == TRUE) {
            printInfoSintactic(OK_CONSULTA_TAULA_SIMBOL_FUN_VAR, "funcio", (yyvsp[(2) - (2)].infoBison).valor);
            (yyval.infoBison).tipus_var = simbol.tipus_var;
            tipus_var_funcio_retorn = simbol.tipus_var;
            
            if ((yyvsp[(2) - (2)].infoBison).num_funcio_parametres == 1) {
               if (((yyvsp[(2) - (2)].infoBison).seguent_param_funcio -> tipus_var == TIPUS_VOID) && (!esTipus((yyvsp[(2) - (2)].infoBison).seguent_param_funcio -> valor))) {
                  funcioDeclaradaCorrecte = FALSE;
                  num_errors++; printErrorSintactic(TRUE, ERR_PARAMETRE_FUNCIO_VOID);
               }
               else if ((yyvsp[(2) - (2)].infoBison).seguent_param_funcio -> tipus_var == TIPUS_VOID) {
                  (yyvsp[(2) - (2)].infoBison).num_funcio_parametres--;
               }
            }
            
            if (funcioDeclaradaCorrecte) {
               if (simbol.num_funcio_parametres != (yyvsp[(2) - (2)].infoBison).num_funcio_parametres) {
                  funcioDeclaradaCorrecte = FALSE;
                  num_errors++; printErrorSintactic(TRUE, ERR_DEF_FUNCIO_NUM_PARAMS_DIFERENTS, (yyvsp[(2) - (2)].infoBison).valor);  
               }
               else {
                  if (simbol.tipus_var == (yyvsp[(1) - (2)].infoBison).tipus_var) {
                     /* Numero de parametres correctes per definir la funcio */
                     recordsetParam = (yyvsp[(2) - (2)].infoBison).seguent_param_funcio;
                     for (count = 0; count < (yyvsp[(2) - (2)].infoBison).num_funcio_parametres; count++) {
                        if ((recordsetParam -> array != TRUE) && (simbol.funcio_params[count].array == TRUE)) {
                           funcioDeclaradaCorrecte = FALSE; num_errors++; printErrorSintactic(TRUE, ERR_FUNCIO_PARAM_ES_ARRAY, count + 1, (yyvsp[(2) - (2)].infoBison).valor);
                        }
                        else if ((recordsetParam -> array == TRUE) && (simbol.funcio_params[count].array != TRUE)) {
                           funcioDeclaradaCorrecte = FALSE; num_errors++; printErrorSintactic(TRUE, ERR_FUNCIO_PARAM_NO_ES_ARRAY, count + 1, (yyvsp[(2) - (2)].infoBison).valor);
                        }
                        else {
                           if (simbol.funcio_params[count].tipus_var != recordsetParam -> tipus_var) {
                              funcioDeclaradaCorrecte = FALSE;
                              num_errors++; printErrorSintactic(TRUE, ERR_PARAM_FUNCIO_DEFINICIO, count + 1, (yyvsp[(2) - (2)].infoBison).valor, tipusDadesID(simbol.funcio_params[count].tipus_var, 0), tipusDadesID(recordsetParam -> tipus_var, 0));
                           }
                        }
                        recordsetParam = recordsetParam -> seguent_param_funcio;
                     }
                     if (funcioDeclaradaCorrecte) {
                        printInfoSintactic(OK_DEFINICIO_FUNCIO, (yyvsp[(2) - (2)].infoBison).valor);   
                     }
                  }
                  else { funcioDeclaradaCorrecte = FALSE; num_errors++; printErrorSintactic(TRUE, ERR_VALOR_RETORN_FUNCIO, (yyvsp[(2) - (2)].infoBison).valor); }
               } 
            }            
         }
         else { funcioDeclaradaCorrecte = FALSE; num_errors++; printErrorSintactic(TRUE, ERR_VARIABLE_NO_FUNCIO, (yyvsp[(2) - (2)].infoBison).valor); }
      }
      else {

         idSimbol = (char *) malloc(strlen((yyvsp[(2) - (2)].infoBison).valor) + 1);
         strcpy(idSimbol, (yyvsp[(2) - (2)].infoBison).valor);
         simbol.tipus_var = (yyvsp[(1) - (2)].infoBison).tipus_var;
         tipus_var_funcio_retorn = (yyvsp[(1) - (2)].infoBison).tipus_var;
         (yyval.infoBison).tipus_var = (yyvsp[(1) - (2)].infoBison).tipus_var;
         simbol.tipus = FUNCIO;
         simbol.funcio = TRUE;
         simbol.num_funcio_parametres = (yyvsp[(2) - (2)].infoBison).num_funcio_parametres;
      
         simbol.idLexic = ID_IDENTIFICADOR;
         strcpy(simbol.nomLexic, "IDENTIFICADOR");
         simbol.ambit = -1; 
         
         if ((yyvsp[(2) - (2)].infoBison).num_funcio_parametres == 1) {
            if (((yyvsp[(2) - (2)].infoBison).seguent_param_funcio -> tipus_var == TIPUS_VOID) && (!esTipus((yyvsp[(2) - (2)].infoBison).seguent_param_funcio -> valor))) {
               funcioDeclaradaCorrecte = FALSE;
               num_errors++; printErrorSintactic(TRUE, ERR_PARAMETRE_FUNCIO_VOID);
            }
            else if ((yyvsp[(2) - (2)].infoBison).seguent_param_funcio -> tipus_var == TIPUS_VOID) {
               (yyvsp[(2) - (2)].infoBison).num_funcio_parametres--;
               simbol.num_funcio_parametres = 0;
            }
         }
         
         if (funcioDeclaradaCorrecte) {
            simbol.funcio_params = malloc(sizeof(struct t_param) * (yyvsp[(2) - (2)].infoBison).num_funcio_parametres);
          
            recordsetParam = (yyvsp[(2) - (2)].infoBison).seguent_param_funcio;
            for (count = 0; (count < (yyvsp[(2) - (2)].infoBison).num_funcio_parametres); count++) {
               if (recordsetParam -> tipus_var == TIPUS_VOID) {
                  funcioDeclaradaCorrecte = FALSE;
                  num_errors++; printErrorSintactic(TRUE, ERR_PARAMETRE_FUNCIO_VOID);
               }
               else {
                  simbol.funcio_params[count].tipus_var = recordsetParam -> tipus_var;
                  if (recordsetParam -> array == TRUE) {
                     simbol.funcio_params[count].array = TRUE;
                     simbol.funcio_params[count].tam_array = recordsetParam -> tam_array;
                  }
                  else {
                     simbol.funcio_params[count].array = FALSE;
                     simbol.funcio_params[count].tam_array = 0;
                  }
               }
               recordsetParam = recordsetParam -> seguent_param_funcio;
            } 
            
            if (funcioDeclaradaCorrecte) {
               if (sym_global_add((char *) idSimbol, &simbol) != SYMTAB_OK) {
                  funcioDeclaradaCorrecte = FALSE;
                  num_errors++; printErrorSintactic(TRUE, ERR_INTRODUCCIO_TAULA_SIMBOL_FUNC_VAR, "funcio", idSimbol);
               }
               else { 
                  printInfoSintactic(OK_INTRODUCCIO_TAULA_SIMBOL_FUN_VAR, "funcio", idSimbol);
               }
         
               printSimbolInfo((char *) idSimbol); 
            }
         }
      }
      if (funcioDeclaradaCorrecte) {
         iniRegistreActivacioFuncions((yyvsp[(2) - (2)].infoBison).valor);
         iniC3AFuncions();
         
         quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
         quadrupleC3A -> num_sentencia = C3AFuncions -> num_quadruples + 1;
         quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen((yyvsp[(2) - (2)].infoBison).valor) + 7);
         sprintf(quadrupleC3A -> sentenciaC3A, "START %s", (yyvsp[(2) - (2)].infoBison).valor);
          
         encuar(C3AFuncions -> quadrupleC3A, (void *) quadrupleC3A);
         C3AFuncions -> num_quadruples++;
         
         afegirParamRA(registreActivacioFuncions, "RETURN", (yyvsp[(1) - (2)].infoBison).tipus_var, (yyvsp[(1) - (2)].infoBison).array, (yyvsp[(1) - (2)].infoBison).tam_array);                   
         
         recordsetParam = (yyvsp[(2) - (2)].infoBison).seguent_param_funcio;
         for (count = 0; count < (yyvsp[(2) - (2)].infoBison).num_funcio_parametres; count++) {
            if (esTipus(recordsetParam -> valor) == FALSE) {          
               idSimbol = (char *) malloc(strlen(recordsetParam -> valor) + 1);
               strcpy(idSimbol, recordsetParam -> valor);
               simbol.tipus_var = recordsetParam -> tipus_var;
               simbol.tipus = VARIABLE;
               simbol.funcio = FALSE;
               simbol.num_funcio_parametres = 0;
      
               if (recordsetParam -> array == TRUE) {
                  simbol.array = TRUE;
                  simbol.tam_array = recordsetParam -> tam_array;
               }
               else simbol.array = FALSE;
      
               simbol.idLexic = ID_IDENTIFICADOR;
               strcpy(simbol.nomLexic, "IDENTIFICADOR");
               simbol.ambit = sym_get_scope(); 

               simbol.funcio_params = NULL;
           
               if (sym_add((char *) idSimbol, &simbol) != SYMTAB_OK) { num_errors++; printErrorSintactic(TRUE, ERR_PARAMETRES_LOCALS_FUNCIO, idSimbol); }
               else {
                  afegirParamRA(registreActivacioFuncions, recordsetParam -> valor, recordsetParam -> tipus_var, recordsetParam -> array, recordsetParam -> tam_array);
                  printInfoSintactic(OK_PARAMETRES_LOCALS_FUNCIO, idSimbol);
               }   
            }
            else printErrorSintactic(FALSE, WARNING_NOM_PARAMETRE_FUNCIO_NO_DEC, count + 1, idSimbol);
            
            recordsetParam = recordsetParam -> seguent_param_funcio;
         }      
      }
   ;}
    break;

  case 174:

/* Line 1455 of yacc.c  */
#line 2681 "sintactic.y"
    {                
      currentScope = sym_get_scope();
      sym_pop_scope();
      printInfoSintactic(OK_DECREMENT_AMBIT, currentScope);
      if (funcioDeclaradaCorrecte) {
         quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
         quadrupleC3A -> num_sentencia = C3AFuncions -> num_quadruples + 1;
         encuar(C3AFuncions -> quadrupleC3A, (void *) quadrupleC3A);
         C3AFuncions -> num_quadruples++;

         if (valor_retorn == NULL) {
            quadrupleC3A -> sentenciaC3A = (char * ) malloc(strlen("RETURN") + 1);
            sprintf(quadrupleC3A -> sentenciaC3A, "RETURN"); 
         }
         else {
            quadrupleC3A -> sentenciaC3A = (char * ) malloc(strlen("RETURN ") + strlen(valor_retorn) + 1);
            sprintf(quadrupleC3A -> sentenciaC3A, "RETURN %s", valor_retorn);
         }
         completar_llista((Cua *) llista_seguents_funcio_retorn, (yyvsp[(5) - (5)].infoBison).punter_quadruple);
         completar_llista((Cua *) (yyvsp[(4) - (5)].infoBison).llista_seguents, (yyvsp[(5) - (5)].infoBison).punter_quadruple);                     
         printRegistreActivacio(registreActivacioFuncions);
         printC3AFuncions(C3AFuncions, (yyvsp[(2) - (5)].infoBison).valor);
      }
      
      fprintf(yyout, ">>> linia %i: declaration_specifiers declarator compound_statement REDUCE TO function_definition\n", numFila);
   ;}
    break;

  case 175:

/* Line 1455 of yacc.c  */
#line 2707 "sintactic.y"
    {               
      fprintf(yyout, ">>> linia %i: declarator declaration_list compound_statement REDUCE TO function_definition\n", numFila);
   ;}
    break;

  case 176:

/* Line 1455 of yacc.c  */
#line 2716 "sintactic.y"
    {
      fprintf(yyout, ">>> linia %i: declaration REDUCE TO declaration_list\n", numFila);
   ;}
    break;

  case 177:

/* Line 1455 of yacc.c  */
#line 2719 "sintactic.y"
    {
      fprintf(yyout, ">>> linia %i: declaration_list declaration REDUCE TO declaration_list\n", numFila);
   ;}
    break;

  case 178:

/* Line 1455 of yacc.c  */
#line 2727 "sintactic.y"
    { 
   (yyval.infoBison).punter_quadruple = C3AFuncions -> num_quadruples + 1; 
;}
    break;

  case 179:

/* Line 1455 of yacc.c  */
#line 2734 "sintactic.y"
    {
   (yyval.infoBison).llista_seguents = (void *) crear_cua();
    
   quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
   quadrupleC3A -> num_sentencia = C3AFuncions -> num_quadruples + 1;
   encuar(C3AFuncions -> quadrupleC3A, (void *) quadrupleC3A);
   C3AFuncions -> num_quadruples++;

   quadrupleC3A -> sentenciaC3A = (char * ) malloc(strlen("GOTO ") + 1);
   sprintf(quadrupleC3A -> sentenciaC3A, "GOTO ");     
         
   (yyval.infoBison).punter_quadruple = C3AFuncions -> num_quadruples;
   encuar((void *) (yyval.infoBison).llista_seguents,(void *) quadrupleC3A);
;}
    break;



/* Line 1455 of yacc.c  */
#line 5289 "sintactic.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 2749 "sintactic.y"


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: emet_operacioC3A(struct t_infoBison * param1,                         ##
      ##                              struct t_infoBison * param2,                            ##
      ##                              struct t_infoBison * paramResult,                       ##   
      ##                              int operacio)                                           ##
      ##                   - param1: parametre 1                                              ##
      ##                   - param2: parametre 2                                              ##
      ##                   - paramResult: parametre resultat                                  ##
      ##                   - operacio: operacio                                               ##
      ##                                                                                      ##
      ##                     Funcio que emet una operacio en C3A                              ##
      ##                                                                                      ##
      ########################################################################################## */
      
void emet_operacioC3A(struct t_infoBison * param1, struct t_infoBison * param2, struct t_infoBison * paramResult, int operacio) { 
   int val, err = FALSE;
   int tipus_var_retorn;
   char * varTMPCasting, * varTMPOperacio, * varTMPComplex1, * varTMPComplex2, * varTMP;
   t_registreC3A * pC3A;
   t_registreActivacio * pRA;
   int solveAssignC3A;
   char * cp1, * cp2;
   
   solveAssignC3A = FALSE;
   currentScope = sym_get_scope();
   if (currentScope == -1) { pRA = registreActivacioGlobal; pC3A = C3AGlobal; }
   else { pRA = registreActivacioFuncions; pC3A = C3AFuncions; } 
   
   if (((operacio != '=') && (param1 -> tipus_var != TIPUS_NULL) && (param2 -> tipus_var != TIPUS_NULL) &&
       (param1 -> tipus_var != TIPUS_STRUCT) && (param2 -> tipus_var != TIPUS_STRUCT)) ||
       ((operacio == '=') && (paramResult -> tipus_var != TIPUS_NULL) && (param1 -> tipus_var != TIPUS_NULL) && 
       (paramResult -> tipus_var != TIPUS_STRUCT) && (param1 -> tipus_var != TIPUS_STRUCT))) {
                    
      if (operacio != '=') {
         cp1 = param1 -> valorC3A;
         cp2 = param2 -> valorC3A;
      
         val = operacioC3A(param1 -> tipus_var, param2 -> tipus_var, operacio);
         if (val == 1) tipus_var_retorn = param2 -> tipus_var;
         else tipus_var_retorn = param1 -> tipus_var;
  
         if (((param1 -> camp_struct_indexat == TRUE) && (param2 -> camp_struct_indexat == TRUE)) ||
            ((param1 -> array_indexat == TRUE) && (param2 -> array_indexat == TRUE)) ||
            ((param1 -> camp_struct_indexat == TRUE) && (param2 -> array_indexat == TRUE)) ||
            ((param1 -> array_indexat == TRUE) && (param2 -> camp_struct_indexat == TRUE))) {
            
            /* Cas complex: param1 i param2 son tipus complexes */
            if ((param1 -> camp_struct_indexat == TRUE) && (param2 -> camp_struct_indexat == TRUE)) {
               varTMPComplex1 = afegirVarTemporalRA(pRA, param1 -> tipus_var);
               quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
               quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
            
               quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPComplex1) + strlen(param1 -> valorC3A) + log10Func(param1 -> offset_camp_struct_indexat) + 7);
               sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s[%d]", varTMPComplex1, param1 -> valorC3A, param1 -> offset_camp_struct_indexat);
 
               param1 -> valorC3A = varTMPComplex1;
            
               encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
               pC3A -> num_quadruples++;
            
               varTMPComplex2 = afegirVarTemporalRA(pRA, param2 -> tipus_var);
               quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
               quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
            
               quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPComplex2) + strlen(param2 -> valorC3A) + log10Func(param2 -> offset_camp_struct_indexat) + 7);
               sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s[%d]", varTMPComplex2, param2 -> valorC3A, param2 -> offset_camp_struct_indexat);
 
               param2 -> valorC3A = varTMPComplex2;
               encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
               pC3A -> num_quadruples++;
            }
            else if ((param1 -> camp_struct_indexat == TRUE) && (param2 -> array_indexat == TRUE)) {
               varTMPComplex1 = afegirVarTemporalRA(pRA, param1 -> tipus_var);
               quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
               quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
            
               quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPComplex1) + strlen(param1 -> valorC3A) + log10Func(param1 -> offset_camp_struct_indexat) + 7);
               sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s[%d]", varTMPComplex1, param1 -> valorC3A, param1 -> offset_camp_struct_indexat);
 
               param1 -> valorC3A = varTMPComplex1;
            
               encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
               pC3A -> num_quadruples++;
               
               varTMPComplex2 = afegirVarTemporalRA(pRA, param2 -> tipus_var);
               quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
               quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
            
               quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPComplex2) + strlen(param2 -> valorC3A) + strlen(param2 -> array_indexat_offset) + 7);
               sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s[%s]", varTMPComplex2, param2 -> valorC3A, param2 -> array_indexat_offset);
 
               param2 -> valorC3A = varTMPComplex2;
            
               encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
               pC3A -> num_quadruples++;
            }
            else if ((param1 -> array_indexat == TRUE) && (param2 -> camp_struct_indexat == TRUE)) {
               varTMPComplex1 = afegirVarTemporalRA(pRA, param1 -> tipus_var);
               quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
               quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
            
               quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPComplex1) + strlen(param1 -> valorC3A) + strlen(param1 -> array_indexat_offset) + 7);
               sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s[%s]", varTMPComplex1, param1 -> valorC3A, param1 -> array_indexat_offset);
 
               param1 -> valorC3A = varTMPComplex1;
            
               encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
               pC3A -> num_quadruples++;
                              
               varTMPComplex2 = afegirVarTemporalRA(pRA, param2 -> tipus_var);
               quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
               quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
            
               quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPComplex2) + strlen(param2 -> valorC3A) + log10Func(param2 -> offset_camp_struct_indexat) + 7);
               sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s[%d]", varTMPComplex2, param2 -> valorC3A, param2 -> offset_camp_struct_indexat);
 
               param2 -> valorC3A = varTMPComplex2;
            
               encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
               pC3A -> num_quadruples++;
            }
            else {
               varTMPComplex1 = afegirVarTemporalRA(pRA, param1 -> tipus_var);
               quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
               quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
            
               quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPComplex1) + strlen(param1 -> valorC3A) + strlen(param1 -> array_indexat_offset) + 7);
               sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s[%s]", varTMPComplex1, param1 -> valorC3A, param1 -> array_indexat_offset);
 
               param1 -> valorC3A = varTMPComplex1;
            
               encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
               pC3A -> num_quadruples++;

               varTMPComplex2 = afegirVarTemporalRA(pRA, param2 -> tipus_var);
               quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
               quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
            
               quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPComplex2) + strlen(param2 -> valorC3A) + strlen(param2 -> array_indexat_offset) + 7);
               sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s[%s]", varTMPComplex2, param2 -> valorC3A, param2 -> array_indexat_offset);
 
               param2 -> valorC3A = varTMPComplex2;
            
               encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
               pC3A -> num_quadruples++;
            }       
         }
         else if ((param1 -> camp_struct_indexat == TRUE) || (param1 -> array_indexat == TRUE) ||
                  (param2 -> camp_struct_indexat == TRUE) || (param2 -> array_indexat == TRUE))  {
            
            /* Cas semi-complex: param1 o param2 es de tipus complex */
            if (param1 -> camp_struct_indexat == TRUE) {
               varTMPComplex1 = afegirVarTemporalRA(pRA, param1 -> tipus_var);
               quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
               quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
            
               quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPComplex1) + strlen(param1 -> valorC3A) + log10Func(param1 -> offset_camp_struct_indexat) + 7);
               sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s[%d]", varTMPComplex1, param1 -> valorC3A, param1 -> offset_camp_struct_indexat);
 
               param1 -> valorC3A = varTMPComplex1;
            }
            else if (param2 -> camp_struct_indexat == TRUE) {
               varTMPComplex1 = afegirVarTemporalRA(pRA, param2 -> tipus_var);
               quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
               quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
            
               quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPComplex1) + strlen(param2 -> valorC3A) + log10Func(param2 -> offset_camp_struct_indexat) + 7);
               sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s[%d]", varTMPComplex1, param2 -> valorC3A, param2 -> offset_camp_struct_indexat);
 
               param2 -> valorC3A = varTMPComplex1;
            }
            else if (param1 -> array_indexat == TRUE) { 
               varTMPComplex1 = afegirVarTemporalRA(pRA, param1 -> tipus_var);
               quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
               quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
            
               quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPComplex1) + strlen(param1 -> valorC3A) + strlen(param1 -> array_indexat_offset) + 7);
               sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s[%s]", varTMPComplex1, param1 -> valorC3A, param1 -> array_indexat_offset);
 
               param1 -> valorC3A = varTMPComplex1;
            }
            else {
               varTMPComplex1 = afegirVarTemporalRA(pRA, param2 -> tipus_var);
               quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
               quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
            
               quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPComplex1) + strlen(param2 -> valorC3A) + strlen(param2 -> array_indexat_offset) + 7);
               sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s[%s]", varTMPComplex1, param2 -> valorC3A, param2 -> array_indexat_offset);
 
               param2 -> valorC3A = varTMPComplex1;
            }
            encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
            pC3A -> num_quadruples++;
         }
         else {
            if ((param1 -> tipus_var == TIPUS_CHARACTER) || (param2 -> tipus_var == TIPUS_CHARACTER)) {
               if ((param1 -> tipus_var == TIPUS_CHARACTER) && (strlen(param1 -> valorC3A) == 1)) {
                  varTMP = (char *) malloc(4);
                  sprintf(varTMP, "'%s'", param1 -> valorC3A);
                  param1 -> valorC3A = varTMP;    
               }
               if ((param2 -> tipus_var == TIPUS_CHARACTER) && (strlen(param2 -> valorC3A) == 1)) {
                  varTMP = (char *) malloc(4);
                  sprintf(varTMP, "'%s'", param2 -> valorC3A);
                  param2 -> valorC3A = varTMP;    
               }
            }  
         }        
      }
      else {
	     val = operacioC3A(paramResult -> tipus_var, param1 -> tipus_var, operacio);
	     tipus_var_retorn = paramResult -> tipus_var;               
         
         if (((param1 -> camp_struct_indexat == TRUE) && (paramResult -> camp_struct_indexat == TRUE)) ||
            ((param1 -> array_indexat == TRUE) && (paramResult -> array_indexat == TRUE)) ||
            ((param1 -> camp_struct_indexat == TRUE) && (paramResult -> array_indexat == TRUE)) ||
            ((param1 -> array_indexat == TRUE) && (paramResult -> camp_struct_indexat == TRUE))) {
                     
            /* Cas complex: param1 i param2 son tipus complexes */
            if ((param1 -> camp_struct_indexat == TRUE) && (paramResult -> camp_struct_indexat == TRUE)) {
               varTMPComplex1 = (char *) malloc(strlen(param1 -> valorC3A) + log10Func(param1 -> offset_camp_struct_indexat) + 3);
               sprintf(varTMPComplex1, "%s[%d]", param1 -> valorC3A, param1 -> offset_camp_struct_indexat);
 
               param1 -> valorC3A = varTMPComplex1;
               
               varTMPComplex2 = (char *) malloc(strlen(paramResult -> valorC3A) + log10Func(paramResult -> offset_camp_struct_indexat) + 3);
               sprintf(varTMPComplex2, "%s[%d]", paramResult -> valorC3A, paramResult -> offset_camp_struct_indexat);
 
               paramResult -> valorC3A = varTMPComplex2;
               solveAssignC3A = TRUE;                    
            }
            else if ((param1 -> camp_struct_indexat == TRUE) && (paramResult -> array_indexat == TRUE)) {
               varTMPComplex1 = (char *) malloc(strlen(param1 -> valorC3A) + log10Func(param1 -> offset_camp_struct_indexat) + 3);
               sprintf(varTMPComplex1, "%s[%d]", param1 -> valorC3A, param1 -> offset_camp_struct_indexat);
 
               param1 -> valorC3A = varTMPComplex1;
               
               varTMPComplex2 = (char *) malloc(strlen(paramResult -> valorC3A) + strlen(paramResult -> array_indexat_offset) + 3);
               sprintf(varTMPComplex2, "%s[%s]", paramResult -> valorC3A, paramResult -> array_indexat_offset);
 
               paramResult -> valorC3A = varTMPComplex2;
               solveAssignC3A = TRUE;
            }
            else if ((param1 -> array_indexat == TRUE) && (paramResult -> camp_struct_indexat == TRUE)) {
               varTMPComplex1 = (char *) malloc(strlen(param1 -> valorC3A) + strlen(param1 -> array_indexat_offset) + 3);
               sprintf(varTMPComplex1, "%s[%s]", param1 -> valorC3A, param1 -> array_indexat_offset);
 
               param1 -> valorC3A = varTMPComplex1;
               
               varTMPComplex2 = (char *) malloc(strlen(paramResult -> valorC3A) + log10Func(paramResult -> offset_camp_struct_indexat) + 3);
               sprintf(varTMPComplex2, "%s[%d]", paramResult -> valorC3A, paramResult -> offset_camp_struct_indexat);
 
               paramResult -> valorC3A = varTMPComplex2;
               solveAssignC3A = TRUE;
            }
            else {
               varTMPComplex1 = (char *) malloc(strlen(param1 -> valorC3A) + strlen(param1 -> array_indexat_offset) + 3);
               sprintf(varTMPComplex1, "%s[%s]", param1 -> valorC3A, param1 -> array_indexat_offset);
 
               param1 -> valorC3A = varTMPComplex1;
               
               varTMPComplex2 = (char *) malloc(strlen(paramResult -> valorC3A) + strlen(paramResult -> array_indexat_offset) + 3);
               sprintf(varTMPComplex2, "%s[%s]", paramResult -> valorC3A, paramResult -> array_indexat_offset);
 
               paramResult -> valorC3A = varTMPComplex2;
               solveAssignC3A = TRUE;
            }
         }
         else if ((param1 -> camp_struct_indexat == TRUE) || (param1 -> array_indexat == TRUE) ||
                  (paramResult -> camp_struct_indexat == TRUE) || (paramResult -> array_indexat == TRUE))  {
            
            /* Cas semi-complex: param1 o param2 es de tipus complex */
            if (param1 -> camp_struct_indexat == TRUE) {
               varTMPComplex1 = (char *) malloc(strlen(param1 -> valorC3A) + log10Func(param1 -> offset_camp_struct_indexat) + 3);
               sprintf(varTMPComplex1, "%s[%d]", param1 -> valorC3A, param1 -> offset_camp_struct_indexat);
 
               param1 -> valorC3A = varTMPComplex1;            
            }
            else if (paramResult -> camp_struct_indexat == TRUE) {
               varTMPComplex1 = (char *) malloc(strlen(paramResult -> valorC3A) + log10Func(paramResult -> offset_camp_struct_indexat) + 3);
               sprintf(varTMPComplex1, "%s[%d]", paramResult -> valorC3A, paramResult -> offset_camp_struct_indexat);
 
               paramResult -> valorC3A = varTMPComplex1;
            }
            else if (param1 -> array_indexat == TRUE) {
               varTMPComplex1 = (char *) malloc(strlen(param1 -> valorC3A) + strlen(param1 -> array_indexat_offset) + 3);
               sprintf(varTMPComplex1, "%s[%s]", param1 -> valorC3A, param1 -> array_indexat_offset);
 
               param1 -> valorC3A = varTMPComplex1;
            }
            else {
               varTMPComplex1 = (char *) malloc(strlen(paramResult -> valorC3A) + strlen(paramResult -> array_indexat_offset) + 3);
               sprintf(varTMPComplex1, "%s[%s]", paramResult -> valorC3A, paramResult -> array_indexat_offset);
 
               paramResult -> valorC3A = varTMPComplex1;
            }
         }
         else {
            if ((param1 -> tipus_var == TIPUS_CHARACTER) || (paramResult -> tipus_var == TIPUS_CHARACTER)) {
               if ((param1 -> tipus_var == TIPUS_CHARACTER) && (strlen(param1 -> valorC3A) == 1)) {
                  varTMP = (char *) malloc(4);
                  sprintf(varTMP, "'%s'", param1 -> valorC3A);
                  param1 -> valorC3A = varTMP;    
               }
               if ((paramResult -> tipus_var == TIPUS_CHARACTER) && (strlen(paramResult -> valorC3A) == 1)) {
                  varTMP = (char *) malloc(4);
                  sprintf(varTMP, "'%s'", paramResult -> valorC3A);
                  paramResult -> valorC3A = varTMP;    
               }
            }  
         } 
      }

      if (val != 0) {
         varTMPCasting = afegirVarTemporalRA(pRA, tipus_var_retorn);
      
         quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
         quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
      
         if (val == 1) {
            quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPCasting) + strlen(strCastingC3A) + strlen(param1 -> valorC3A) + 6);
            sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s %s", varTMPCasting, strCastingC3A, param1 -> valorC3A);
         }
         else {
            if (operacio != '=') {
               quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPCasting) + strlen(strCastingC3A) + strlen(param2 -> valorC3A) + 6);
               sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s %s", varTMPCasting, strCastingC3A, param2 -> valorC3A);
            }
            else {
               quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPCasting) + strlen(strCastingC3A) + strlen(param1 -> valorC3A) + 6);
               sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s %s", varTMPCasting, strCastingC3A, param1 -> valorC3A);         
            }
         }
      
         encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
         pC3A -> num_quadruples++;
      }
      else {
         if (solveAssignC3A == TRUE) {
            varTMPCasting = afegirVarTemporalRA(pRA, tipus_var_retorn);
      
            quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
            quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
            
            quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPCasting) + strlen(param1 -> valorC3A) + 5);
            sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s", varTMPCasting, param1 -> valorC3A);
               
            encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
            pC3A -> num_quadruples++;
            val = 2;
         }
      }

      /* ################# C3A -> OPERACIO ################# */
      quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
      quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
      encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
      pC3A -> num_quadruples++;
   
      if (operacio != '=') {
         varTMPOperacio = afegirVarTemporalRA(pRA, tipus_var_retorn);
         paramResult -> valorC3A = varTMPOperacio;
   
         if (val == 1) {
            quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(paramResult -> valorC3A) + strlen(varTMPCasting) + strlen(strOperacioC3A) + strlen(param2 -> valorC3A) + 7);
            sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s %s %s", paramResult -> valorC3A, varTMPCasting, strOperacioC3A, param2 -> valorC3A);
         }
         else if (val == 2) {
            quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(paramResult -> valorC3A) + strlen(param1 -> valorC3A) + strlen(strOperacioC3A) + strlen(varTMPCasting) + 7);
            sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s %s %s", paramResult -> valorC3A, param1 -> valorC3A, strOperacioC3A, varTMPCasting);
         }
         else {
            quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(paramResult -> valorC3A) + strlen(param1 -> valorC3A) + strlen(strOperacioC3A) + strlen(param2 -> valorC3A) + 7);
            sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s %s %s", paramResult -> valorC3A, param1 -> valorC3A, strOperacioC3A, param2 -> valorC3A);
         }
         param1 -> valorC3A = cp1;
         param2 -> valorC3A = cp2;
      }
      else {
         if (val == 2) {
            quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(paramResult -> valorC3A) + strlen(varTMPCasting) + 5);
            sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s", paramResult -> valorC3A, varTMPCasting);   
         }
         else {
            quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(paramResult -> valorC3A) + strlen(param1 -> valorC3A) + 5);
            sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s", paramResult -> valorC3A, param1 -> valorC3A);
         }   
      }
      paramResult -> array_indexat = FALSE;
      paramResult -> camp_struct_indexat = FALSE;
      paramResult -> tipus_var = tipus_var_retorn;
   }
   else paramResult -> tipus_var = TIPUS_NULL;   
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: emet_operacioCanviSigneC3A(struct t_infoBison * param1,               ##
      ##                                           struct t_infoBison * paramResult)          ##
      ##                   - param1: parametre1                                               ##
      ##                   - paramResult: parametre resultat                                  ##
      ##                                                                                      ##
      ##                     Funcio que emet una operacio de canvi de signe en C3A            ##
      ##                                                                                      ##
      ########################################################################################## */
      
void emet_operacioCanviSigneC3A(struct t_infoBison * param1, struct t_infoBison * paramResult) {
   t_registreC3A * pC3A;
   t_registreActivacio * pRA;   
   char * varTMPComplex1, * varTMPOperacio;
   char * cp1, * varTMP;
   
   currentScope = sym_get_scope();
   if (currentScope == -1) { pRA = registreActivacioGlobal; pC3A = C3AGlobal; }
   else { pRA = registreActivacioFuncions; pC3A = C3AFuncions; } 
   
   if ((param1 -> tipus_var != TIPUS_NULL) && (param1 -> tipus_var != TIPUS_STRUCT)) {
      cp1 = param1 -> valorC3A;
      
      if ((param1 -> camp_struct_indexat == TRUE) || (param1 -> array_indexat == TRUE)) {
         if (param1 -> camp_struct_indexat == TRUE) {
            varTMPComplex1 = (char *) malloc(strlen(param1 -> valorC3A) + log10Func(param1 -> offset_camp_struct_indexat) + 3);
            sprintf(varTMPComplex1, "%s[%d]", param1 -> valorC3A, param1 -> offset_camp_struct_indexat);
 
            param1 -> valorC3A = varTMPComplex1; 
         }
         else {
            varTMPComplex1 = (char *) malloc(strlen(param1 -> valorC3A) + strlen(param1 -> array_indexat_offset) + 3);
            sprintf(varTMPComplex1, "%s[%s]", param1 -> valorC3A, param1 -> array_indexat_offset);
 
            param1 -> valorC3A = varTMPComplex1;
         }
      }
      else {
         if (param1 -> tipus_var == TIPUS_CHARACTER) {
            if ((param1 -> tipus_var == TIPUS_CHARACTER) && (strlen(param1 -> valorC3A) == 1)) {
               varTMP = (char *) malloc(4);
               sprintf(varTMP, "'%s'", param1 -> valorC3A);
               param1 -> valorC3A = varTMP;    
            }
         }  
      }
      
      /* ################# C3A -> OPERACIO ################# */
      quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
      quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
      encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
      pC3A -> num_quadruples++;
   
      varTMPOperacio = afegirVarTemporalRA(pRA, param1 -> tipus_var);
      paramResult -> valorC3A = varTMPOperacio;
      paramResult -> tipus_var = param1 -> tipus_var;

      switch (param1 -> tipus_var) {
         case TIPUS_CHARACTER: strcpy(strOperacioC3A, "CHSC"); break; 
         case TIPUS_SHORT: strcpy(strOperacioC3A, "CHSS"); break;
         case TIPUS_INTEGER: strcpy(strOperacioC3A, "CHSI"); break;            
         case TIPUS_LONG: strcpy(strOperacioC3A, "CHSL"); break;             
         case TIPUS_FLOAT: strcpy(strOperacioC3A, "CHSF"); break;
         case TIPUS_DOUBLE: strcpy(strOperacioC3A, "CHSD"); break;            
      }
            
      quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(paramResult -> valorC3A) + strlen(strOperacioC3A) + strlen(param1 -> valorC3A) + 6);
      sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s %s", paramResult -> valorC3A, strOperacioC3A, param1 -> valorC3A);
             
      param1 -> valorC3A = cp1;
      paramResult -> array_indexat = FALSE;
      paramResult -> camp_struct_indexat = FALSE;
   }
   else paramResult -> tipus_var = TIPUS_NULL;
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: emet_condicioC3A(struct t_infoBison * param1,                         ##
      ##                                 struct t_infoBison * paramResult)                    ##
      ##                   - param1: parametre1                                               ##
      ##                   - paramResult: parametre resultat                                  ##
      ##                                                                                      ##
      ##                     Funcio que emet una condicio en C3A                              ##
      ##                                                                                      ##
      ########################################################################################## */
      
void emet_condicioC3A(struct t_infoBison * param1, struct t_infoBison * paramResult) {
   int val;
   char * varTMPCasting, * varTMPComplex1, * varTMP;
   t_registreC3A * pC3A;
   t_registreActivacio * pRA;
   
   currentScope = sym_get_scope();
   if (currentScope == -1) { pRA = registreActivacioGlobal; pC3A = C3AGlobal; }
   else { pRA = registreActivacioFuncions; pC3A = C3AFuncions; }
   
   if ((param1 -> tipus_var != TIPUS_NULL) && (paramResult -> tipus_var != TIPUS_STRUCT)) {
      
      val = operacioC3A(TIPUS_INTEGER, param1 -> tipus_var, '=');
      
      if ((param1 -> camp_struct_indexat == TRUE) || (param1 -> array_indexat == TRUE)) {     
         /* Cas semi-complex: param1 o param2 es de tipus complex */
         if (param1 -> camp_struct_indexat == TRUE) {
            varTMPComplex1 = (char *) malloc(strlen(param1 -> valorC3A) + log10Func(param1 -> offset_camp_struct_indexat) + 3);
            sprintf(varTMPComplex1, "%s[%d]", param1 -> valorC3A, param1 -> offset_camp_struct_indexat);
 
            param1 -> valorC3A = varTMPComplex1;            
         }
         else if (param1 -> array_indexat == TRUE) {
            varTMPComplex1 = (char *) malloc(strlen(param1 -> valorC3A) + strlen(param1 -> array_indexat_offset) + 3);
            sprintf(varTMPComplex1, "%s[%s]", param1 -> valorC3A, param1 -> array_indexat_offset);
 
            param1 -> valorC3A = varTMPComplex1;
         }
      }
      else {
         if ((param1 -> tipus_var == TIPUS_CHARACTER) && (strlen(param1 -> valorC3A) == 1)) {
            varTMP = (char *) malloc(4);
            sprintf(varTMP, "'%s'", param1 -> valorC3A);
            param1 -> valorC3A = varTMP;    
         }  
      }
         
      if (val == 2) {
         quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
         quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
         
         varTMPCasting = afegirVarTemporalRA(pRA, TIPUS_INTEGER);  
         quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPCasting) + strlen(strCastingC3A) + strlen(param1 -> valorC3A) + 6);
         sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s %s", varTMPCasting, strCastingC3A, param1 -> valorC3A);

         encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
         pC3A -> num_quadruples++;
      }
      
      /* ################# C3A -> CONDICIO ################# */
      quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
      quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
      encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
      pC3A -> num_quadruples++;
 
      if (val == 2) {
         quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPCasting) + 10);
         sprintf(quadrupleC3A -> sentenciaC3A, "IF %s GOTO ", varTMPCasting);
      }
      else {
         quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(param1 -> valorC3A) + 10);
         sprintf(quadrupleC3A -> sentenciaC3A, "IF %s GOTO ", param1 -> valorC3A);
      }

  	  paramResult -> llista_certs = (void *) crear_cua();
	  encuar((void *) paramResult -> llista_certs, (void *) quadrupleC3A); 
	 
      quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
      quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
      encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
      pC3A -> num_quadruples++;

      quadrupleC3A -> sentenciaC3A = (char * ) malloc(strlen("GOTO ") + 1);
  	  sprintf(quadrupleC3A -> sentenciaC3A, "GOTO ");

  	  paramResult -> llista_falsos = (void *) crear_cua();
	  encuar((void *) paramResult -> llista_falsos, (void *) quadrupleC3A);    
   }    
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: emet_saltC3A(int num_linia)                                           ##  
      ##                   - num_linia: numero de linia                                       ##
      ##                                                                                      ##
      ##                     Funcio que emet un salt al numero de linia indicat               ##
      ##                                                                                      ##
      ########################################################################################## */
      
void emet_saltC3A(int num_linia) {
   t_registreC3A * pC3A;
   t_registreActivacio * pRA;

   currentScope = sym_get_scope();
   if (currentScope == -1) { pRA = registreActivacioGlobal; pC3A = C3AGlobal; }
   else { pRA = registreActivacioFuncions; pC3A = C3AFuncions; }

   quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
   quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
   encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
   pC3A -> num_quadruples++;

   quadrupleC3A -> sentenciaC3A = (char * ) malloc(strlen("GOTO ") + log10Func(num_linia) + 1);
   sprintf(quadrupleC3A -> sentenciaC3A, "GOTO %d", num_linia);
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: emet_cridaC3A(char * nom_funcio,                                      ##
      ##                              struct t_infoBison * parametres,                        ##
      ##                              int tipus_retorn,                                       ##   
      ##                              struct t_infoBison * paramResult)                       ##
      ##                   - nom_funcio: nom de la funcio                                     ##
      ##                   - parametres: parametres de la funcio                              ##
      ##                   - tipus_retorn: tipus de retorn de la funcio                       ##
      ##                   - paramResult: parametre resultat                                  ##
      ##                                                                                      ##
      ##                     Funcio que emet una crida a funcio en C3A                        ##
      ##                                                                                      ##
      ########################################################################################## */
      
void emet_cridaC3A(char * nom_funcio, struct t_infoBison * parametres, int tipus_retorn, struct t_infoBison * paramResult) {
   t_registreC3A * pC3A;
   t_registreActivacio * pRA;
   int numParametres, val;
   char * varTMPComplex1, * varTMPCasting, * varTMP;
   
   currentScope = sym_get_scope();
   if (currentScope == -1) { pRA = registreActivacioGlobal; pC3A = C3AGlobal; }
   else { pRA = registreActivacioFuncions; pC3A = C3AFuncions; }
   
   if (parametres != NULL) {
      recordsetParam = parametres -> seguent_param_funcio; 
      for (count = 0; count < parametres -> num_funcio_parametres; count++) {
         quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
         quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
         encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
         pC3A -> num_quadruples++;

         if (recordsetParam -> valorC3A == NULL) {
            recordsetParam -> valorC3A = malloc(strlen(recordsetParam -> valor) + 1); 
            strcpy(recordsetParam -> valorC3A, recordsetParam -> valor);
         }
         
         if (recordsetParam -> camp_struct_indexat == TRUE) {
            varTMPComplex1 = (char *) malloc(strlen(recordsetParam -> valorC3A) + log10Func(recordsetParam -> offset_camp_struct_indexat) + 3);
            sprintf(varTMPComplex1, "%s[%d]", recordsetParam -> valorC3A, recordsetParam -> offset_camp_struct_indexat);
 
            recordsetParam -> valorC3A = varTMPComplex1;            
         }
         else if (recordsetParam -> array_indexat == TRUE) {
            varTMPComplex1 = (char *) malloc(strlen(recordsetParam -> valorC3A) + strlen(recordsetParam -> array_indexat_offset) + 3);
            sprintf(varTMPComplex1, "%s[%s]", recordsetParam -> valorC3A, recordsetParam -> array_indexat_offset);
 
            recordsetParam -> valorC3A = varTMPComplex1;
         }
         else if (recordsetParam -> tipus_var == TIPUS_CHARACTER) {
            varTMP = (char *) malloc(4);
            sprintf(varTMP, "'%s'", recordsetParam -> valorC3A);
            recordsetParam -> valorC3A = varTMP;
         }
         
         val = operacioC3A(simbol.funcio_params[count].tipus_var, recordsetParam -> tipus_var, '=');
         
         if (val == 2) { 
            varTMPCasting = afegirVarTemporalRA(pRA, simbol.funcio_params[count].tipus_var);
              
            quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPCasting) + strlen(strCastingC3A) + strlen(strOperacioC3A) + strlen(recordsetParam -> valorC3A) + 6);
            sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s %s", varTMPCasting, strCastingC3A, recordsetParam -> valorC3A);

            quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
            quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
            encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
            pC3A -> num_quadruples++;
            
            quadrupleC3A -> sentenciaC3A = (char * ) malloc(strlen("PARAM ") + strlen(varTMPCasting) + 1);
            sprintf(quadrupleC3A -> sentenciaC3A, "PARAM %s", varTMPCasting);
         }
         else {
            quadrupleC3A -> sentenciaC3A = (char * ) malloc(strlen("PARAM ") + strlen(recordsetParam -> valorC3A) + 1);
            sprintf(quadrupleC3A -> sentenciaC3A, "PARAM %s", recordsetParam -> valorC3A);
         }
         recordsetParam = recordsetParam -> seguent_param_funcio;
      }
      numParametres = parametres -> num_funcio_parametres;
   }
   else numParametres = 0;
   
   quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
   quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
   encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
   pC3A -> num_quadruples++;
   
   paramResult -> tipus_var = tipus_retorn;
   if ((tipus_retorn != TIPUS_VOID) && (tipus_retorn != TIPUS_NULL)) {
	  paramResult -> valorC3A = afegirVarTemporalRA(pRA, tipus_retorn);
      quadrupleC3A -> sentenciaC3A = (char * ) malloc(strlen(paramResult -> valorC3A) + strlen(nom_funcio) + log10Func(numParametres) + 12);
      sprintf(quadrupleC3A -> sentenciaC3A, "%s := CALL %s, %d", paramResult -> valorC3A, nom_funcio, numParametres);
   }
   else {
      quadrupleC3A -> sentenciaC3A = (char * ) malloc(strlen(nom_funcio) + log10Func(numParametres) + 8);
      sprintf(quadrupleC3A -> sentenciaC3A, "CALL %s, %d", nom_funcio, numParametres);
   }
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: emet_structC3A(struct t_infoBison * paramStruct)                      ##  
      ##                   - paramStruct: parametre de l'estructura                           ##
      ##                                                                                      ##
      ##                     Funcio que emet una estructura en C3A                            ##
      ##                                                                                      ##
      ########################################################################################## */
      
void emet_structC3A(struct t_infoBison * paramStruct) {
   struct t_infoBison p1Temp;
   t_registreC3A * pC3A;
   t_registreActivacio * pRA;
   char * varTMP;

   if (paramStruct -> tipus_var != TIPUS_NULL) { 
      currentScope = sym_get_scope();
      if (currentScope == -1) { pRA = registreActivacioGlobal; pC3A = C3AGlobal; }
      else { pRA = registreActivacioFuncions; pC3A = C3AFuncions; }
   
      varTMP = afegirVarTemporalRA(pRA, paramStruct -> tipus_var);
      
      p1Temp.valorC3A = (char *) malloc(strlen(paramStruct -> valorC3A) + log10Func(paramStruct -> offset_camp_struct_indexat) + 3);
      sprintf(p1Temp.valorC3A, "%s[%d]", paramStruct -> valorC3A, paramStruct -> offset_camp_struct_indexat);
      
      paramStruct -> valorC3A = varTMP;
      
      p1Temp.tipus_var = paramStruct -> tipus_var;
      p1Temp.array_indexat = FALSE;
      paramStruct -> array_indexat = FALSE; 
      p1Temp.camp_struct_indexat = FALSE;
      paramStruct -> camp_struct_indexat = FALSE;
      
      emet_operacioC3A(&p1Temp, NULL, paramStruct, '=');                        
   }
   else paramStruct -> tipus_var = TIPUS_NULL; 
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: emet_arrayC3A(struct t_infoBison * paramResult,                       ##
      ##                              struct t_infoBison * paramArray,                        ##
      ##                              struct t_infoBison * paramArrayIndex)                   ##   
      ##                   - paramResult: parametre resultat                                  ##
      ##                   - paramArray: parametre array                                      ##
      ##                   - paramArrayIndex: parametre index del array                       ##
      ##                                                                                      ##
      ##                     Funcio que emet un array en C3A                                  ##
      ##                                                                                      ##
      ########################################################################################## */
      
void emet_arrayC3A(struct t_infoBison * paramResult, struct t_infoBison * paramArray, struct t_infoBison * paramArrayIndex) {
   t_registreC3A * pC3A;
   t_registreActivacio * pRA;
   int tamTipus;
   struct t_infoBison p1Temp, pResTemp;
   char * varTMP;
   
   if ((paramResult -> tipus_var != TIPUS_NULL) && (paramArray -> tipus_var != TIPUS_NULL) && (paramArrayIndex -> tipus_var != TIPUS_NULL)) {
      currentScope = sym_get_scope();
      if (currentScope == -1) { pRA = registreActivacioGlobal; pC3A = C3AGlobal; }
      else { pRA = registreActivacioFuncions; pC3A = C3AFuncions; } 
   
      if (paramArrayIndex -> camp_struct_indexat == TRUE) {
         emet_structC3A(paramArrayIndex);
      }
      paramResult -> camp_struct_indexat = FALSE;
      
      p1Temp.tipus_var = TIPUS_INTEGER;
      if (paramArray -> tipus_var != TIPUS_STRUCT) tamTipus = tamanyTipusVar(paramArray -> tipus_var);
      else tamTipus = tamanyStructbyInfoBison(paramArray);
   
      p1Temp.valorC3A = (char *) malloc(log10Func(tamTipus) + 1);
      sprintf(p1Temp.valorC3A, "%d", tamTipus);
   
      p1Temp.array_indexat = FALSE;
      paramArrayIndex -> array_indexat = FALSE;
      pResTemp.array_indexat = FALSE;
      p1Temp.camp_struct_indexat = FALSE;
      
      emet_operacioC3A(&p1Temp, paramArrayIndex, &pResTemp, '*');
   
      paramResult -> array_indexat_offset = (char *) malloc(log10Func(pRA -> num_llista_temporals) + 3);
      sprintf(paramResult -> array_indexat_offset, "$t%d", pRA -> num_llista_temporals);
      
      paramResult -> array_indexat = TRUE;
      paramResult -> tipus_var = paramArray -> tipus_var;
   }
   else paramResult -> tipus_var = TIPUS_NULL;   
}

void emet_retornFuncioC3A(struct t_infoBison * param1) {
   t_registreC3A * pC3A;
   t_registreActivacio * pRA;
   struct t_infoBison p1Temp;
      
   if ((tipus_var_funcio_retorn != TIPUS_NULL) && (tipus_var_funcio_retorn != TIPUS_VOID) && (param1 -> tipus_var != TIPUS_STRUCT) && (llista_seguents_funcio_retorn != NULL)) {
      currentScope = sym_get_scope();
      if (currentScope == -1) { pRA = registreActivacioGlobal; pC3A = C3AGlobal; }
      else { pRA = registreActivacioFuncions; pC3A = C3AFuncions; }
      
      if (valor_retorn == NULL) {
         valor_retorn = afegirVarTemporalRA(pRA, tipus_var_funcio_retorn);
      }
      
      p1Temp.valorC3A = valor_retorn;
      p1Temp.tipus_var = tipus_var_funcio_retorn;
      p1Temp.array_indexat = FALSE;
      p1Temp.camp_struct_indexat = FALSE;
      
      emet_operacioC3A(param1, NULL, &p1Temp, '=');

      quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
      quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
      encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
      pC3A -> num_quadruples++;

      quadrupleC3A -> sentenciaC3A = (char * ) malloc(strlen("GOTO ") + 1);
      sprintf(quadrupleC3A -> sentenciaC3A, "GOTO ");     
         
      encuar((void *) llista_seguents_funcio_retorn, (void *) quadrupleC3A);
   }  
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: completar_llista(Cua * llista, int seguent)                           ##                           
      ##                   - llista: llista per completar                                     ##
      ##                   - seguent: num linia                                               ##
      ##                                                                                      ##
      ##                     Funcio que completa la llista de seguents                        ##
      ##                                                                                      ##
      ########################################################################################## */
      
void completar_llista(Cua * llista, int seguent) {
   struct t_quadrupleC3A * tmpQuadruple;
   char * tmpSentencia;
	
   if (llista != NULL) {
	   	
      tmpQuadruple = (struct t_quadrupleC3A *) primer(llista);
      while (tmpQuadruple != NULL) {
         tmpSentencia = (char *) malloc(strlen(tmpQuadruple -> sentenciaC3A) + log10Func(seguent) + 1);
         sprintf(tmpSentencia, "%s%d", tmpQuadruple -> sentenciaC3A, seguent);  
         tmpQuadruple -> sentenciaC3A = tmpSentencia;
             
	     desencuar(llista);
         tmpQuadruple = (struct t_quadrupleC3A *) primer(llista);
      }
   }
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: iniC3AFuncions()                                                      ## 
      ##                                                                                      ##                          
      ##                   Funcio que inicialitza el registre C3A de les funcions             ##
      ##                                                                                      ##
      ########################################################################################## */

int iniC3AFuncions() {
   C3AFuncions = (t_registreC3A *) malloc(sizeof(t_registreC3A));
   return iniC3A(C3AFuncions);
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: iniC3A(t_registreC3A * pC3A)                                          ##                           ##
      ##                   - pC3A: registre C3A                                               ##
      ##                                                                                      ##
      ##                     Funcio que inicialitza el registre C3A                           ##
      ##                                                                                      ##
      ########################################################################################## */
      
int iniC3A(t_registreC3A * pC3A) {
     
   if (pC3A != NULL) {

      pC3A -> num_quadruples = 0;
	  pC3A -> quadrupleC3A = crear_cua();

      return 0;         
   }
   return -1;
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: iniRegistreActivacioFuncions(char * nom_registre)                     ##                           
      ##                   - nom_registre: nom del registre d'activacio                       ##
      ##                                                                                      ##
      ##                     Funcio que inicialitza el registre d'activacio de les funcions   ##
      ##                                                                                      ##
      ########################################################################################## */
        
int iniRegistreActivacioFuncions(char * nom_registre) {
   registreActivacioFuncions = (t_registreActivacio *) malloc(sizeof(t_registreActivacio));
   return iniRegistreActivacio(registreActivacioFuncions, nom_registre);
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: iniRegistreActivacio(t_registreActivacio * pRA, char * nom_registre)  ##                           
      ##                   - pRA: registre d'activacio                                        ##
      ##                   - nom_registre: nom del registre d'activacio                       ##
      ##                                                                                      ##
      ##                     Funcio que inicialitza el registre d'activacio                   ##
      ##                                                                                      ##
      ########################################################################################## */
         
int iniRegistreActivacio(t_registreActivacio * pRegistreActivacio, char * nom_registre) {
     
   if (pRegistreActivacio != NULL) {
      pRegistreActivacio -> nom_registre = malloc(strlen(nom_registre) + 1); strcpy(pRegistreActivacio -> nom_registre, nom_registre);                    
      pRegistreActivacio -> num_llista_parametres = 0;
      pRegistreActivacio -> num_llista_locals = 0;
      pRegistreActivacio -> num_llista_temporals = 0;
      pRegistreActivacio -> currentOffset = 0; 
      
      pRegistreActivacio -> primer_llista_parametres = NULL;
      pRegistreActivacio -> primer_llista_locals = NULL;
      pRegistreActivacio -> primer_llista_temporals = NULL;
      pRegistreActivacio -> ultim_llista_parametres = NULL;
      pRegistreActivacio -> ultim_llista_locals = NULL;
      pRegistreActivacio -> ultim_llista_temporals = NULL;
      
      return 0;         
   }
   return -1;
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: printRegistreActivacio(t_registreActivacio * pRA)                     ##                           
      ##                   - pRA: registre d'activacio                                        ##
      ##                                                                                      ##
      ##                     Funcio que imprimeix el registre d'activacio                     ##
      ##                                                                                      ##
      ########################################################################################## */
       
void printRegistreActivacio(t_registreActivacio * pRegistreActivacio) {
   t_cadenaRegistreActivacio * pvalors;
   
   fprintf(fRegActivacio, "FUNCIO %s\n", pRegistreActivacio->nom_registre);
   pvalors = pRegistreActivacio -> primer_llista_parametres;
   
   fprintf(fRegActivacio, "\n[ + ] Parametres (nom_param tipus_param tipus_param_tamany offset)\n\n");
   
   for (;pvalors;) {
      if (pvalors -> es_array == FALSE) { 
         fprintf(fRegActivacio, "\t\t[ - ] %s %s %d %d\n", pvalors -> nom, tipusDadesID(pvalors -> tipus, 0), pvalors -> tam_tipus, pvalors -> offset);
      }
      else {
         fprintf(fRegActivacio, "\t\t[ - ] %s %s[%lu] %d %d\n", pvalors -> nom, tipusDadesID(pvalors -> tipus, 0), pvalors -> tam_array, pvalors -> tam_tipus, pvalors -> offset);
      }
      
      pvalors = pvalors -> seguent;
   } 
   
   pvalors = pRegistreActivacio -> primer_llista_locals;
   fprintf(fRegActivacio, "\n[ + ] Variables Locals (nom_param tipus_param tipus_param_tamany offset)\n\n");
   
   for (;pvalors;) {
      if (pvalors -> es_array == FALSE) { 
         fprintf(fRegActivacio, "\t\t[ - ] %s %s %d %d\n", pvalors -> nom, tipusDadesID(pvalors -> tipus, 0), pvalors -> tam_tipus, pvalors -> offset);
      }
      else {
         fprintf(fRegActivacio, "\t\t[ - ] %s %s[%lu] %d %d\n", pvalors -> nom, tipusDadesID(pvalors -> tipus, 0), pvalors -> tam_array, pvalors -> tam_tipus, pvalors -> offset);
      }
      
      pvalors = pvalors -> seguent;
   }     

   pvalors = pRegistreActivacio -> primer_llista_temporals;
   fprintf(fRegActivacio, "\n[ + ] Variables Temporals (nom_param tipus_param tipus_param_tamany offset)\n\n");
   
   for (;pvalors;) {
      fprintf(fRegActivacio, "\t\t[ - ] %s %s %d %d\n", pvalors -> nom, tipusDadesID(pvalors -> tipus, 0), pvalors -> tam_tipus, pvalors -> offset);
      
      pvalors = pvalors -> seguent;
   }     
   fprintf(fRegActivacio, "\n\n");
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: printRegistreActivacioGlobal(t_registreActivacio * pRA)               ##                           
      ##                   - pRA: registre d'activacio                                        ##
      ##                                                                                      ##
      ##                     Funcio que imprimeix el registre d'activacio Global              ##
      ##                                                                                      ##
      ########################################################################################## */
      
void printRegistreActivacioGlobal(t_registreActivacio * pRegistreActivacio) {
   t_cadenaRegistreActivacio * pvalors;
   
   fprintf(fRegActivacio, "GLOBAL\n");
      
   pvalors = pRegistreActivacio -> primer_llista_locals;
   fprintf(fRegActivacio, "\n[ + ] Variables Globals (nom_param tipus_param tipus_param_tamany offset)\n\n");
   
   for (;pvalors;) {
      if (pvalors -> es_array == FALSE) { 
         fprintf(fRegActivacio, "\t\t[ - ] %s %s %d %d\n", pvalors -> nom, tipusDadesID(pvalors -> tipus, 0), pvalors -> tam_tipus, pvalors -> offset);
      }
      else {
         fprintf(fRegActivacio, "\t\t[ - ] %s %s[%lu] %d %d\n", pvalors -> nom, tipusDadesID(pvalors -> tipus, 0), pvalors -> tam_array, pvalors -> tam_tipus, pvalors -> offset);
      }
      
      pvalors = pvalors -> seguent;
   }
   
   pvalors = pRegistreActivacio -> primer_llista_temporals;
   fprintf(fRegActivacio, "\n[ + ] Variables Temporals (nom_param tipus_param tipus_param_tamany offset)\n\n");
   
   for (;pvalors;) {
      fprintf(fRegActivacio, "\t\t[ - ] %s %s %d %d\n", pvalors -> nom, tipusDadesID(pvalors -> tipus, 0), pvalors -> tam_tipus, pvalors -> offset);
      
      pvalors = pvalors -> seguent;
   }     
   fprintf(fRegActivacio, "\n\n"); 
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: printC3AFuncions(t_registreActivacio * pC3A, char * nom_funcio)       ##                           
      ##                   - pC3A: registre C3A                                               ##
      ##                   - nom_funcio: nom de la funcio                                     ##
      ##                                                                                      ##
      ##                     Funcio que imprimeix el registre C3A                             ##
      ##                                                                                      ##
      ########################################################################################## */
      
void printC3AFuncions(t_registreC3A * pC3A, char * nom_funcio) {
   t_quadrupleC3A * pQuadruple;
   Cua * llista_quadruples;

   fprintf(fCodi3A, "SUBRUTINA %s:\n\n", nom_funcio);
   
   llista_quadruples = pC3A -> quadrupleC3A;
    
   for (;primer(llista_quadruples);) {
      pQuadruple = (struct t_quadrupleC3A *) primer(llista_quadruples);
      fprintf(fCodi3A, "\tLINIA %d: %s\n", pQuadruple -> num_sentencia, pQuadruple -> sentenciaC3A);
      
      desencuar(llista_quadruples);
   }
   fprintf(fCodi3A, "\n");
   
   fprintf(fCodi3A, "HALT\n\n");
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: printC3AGlobal(t_registreActivacio * pC3A)                            ##                           
      ##                   - pC3A: registre C3A                                               ##
      ##                                                                                      ##
      ##                     Funcio que imprimeix el registre C3A Global                      ##
      ##                                                                                      ##
      ########################################################################################## */
      
void printC3AGlobal(t_registreC3A * pC3A) {
   t_quadrupleC3A * pQuadruple;
   Cua * llista_quadruples;

   fprintf(fCodi3A, "GLOBAL:\n\n");
   
   llista_quadruples = pC3A -> quadrupleC3A;
    
   for (;primer(llista_quadruples);) {
      pQuadruple = (struct t_quadrupleC3A *) primer(llista_quadruples);
      fprintf(fCodi3A, "\tLINIA %d: %s\n", pQuadruple -> num_sentencia, pQuadruple -> sentenciaC3A);
      
      desencuar(llista_quadruples);
   }
}
 
 
   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: afegirParamRA(t_registreActivacio * pRA, char * nom_var, int t_var)   ##                           
      ##                   - pRA: registre d'activacio                                        ##
      ##                   - nom_var: nom de la variable                                      ##
      ##                   - t_var: tipus de la variable                                      ##
      ##                   - es_array: el paràmetre es un array o no                          ##
      ##                   - tam_array: en cas de que sigui un array indica el seu tamany     ##
      ##                                                                                      ##
      ########################################################################################## */

void afegirParamRA(t_registreActivacio * pRegistreActivacio, char * nom_var, int tipus_var, int es_array, long tam_array) {
   t_cadenaRegistreActivacio * pcadenaRA;
   
   pcadenaRA = (t_cadenaRegistreActivacio *) malloc(sizeof(t_cadenaRegistreActivacio));
   pcadenaRA -> nom = (char *) malloc(strlen(nom_var) + 1); strcpy(pcadenaRA -> nom, nom_var);
   
   if (tipus_var == TIPUS_STRUCT) pcadenaRA -> tam_tipus = tamanyStruct(&simbol);
   else pcadenaRA -> tam_tipus = tamanyTipusVar(tipus_var);
    
   pcadenaRA -> tipus = tipus_var;
   pcadenaRA -> offset = pRegistreActivacio -> currentOffset;
   pcadenaRA -> es_array = es_array;
   if (es_array) {
      pcadenaRA -> tam_array = tam_array;
      pcadenaRA -> tam_total = (tam_array * (pcadenaRA -> tam_tipus));
   }
   else { 
      pcadenaRA -> tam_array = 0; 
      pcadenaRA -> tam_total = (pcadenaRA -> tam_tipus); 
   }
   
   pRegistreActivacio -> currentOffset += pcadenaRA -> tam_total; 
   
   if (pRegistreActivacio -> num_llista_parametres == 0) {                
      pRegistreActivacio -> primer_llista_parametres = pcadenaRA;
      pRegistreActivacio -> ultim_llista_parametres = pcadenaRA;
   }
   else { 
      (pRegistreActivacio -> ultim_llista_parametres) -> seguent = pcadenaRA;
      pRegistreActivacio -> ultim_llista_parametres = pcadenaRA;
   }
   pRegistreActivacio -> num_llista_parametres++;	
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: afegirVarLocalRA(t_registreActivacio * pRA, char * nom_var,           ##
      ##                                 struct t_simbol * simbol)                            ##                           
      ##                   - pRA: registre d'activacio                                        ##
      ##                   - nom_var: nom de la variable                                      ##
      ##                   - simbol: referencia a la taula de simbols                         ##
      ##                                                                                      ##
      ########################################################################################## */

void afegirVarLocalRA(t_registreActivacio * pRegistreActivacio, char * nom_var, struct t_simbol * simbol) {
   t_cadenaRegistreActivacio * pcadenaRA;
   
   pcadenaRA = (t_cadenaRegistreActivacio *) malloc(sizeof(t_cadenaRegistreActivacio));
   pcadenaRA -> nom = (char *) malloc(strlen(nom_var) + 1); strcpy(pcadenaRA -> nom, nom_var);
   
   if (simbol -> tipus_var == TIPUS_STRUCT) pcadenaRA -> tam_tipus = tamanyStruct(simbol);
   else pcadenaRA -> tam_tipus = tamanyTipusVar(simbol -> tipus_var);
   
   pcadenaRA -> tipus = simbol -> tipus_var;
   pcadenaRA -> offset = pRegistreActivacio -> currentOffset;
   pcadenaRA -> es_array = simbol -> array;
   if (simbol -> array) {
      pcadenaRA -> tam_array = simbol -> tam_array;
      pcadenaRA -> tam_total = (simbol -> tam_array * (pcadenaRA -> tam_tipus));
   }
   else { 
      pcadenaRA -> tam_array = 0; 
      pcadenaRA -> tam_total = (pcadenaRA -> tam_tipus);
   }
   
   pRegistreActivacio -> currentOffset += pcadenaRA -> tam_total; 
   
   if (pRegistreActivacio -> num_llista_locals == 0) {                
      pRegistreActivacio -> primer_llista_locals = pcadenaRA;
      pRegistreActivacio -> ultim_llista_locals = pcadenaRA;
   }
   else { 
      (pRegistreActivacio -> ultim_llista_locals) -> seguent = pcadenaRA;
      pRegistreActivacio -> ultim_llista_locals = pcadenaRA;
   }
   pRegistreActivacio -> num_llista_locals++;	
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: afegirVarTemporalRA(t_registreActivacio * pRA, int tipusVarTemp)      ##                          
      ##                   - pRA: registre d'activacio                                        ##
      ##                   - tipusVarTemp: tipus de la variable temporal                      ##
      ##                                                                                      ##
      ########################################################################################## */
      
char * afegirVarTemporalRA(t_registreActivacio * pRegistreActivacio, int tipusVarTemp) {
   t_cadenaRegistreActivacio * pcadenaRA;
   
   pcadenaRA = (t_cadenaRegistreActivacio *) malloc(sizeof(t_cadenaRegistreActivacio));
   pcadenaRA -> nom = (char *) malloc(2 + (log10Func((pRegistreActivacio -> num_llista_temporals) + 1) + 1)); 
   sprintf(pcadenaRA -> nom, "$t%d", (pRegistreActivacio -> num_llista_temporals) + 1);
   
   pcadenaRA -> tam_tipus = tamanyTipusVar(tipusVarTemp);
   pcadenaRA -> tipus = tipusVarTemp;
   pcadenaRA -> offset = pRegistreActivacio -> currentOffset;
   pcadenaRA -> es_array = 0;
   pcadenaRA -> tam_array = 0;
   pcadenaRA -> tam_total = (pcadenaRA -> tam_tipus);
   pRegistreActivacio -> currentOffset += pcadenaRA -> tam_total;
   
   if (pRegistreActivacio -> num_llista_temporals == 0) {                
      pRegistreActivacio -> primer_llista_temporals = pcadenaRA;
      pRegistreActivacio -> ultim_llista_temporals = pcadenaRA;
   }
   else { 
      (pRegistreActivacio -> ultim_llista_temporals) -> seguent = pcadenaRA;
      pRegistreActivacio -> ultim_llista_temporals = pcadenaRA;
   }
   pRegistreActivacio -> num_llista_temporals++;
   
   return pcadenaRA -> nom;      
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: tamanyTipusVar(int tipus)                                             ##
      ##                   - tipus: tipus de la variable                                      ##
      ##                                                                                      ##
      ##                     Retorna int: numero de bytes del tipus                           ##
      ##                                                                                      ##
      ########################################################################################## */
      
int tamanyTipusVar(int tipus) {
   switch (tipus) {
      case (TIPUS_CHARACTER): return 1;
      case (TIPUS_SHORT): return 2;
      case (TIPUS_INTEGER): return 4;
      case (TIPUS_LONG): return 8;
      case (TIPUS_FLOAT): return 4;
      case (TIPUS_DOUBLE): return 8;
   }
   return 0;
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: log10Func(int num)                                                    ##
      ##                   - num: numero                                                      ##
      ##                                                                                      ##
      ##                     Retorna int: numero de bytes que ocupa el numero en string       ##
      ##                                                                                      ##
      ########################################################################################## */
      
int log10Func(int num) {
   if (num <= 0) return 1;
   else return (log10(num) + 1);
}    
     
      
   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: init_analisi_sintactic_O(char * fileOutput, char * nomFitxerRA)       ##
      ##                   - fileOutput: fitxer de sortida                                    ##
      ##                                                                                      ##
      ########################################################################################## */

int init_analisi_sintactic_O(char * fileOutput, char * nomFitxerRA, char * nomFitxerC3A) {
   int error; 
   
   nom_fitxerRA = nomFitxerRA;
   nom_fitxerC3A = nomFitxerC3A;
   yyout = fopen(fileOutput, "w");

   fRegActivacio = fopen(nomFitxerRA, "w");
   fCodi3A = fopen(nomFitxerC3A, "w");
   
   num_errors = 0; valor_retorn = NULL;
   if ((yyout == NULL) || (fRegActivacio == NULL) || (fCodi3A == NULL)) { error = EXIT_FAILURE; }
   else { error = EXIT_SUCCESS; }

   return error;

}

   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: end_analisi_sintactic_O(): tancament del fitxer de sortida            ##
      ##                                                                                      ##
      ########################################################################################## */

int end_analisi_sintactic_O() {
   int error;
   
   printRegistreActivacioGlobal(registreActivacioGlobal);
   printC3AGlobal(C3AGlobal);
   error = fclose(yyout);
   error |= fclose(fRegActivacio);
   error |= fclose(fCodi3A);
   
   if (num_errors > 0) {
      remove(nom_fitxerRA);
      remove(nom_fitxerC3A);         
      fprintf(stdout, "\n\n\t-----------------------------------------------------");
      fprintf(stdout, "\n\t\t[ ERR ] Compilacio amb %d error/s\n", num_errors);
      fprintf(stdout, "\t-----------------------------------------------------\n\n");
   }
   else {
      fprintf(stdout, "\n\n\t-----------------------------------------------------");
      fprintf(stdout, "\n\t\t[ OK ] Compilacio generada correctament\n"); 
      fprintf(stdout, "\t-----------------------------------------------------\n\n");
   }
   
   if (error == 0) { error = EXIT_SUCCESS; }
   else { error = EXIT_FAILURE; }
   
   return error; 
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: analisi_semantic()                                                    ##
      ##                                                                                      ##
      ########################################################################################## */
      
int analisi_semantic() {
   int error;
   
   registreActivacioGlobal = (t_registreActivacio *) malloc(sizeof(t_registreActivacio));
   iniRegistreActivacio(registreActivacioGlobal, "GLOBAL");
   
   C3AGlobal = (t_registreC3A *) malloc(sizeof(t_registreC3A));
   iniC3A(C3AGlobal);
   
   if (yyparse() == 0) { error =  EXIT_SUCCESS; }
   else { error =  EXIT_FAILURE; }
   
   return error;
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: identificadorDeclaratMateixAmbit(char * idSimbol)                     ##
      ##                   - idSimbol: identificador del simbol                               ##
      ##                                                                                      ##
      ##                     Funcio per evitar redeclaracions de variables                    ##
      ##                                                                                      ##
      ########################################################################################## */
      
Boolean identificadorDeclaratMateixAmbit(char * idSimbol) {
   currentScope = sym_get_scope();
      
   if (sym_lookup(idSimbol, &simbol_tmp) == SYMTAB_OK) {
      if (simbol_tmp.ambit == currentScope) return TRUE;
   }
   return FALSE;
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: identificadorDeclarat(char * idSimbol)                                ##
      ##                   - idSimbol: identificador del simbol                               ##
      ##                                                                                      ##
      ##                     Funcio que retorna TRUE: si esta a la taula de simbols           ##
      ##                                        FALSE: si no esta a la taula de simbols       ##
      ##                                                                                      ##
      ########################################################################################## */
      
Boolean identificadorDeclarat(char * idSimbol) {
   currentScope = sym_get_scope();
      
   if (sym_lookup(idSimbol, &simbol) == SYMTAB_OK) {
      return TRUE;
   }
   return FALSE;
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: comprovacioTipusDades(Tipus_Dades t1, Tipus_Dades t2, int vsituacio)  ##
      ##                   - t1: tipus del paràmetre 1                                        ##
      ##                   - t2: tipus del paràmetre 2                                        ##
      ##                   - vsituacio: operacio, assignació, crida a funcio                  ##
      ##                                                                                      ##
      ##                     Funcio que retorna el tipus respecte les entrades                ##
      ##                                                                                      ##
      ########################################################################################## */
      
int comprovacioTipusDades(Tipus_Dades t1, Tipus_Dades t2, int vsituacio) {
   char situacio[20];
   int t3;
   
   if (vsituacio == 0) strcpy(situacio, "assignacio");
   else if (vsituacio == 1) strcpy(situacio, "funcio");
   else strcpy(situacio, "operacio");
   
   
   if ((vsituacio == 1) && (((t1 == TIPUS_STRUCT) && (t1 != t2)) || ((t2 == TIPUS_STRUCT) && (t1 != t2)))) {
      num_errors++; printErrorSintactic(TRUE, ERR_CRIDA_FUNCIO_STRUCTS);
   } 
   else if (((vsituacio == 0) || (vsituacio == 2)) && ((t1 == TIPUS_STRUCT) || (t2 == TIPUS_STRUCT))) {
      num_errors++; printErrorSintactic(TRUE, ERR_OPERACIO_ASSIG_ENTRE_STRUCTS, situacio);
   }
   else { 
       if ((vsituacio == ID_SITUACIO_OPERACIO) && (t1 < t2)) {
          t3 = t1; t1 = t2; t2 = t3;
       }
       
       switch (t1) {
          case TIPUS_INTEGER: 
               switch (t2) {
                  case TIPUS_INTEGER: break;
                  case TIPUS_STRING: funcioDeclaradaCorrecte = FALSE; num_errors++; printErrorSintactic(TRUE, ERR_STRING, situacio, "int"); break;
                  case TIPUS_SHORT: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "SHORT", "INT"); break;
                  case TIPUS_CHARACTER: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "CHAR", "INT"); break;
                    
                  case TIPUS_LONG: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "LONG", "INT");  
                                   printErrorSintactic(FALSE, WARNING_PRECISIO, situacio, "LONG", "INT"); 
                                   break;
                  
                  case TIPUS_FLOAT: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "FLOAT", "INT");   
                                    printErrorSintactic(FALSE, WARNING_PRECISIO, situacio, "FLOAT", "INT");  
                                    break;
                  
                  case TIPUS_DOUBLE: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "DOUBLE", "INT");  
                                     printErrorSintactic(FALSE, WARNING_PRECISIO, situacio, "DOUBLE", "INT");  
                                     break;
                                    
               }
               break;
               
          case TIPUS_SHORT: 
               switch (t2) {
                  case TIPUS_SHORT: break;
                  case TIPUS_STRING: funcioDeclaradaCorrecte = FALSE; num_errors++; printErrorSintactic(TRUE, ERR_STRING, situacio, "short"); break; 
                  case TIPUS_CHARACTER: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "CHAR", "SHORT"); break;
                   
                  case TIPUS_INTEGER: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "INT", "SHORT");  
                                      printErrorSintactic(FALSE, WARNING_PRECISIO, situacio, "INT", "SHORT"); 
                                      break;
                    
                  case TIPUS_LONG: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "LONG", "SHORT");  
                                   printErrorSintactic(FALSE, WARNING_PRECISIO, situacio, "LONG", "SHORT"); 
                                   break;
                  
                  case TIPUS_FLOAT: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "FLOAT", "SHORT");   
                                    printErrorSintactic(FALSE, WARNING_PRECISIO, situacio, "FLOAT", "SHORT");  
                                    break;
                  
                  case TIPUS_DOUBLE: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "DOUBLE", "SHORT");  
                                     printErrorSintactic(FALSE, WARNING_PRECISIO, situacio, "DOUBLE", "SHORT");  
                                     break;
                                    
               }
               break;
               
          case TIPUS_CHARACTER: 
               switch (t2) {
                  case TIPUS_CHARACTER: break;
                  case TIPUS_STRING: if (!arrayDeclaracio) {
                                        arrayDeclaracio = FALSE;
                                        funcioDeclaradaCorrecte = FALSE;
                                        num_errors++; printErrorSintactic(TRUE, ERR_STRING, situacio, "char"); 
                                     }   
                                     break;  
                  
                  case TIPUS_SHORT: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "SHORT", "CHAR");  
                                    printErrorSintactic(FALSE, WARNING_PRECISIO, situacio, "SHORT", "CHAR"); 
                                    break;
                                      
                  case TIPUS_INTEGER: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "INT", "CHAR");  
                                      printErrorSintactic(FALSE, WARNING_PRECISIO, situacio, "INT", "CHAR"); 
                                      break;
                    
                  case TIPUS_LONG: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "LONG", "CHAR");  
                                   printErrorSintactic(FALSE, WARNING_PRECISIO, situacio, "LONG", "CHAR"); 
                                   break;
                  
                  case TIPUS_FLOAT: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "FLOAT", "CHAR");   
                                    printErrorSintactic(FALSE, WARNING_PRECISIO, situacio, "FLOAT", "CHAR");  
                                    break;
                  
                  case TIPUS_DOUBLE: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "DOUBLE", "CHAR");  
                                     printErrorSintactic(FALSE, WARNING_PRECISIO, situacio, "DOUBLE", "CHAR");  
                                     break;          
               }
               break;
               
          case TIPUS_FLOAT: 
               switch (t2) {
                  case TIPUS_FLOAT: break;
                  case TIPUS_STRING: funcioDeclaradaCorrecte = FALSE; num_errors++; printErrorSintactic(TRUE, ERR_STRING, situacio, "float"); break;  
                  case TIPUS_SHORT: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "SHORT", "FLOAT"); break;
                  case TIPUS_INTEGER: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "INT", "FLOAT"); break;
                  case TIPUS_CHARACTER: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "CHAR", "FLOAT"); break;
                    
                  case TIPUS_LONG: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "LONG", "FLOAT");  
                                   printErrorSintactic(FALSE, WARNING_PRECISIO, situacio, "LONG", "FLOAT"); 
                                   break;
                  
                  case TIPUS_DOUBLE: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "DOUBLE", "FLOAT");  
                                     printErrorSintactic(FALSE, WARNING_PRECISIO, situacio, "DOUBLE", "FLOAT");  
                                     break;          
               }
               break;
               
          case TIPUS_DOUBLE: 
               switch (t2) {
                  case TIPUS_DOUBLE: break;
                  case TIPUS_STRING: funcioDeclaradaCorrecte = FALSE; num_errors++; printErrorSintactic(TRUE, ERR_STRING, situacio, "double"); break;  
                  case TIPUS_SHORT: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "SHORT", "DOUBLE"); break;
                  case TIPUS_FLOAT: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "FLOAT", "DOUBLE"); break;
                  case TIPUS_INTEGER: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "INT", "DOUBLE"); break;
                  case TIPUS_CHARACTER: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "CHAR", "DOUBLE"); break;
                    
                  case TIPUS_LONG: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "LONG", "DOUBLE");  
                                   printErrorSintactic(FALSE, WARNING_PRECISIO, situacio, "LONG", "DOUBLE"); 
                                   break;         
               }
               break;
               
          case TIPUS_LONG: 
               switch (t2) {
                  case TIPUS_LONG: break;
                  case TIPUS_STRING: funcioDeclaradaCorrecte = FALSE; num_errors++; printErrorSintactic(TRUE, ERR_STRING, situacio, "long"); break;  
                  case TIPUS_SHORT: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "SHORT", "LONG"); break;
                  case TIPUS_INTEGER: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "INT", "LONG"); break;
                  case TIPUS_CHARACTER: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "CHAR", "LONG"); break;
                    
                  case TIPUS_FLOAT: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "FLOAT", "LONG");  
                                    printErrorSintactic(FALSE, WARNING_PRECISIO, situacio, "FLOAT", "LONG"); 
                                    break;
                  
                  case TIPUS_DOUBLE: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "DOUBLE", "LONG");  
                                     printErrorSintactic(FALSE, WARNING_PRECISIO, situacio, "DOUBLE", "LONG");  
                                     break;          
               }
               break;
               
          case TIPUS_STRING: 
               switch (t2) {
                  case TIPUS_STRING: if (vsituacio == ID_SITUACIO_OPERACIO) {
                                        num_errors++; printErrorSintactic(TRUE, ERR_STRING_STRING_OP, situacio);   
                                     }
                                     break;
                                     
                  case TIPUS_LONG: funcioDeclaradaCorrecte = FALSE; num_errors++; printErrorSintactic(TRUE, ERR_TYPE_TO_STRING, situacio, "long"); break;
                  
                  case TIPUS_SHORT: funcioDeclaradaCorrecte = FALSE; num_errors++; printErrorSintactic(TRUE, ERR_TYPE_TO_STRING, situacio, "long"); break;
                  case TIPUS_INTEGER: funcioDeclaradaCorrecte = FALSE; num_errors++; printErrorSintactic(TRUE, ERR_TYPE_TO_STRING, situacio, "int"); break;
                  case TIPUS_CHARACTER: funcioDeclaradaCorrecte = FALSE; num_errors++; printErrorSintactic(TRUE, ERR_TYPE_TO_STRING, situacio, "char"); break;
                  case TIPUS_FLOAT: funcioDeclaradaCorrecte = FALSE; num_errors++; printErrorSintactic(TRUE, ERR_TYPE_TO_STRING, situacio, "float"); break;
                  case TIPUS_DOUBLE: funcioDeclaradaCorrecte = FALSE; num_errors++; printErrorSintactic(TRUE, ERR_TYPE_TO_STRING, situacio, "double"); break;       
               }
               break;
       }
   }
   
   if ((vsituacio == ID_SITUACIO_OPERACIO) && (t1 != TIPUS_STRING) && (t2 != TIPUS_STRING) && (t1 != TIPUS_STRUCT) && (t2 != TIPUS_STRUCT)) {
       return t1;   
   }
   return -1;
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: operacioC3A(Tipus_Dades t1, Tipus_Dades t2, int operacio)             ##
      ##                   - t1: tipus del paràmetre 1                                        ##
      ##                   - t2: tipus del paràmetre 2                                        ##
      ##                   - operacio: operacio                                               ##
      ##                                                                                      ##
      ##                     Funcio que retorna el codi 3 adreçes                             ##
      ##                                                                                      ##
      ########################################################################################## */
            
int operacioC3A(Tipus_Dades t1, Tipus_Dades t2, int operacio) {
   char tipus;
   int result = 0;
   
   strcpy(strCastingC3A, "");
   strcpy(strOperacioC3A, "");
   
   switch (t1) {
      case TIPUS_CHARACTER:
         tipus = 'C';
         switch (t2) {        
            case TIPUS_CHARACTER: break; 
            case TIPUS_SHORT: if (operacio == '=') { strcpy(strCastingC3A, "STC"); result = 2; }
                              else { tipus = 'S'; strcpy(strCastingC3A, "CTS"); result = 1; } 
                              break;
                              
            case TIPUS_INTEGER: if (operacio == '=') { strcpy(strCastingC3A, "ITC"); result = 2; }
                                else { tipus = 'I'; strcpy(strCastingC3A, "CTI"); result = 1; } 
                                break;
                            
            case TIPUS_LONG: if (operacio == '=') { strcpy(strCastingC3A, "LTC"); result = 2; }
                             else { tipus = 'L'; strcpy(strCastingC3A, "CTL"); result = 1; } 
                             break;
                              
            case TIPUS_FLOAT: if (operacio == '=') { strcpy(strCastingC3A, "FTC"); result = 2; }
                              else { tipus = 'F'; strcpy(strCastingC3A, "CTF"); result = 1; }
                              break;
                              
            case TIPUS_DOUBLE: if (operacio == '=') { strcpy(strCastingC3A, "DTC"); result = 2; }
                               else { tipus = 'D'; strcpy(strCastingC3A, "CTD"); result = 1; } 
                               break;
         }
         break;
         
      case TIPUS_SHORT : 
         tipus = 'S';   
         switch (t2) {
            case TIPUS_CHARACTER: strcpy(strCastingC3A, "CTS"); result = 2; break;
            case TIPUS_SHORT: break;   
                        
            case TIPUS_INTEGER: if (operacio == '=') { strcpy(strCastingC3A, "ITS"); result = 2; }
                                else { tipus = 'I'; strcpy(strCastingC3A, "STI"); result = 1; }
                                break;
                                
            case TIPUS_LONG: if (operacio == '=') { strcpy(strCastingC3A, "LTS"); result = 2; }
                             else { tipus = 'L'; strcpy(strCastingC3A, "STL"); result = 1; } 
                             break;
                             
            case TIPUS_FLOAT: if (operacio == '=') { strcpy(strCastingC3A, "FTS"); result = 2; }
                              else { tipus = 'F'; strcpy(strCastingC3A, "STF"); result = 1; }
                              break;
                              
            case TIPUS_DOUBLE: if (operacio == '=') { strcpy(strCastingC3A, "DTS"); result = 2; }
                               else { tipus = 'D'; strcpy(strCastingC3A, "STD"); result = 1; }
                               break;
         }
         break;
         
      case TIPUS_INTEGER: 
         tipus = 'I'; 
         switch (t2) {
            case TIPUS_CHARACTER: strcpy(strCastingC3A, "CTI"); result = 2; break;
            case TIPUS_SHORT: strcpy(strCastingC3A, "STI"); result = 2; break;               
            case TIPUS_INTEGER: break;
                           
            case TIPUS_LONG: if (operacio == '=') { strcpy(strCastingC3A, "LTI"); result = 2; }
                             else { tipus = 'L'; strcpy(strCastingC3A, "ITL"); result = 1; } 
                             break;
                              
            case TIPUS_FLOAT: if (operacio == '=') { strcpy(strCastingC3A, "FTI"); result = 2; }
                              else { tipus = 'F'; strcpy(strCastingC3A, "ITF"); result = 1; } 
                              break;
                              
            case TIPUS_DOUBLE: if (operacio=='=') { strcpy(strCastingC3A, "DTI"); result = 2; }
                               else { tipus = 'D'; strcpy(strCastingC3A, "ITD"); result = 1; } 
                               break;
         }
         break;
      
      case TIPUS_LONG :
         tipus = 'L'; 
         switch (t2){
            case TIPUS_CHARACTER: strcpy(strCastingC3A, "CTL"); result = 2; break;
            case TIPUS_SHORT: strcpy(strCastingC3A, "STL"); result = 2; break;
            case TIPUS_INTEGER: strcpy(strCastingC3A, "ITL"); result = 2; break;
            case TIPUS_LONG: break;
            
            case TIPUS_FLOAT: if (operacio == '=') { strcpy(strCastingC3A, "FTL"); result = 2; }
                              else { tipus = 'F'; strcpy(strCastingC3A, "LTF"); result = 1; } 
                              break;
            
            case TIPUS_DOUBLE: if (operacio == '=') { strcpy(strCastingC3A, "DTL"); result = 2; }
                               else { tipus = 'D'; strcpy(strCastingC3A, "LTD"); result = 1; } 
                               break;
         }
         break;
         
      case TIPUS_FLOAT:
         tipus = 'F';
         switch (t2){
            case TIPUS_CHARACTER: strcpy(strCastingC3A, "CTF"); result = 2; break;
            case TIPUS_SHORT: strcpy(strCastingC3A, "STF"); result = 2; break;
            case TIPUS_INTEGER: strcpy(strCastingC3A, "ITF"); result = 2; break;
            case TIPUS_LONG: strcpy(strCastingC3A, "LTF"); result = 2; break;
            case TIPUS_FLOAT: break;
            
            case TIPUS_DOUBLE: if (operacio == '=') { strcpy(strCastingC3A, "DTF"); result = 2; }
                               else { tipus = 'D'; strcpy(strCastingC3A, "FTD"); result = 1; } 
                               break;
         }
         break;
         
      case TIPUS_DOUBLE :
         tipus = 'D';
         switch (t2){
            case TIPUS_CHARACTER: strcpy(strCastingC3A, "CTD"); result = 2; break;
            case TIPUS_SHORT: strcpy(strCastingC3A, "STD"); result = 2; break;
            case TIPUS_INTEGER: strcpy(strCastingC3A, "ITD"); result = 2; break;
            case TIPUS_LONG: strcpy(strCastingC3A, "LTD"); result = 2; break;
            case TIPUS_FLOAT: strcpy(strCastingC3A, "FTD"); result = 2; break;
            case TIPUS_DOUBLE: break;
         }
         break;
   }
   
   switch(operacio) {
      case '+': strcpy(strOperacioC3A, "ADD_");
                strOperacioC3A[3] = tipus; break;
      
      case '-': strcpy(strOperacioC3A, "SUB_");
                strOperacioC3A[3] = tipus; break;
      
      case '*': strcpy(strOperacioC3A, "MUL_");
                strOperacioC3A[3] = tipus; break;
      
      case '/': strcpy(strOperacioC3A, "DIV_");
                strOperacioC3A[3] = tipus; break;
                 
      case '%': strcpy(strOperacioC3A, "MOD_");
                strOperacioC3A[3] = tipus; break;

      case ID_NE_OP: strcpy(strOperacioC3A, "NE"); break;
      case ID_EQ_OP: strcpy(strOperacioC3A, "EQ"); break;

      case '<': strcpy(strOperacioC3A, "LT_");
                strOperacioC3A[2] = tipus; break;
                
      case ID_LE_OP: strcpy(strOperacioC3A, "LE_");
                     strOperacioC3A[2] = tipus; break;
                  
      case '>': strcpy(strOperacioC3A, "GT_");
                strOperacioC3A[2] = tipus; break;
               
      case ID_GE_OP: strcpy(strOperacioC3A, "GE_");
                     strOperacioC3A[2] = tipus; break;
   }
   return result;
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: yyerror(char * explanation)                                           ##
      ##                   - explanation: texte d'error                                       ##
      ##                                                                                      ##
      ########################################################################################## */
      
void yyerror(char * explanation) {
   num_errors++;  
   fprintf(stderr, "\n[ SINTACTIC/SEMANTIC -> Error ] >>> linia %i: %s\n", numFila, explanation);
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: printErrorSintactic(Boolean err, char * errorDesc, ...)               ##
      ##                   - err: indica si es error o warning                                ##
      ##                   - errorDesc: descripcio del error                                  ##
      ##                                                                                      ##
      ########################################################################################## */
      
void printErrorSintactic(Boolean err, char * errorDesc, ...) {
   va_list args;
   va_start(args, errorDesc);
   char linea[2048];
   
   if (err) sprintf(linea, "\n[ SINTACTIC/SEMANTIC -> Error ] >>> linia %i: ", numFila);
   else sprintf(linea, "\n[ SINTACTIC/SEMANTIC -> Warning ] >>> linia %i: ", numFila);
   
   vsprintf(&linea[strlen(linea)], errorDesc, args);
   if (stdout != yyout) {
      fprintf(stderr, "%s\n", linea);
      fprintf(yyout, "%s\n", linea + 1);
   }
   else fprintf(stderr, "%s\n", linea);    
   va_end(args);
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: printSimbolInfo(char * idSimbol)                                      ##
      ##                   - idSimbol: identificador del simbol                               ##
      ##                                                                                      ##
      ##                     Mostra tota la informació per pantalla d'un simbol               ##
      ##                                                                                      ##
      ########################################################################################## */
      
void printSimbolInfo(char * idSimbol) {
   if (sym_lookup(idSimbol, &simbol) == SYMTAB_OK) {
      if (simbol.funcio == TRUE) {
         if (stdout != yyout) {
            fprintf(stderr, "\t[ - ] Funcio: %s\n", idSimbol);
            fprintf(yyout, "\t[ - ] Funcio: %s\n", idSimbol);
            fprintf(stderr, "\t[ - ] %i Parametres:\n", simbol.num_funcio_parametres);
            fprintf(yyout, "\t[ - ] %i Parametres:\n", simbol.num_funcio_parametres);
            
            for (count = 0; count < simbol.num_funcio_parametres; count++) {
               if (simbol.funcio_params[count].array == TRUE) {
                  fprintf(stderr, "\t\tTipus: %s  Array: SI  Tamany_Array: %lu\n", tipusDadesID(simbol.funcio_params[count].tipus_var, 1), simbol.funcio_params[count].tam_array, 1);
                  fprintf(yyout, "\t\t\tTipus: %s  Array: SI  Tamany_Array: %lu\n", tipusDadesID(simbol.funcio_params[count].tipus_var, 1), simbol.funcio_params[count].tam_array, 1);
               }
               else {
                  fprintf(stderr, "\t\tTipus: %s  Array: NO\n\n", tipusDadesID(simbol.funcio_params[count].tipus_var, 1));
                  fprintf(yyout, "\t\t\tTipus: %s  Array: NO\n", tipusDadesID(simbol.funcio_params[count].tipus_var, 1));
               }    
            }
            
            fprintf(stderr, "\t[ - ] Tipus Retorn: %s\n\n", tipusDadesID(simbol.tipus_var, 1));
            fprintf(yyout, "\t[ - ] Tipus Retorn: %s\n", tipusDadesID(simbol.tipus_var, 1));
         }
         else {
            fprintf(stderr, "\t[ - ] Funcio: %s\n", idSimbol);
            fprintf(stderr, "\t[ - ] %i Parametres:\n", simbol.num_funcio_parametres);
            
            for (count = 0; count < simbol.num_funcio_parametres; count++) {
               if (simbol.funcio_params[count].array == TRUE) {
                  fprintf(stderr, "\t\tTipus: %s  Array: SI  Tamany_Array: %lu\n", tipusDadesID(simbol.funcio_params[count].tipus_var, 1), simbol.funcio_params[count].tam_array);
               }
               else {
                  fprintf(stderr, "\t\tTipus: %s  Array: NO\n", tipusDadesID(simbol.funcio_params[count].tipus_var, 1));
               }    
            }
            
            fprintf(stderr, "\t[ - ] Tipus Retorn: %s\n\n", tipusDadesID(simbol.tipus_var, 1));
         }   
      }
      else {
         if (stdout != yyout) {
            fprintf(stderr, "\t[ - ] Variable: %s\n", idSimbol);
            fprintf(yyout, "\t[ - ] Variable: %s\n", idSimbol);
            if (simbol.array == TRUE) {
               fprintf(stderr, "\t\tTipus: %s  Ambit: %d  Array: SI  Tamany_Array: %lu\n\n", tipusDadesID(simbol.tipus_var, 1), simbol.ambit, simbol.tam_array);
               fprintf(yyout, "\t\t\tTipus: %s  Ambit %d  Array: SI  Tamany_Array: %lu\n", tipusDadesID(simbol.tipus_var, 1), simbol.ambit, simbol.tam_array);
            }
            else {
               fprintf(stderr, "\t\tTipus: %s  Ambit %d  Array: NO\n\n", tipusDadesID(simbol.tipus_var, 1), simbol.ambit);
               fprintf(yyout, "\t\t\tTipus: %s  Ambit %d  Array: NO\n", tipusDadesID(simbol.tipus_var, 1), simbol.ambit);            
               if (simbol.tipus_var == TIPUS_STRUCT) {
                  fprintf(stderr, "\t\t[ - ] Struct: %s\n", idSimbol);
                  fprintf(stderr, "\t\t[ - ] %i Camps:\n", simbol.num_struct_camps);
                  fprintf(yyout, "\t\t\t[ - ] Struct: %s\n", idSimbol);
                  fprintf(yyout, "\t\t\t[ - ] %i Camps:\n", simbol.num_struct_camps);
                               
                  for (count = 0; count < simbol.num_struct_camps; count++) {
                     if (simbol.struct_camps[count].array == TRUE) {
                        fprintf(stderr, "\t\t\tNom: %s  Tipus: %s  Array: SI  Tamany_Array: %lu\n", simbol.struct_camps[count].valor, tipusDadesID(simbol.struct_camps[count].tipus_var, 1), simbol.struct_camps[count].tam_array, 1);
                        fprintf(yyout, "\t\t\t\t    Nom: %s  Tipus: %s  Array: SI  Tamany_Array: %lu\n", simbol.struct_camps[count].valor, tipusDadesID(simbol.struct_camps[count].tipus_var, 1), simbol.struct_camps[count].tam_array, 1);
                     }
                     else {
                        fprintf(stderr, "\t\t\tNom: %s  Tipus: %s  Array: NO\n\n", simbol.struct_camps[count].valor, tipusDadesID(simbol.struct_camps[count].tipus_var, 1));
                        fprintf(yyout, "\t\t\t\t    Nom: %s  Tipus: %s  Array: NO\n", simbol.struct_camps[count].valor, tipusDadesID(simbol.struct_camps[count].tipus_var, 1));
                     }    
                  }
                  fprintf(stderr, "\n");    
               }
            }
         }
         else {
            fprintf(stderr, "\t[ - ] Variable: %s\n", idSimbol);
            if (simbol.array == TRUE) {
               fprintf(stderr, "\t\tTipus: %s  Array: SI  Ambit %d  Tamany_Array: %lu\n\n", tipusDadesID(simbol.tipus_var, 1), simbol.ambit, simbol.tam_array);
            }
            else {
               fprintf(stderr, "\t\tTipus: %s  Ambit %d Array: NO\n\n", tipusDadesID(simbol.tipus_var, 1), simbol.ambit);
               if (simbol.tipus_var == TIPUS_STRUCT) {
                  fprintf(stderr, "\t\t[ - ] Struct: %s\n", idSimbol);
                  fprintf(stderr, "\t\t[ - ] %i Camps:\n", simbol.num_struct_camps);
                               
                  for (count = 0; count < simbol.num_struct_camps; count++) {
                     if (simbol.struct_camps[count].array == TRUE) {
                        fprintf(stderr, "\t\t\tNom: %s  Tipus: %s  Array: SI  Tamany_Array: %lu\n", simbol.struct_camps[count].valor, tipusDadesID(simbol.struct_camps[count].tipus_var, 1), simbol.struct_camps[count].tam_array, 1);
                     }
                     else {
                        fprintf(stderr, "\t\t\tNom: %s  Tipus: %s  Array: NO\n\n", simbol.struct_camps[count].valor, tipusDadesID(simbol.struct_camps[count].tipus_var, 1));
                     }   
                  }
                  fprintf(stderr, "\n");      
               }         
            }
         }
      }   
   }
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: printInfoSintactic(char * errorDesc, ...)                             ##
      ##                   - errorDesc: descripcio de la informació a mostrar                 ##
      ##                                                                                      ##
      ########################################################################################## */
      
void printInfoSintactic(char * desc, ...) {
   va_list args;
   va_start(args, desc);
   char linea[2048];
   
   sprintf(linea, "\n[ SINTACTIC/SEMANTIC -> OK ] >>> linia %i: ", numFila);
   
   vsprintf(&linea[strlen(linea)], desc, args);
   if (stdout != yyout) {
      fprintf(stdout, "%s\n", linea);
      fprintf(yyout, "%s\n", linea + 1);
   }
   else fprintf(stderr, "%s\n", linea);     
   va_end(args);
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: tamanyStruct(struct t_infoBison * p1)                                 ##
      ##                   - p1: estructura                                                   ##
      ##                                                                                      ##
      ##                     Retorna int: tamany de l'estructura                              ##
      ##                                                                                      ##
      ########################################################################################## */

int tamanyStruct(struct t_simbol * p1) {
   int tamany = 0;
   int count;
 
   if (p1 -> tipus_var == TIPUS_STRUCT) { 
      for (count = 0; count < p1 -> num_struct_camps; count++) {
         if (p1 -> struct_camps[count].array == TRUE) {
            tamany += ((tamanyTipusVar(p1 -> struct_camps[count].tipus_var)) * (p1 -> struct_camps[count].tam_array));
         }
         else {
            tamany += tamanyTipusVar(p1 -> struct_camps[count].tipus_var);
         }   
      }
   }                                
   return tamany;
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: tamanyStructbyInfoBison(struct t_infoBison * p1)                      ##
      ##                   - p1: estructura                                                   ##
      ##                                                                                      ##
      ##                     Retorna int: tamany de l'estructura                              ##
      ##                                                                                      ##
      ########################################################################################## */
      
int tamanyStructbyInfoBison(struct t_infoBison * p1) {
   int tamany = 0;
   int count;
   
   if (sym_lookup(p1 -> valor, &simbol) == SYMTAB_OK) {
      tamany = tamanyStruct(&simbol);
   }                                        
   return tamany; 
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: offsetCampStruct(struct t_simbol * p1, char * nomCamp)                ##
      ##                   - p1: estructura                                                   ##
      ##                   - nomCamp: nom del camp de l'estructura                            ##
      ##                     Retorna int: calcul de l'offset del camp respecte a l'estructura ##
      ##                                                                                      ##
      ########################################################################################## */
      
int offsetCampStruct(struct t_simbol * p1, char * nomCamp) {
   int tamany = 0;
   int count;
   int final = 0;
   
   if (p1 -> tipus_var == TIPUS_STRUCT) { 
      for (count = 0; ((count < p1 -> num_struct_camps) && (!final)); count++) {
         if (strcmp(nomCamp, p1 -> struct_camps[count].valor) != 0) {
            if (p1 -> struct_camps[count].array == TRUE) {
               tamany += ((tamanyTipusVar(p1 -> struct_camps[count].tipus_var)) * (p1 -> struct_camps[count].tam_array));
            }
            else {
               tamany += tamanyTipusVar(p1 -> struct_camps[count].tipus_var);
            }   
         }
         else final = 1;
      }
   }                                
   return tamany;
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: campExisteixStruct(char * nomStruct, char * campStruct)               ##
      ##                   - nomStruct: idSimbol de l'estructura                              ##
      ##                   - campStruct: nom del camp de l'estructura                         ##
      ##                                                                                      ##
      ##                     Retorna TRUE: si existeix el camp a l'estructura                 ##
      ##                             FALSE: si no existeix el camp                            ##
      ##                                                                                      ##
      ########################################################################################## */
      
int campExisteixStruct(char * nomStruct, char * campStruct) {
   int resultat = TIPUS_NULL;
   
   if (sym_lookup(nomStruct, &simbol) == SYMTAB_OK) {
      if (simbol.tipus_var == TIPUS_STRUCT) {
         for (count = 0; ((count < simbol.num_struct_camps) && (resultat == TIPUS_NULL)); count++) {
            if (strcmp(simbol.struct_camps[count].valor, campStruct) == 0) {
               resultat = simbol.struct_camps[count].tipus_var;
            } 
         }  
      }
   }
   return resultat;
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: campStructEsArray(char * nomStruct, char * campStruct)                ##
      ##                   - nomStruct: idSimbol de l'estructura                              ##
      ##                   - campStruct: nom del camp de l'estructura                         ##
      ##                                                                                      ##
      ##                     Retorna TRUE: si el camp de l'estructura es un array             ##
      ##                             FALSE: si no es un array                                 ##
      ##                                                                                      ##
      ########################################################################################## */
      
int campStructEsArray(char * nomStruct, char * campStruct) {
   int resultat = FALSE;
   
   if (sym_lookup(nomStruct, &simbol) == SYMTAB_OK) {
      if (simbol.tipus_var == TIPUS_STRUCT) {
         for (count = 0; ((count < simbol.num_struct_camps) && (resultat == FALSE)); count++) {
            if (strcmp(simbol.struct_camps[count].valor, campStruct) == 0) {
               resultat = simbol.struct_camps[count].array;
            } 
         }  
      }
   }
   return resultat;
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: checkOperadorIncDec(struct t_infoBison p1)                            ##
      ##                   - p1: struct infoBison                                             ##
      ##                                                                                      ##
      ##                     Retorna el tipus de l'increment d'un identificador ex -> i++;    ##
      ##                                                                                      ##
      ########################################################################################## */
      
int checkOperadorIncDec(struct t_infoBison p1) {
   if ((p1.constant != TRUE) && (identificadorDeclarat(p1.valor))) {
      if ((simbol.array == TRUE) && (p1.array != TRUE)) {
         num_errors++; printErrorSintactic(TRUE, ERR_UTILITZACIO_ARRAY, p1.valor);   
      }
      else {
         return comprovacioTipusDades(p1.tipus_var, comprovacioTipusDades(p1.tipus_var, TIPUS_INTEGER, ID_SITUACIO_OPERACIO), ID_SITUACIO_ASSIGNACIO);    
      }      
   }
   return TIPUS_NULL;
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: checkOperadors(struct t_infoBison p1, struct t_infoBison p2)          ##
      ##                   - p1: struct infoBison                                             ##
      ##                   - p2: struct infoBison                                             ##
      ##                                                                                      ##
      ##                     Retorna el tipus resultant d'una operació                        ##
      ##                                                                                      ##
      ########################################################################################## */
      
int checkOperadors(struct t_infoBison p1, struct t_infoBison p2) {
      
   if ((p1.constant != TRUE) && (identificadorDeclarat(p1.valor))) {
      if ((simbol.array == TRUE) && (p1.array != TRUE)) {
         num_errors++; printErrorSintactic(TRUE, ERR_UTILITZACIO_ARRAY, p1.valor);   
      }
      else {
         if (p2.constant == TRUE) {
            return comprovacioTipusDades(p1.tipus_var, p2.tipus_var, ID_SITUACIO_OPERACIO);
         }
         else {
            if (identificadorDeclarat(p2.valor)) {
               if ((simbol.array == TRUE) && (p2.array != TRUE)) {
                  num_errors++; printErrorSintactic(TRUE, ERR_UTILITZACIO_ARRAY, p2.valor);   
               }
               else return comprovacioTipusDades(p1.tipus_var, p2.tipus_var, ID_SITUACIO_OPERACIO);
            }
         }
      }
   }
   else {
      if (p1.constant == TRUE) {
         if (p2.constant == TRUE) {
            return comprovacioTipusDades(p1.tipus_var, p2.tipus_var, ID_SITUACIO_OPERACIO);
         }
         else {
            if (identificadorDeclarat(p2.valor)) {
               if ((simbol.array == TRUE) && (p2.array != TRUE)) {
                  num_errors++; printErrorSintactic(TRUE, ERR_UTILITZACIO_ARRAY, p2.valor);   
               }
               else return comprovacioTipusDades(p1.tipus_var, p2.tipus_var, ID_SITUACIO_OPERACIO);
            }
         }   
      } 
   }
      
   return TIPUS_NULL;
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: esTipus(char * nom)                                                   ##
      ##                   - nom: identificador del tipus                                     ##
      ##                                                                                      ##
      ##                     Retorna TRUE: si el tipus del simbol es un TIPUS_BASIC           ##
      ##                             FALSE: en cas contrari                                   ##
      ##                                                                                      ##
      ########################################################################################## */
      
int esTipus(char * nom) {
   if (sym_lookup(nom, &simbol_tmp) == SYMTAB_OK) {
      if (simbol_tmp.tipus == TIPUS_BASIC) {
         return TRUE;
      }
   }
   return FALSE;
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: tipusDadesID(int idTipus, int espais)                                 ##
      ##                   - idTipus: identificador del tipus de dades                        ##
      ##                   - espais: es mostra la informació amb un format o no               ##
      ##                                                                                      ##
      ##                     Retorna el string del tipus                                      ##
      ##                                                                                      ##
      ########################################################################################## */
      
char * tipusDadesID(int idTipus, int espais) {
   char * tdades = (char *) malloc(10);
   
   strcpy(tdades, "");
   
   if (espais) {
      switch (idTipus) {
         case -1: strcpy(tdades, "NULL     "); break;
         case 0: strcpy(tdades, "VOID     "); break;
         case 1: strcpy(tdades, "CHAR     "); break;
         case 2: strcpy(tdades, "SHORT    "); break;
         case 3: strcpy(tdades, "INT      "); break;
         case 4: strcpy(tdades, "LONG     "); break;
         case 5: strcpy(tdades, "FLOAT    "); break;
         case 6: strcpy(tdades, "DOUBLE   "); break;
         case 7: strcpy(tdades, "STRING   "); break;
         case 8: strcpy(tdades, "STRUCT   "); break;
      }
   }
   else {
      switch (idTipus) {
         case -1: strcpy(tdades, "NULL"); break;
         case 0: strcpy(tdades, "VOID"); break;
         case 1: strcpy(tdades, "CHAR"); break;
         case 2: strcpy(tdades, "SHORT"); break;
         case 3: strcpy(tdades, "INT"); break;
         case 4: strcpy(tdades, "LONG"); break;
         case 5: strcpy(tdades, "FLOAT"); break;
         case 6: strcpy(tdades, "DOUBLE"); break;
         case 7: strcpy(tdades, "STRING"); break;
         case 8: strcpy(tdades, "STRUCT"); break;
      }   
   }
   return tdades;
}

