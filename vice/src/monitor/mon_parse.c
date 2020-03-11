/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
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
#define YYBISON_VERSION "3.3.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "vice/src/monitor/mon_parse.y" /* yacc.c:337  */

/* -*- C -*-
 *
 * mon_parse.y - Parser for the VICE built-in monitor.
 *
 * Written by
 *  Daniel Sladic <sladic@eecg.toronto.edu>
 *  Andreas Boose <viceteam@t-online.de>
 *  Thomas Giesel <skoe@directbox.com>
 *
 * This file is part of VICE, the Versatile Commodore Emulator.
 * See README for copyright notice.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307  USA.
 *
 */

#include "vice.h"

#if !defined(MACOS_COMPILE) && !(defined(__OS2__) && defined(IDE_COMPILE))
#ifdef __GNUC__
#undef alloca
#ifndef ANDROID_COMPILE
#define        alloca(n)       __builtin_alloca (n)
#endif
#else
#ifdef HAVE_ALLOCA_H
#include <alloca.h>
#else  /* Not HAVE_ALLOCA_H.  */
#if !defined(_AIX) && !defined(WINCE)
#ifndef _MSC_VER
extern char *alloca();
#else
#define alloca(n)   _alloca(n)
#endif  /* MSVC */
#endif /* Not AIX and not WINCE.  */
#endif /* HAVE_ALLOCA_H.  */
#endif /* GCC.  */
#endif /* MACOS OS2 */

/* SunOS 4.x specific stuff */
#if defined(sun) || defined(__sun)
#  if !defined(__SVR4) && !defined(__svr4__)
#    ifdef __sparc__
#      define YYFREE
#    endif
#  endif
#endif

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "asm.h"
#include "console.h"
#include "lib.h"
#include "machine.h"
#include "mon_breakpoint.h"
#include "mon_command.h"
#include "mon_disassemble.h"
#include "mon_drive.h"
#include "mon_file.h"
#include "mon_memmap.h"
#include "mon_memory.h"
#include "mon_register.h"
#include "mon_util.h"
#include "montypes.h"
#include "resources.h"
#include "types.h"
#include "uimon.h"

#ifdef AMIGA_MORPHOS
#undef REG_PC
#endif

#define join_ints(x,y) (LO16_TO_HI16(x)|y)
#define separate_int1(x) (HI16_TO_LO16(x))
#define separate_int2(x) (LO16(x))

static int yyerror(char *s);
static int temp;
static int resolve_datatype(unsigned guess_type, const char *num);
static int resolve_range(enum t_memspace memspace, MON_ADDR range[2],
                         const char *num);

#ifdef __IBMC__
static void __yy_memcpy (char *to, char *from, int count);
#endif

/* Defined in the lexer */
extern void free_buffer(void);
extern void make_buffer(char *str);
extern int yylex(void);
extern int cur_len, last_len;

#define ERR_ILLEGAL_INPUT 1     /* Generic error as returned by yacc.  */
#define ERR_RANGE_BAD_START 2
#define ERR_RANGE_BAD_END 3
#define ERR_BAD_CMD 4
#define ERR_EXPECT_CHECKNUM 5
#define ERR_EXPECT_END_CMD 6
#define ERR_MISSING_CLOSE_PAREN 7
#define ERR_INCOMPLETE_COMPARE_OP 8
#define ERR_EXPECT_FILENAME 9
#define ERR_ADDR_TOO_BIG 10
#define ERR_IMM_TOO_BIG 11
#define ERR_EXPECT_STRING 12
#define ERR_UNDEFINED_LABEL 13
#define ERR_EXPECT_DEVICE_NUM 14
#define ERR_EXPECT_ADDRESS 15
#define ERR_INVALID_REGISTER 16

#define BAD_ADDR (new_addr(e_invalid_space, 0))
#define CHECK_ADDR(x) ((x) == addr_mask(x))

#define YYDEBUG 1


#line 203 "y.tab.c" /* yacc.c:337  */
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
# define YYERROR_VERBOSE 0
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    H_NUMBER = 258,
    D_NUMBER = 259,
    O_NUMBER = 260,
    B_NUMBER = 261,
    CONVERT_OP = 262,
    B_DATA = 263,
    H_RANGE_GUESS = 264,
    D_NUMBER_GUESS = 265,
    O_NUMBER_GUESS = 266,
    B_NUMBER_GUESS = 267,
    BAD_CMD = 268,
    MEM_OP = 269,
    IF = 270,
    MEM_COMP = 271,
    MEM_DISK8 = 272,
    MEM_DISK9 = 273,
    MEM_DISK10 = 274,
    MEM_DISK11 = 275,
    EQUALS = 276,
    TRAIL = 277,
    CMD_SEP = 278,
    LABEL_ASGN_COMMENT = 279,
    CMD_SIDEFX = 280,
    CMD_RETURN = 281,
    CMD_BLOCK_READ = 282,
    CMD_BLOCK_WRITE = 283,
    CMD_UP = 284,
    CMD_DOWN = 285,
    CMD_LOAD = 286,
    CMD_SAVE = 287,
    CMD_VERIFY = 288,
    CMD_IGNORE = 289,
    CMD_HUNT = 290,
    CMD_FILL = 291,
    CMD_MOVE = 292,
    CMD_GOTO = 293,
    CMD_REGISTERS = 294,
    CMD_READSPACE = 295,
    CMD_WRITESPACE = 296,
    CMD_RADIX = 297,
    CMD_MEM_DISPLAY = 298,
    CMD_BREAK = 299,
    CMD_TRACE = 300,
    CMD_IO = 301,
    CMD_BRMON = 302,
    CMD_COMPARE = 303,
    CMD_DUMP = 304,
    CMD_UNDUMP = 305,
    CMD_EXIT = 306,
    CMD_DELETE = 307,
    CMD_CONDITION = 308,
    CMD_COMMAND = 309,
    CMD_ASSEMBLE = 310,
    CMD_DISASSEMBLE = 311,
    CMD_NEXT = 312,
    CMD_STEP = 313,
    CMD_PRINT = 314,
    CMD_DEVICE = 315,
    CMD_HELP = 316,
    CMD_WATCH = 317,
    CMD_DISK = 318,
    CMD_QUIT = 319,
    CMD_CHDIR = 320,
    CMD_BANK = 321,
    CMD_LOAD_LABELS = 322,
    CMD_SAVE_LABELS = 323,
    CMD_ADD_LABEL = 324,
    CMD_DEL_LABEL = 325,
    CMD_SHOW_LABELS = 326,
    CMD_CLEAR_LABELS = 327,
    CMD_RECORD = 328,
    CMD_MON_STOP = 329,
    CMD_PLAYBACK = 330,
    CMD_CHAR_DISPLAY = 331,
    CMD_SPRITE_DISPLAY = 332,
    CMD_TEXT_DISPLAY = 333,
    CMD_SCREENCODE_DISPLAY = 334,
    CMD_ENTER_DATA = 335,
    CMD_ENTER_BIN_DATA = 336,
    CMD_KEYBUF = 337,
    CMD_BLOAD = 338,
    CMD_BSAVE = 339,
    CMD_SCREEN = 340,
    CMD_UNTIL = 341,
    CMD_CPU = 342,
    CMD_YYDEBUG = 343,
    CMD_BACKTRACE = 344,
    CMD_SCREENSHOT = 345,
    CMD_PWD = 346,
    CMD_DIR = 347,
    CMD_RESOURCE_GET = 348,
    CMD_RESOURCE_SET = 349,
    CMD_LOAD_RESOURCES = 350,
    CMD_SAVE_RESOURCES = 351,
    CMD_ATTACH = 352,
    CMD_DETACH = 353,
    CMD_MON_RESET = 354,
    CMD_TAPECTRL = 355,
    CMD_CARTFREEZE = 356,
    CMD_CPUHISTORY = 357,
    CMD_MEMMAPZAP = 358,
    CMD_MEMMAPSHOW = 359,
    CMD_MEMMAPSAVE = 360,
    CMD_COMMENT = 361,
    CMD_LIST = 362,
    CMD_STOPWATCH = 363,
    RESET = 364,
    CMD_EXPORT = 365,
    CMD_AUTOSTART = 366,
    CMD_AUTOLOAD = 367,
    CMD_MAINCPU_TRACE = 368,
    CMD_LABEL_ASGN = 369,
    L_PAREN = 370,
    R_PAREN = 371,
    ARG_IMMEDIATE = 372,
    REG_A = 373,
    REG_X = 374,
    REG_Y = 375,
    COMMA = 376,
    INST_SEP = 377,
    L_BRACKET = 378,
    R_BRACKET = 379,
    LESS_THAN = 380,
    REG_U = 381,
    REG_S = 382,
    REG_PC = 383,
    REG_PCR = 384,
    REG_B = 385,
    REG_C = 386,
    REG_D = 387,
    REG_E = 388,
    REG_H = 389,
    REG_L = 390,
    REG_AF = 391,
    REG_BC = 392,
    REG_DE = 393,
    REG_HL = 394,
    REG_IX = 395,
    REG_IY = 396,
    REG_SP = 397,
    REG_IXH = 398,
    REG_IXL = 399,
    REG_IYH = 400,
    REG_IYL = 401,
    PLUS = 402,
    MINUS = 403,
    STRING = 404,
    FILENAME = 405,
    R_O_L = 406,
    OPCODE = 407,
    LABEL = 408,
    BANKNAME = 409,
    CPUTYPE = 410,
    MON_REGISTER = 411,
    COMPARE_OP = 412,
    RADIX_TYPE = 413,
    INPUT_SPEC = 414,
    CMD_CHECKPT_ON = 415,
    CMD_CHECKPT_OFF = 416,
    TOGGLE = 417,
    MASK = 418
  };
#endif
/* Tokens.  */
#define H_NUMBER 258
#define D_NUMBER 259
#define O_NUMBER 260
#define B_NUMBER 261
#define CONVERT_OP 262
#define B_DATA 263
#define H_RANGE_GUESS 264
#define D_NUMBER_GUESS 265
#define O_NUMBER_GUESS 266
#define B_NUMBER_GUESS 267
#define BAD_CMD 268
#define MEM_OP 269
#define IF 270
#define MEM_COMP 271
#define MEM_DISK8 272
#define MEM_DISK9 273
#define MEM_DISK10 274
#define MEM_DISK11 275
#define EQUALS 276
#define TRAIL 277
#define CMD_SEP 278
#define LABEL_ASGN_COMMENT 279
#define CMD_SIDEFX 280
#define CMD_RETURN 281
#define CMD_BLOCK_READ 282
#define CMD_BLOCK_WRITE 283
#define CMD_UP 284
#define CMD_DOWN 285
#define CMD_LOAD 286
#define CMD_SAVE 287
#define CMD_VERIFY 288
#define CMD_IGNORE 289
#define CMD_HUNT 290
#define CMD_FILL 291
#define CMD_MOVE 292
#define CMD_GOTO 293
#define CMD_REGISTERS 294
#define CMD_READSPACE 295
#define CMD_WRITESPACE 296
#define CMD_RADIX 297
#define CMD_MEM_DISPLAY 298
#define CMD_BREAK 299
#define CMD_TRACE 300
#define CMD_IO 301
#define CMD_BRMON 302
#define CMD_COMPARE 303
#define CMD_DUMP 304
#define CMD_UNDUMP 305
#define CMD_EXIT 306
#define CMD_DELETE 307
#define CMD_CONDITION 308
#define CMD_COMMAND 309
#define CMD_ASSEMBLE 310
#define CMD_DISASSEMBLE 311
#define CMD_NEXT 312
#define CMD_STEP 313
#define CMD_PRINT 314
#define CMD_DEVICE 315
#define CMD_HELP 316
#define CMD_WATCH 317
#define CMD_DISK 318
#define CMD_QUIT 319
#define CMD_CHDIR 320
#define CMD_BANK 321
#define CMD_LOAD_LABELS 322
#define CMD_SAVE_LABELS 323
#define CMD_ADD_LABEL 324
#define CMD_DEL_LABEL 325
#define CMD_SHOW_LABELS 326
#define CMD_CLEAR_LABELS 327
#define CMD_RECORD 328
#define CMD_MON_STOP 329
#define CMD_PLAYBACK 330
#define CMD_CHAR_DISPLAY 331
#define CMD_SPRITE_DISPLAY 332
#define CMD_TEXT_DISPLAY 333
#define CMD_SCREENCODE_DISPLAY 334
#define CMD_ENTER_DATA 335
#define CMD_ENTER_BIN_DATA 336
#define CMD_KEYBUF 337
#define CMD_BLOAD 338
#define CMD_BSAVE 339
#define CMD_SCREEN 340
#define CMD_UNTIL 341
#define CMD_CPU 342
#define CMD_YYDEBUG 343
#define CMD_BACKTRACE 344
#define CMD_SCREENSHOT 345
#define CMD_PWD 346
#define CMD_DIR 347
#define CMD_RESOURCE_GET 348
#define CMD_RESOURCE_SET 349
#define CMD_LOAD_RESOURCES 350
#define CMD_SAVE_RESOURCES 351
#define CMD_ATTACH 352
#define CMD_DETACH 353
#define CMD_MON_RESET 354
#define CMD_TAPECTRL 355
#define CMD_CARTFREEZE 356
#define CMD_CPUHISTORY 357
#define CMD_MEMMAPZAP 358
#define CMD_MEMMAPSHOW 359
#define CMD_MEMMAPSAVE 360
#define CMD_COMMENT 361
#define CMD_LIST 362
#define CMD_STOPWATCH 363
#define RESET 364
#define CMD_EXPORT 365
#define CMD_AUTOSTART 366
#define CMD_AUTOLOAD 367
#define CMD_MAINCPU_TRACE 368
#define CMD_LABEL_ASGN 369
#define L_PAREN 370
#define R_PAREN 371
#define ARG_IMMEDIATE 372
#define REG_A 373
#define REG_X 374
#define REG_Y 375
#define COMMA 376
#define INST_SEP 377
#define L_BRACKET 378
#define R_BRACKET 379
#define LESS_THAN 380
#define REG_U 381
#define REG_S 382
#define REG_PC 383
#define REG_PCR 384
#define REG_B 385
#define REG_C 386
#define REG_D 387
#define REG_E 388
#define REG_H 389
#define REG_L 390
#define REG_AF 391
#define REG_BC 392
#define REG_DE 393
#define REG_HL 394
#define REG_IX 395
#define REG_IY 396
#define REG_SP 397
#define REG_IXH 398
#define REG_IXL 399
#define REG_IYH 400
#define REG_IYL 401
#define PLUS 402
#define MINUS 403
#define STRING 404
#define FILENAME 405
#define R_O_L 406
#define OPCODE 407
#define LABEL 408
#define BANKNAME 409
#define CPUTYPE 410
#define MON_REGISTER 411
#define COMPARE_OP 412
#define RADIX_TYPE 413
#define INPUT_SPEC 414
#define CMD_CHECKPT_ON 415
#define CMD_CHECKPT_OFF 416
#define TOGGLE 417
#define MASK 418

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 134 "vice/src/monitor/mon_parse.y" /* yacc.c:352  */

    MON_ADDR a;
    MON_ADDR range[2];
    int i;
    REG_ID reg;
    CONDITIONAL cond_op;
    cond_node_t *cond_node;
    RADIXTYPE rt;
    ACTION action;
    char *str;
    asm_mode_addr_info_t mode;

#line 582 "y.tab.c" /* yacc.c:352  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);





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
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
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
#  define YYSIZE_T unsigned
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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
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
#define YYFINAL  312
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1713

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  172
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  55
/* YYNRULES -- Number of rules.  */
#define YYNRULES  314
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  628

#define YYUNDEFTOK  2
#define YYMAXUTOK   418

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     168,   169,   166,   164,     2,   165,     2,   167,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   171,     2,
       2,     2,     2,     2,   170,     2,     2,     2,     2,     2,
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
     155,   156,   157,   158,   159,   160,   161,   162,   163
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   198,   198,   199,   200,   203,   204,   207,   208,   209,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   227,   229,   231,   233,   235,   237,   239,
     241,   243,   245,   247,   249,   251,   253,   255,   257,   259,
     261,   263,   265,   267,   269,   271,   273,   275,   278,   280,
     282,   285,   290,   295,   297,   299,   301,   303,   305,   307,
     309,   311,   313,   317,   324,   323,   326,   328,   330,   334,
     336,   338,   340,   342,   344,   346,   348,   350,   352,   354,
     356,   358,   360,   362,   364,   366,   368,   370,   372,   376,
     385,   388,   392,   395,   404,   407,   416,   421,   423,   425,
     427,   429,   431,   433,   435,   437,   439,   441,   445,   447,
     452,   454,   472,   474,   476,   478,   480,   484,   486,   488,
     490,   492,   494,   496,   498,   500,   502,   504,   506,   508,
     510,   512,   514,   516,   518,   520,   522,   524,   526,   528,
     532,   534,   536,   538,   540,   542,   544,   546,   548,   550,
     552,   554,   556,   558,   560,   562,   564,   566,   568,   572,
     574,   576,   580,   582,   586,   590,   593,   594,   597,   598,
     601,   602,   605,   606,   609,   610,   613,   619,   627,   628,
     631,   635,   636,   639,   640,   643,   644,   646,   650,   651,
     654,   659,   664,   674,   675,   678,   679,   680,   681,   682,
     685,   687,   689,   690,   691,   692,   693,   694,   695,   698,
     699,   701,   706,   708,   710,   712,   716,   722,   728,   736,
     737,   740,   741,   744,   745,   748,   749,   750,   753,   754,
     757,   758,   759,   760,   763,   764,   765,   768,   769,   770,
     771,   772,   775,   776,   777,   780,   790,   791,   794,   801,
     812,   823,   831,   850,   856,   864,   872,   874,   876,   877,
     878,   879,   880,   881,   882,   884,   886,   888,   890,   891,
     892,   893,   894,   895,   896,   897,   898,   899,   900,   901,
     902,   903,   904,   905,   906,   907,   908,   910,   911,   926,
     930,   934,   938,   942,   946,   950,   954,   958,   970,   985,
     989,   993,   997,  1001,  1005,  1009,  1013,  1017,  1029,  1034,
    1042,  1043,  1044,  1045,  1049
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "H_NUMBER", "D_NUMBER", "O_NUMBER",
  "B_NUMBER", "CONVERT_OP", "B_DATA", "H_RANGE_GUESS", "D_NUMBER_GUESS",
  "O_NUMBER_GUESS", "B_NUMBER_GUESS", "BAD_CMD", "MEM_OP", "IF",
  "MEM_COMP", "MEM_DISK8", "MEM_DISK9", "MEM_DISK10", "MEM_DISK11",
  "EQUALS", "TRAIL", "CMD_SEP", "LABEL_ASGN_COMMENT", "CMD_SIDEFX",
  "CMD_RETURN", "CMD_BLOCK_READ", "CMD_BLOCK_WRITE", "CMD_UP", "CMD_DOWN",
  "CMD_LOAD", "CMD_SAVE", "CMD_VERIFY", "CMD_IGNORE", "CMD_HUNT",
  "CMD_FILL", "CMD_MOVE", "CMD_GOTO", "CMD_REGISTERS", "CMD_READSPACE",
  "CMD_WRITESPACE", "CMD_RADIX", "CMD_MEM_DISPLAY", "CMD_BREAK",
  "CMD_TRACE", "CMD_IO", "CMD_BRMON", "CMD_COMPARE", "CMD_DUMP",
  "CMD_UNDUMP", "CMD_EXIT", "CMD_DELETE", "CMD_CONDITION", "CMD_COMMAND",
  "CMD_ASSEMBLE", "CMD_DISASSEMBLE", "CMD_NEXT", "CMD_STEP", "CMD_PRINT",
  "CMD_DEVICE", "CMD_HELP", "CMD_WATCH", "CMD_DISK", "CMD_QUIT",
  "CMD_CHDIR", "CMD_BANK", "CMD_LOAD_LABELS", "CMD_SAVE_LABELS",
  "CMD_ADD_LABEL", "CMD_DEL_LABEL", "CMD_SHOW_LABELS", "CMD_CLEAR_LABELS",
  "CMD_RECORD", "CMD_MON_STOP", "CMD_PLAYBACK", "CMD_CHAR_DISPLAY",
  "CMD_SPRITE_DISPLAY", "CMD_TEXT_DISPLAY", "CMD_SCREENCODE_DISPLAY",
  "CMD_ENTER_DATA", "CMD_ENTER_BIN_DATA", "CMD_KEYBUF", "CMD_BLOAD",
  "CMD_BSAVE", "CMD_SCREEN", "CMD_UNTIL", "CMD_CPU", "CMD_YYDEBUG",
  "CMD_BACKTRACE", "CMD_SCREENSHOT", "CMD_PWD", "CMD_DIR",
  "CMD_RESOURCE_GET", "CMD_RESOURCE_SET", "CMD_LOAD_RESOURCES",
  "CMD_SAVE_RESOURCES", "CMD_ATTACH", "CMD_DETACH", "CMD_MON_RESET",
  "CMD_TAPECTRL", "CMD_CARTFREEZE", "CMD_CPUHISTORY", "CMD_MEMMAPZAP",
  "CMD_MEMMAPSHOW", "CMD_MEMMAPSAVE", "CMD_COMMENT", "CMD_LIST",
  "CMD_STOPWATCH", "RESET", "CMD_EXPORT", "CMD_AUTOSTART", "CMD_AUTOLOAD",
  "CMD_MAINCPU_TRACE", "CMD_LABEL_ASGN", "L_PAREN", "R_PAREN",
  "ARG_IMMEDIATE", "REG_A", "REG_X", "REG_Y", "COMMA", "INST_SEP",
  "L_BRACKET", "R_BRACKET", "LESS_THAN", "REG_U", "REG_S", "REG_PC",
  "REG_PCR", "REG_B", "REG_C", "REG_D", "REG_E", "REG_H", "REG_L",
  "REG_AF", "REG_BC", "REG_DE", "REG_HL", "REG_IX", "REG_IY", "REG_SP",
  "REG_IXH", "REG_IXL", "REG_IYH", "REG_IYL", "PLUS", "MINUS", "STRING",
  "FILENAME", "R_O_L", "OPCODE", "LABEL", "BANKNAME", "CPUTYPE",
  "MON_REGISTER", "COMPARE_OP", "RADIX_TYPE", "INPUT_SPEC",
  "CMD_CHECKPT_ON", "CMD_CHECKPT_OFF", "TOGGLE", "MASK", "'+'", "'-'",
  "'*'", "'/'", "'('", "')'", "'@'", "':'", "$accept", "top_level",
  "command_list", "end_cmd", "command", "machine_state_rules",
  "register_mod", "symbol_table_rules", "asm_rules", "$@1", "memory_rules",
  "checkpoint_rules", "checkpoint_control_rules", "monitor_state_rules",
  "monitor_misc_rules", "disk_rules", "cmd_file_rules", "data_entry_rules",
  "monitor_debug_rules", "rest_of_line", "opt_rest_of_line", "filename",
  "device_num", "mem_op", "opt_mem_op", "register", "reg_list", "reg_asgn",
  "checkpt_num", "address_opt_range", "address_range", "opt_address",
  "address", "opt_sep", "memspace", "memloc", "memaddr", "expression",
  "opt_if_cond_expr", "cond_expr", "compare_operand", "data_list",
  "data_element", "hunt_list", "hunt_element", "value", "d_number",
  "guess_default", "number", "assembly_instr_list", "assembly_instruction",
  "post_assemble", "asm_operand_mode", "index_reg", "index_ureg", YY_NULLPTR
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
     415,   416,   417,   418,    43,    45,    42,    47,    40,    41,
      64,    58
};
# endif

#define YYPACT_NINF -398

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-398)))

#define YYTABLE_NINF -195

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1117,   890,  -398,  -398,   103,   365,   890,   890,    89,    89,
      49,    49,    49,   574,  1473,  1473,  1473,  1115,   409,    60,
     983,  1231,  1231,  1115,  1473,    49,    49,   365,   742,   574,
     574,  1491,  1369,    89,    89,   890,   696,   169,  1231,  -132,
     365,  -132,   515,   189,   189,  1491,   426,  1511,  1511,    49,
     365,    49,  1369,  1369,  1369,  1369,  1491,   365,  -132,    49,
      49,   365,  1369,   137,   365,   365,    49,   365,  -126,  -122,
     -78,    49,    49,    49,   890,    89,   -70,   365,    89,   365,
      89,    49,  -126,   503,   324,   365,    49,    49,   -73,    70,
    1536,   742,   742,   121,  1254,  -398,  -398,  -398,  -398,  -398,
    -398,  -398,  -398,  -398,  -398,  -398,  -398,  -398,  -398,   107,
    -398,  -398,  -398,  -398,  -398,  -398,  -398,  -398,  -398,  -398,
    -398,  -398,  -398,   890,  -398,   -21,   241,  -398,  -398,  -398,
    -398,  -398,  -398,   365,  -398,  -398,   927,   927,  -398,  -398,
     890,  -398,   890,  -398,  -398,   669,   691,   669,  -398,  -398,
    -398,  -398,  -398,    89,  -398,  -398,  -398,   -70,   -70,   -70,
    -398,  -398,  -398,   -70,   -70,  -398,   365,   -70,  -398,   122,
     233,  -398,    95,   365,  -398,   -70,  -398,   365,  -398,   340,
    -398,  -398,   138,  1473,  -398,  1473,  -398,   365,   -70,   365,
     365,  -398,   472,  -398,   365,   152,   109,   171,  -398,   365,
    -398,   890,  -398,   890,   241,   365,  -398,  -398,   365,  -398,
    1473,   365,  -398,   365,   365,  -398,    65,   365,   -70,   365,
     -70,   -70,   365,   -70,  -398,   365,  -398,   365,   365,  -398,
     365,  -398,   365,  -398,   365,  -398,   365,  -398,   365,  1097,
    -398,   365,   669,   669,  -398,  -398,   365,   365,  -398,  -398,
    -398,    89,  -398,  -398,   365,   365,    31,   365,   365,   890,
     241,  -398,   890,   890,  -398,  -398,   890,  -398,  -398,   890,
     -70,   365,   476,  -398,   365,   255,   365,  -398,  -398,  1592,
    1592,   365,  1491,   830,  1546,    61,   264,  1566,  1546,    66,
    -398,    74,  -398,  -398,  -398,  -398,  -398,  -398,  -398,  -398,
    -398,  -398,  -398,  -398,  -398,  -398,    76,  -398,  -398,   365,
    -398,   365,  -398,  -398,  -398,    12,  -398,   890,   890,   890,
     890,  -398,  -398,   162,   946,   241,   241,  -398,   277,  1392,
    1415,  1455,  -398,   890,   144,  1491,  1253,  1097,  1491,  -398,
    1546,  1546,   230,  -398,  -398,  -398,  1473,  -398,  -398,   186,
     186,  -398,  1491,  -398,  -398,  -398,   716,   365,    54,  -398,
      62,  -398,   241,   241,  -398,  -398,  -398,   186,  -398,  -398,
    -398,  -398,    72,  -398,    49,  -398,    49,    71,  -398,    79,
    -398,  -398,  -398,  -398,  -398,  -398,  -398,  -398,  -398,  1513,
    -398,  -398,  -398,   277,  1435,  -398,  -398,  -398,   890,  -398,
    -398,   365,  -398,  -398,   241,  -398,   241,   241,   241,   857,
     890,  -398,  -398,  -398,  -398,  1546,  -398,  1546,  -398,   468,
      99,   113,   117,   120,   128,   143,    -1,  -398,   442,  -398,
    -398,  -398,  -398,   332,    91,  -398,   133,   362,   140,   141,
      -5,  -398,   442,   442,  1580,  -398,  -398,  -398,  -398,    -9,
      -9,  -398,  -398,   365,  1491,   365,  -398,  -398,   365,  -398,
     365,  -398,   365,   241,  -398,  -398,    53,  -398,  -398,  -398,
    -398,  -398,  1513,   365,  -398,  -398,   365,   716,   365,   365,
     365,   716,   119,  -398,    80,  -398,  -398,  -398,   365,   149,
     157,   365,  -398,  -398,   365,   365,   365,   365,   365,   365,
    -398,  1097,   365,  -398,   365,   241,  -398,  -398,  -398,  -398,
    -398,  -398,   365,   241,   365,   365,   365,  -398,  -398,  -398,
    -398,  -398,  -398,  -398,   153,  -107,  -398,   442,  -398,   134,
     442,   422,   -98,   442,   442,   534,   173,  -398,  -398,  -398,
    -398,  -398,  -398,  -398,  -398,  -398,  -398,  -398,  -398,  -398,
    -398,  -398,  -398,  -398,  -398,  -398,  -398,   155,  -398,  -398,
    -398,     7,   127,   285,  -398,  -398,    62,    62,  -398,  -398,
    -398,  -398,  -398,  -398,  -398,  -398,  -398,  -398,  -398,  -398,
    -398,  -398,  -398,  -398,   238,   190,   193,  -398,  -398,   194,
     442,   195,  -398,   -69,   198,   212,   213,   216,   222,  -398,
    -398,  1491,  -398,  -398,  -398,  -398,  -398,  -398,  -398,  -398,
    -398,  -398,   192,  -398,   221,  -398,  -398,   224,  -398,  -398,
    -398,  -398,  -398,  -398,   231,  -398,  -398,  -398
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     0,    22,     4,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   167,     0,
       0,     0,     0,     0,     0,     0,   194,     0,     0,     0,
       0,     0,   167,     0,     0,     0,     0,     0,     0,     0,
     268,     0,     0,     0,     2,     5,    10,    47,    11,    13,
      12,    14,    15,    16,    17,    18,    19,    20,    21,     0,
     237,   238,   239,   240,   236,   235,   234,   195,   196,   197,
     198,   199,   176,     0,   229,     0,     0,   208,   241,   228,
       9,     8,     7,     0,   109,    35,     0,     0,   193,    42,
       0,    44,     0,   169,   168,     0,     0,     0,   182,   230,
     233,   232,   231,     0,   181,   186,   192,   194,   194,   194,
     190,   200,   201,   194,   194,    28,     0,   194,    48,     0,
       0,   179,     0,     0,   111,   194,    75,     0,   183,   194,
     173,    90,   174,     0,    96,     0,    29,     0,   194,     0,
       0,   115,     9,   104,     0,     0,     0,     0,    68,     0,
      40,     0,    38,     0,     0,     0,   165,   119,     0,    94,
       0,     0,   114,     0,     0,    23,     0,     0,   194,     0,
     194,   194,     0,   194,    59,     0,    61,     0,     0,   160,
       0,    77,     0,    79,     0,    81,     0,    83,     0,     0,
     163,     0,     0,     0,    46,    92,     0,     0,    31,   164,
     124,     0,   126,   166,     0,     0,     0,     0,     0,     0,
       0,   133,     0,     0,   136,    33,     0,    84,    85,     0,
     194,     0,     9,   151,     0,   170,     0,   139,   113,     0,
       0,     0,     0,     0,     0,   269,     0,     0,     0,   270,
     271,   272,   273,   274,   277,   280,   281,   282,   283,   284,
     285,   286,   275,   278,   276,   279,   249,   245,    98,     0,
     100,     0,     1,     6,     3,     0,   177,     0,     0,     0,
       0,   121,   108,   194,     0,     0,     0,   171,   194,   143,
       0,     0,   101,     0,     0,     0,     0,     0,     0,    27,
       0,     0,     0,    50,    49,   110,     0,    74,   172,   210,
     210,    30,     0,    36,    37,   103,     0,     0,     0,    66,
       0,    67,     0,     0,   118,   112,   120,   210,   117,   122,
      25,    24,     0,    52,     0,    54,     0,     0,    56,     0,
      58,    60,   159,   161,    76,    78,    80,    82,   222,     0,
     220,   221,   123,   194,     0,    91,    32,   127,     0,   125,
     129,     0,   131,   132,     0,   154,     0,     0,     0,     0,
       0,   137,   152,   138,   155,     0,   157,     0,   116,     0,
       0,     0,     0,     0,     0,     0,     0,   248,     0,   310,
     311,   314,   313,     0,   293,   312,     0,     0,     0,     0,
       0,   287,     0,     0,     0,    97,    99,   207,   206,   202,
     203,   204,   205,     0,     0,     0,    43,    45,     0,   144,
       0,   148,     0,     0,   227,   226,     0,   224,   225,   185,
     187,   191,     0,     0,   180,   178,     0,     0,     0,     0,
       0,     0,     0,   216,     0,   215,   217,   107,     0,   247,
     246,     0,    41,    39,     0,     0,     0,     0,     0,     0,
     162,     0,     0,   146,     0,     0,   130,   153,   134,   135,
      34,    86,     0,     0,     0,     0,     0,    62,   258,   259,
     260,   261,   262,   263,   254,     0,   295,     0,   291,   289,
       0,     0,     0,     0,     0,     0,   308,   294,   296,   250,
     251,   252,   297,   253,   288,   149,   188,   150,   140,   142,
     147,   102,    72,   223,    71,    69,    73,   209,    89,    95,
      70,     0,     0,     0,   105,   106,     0,   244,    65,    93,
      26,    51,    53,    55,    57,   219,   141,   145,   128,    87,
      88,   156,   158,    63,     0,     0,     0,   292,   290,     0,
       0,     0,   303,     0,     0,     0,     0,     0,     0,   214,
     213,     0,   212,   211,   242,   243,   264,   257,   265,   266,
     267,   255,     0,   305,     0,   301,   299,     0,   304,   306,
     307,   298,   309,   218,     0,   302,   300,   256
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -398,  -398,  -398,   572,   220,  -398,  -398,  -398,  -398,  -398,
    -398,  -398,  -398,  -398,  -398,  -398,  -398,  -398,  -398,    83,
     268,   102,  -110,  -398,   -15,    -7,  -398,    10,   374,    15,
       0,  -307,    29,    64,   -14,  -206,  -398,   234,  -288,  -397,
    -398,    28,  -133,  -398,   -91,  -398,  -398,  -398,   130,  -398,
    -355,  -398,  -398,   485,   -62
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    93,    94,   134,    95,    96,    97,    98,    99,   360,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   208,
     254,   145,   274,   182,   183,   124,   170,   171,   153,   177,
     178,   453,   179,   454,   125,   160,   161,   275,   478,   484,
     485,   389,   390,   466,   467,   127,   154,   128,   162,   489,
     109,   491,   307,   434,   435
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     159,   159,   159,   167,   172,   490,   159,   185,   599,   167,
     159,   169,   585,   447,   157,   163,   164,   167,   159,   206,
     586,   458,   205,   210,   188,   253,   592,   255,   216,   218,
     220,   167,   223,   225,   227,   328,   330,   331,   159,   159,
     159,   159,   167,   158,   158,   158,   166,   199,   159,   593,
     143,   138,   187,   158,   130,   616,   110,   111,   112,   113,
     197,   130,   479,   114,   115,   116,   130,   232,   234,   236,
     238,   256,   140,   142,   221,   131,   132,   246,   617,   494,
     557,   130,   131,   132,   561,   239,   502,   131,   132,   281,
     130,   282,  -194,  -194,  -194,  -194,   130,   201,   203,  -194,
    -194,  -194,   131,   132,   130,  -194,  -194,  -194,  -194,  -194,
     357,   131,   132,   146,   147,   524,   535,   131,   132,   536,
     525,   312,   211,   600,   213,   131,   132,   189,   190,   314,
     471,   129,   393,   394,   471,   316,   129,   129,   130,   262,
     263,   241,   266,   341,   269,   217,   219,   110,   111,   112,
     113,   228,   348,   230,   114,   115,   116,   319,   320,   131,
     132,   242,   243,  -189,   563,   129,   603,   356,   251,   159,
     130,   159,   130,   257,   258,   259,   317,   318,   319,   320,
     401,   448,   428,   270,  -189,  -189,   138,   442,   279,   280,
     143,   131,   132,   131,   132,   443,   159,   444,   349,   144,
     350,   477,   464,   488,   129,   117,   118,   119,   120,   121,
     138,   604,   605,   129,    90,   518,   465,   333,   173,  -194,
     306,   334,   335,   336,   498,   367,   495,   337,   338,   519,
     138,   340,   499,   520,   130,   126,   521,   563,   529,   346,
     136,   137,   130,   335,   522,  -194,   117,   118,   119,   120,
     121,   316,   352,   129,   530,   131,   132,  -194,  -194,   523,
     358,   533,   534,   131,   132,   133,   129,   129,   167,   204,
     129,   566,   129,   562,   584,   129,   129,   129,  -189,   567,
     372,   588,   374,   138,   376,   377,   602,   379,   110,   111,
     112,   113,   247,   464,   598,   114,   115,   116,   601,  -189,
    -189,   117,   118,   119,   120,   121,   611,   465,   260,   612,
     167,   419,   563,   624,   313,   398,   159,   167,   613,   615,
     206,   167,   618,   -64,   167,   130,   317,   318,   319,   320,
     460,   129,   159,   129,   410,   169,   619,   620,   167,   144,
     621,  -184,   622,   415,   417,   625,   131,   132,   626,   483,
     271,   627,   475,   455,   342,  -184,   606,   315,   607,   158,
     462,   476,  -184,  -184,   469,   472,   130,   473,   575,   391,
     323,   324,   129,   129,   325,   553,   326,   608,   609,   610,
     159,   480,   544,   429,   430,     0,   122,   131,   132,   129,
     431,   432,   129,   129,   504,   159,   129,     0,   138,   129,
     481,     0,   194,   195,   196,   317,   318,   319,   320,     0,
     130,     0,   433,   426,   427,     0,     0,   440,   441,   317,
     318,   319,   320,   158,   512,   117,   118,   119,   120,   121,
       0,   131,   132,   276,     0,   362,     0,   363,     0,     0,
     167,   122,   117,   118,   119,   120,   121,   129,   129,   129,
     129,   429,   430,   501,     0,   482,     0,     0,   431,   432,
       0,   138,     0,   129,   468,   309,   311,   391,     0,   130,
     483,   474,     0,  -182,   483,     0,   496,  -171,   497,     0,
     527,   429,   430,   546,     0,     0,   486,     0,   431,   432,
     131,   132,   516,   404,  -182,  -182,   406,   407,  -171,  -171,
     408,     0,     0,   409,   272,     0,   110,   111,   112,   113,
     531,     0,     0,   114,   115,   116,   130,     0,     0,   117,
     118,   119,   120,   121,     0,   131,   132,     0,   129,     0,
       0,   117,   118,   119,   120,   121,   501,   131,   132,     0,
     129,   429,   430,     0,     0,   514,     0,   515,   431,   432,
       0,   449,   450,   451,   452,     0,   483,     0,     0,     0,
       0,   429,   430,     0,     0,   122,     0,   463,   431,   432,
     590,     0,     0,     0,   543,   148,     0,   135,   149,   222,
     139,   141,     0,     0,   150,   151,   152,   167,     0,   165,
     168,   174,   176,   181,   184,   186,   468,     0,     0,   191,
     193,     0,     0,     0,   198,   200,   202,   486,     0,   207,
     209,   486,   212,     0,   215,     0,     0,     0,     0,   224,
     226,     0,   229,     0,   231,   233,   235,   237,     0,   240,
     623,   391,   505,   244,   245,   248,   249,   250,     0,   252,
       0,     0,     0,     0,   513,     0,     0,   261,     0,   264,
     265,   267,   268,   429,   430,   273,   277,   278,     0,   122,
     431,   432,   596,   308,   310,     0,     0,     0,     0,   214,
     327,   123,   110,   111,   112,   113,     0,     0,     0,   114,
     115,   116,     0,     0,     0,   117,   118,   119,   120,   121,
       0,     0,   329,   486,   110,   111,   112,   113,   321,     0,
       0,   114,   115,   116,     0,   322,     0,   117,   118,   119,
     120,   121,   117,   118,   119,   120,   121,     0,     0,   110,
     111,   112,   113,     0,     0,   332,   114,   115,   116,     0,
       0,     0,   117,   118,   119,   120,   121,     0,   339,     0,
       0,     0,   343,   192,   344,   345,   149,     0,     0,   347,
       0,     0,   150,   151,   152,     0,     0,     0,     0,   351,
       0,   353,   354,     0,   131,   132,   355,     0,     0,   359,
       0,   361,     0,     0,     0,     0,   364,   365,     0,     0,
     366,     0,     0,   368,     0,   369,   370,     0,   371,   373,
       0,   375,     0,     0,   378,     0,     0,   380,     0,   381,
     382,     0,   383,     0,   384,     0,   385,     0,   386,     0,
     387,     0,     0,   392,     0,     0,     0,     0,   395,   396,
       0,     0,     0,   397,     0,   122,   399,   400,     0,   402,
     403,   481,   405,   110,   111,   112,   113,   123,     0,     0,
     114,   115,   116,   411,     0,     0,   412,   122,   413,     0,
       0,   414,   416,   418,     0,     0,     0,     0,   130,   123,
     110,   111,   112,   113,     0,     0,   155,   114,   115,   116,
       0,     0,   122,   117,   118,   119,   120,   121,     0,   131,
     132,   445,     0,   446,     0,     0,   482,     0,     0,     0,
       0,     0,     0,   110,   111,   112,   113,   456,   457,     0,
     114,   115,   116,     0,     0,     0,   117,   118,   119,   120,
     121,     0,     0,   526,     0,     0,     0,     0,   528,     0,
       0,     0,   532,     0,     0,     0,     0,   537,   538,   487,
     110,   111,   112,   113,   492,   493,     0,   114,   115,   116,
       0,     0,     0,   117,   118,   119,   120,   121,     0,   110,
     111,   112,   113,     0,     0,     0,   114,   115,   116,     0,
       0,   500,   117,   118,   119,   120,   121,   420,   421,   422,
     423,   424,   425,   506,     0,     0,   507,     0,   508,   509,
     510,   511,     0,     0,   130,     0,   110,   111,   112,   113,
       0,   517,   155,   114,   115,   116,     0,     0,     0,   117,
     118,   119,   120,   121,     0,   131,   132,     0,     0,     0,
     156,     0,   587,     0,     0,   589,   591,     0,   594,   595,
     597,   317,   318,   319,   320,   545,     0,   547,     0,     0,
     548,     0,   549,     0,   550,   551,     0,     0,   552,     0,
       0,     0,     0,     0,   554,   555,   122,     0,   556,     0,
     558,   559,   560,     0,     0,     0,   564,     0,   123,     0,
     565,     0,     0,   568,     0,     0,   569,   570,   571,   572,
     573,   574,     0,     0,   576,   614,   577,   578,     0,     0,
       0,     0,     0,   122,   579,   580,   581,   582,   583,     0,
       0,   317,   318,   319,   320,   123,     0,     0,     0,   156,
     110,   111,   112,   113,     0,     0,     0,   114,   115,   116,
     317,   318,   319,   320,     0,     0,   130,     0,   110,   111,
     112,   113,     0,     0,     1,   114,   115,   116,     0,     0,
       2,   117,   118,   119,   120,   121,   156,   131,   132,     3,
       0,   175,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,     0,     0,    19,
      20,    21,    22,    23,     0,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,     0,    85,    86,    87,
      88,    89,   130,     0,  -175,  -175,  -175,  -175,     0,     0,
    -175,  -175,  -175,  -175,     0,   180,   388,  -175,  -175,  -175,
    -175,  -175,     0,   131,   132,     0,   110,   111,   112,   113,
       0,     1,   470,   114,   115,   116,     0,     2,   156,    90,
       0,     0,     0,     0,     0,     0,     0,    91,    92,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,     0,     0,    19,    20,    21,    22,
      23,     0,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,     0,    85,    86,    87,    88,    89,     0,
     130,     0,   110,   111,   112,   113,     0,     0,   155,   114,
     115,   116,     0,     0,  -175,   117,   118,   119,   120,   121,
       0,   131,   132,  -171,     0,  -171,  -171,  -171,  -171,     0,
       0,  -171,  -171,  -171,  -171,     0,     0,     0,  -171,  -171,
    -171,  -171,  -171,     0,    91,    92,   459,     0,   110,   111,
     112,   113,     0,     0,   155,   114,   115,   116,     0,     0,
       0,   117,   118,   119,   120,   121,   503,     0,   110,   111,
     112,   113,     0,     0,   155,   114,   115,   116,     0,     0,
       0,   117,   118,   119,   120,   121,   461,     0,   110,   111,
     112,   113,     0,     0,     0,   114,   115,   116,     0,     0,
       0,   117,   118,   119,   120,   121,   110,   111,   112,   113,
       0,     0,   155,   114,   115,   116,     0,     0,     0,   117,
     118,   119,   120,   121,   110,   111,   112,   113,     0,     0,
       0,   114,   115,   116,     0,     0,     0,   117,   118,   119,
     120,   121,   130,     0,   130,     0,  -194,  -194,  -194,  -194,
       0,     0,   156,  -194,  -194,  -194,     0,   117,   118,   119,
     120,   121,     0,   131,   132,   131,   132,     0,     0,   110,
     111,   112,   113,     0,     0,  -171,   114,   115,   116,   110,
     111,   112,   113,     0,     0,     0,   114,   115,   116,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   156,   110,
     111,   112,   113,     0,     0,     0,   114,   115,   116,     0,
       0,     0,     0,   110,   111,   112,   113,     0,   156,     0,
     114,   115,   116,   130,     0,  -194,  -194,  -194,  -194,     0,
       0,     0,  -194,  -194,  -194,     0,     0,     0,   156,     0,
       0,     0,     0,     0,   131,   132,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   156,     0,     0,     0,
       0,     0,     0,     0,   138,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   156,     0,     0,     0,     0,     0,
       0,   283,     0,   284,   285,     0,     0,   286,     0,   287,
       0,   288,  -194,     0,     0,     0,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,     0,   436,     0,     0,   437,     0,     0,
       0,     0,     0,     0,     0,     0,   438,     0,   439,   539,
     540,     0,     0,     0,     0,     0,   431,   541,   542,     0,
       0,     0,     0,   138
};

static const yytype_int16 yycheck[] =
{
      14,    15,    16,    17,    18,   360,    20,    22,     1,    23,
      24,    18,   119,     1,    14,    15,    16,    31,    32,   151,
     127,   328,    36,    38,    24,   151,   124,   149,    42,    43,
      44,    45,    46,    47,    48,   145,   146,   147,    52,    53,
      54,    55,    56,    14,    15,    16,    17,    32,    62,   147,
       1,   121,    23,    24,     1,   124,     3,     4,     5,     6,
      31,     1,   350,    10,    11,    12,     1,    52,    53,    54,
      55,   149,     8,     9,    45,    22,    23,    62,   147,   367,
     477,     1,    22,    23,   481,    56,   393,    22,    23,   162,
       1,    21,     3,     4,     5,     6,     1,    33,    34,    10,
      11,    12,    22,    23,     1,    16,    17,    18,    19,    20,
       1,    22,    23,    11,    12,   116,   121,    22,    23,   124,
     121,     0,    39,   116,    41,    22,    23,    25,    26,    22,
     336,     1,   242,   243,   340,   156,     6,     7,     1,    75,
      76,    58,    78,    21,    80,    43,    44,     3,     4,     5,
       6,    49,    14,    51,    10,    11,    12,   166,   167,    22,
      23,    59,    60,     1,   157,    35,   563,    15,    66,   183,
       1,   185,     1,    71,    72,    73,   164,   165,   166,   167,
     149,   169,   121,    81,    22,    23,   121,   121,    86,    87,
       1,    22,    23,    22,    23,   121,   210,   121,   183,   150,
     185,    15,   149,   149,    74,    16,    17,    18,    19,    20,
     121,   566,   567,    83,   152,   116,   163,   153,   158,   154,
      90,   157,   158,   159,   153,   210,   154,   163,   164,   116,
     121,   167,   153,   116,     1,     1,   116,   157,   147,   175,
       6,     7,     1,   179,   116,   156,    16,    17,    18,    19,
      20,   156,   188,   123,   121,    22,    23,   168,   149,   116,
     196,   121,   121,    22,    23,   162,   136,   137,   282,    35,
     140,   122,   142,   154,   121,   145,   146,   147,     1,   122,
     216,   147,   218,   121,   220,   221,     1,   223,     3,     4,
       5,     6,   155,   149,   121,    10,    11,    12,   171,    22,
      23,    16,    17,    18,    19,    20,   116,   163,    74,   116,
     324,   282,   157,   121,    94,   251,   330,   331,   124,   124,
     151,   335,   124,   152,   338,     1,   164,   165,   166,   167,
     330,   201,   346,   203,   270,   342,   124,   124,   352,   150,
     124,     1,   120,   279,   280,   124,    22,    23,   124,   356,
      82,   120,   342,   324,   121,    15,   118,   123,   120,   330,
     331,   346,    22,    23,   335,   337,     1,   338,   501,   239,
     136,   137,   242,   243,   140,   466,   142,   139,   140,   141,
     394,   352,   444,   119,   120,    -1,   156,    22,    23,   259,
     126,   127,   262,   263,   394,   409,   266,    -1,   121,   269,
     115,    -1,    28,    29,    30,   164,   165,   166,   167,    -1,
       1,    -1,   148,   283,   284,    -1,    -1,   287,   288,   164,
     165,   166,   167,   394,   409,    16,    17,    18,    19,    20,
      -1,    22,    23,   109,    -1,   201,    -1,   203,    -1,    -1,
     454,   156,    16,    17,    18,    19,    20,   317,   318,   319,
     320,   119,   120,   389,    -1,   170,    -1,    -1,   126,   127,
      -1,   121,    -1,   333,   334,    91,    92,   337,    -1,     1,
     477,   341,    -1,     1,   481,    -1,   374,     1,   376,    -1,
     148,   119,   120,   454,    -1,    -1,   356,    -1,   126,   127,
      22,    23,    24,   259,    22,    23,   262,   263,    22,    23,
     266,    -1,    -1,   269,     1,    -1,     3,     4,     5,     6,
     148,    -1,    -1,    10,    11,    12,     1,    -1,    -1,    16,
      17,    18,    19,    20,    -1,    22,    23,    -1,   398,    -1,
      -1,    16,    17,    18,    19,    20,   472,    22,    23,    -1,
     410,   119,   120,    -1,    -1,   415,    -1,   417,   126,   127,
      -1,   317,   318,   319,   320,    -1,   563,    -1,    -1,    -1,
      -1,   119,   120,    -1,    -1,   156,    -1,   333,   126,   127,
     148,    -1,    -1,    -1,   444,     1,    -1,     5,     4,   153,
       8,     9,    -1,    -1,    10,    11,    12,   601,    -1,    17,
      18,    19,    20,    21,    22,    23,   466,    -1,    -1,    27,
      28,    -1,    -1,    -1,    32,    33,    34,   477,    -1,    37,
      38,   481,    40,    -1,    42,    -1,    -1,    -1,    -1,    47,
      48,    -1,    50,    -1,    52,    53,    54,    55,    -1,    57,
     601,   501,   398,    61,    62,    63,    64,    65,    -1,    67,
      -1,    -1,    -1,    -1,   410,    -1,    -1,    75,    -1,    77,
      78,    79,    80,   119,   120,    83,    84,    85,    -1,   156,
     126,   127,   128,    91,    92,    -1,    -1,    -1,    -1,   154,
       1,   168,     3,     4,     5,     6,    -1,    -1,    -1,    10,
      11,    12,    -1,    -1,    -1,    16,    17,    18,    19,    20,
      -1,    -1,     1,   563,     3,     4,     5,     6,   126,    -1,
      -1,    10,    11,    12,    -1,   133,    -1,    16,    17,    18,
      19,    20,    16,    17,    18,    19,    20,    -1,    -1,     3,
       4,     5,     6,    -1,    -1,   153,    10,    11,    12,    -1,
      -1,    -1,    16,    17,    18,    19,    20,    -1,   166,    -1,
      -1,    -1,   170,     1,   172,   173,     4,    -1,    -1,   177,
      -1,    -1,    10,    11,    12,    -1,    -1,    -1,    -1,   187,
      -1,   189,   190,    -1,    22,    23,   194,    -1,    -1,   197,
      -1,   199,    -1,    -1,    -1,    -1,   204,   205,    -1,    -1,
     208,    -1,    -1,   211,    -1,   213,   214,    -1,   216,   217,
      -1,   219,    -1,    -1,   222,    -1,    -1,   225,    -1,   227,
     228,    -1,   230,    -1,   232,    -1,   234,    -1,   236,    -1,
     238,    -1,    -1,   241,    -1,    -1,    -1,    -1,   246,   247,
      -1,    -1,    -1,   251,    -1,   156,   254,   255,    -1,   257,
     258,   115,   260,     3,     4,     5,     6,   168,    -1,    -1,
      10,    11,    12,   271,    -1,    -1,   274,   156,   276,    -1,
      -1,   279,   280,   281,    -1,    -1,    -1,    -1,     1,   168,
       3,     4,     5,     6,    -1,    -1,     9,    10,    11,    12,
      -1,    -1,   156,    16,    17,    18,    19,    20,    -1,    22,
      23,   309,    -1,   311,    -1,    -1,   170,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,   325,   326,    -1,
      10,    11,    12,    -1,    -1,    -1,    16,    17,    18,    19,
      20,    -1,    -1,   428,    -1,    -1,    -1,    -1,   433,    -1,
      -1,    -1,   437,    -1,    -1,    -1,    -1,   442,   443,   357,
       3,     4,     5,     6,   362,   363,    -1,    10,    11,    12,
      -1,    -1,    -1,    16,    17,    18,    19,    20,    -1,     3,
       4,     5,     6,    -1,    -1,    -1,    10,    11,    12,    -1,
      -1,   389,    16,    17,    18,    19,    20,   137,   138,   139,
     140,   141,   142,   401,    -1,    -1,   404,    -1,   406,   407,
     408,   409,    -1,    -1,     1,    -1,     3,     4,     5,     6,
      -1,   419,     9,    10,    11,    12,    -1,    -1,    -1,    16,
      17,    18,    19,    20,    -1,    22,    23,    -1,    -1,    -1,
     153,    -1,   527,    -1,    -1,   530,   531,    -1,   533,   534,
     535,   164,   165,   166,   167,   453,    -1,   455,    -1,    -1,
     458,    -1,   460,    -1,   462,   463,    -1,    -1,   466,    -1,
      -1,    -1,    -1,    -1,   472,   473,   156,    -1,   476,    -1,
     478,   479,   480,    -1,    -1,    -1,   484,    -1,   168,    -1,
     488,    -1,    -1,   491,    -1,    -1,   494,   495,   496,   497,
     498,   499,    -1,    -1,   502,   590,   504,   505,    -1,    -1,
      -1,    -1,    -1,   156,   512,   513,   514,   515,   516,    -1,
      -1,   164,   165,   166,   167,   168,    -1,    -1,    -1,   153,
       3,     4,     5,     6,    -1,    -1,    -1,    10,    11,    12,
     164,   165,   166,   167,    -1,    -1,     1,    -1,     3,     4,
       5,     6,    -1,    -1,     7,    10,    11,    12,    -1,    -1,
      13,    16,    17,    18,    19,    20,   153,    22,    23,    22,
      -1,   158,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    -1,    -1,    42,
      43,    44,    45,    46,    -1,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,    -1,   110,   111,   112,
     113,   114,     1,    -1,     3,     4,     5,     6,    -1,    -1,
       9,    10,    11,    12,    -1,    14,   149,    16,    17,    18,
      19,    20,    -1,    22,    23,    -1,     3,     4,     5,     6,
      -1,     7,     9,    10,    11,    12,    -1,    13,   153,   152,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   160,   161,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    -1,    -1,    42,    43,    44,    45,
      46,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,    -1,   110,   111,   112,   113,   114,    -1,
       1,    -1,     3,     4,     5,     6,    -1,    -1,     9,    10,
      11,    12,    -1,    -1,   153,    16,    17,    18,    19,    20,
      -1,    22,    23,     1,    -1,     3,     4,     5,     6,    -1,
      -1,     9,    10,    11,    12,    -1,    -1,    -1,    16,    17,
      18,    19,    20,    -1,   160,   161,     1,    -1,     3,     4,
       5,     6,    -1,    -1,     9,    10,    11,    12,    -1,    -1,
      -1,    16,    17,    18,    19,    20,     1,    -1,     3,     4,
       5,     6,    -1,    -1,     9,    10,    11,    12,    -1,    -1,
      -1,    16,    17,    18,    19,    20,     1,    -1,     3,     4,
       5,     6,    -1,    -1,    -1,    10,    11,    12,    -1,    -1,
      -1,    16,    17,    18,    19,    20,     3,     4,     5,     6,
      -1,    -1,     9,    10,    11,    12,    -1,    -1,    -1,    16,
      17,    18,    19,    20,     3,     4,     5,     6,    -1,    -1,
      -1,    10,    11,    12,    -1,    -1,    -1,    16,    17,    18,
      19,    20,     1,    -1,     1,    -1,     3,     4,     5,     6,
      -1,    -1,   153,    10,    11,    12,    -1,    16,    17,    18,
      19,    20,    -1,    22,    23,    22,    23,    -1,    -1,     3,
       4,     5,     6,    -1,    -1,   153,    10,    11,    12,     3,
       4,     5,     6,    -1,    -1,    -1,    10,    11,    12,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   153,     3,
       4,     5,     6,    -1,    -1,    -1,    10,    11,    12,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,    -1,   153,    -1,
      10,    11,    12,     1,    -1,     3,     4,     5,     6,    -1,
      -1,    -1,    10,    11,    12,    -1,    -1,    -1,   153,    -1,
      -1,    -1,    -1,    -1,    22,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   153,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   121,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   153,    -1,    -1,    -1,    -1,    -1,
      -1,   115,    -1,   117,   118,    -1,    -1,   121,    -1,   123,
      -1,   125,   149,    -1,    -1,    -1,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,    -1,   118,    -1,    -1,   121,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   130,    -1,   132,   119,
     120,    -1,    -1,    -1,    -1,    -1,   126,   127,   128,    -1,
      -1,    -1,    -1,   121
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,    13,    22,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    42,
      43,    44,    45,    46,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   110,   111,   112,   113,   114,
     152,   160,   161,   173,   174,   176,   177,   178,   179,   180,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   222,
       3,     4,     5,     6,    10,    11,    12,    16,    17,    18,
      19,    20,   156,   168,   197,   206,   209,   217,   219,   220,
       1,    22,    23,   162,   175,   175,   209,   209,   121,   175,
     205,   175,   205,     1,   150,   193,   193,   193,     1,     4,
      10,    11,    12,   200,   218,     9,   153,   202,   204,   206,
     207,   208,   220,   202,   202,   175,   204,   206,   175,   197,
     198,   199,   206,   158,   175,   158,   175,   201,   202,   204,
      14,   175,   195,   196,   175,   196,   175,   204,   202,   193,
     193,   175,     1,   175,   200,   200,   200,   204,   175,   201,
     175,   205,   175,   205,   209,   206,   151,   175,   191,   175,
     196,   191,   175,   191,   154,   175,   206,   193,   206,   193,
     206,   204,   153,   206,   175,   206,   175,   206,   193,   175,
     193,   175,   201,   175,   201,   175,   201,   175,   201,   204,
     175,   191,   193,   193,   175,   175,   201,   155,   175,   175,
     175,   193,   175,   151,   192,   149,   149,   193,   193,   193,
     209,   175,   205,   205,   175,   175,   205,   175,   175,   205,
     193,   192,     1,   175,   194,   209,   109,   175,   175,   193,
     193,   162,    21,   115,   117,   118,   121,   123,   125,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   220,   224,   175,   200,
     175,   200,     0,   176,    22,   209,   156,   164,   165,   166,
     167,   175,   175,   209,   209,   209,   209,     1,   194,     1,
     194,   194,   175,   205,   205,   205,   205,   205,   205,   175,
     205,    21,   121,   175,   175,   175,   205,   175,    14,   201,
     201,   175,   205,   175,   175,   175,    15,     1,   205,   175,
     181,   175,   209,   209,   175,   175,   175,   201,   175,   175,
     175,   175,   205,   175,   205,   175,   205,   205,   175,   205,
     175,   175,   175,   175,   175,   175,   175,   175,   149,   213,
     214,   220,   175,   194,   194,   175,   175,   175,   205,   175,
     175,   149,   175,   175,   209,   175,   209,   209,   209,   209,
     205,   175,   175,   175,   175,   205,   175,   205,   175,   204,
     137,   138,   139,   140,   141,   142,   220,   220,   121,   119,
     120,   126,   127,   148,   225,   226,   118,   121,   130,   132,
     220,   220,   121,   121,   121,   175,   175,     1,   169,   209,
     209,   209,   209,   203,   205,   204,   175,   175,   203,     1,
     202,     1,   204,   209,   149,   163,   215,   216,   220,   204,
       9,   207,   213,   204,   220,   199,   201,    15,   210,   210,
     204,   115,   170,   197,   211,   212,   220,   175,   149,   221,
     222,   223,   175,   175,   210,   154,   193,   193,   153,   153,
     175,   205,   203,     1,   202,   209,   175,   175,   175,   175,
     175,   175,   201,   209,   220,   220,    24,   175,   116,   116,
     116,   116,   116,   116,   116,   121,   225,   148,   225,   147,
     121,   148,   225,   121,   121,   121,   124,   225,   225,   119,
     120,   127,   128,   220,   226,   175,   204,   175,   175,   175,
     175,   175,   175,   216,   175,   175,   175,   211,   175,   175,
     175,   211,   154,   157,   175,   175,   122,   122,   175,   175,
     175,   175,   175,   175,   175,   214,   175,   175,   175,   175,
     175,   175,   175,   175,   121,   119,   127,   225,   147,   225,
     148,   225,   124,   147,   225,   225,   128,   225,   121,     1,
     116,   171,     1,   211,   222,   222,   118,   120,   139,   140,
     141,   116,   116,   124,   225,   124,   124,   147,   124,   124,
     124,   124,   120,   204,   121,   124,   124,   120
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   172,   173,   173,   173,   174,   174,   175,   175,   175,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   178,   178,
     178,   179,   179,   179,   179,   179,   179,   179,   179,   179,
     179,   179,   179,   179,   181,   180,   180,   180,   180,   182,
     182,   182,   182,   182,   182,   182,   182,   182,   182,   182,
     182,   182,   182,   182,   182,   182,   182,   182,   182,   183,
     183,   183,   183,   183,   183,   183,   183,   184,   184,   184,
     184,   184,   184,   184,   184,   184,   184,   184,   185,   185,
     185,   185,   185,   185,   185,   185,   185,   186,   186,   186,
     186,   186,   186,   186,   186,   186,   186,   186,   186,   186,
     186,   186,   186,   186,   186,   186,   186,   186,   186,   186,
     187,   187,   187,   187,   187,   187,   187,   187,   187,   187,
     187,   187,   187,   187,   187,   187,   187,   187,   187,   188,
     188,   188,   189,   189,   190,   191,   192,   192,   193,   193,
     194,   194,   195,   195,   196,   196,   197,   197,   198,   198,
     199,   200,   200,   201,   201,   202,   202,   202,   203,   203,
     204,   204,   204,   205,   205,   206,   206,   206,   206,   206,
     207,   208,   209,   209,   209,   209,   209,   209,   209,   210,
     210,   211,   211,   211,   211,   211,   212,   212,   212,   213,
     213,   214,   214,   215,   215,   216,   216,   216,   217,   217,
     218,   218,   218,   218,   219,   219,   219,   220,   220,   220,
     220,   220,   221,   221,   221,   222,   223,   223,   224,   224,
     224,   224,   224,   224,   224,   224,   224,   224,   224,   224,
     224,   224,   224,   224,   224,   224,   224,   224,   224,   224,
     224,   224,   224,   224,   224,   224,   224,   224,   224,   224,
     224,   224,   224,   224,   224,   224,   224,   224,   224,   224,
     224,   224,   224,   224,   224,   224,   224,   224,   224,   224,
     224,   224,   224,   224,   224,   224,   224,   224,   224,   224,
     225,   225,   225,   225,   226
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     3,     3,     5,     3,     2,     2,
       3,     2,     3,     2,     4,     2,     3,     3,     2,     4,
       2,     4,     2,     4,     2,     4,     2,     1,     2,     3,
       3,     5,     3,     5,     3,     5,     3,     5,     3,     2,
       3,     2,     4,     5,     0,     5,     3,     3,     2,     5,
       5,     5,     5,     5,     3,     2,     3,     2,     3,     2,
       3,     2,     3,     2,     2,     2,     4,     5,     5,     5,
       2,     3,     2,     5,     2,     5,     2,     3,     2,     3,
       2,     3,     5,     3,     2,     5,     5,     4,     3,     2,
       3,     2,     3,     2,     2,     2,     3,     3,     3,     2,
       3,     3,     3,     3,     2,     3,     2,     3,     5,     3,
       4,     3,     3,     2,     4,     4,     2,     3,     3,     2,
       5,     5,     5,     3,     4,     5,     4,     5,     4,     5,
       5,     2,     3,     4,     3,     3,     5,     3,     5,     3,
       2,     3,     4,     2,     2,     1,     1,     0,     1,     1,
       1,     1,     2,     1,     1,     0,     1,     2,     3,     1,
       3,     1,     1,     1,     1,     3,     1,     3,     2,     0,
       1,     3,     1,     1,     0,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     1,     2,
       0,     3,     3,     3,     3,     1,     1,     1,     4,     3,
       1,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     2,     2,     1,     1,     2,     1,
       3,     3,     3,     3,     3,     5,     7,     5,     3,     3,
       3,     3,     3,     3,     5,     5,     5,     5,     0,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     3,     3,
       4,     3,     4,     2,     3,     3,     3,     3,     5,     5,
       6,     5,     6,     4,     5,     5,     5,     5,     3,     5,
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
  YYUSE (yytype);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long yylno = yyrline[yyrule];
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

  if (! yyres)
    return yystrlen (yystr);

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
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
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

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

    YYSIZE_T yystacksize;

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
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
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
# else /* defined YYSTACK_RELOCATE */
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
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
#line 198 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = 0; }
#line 2371 "y.tab.c" /* yacc.c:1652  */
    break;

  case 3:
#line 199 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = 0; }
#line 2377 "y.tab.c" /* yacc.c:1652  */
    break;

  case 4:
#line 200 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { new_cmd = 1; asm_mode = 0;  (yyval.i) = 0; }
#line 2383 "y.tab.c" /* yacc.c:1652  */
    break;

  case 9:
#line 209 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { return ERR_EXPECT_END_CMD; }
#line 2389 "y.tab.c" /* yacc.c:1652  */
    break;

  case 22:
#line 224 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { return ERR_BAD_CMD; }
#line 2395 "y.tab.c" /* yacc.c:1652  */
    break;

  case 23:
#line 228 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_bank(e_default_space, NULL); }
#line 2401 "y.tab.c" /* yacc.c:1652  */
    break;

  case 24:
#line 230 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_bank((yyvsp[-1].i), NULL); }
#line 2407 "y.tab.c" /* yacc.c:1652  */
    break;

  case 25:
#line 232 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_bank(e_default_space, (yyvsp[-1].str)); }
#line 2413 "y.tab.c" /* yacc.c:1652  */
    break;

  case 26:
#line 234 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_bank((yyvsp[-3].i), (yyvsp[-1].str)); }
#line 2419 "y.tab.c" /* yacc.c:1652  */
    break;

  case 27:
#line 236 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_jump((yyvsp[-1].a)); }
#line 2425 "y.tab.c" /* yacc.c:1652  */
    break;

  case 28:
#line 238 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_go(); }
#line 2431 "y.tab.c" /* yacc.c:1652  */
    break;

  case 29:
#line 240 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_display_io_regs(0); }
#line 2437 "y.tab.c" /* yacc.c:1652  */
    break;

  case 30:
#line 242 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_display_io_regs((yyvsp[-1].a)); }
#line 2443 "y.tab.c" /* yacc.c:1652  */
    break;

  case 31:
#line 244 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { monitor_cpu_type_set(""); }
#line 2449 "y.tab.c" /* yacc.c:1652  */
    break;

  case 32:
#line 246 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { monitor_cpu_type_set((yyvsp[-1].str)); }
#line 2455 "y.tab.c" /* yacc.c:1652  */
    break;

  case 33:
#line 248 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_cpuhistory(-1); }
#line 2461 "y.tab.c" /* yacc.c:1652  */
    break;

  case 34:
#line 250 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_cpuhistory((yyvsp[-1].i)); }
#line 2467 "y.tab.c" /* yacc.c:1652  */
    break;

  case 35:
#line 252 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_instruction_return(); }
#line 2473 "y.tab.c" /* yacc.c:1652  */
    break;

  case 36:
#line 254 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { machine_write_snapshot((yyvsp[-1].str),0,0,0); /* FIXME */ }
#line 2479 "y.tab.c" /* yacc.c:1652  */
    break;

  case 37:
#line 256 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { machine_read_snapshot((yyvsp[-1].str), 0); }
#line 2485 "y.tab.c" /* yacc.c:1652  */
    break;

  case 38:
#line 258 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_instructions_step(-1); }
#line 2491 "y.tab.c" /* yacc.c:1652  */
    break;

  case 39:
#line 260 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_instructions_step((yyvsp[-1].i)); }
#line 2497 "y.tab.c" /* yacc.c:1652  */
    break;

  case 40:
#line 262 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_instructions_next(-1); }
#line 2503 "y.tab.c" /* yacc.c:1652  */
    break;

  case 41:
#line 264 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_instructions_next((yyvsp[-1].i)); }
#line 2509 "y.tab.c" /* yacc.c:1652  */
    break;

  case 42:
#line 266 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_stack_up(-1); }
#line 2515 "y.tab.c" /* yacc.c:1652  */
    break;

  case 43:
#line 268 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_stack_up((yyvsp[-1].i)); }
#line 2521 "y.tab.c" /* yacc.c:1652  */
    break;

  case 44:
#line 270 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_stack_down(-1); }
#line 2527 "y.tab.c" /* yacc.c:1652  */
    break;

  case 45:
#line 272 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_stack_down((yyvsp[-1].i)); }
#line 2533 "y.tab.c" /* yacc.c:1652  */
    break;

  case 46:
#line 274 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_display_screen(); }
#line 2539 "y.tab.c" /* yacc.c:1652  */
    break;

  case 48:
#line 279 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (monitor_cpu_for_memspace[default_memspace]->mon_register_print)(default_memspace); }
#line 2545 "y.tab.c" /* yacc.c:1652  */
    break;

  case 49:
#line 281 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (monitor_cpu_for_memspace[(yyvsp[-1].i)]->mon_register_print)((yyvsp[-1].i)); }
#line 2551 "y.tab.c" /* yacc.c:1652  */
    break;

  case 51:
#line 286 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
                        /* What about the memspace? */
                        mon_playback_init((yyvsp[-1].str));
                    }
#line 2560 "y.tab.c" /* yacc.c:1652  */
    break;

  case 52:
#line 291 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
                        /* What about the memspace? */
                        mon_playback_init((yyvsp[-1].str));
                    }
#line 2569 "y.tab.c" /* yacc.c:1652  */
    break;

  case 53:
#line 296 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_save_symbols((yyvsp[-3].i), (yyvsp[-1].str)); }
#line 2575 "y.tab.c" /* yacc.c:1652  */
    break;

  case 54:
#line 298 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_save_symbols(e_default_space, (yyvsp[-1].str)); }
#line 2581 "y.tab.c" /* yacc.c:1652  */
    break;

  case 55:
#line 300 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_add_name_to_symbol_table((yyvsp[-3].a), (yyvsp[-1].str)); }
#line 2587 "y.tab.c" /* yacc.c:1652  */
    break;

  case 56:
#line 302 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_remove_name_from_symbol_table(e_default_space, (yyvsp[-1].str)); }
#line 2593 "y.tab.c" /* yacc.c:1652  */
    break;

  case 57:
#line 304 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_remove_name_from_symbol_table((yyvsp[-3].i), (yyvsp[-1].str)); }
#line 2599 "y.tab.c" /* yacc.c:1652  */
    break;

  case 58:
#line 306 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_print_symbol_table((yyvsp[-1].i)); }
#line 2605 "y.tab.c" /* yacc.c:1652  */
    break;

  case 59:
#line 308 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_print_symbol_table(e_default_space); }
#line 2611 "y.tab.c" /* yacc.c:1652  */
    break;

  case 60:
#line 310 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_clear_symbol_table((yyvsp[-1].i)); }
#line 2617 "y.tab.c" /* yacc.c:1652  */
    break;

  case 61:
#line 312 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_clear_symbol_table(e_default_space); }
#line 2623 "y.tab.c" /* yacc.c:1652  */
    break;

  case 62:
#line 314 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
                        mon_add_name_to_symbol_table((yyvsp[-1].a), mon_prepend_dot_to_name((yyvsp[-3].str)));
                    }
#line 2631 "y.tab.c" /* yacc.c:1652  */
    break;

  case 63:
#line 318 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
                        mon_add_name_to_symbol_table((yyvsp[-2].a), mon_prepend_dot_to_name((yyvsp[-4].str)));
                    }
#line 2639 "y.tab.c" /* yacc.c:1652  */
    break;

  case 64:
#line 324 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_start_assemble_mode((yyvsp[0].a), NULL); }
#line 2645 "y.tab.c" /* yacc.c:1652  */
    break;

  case 65:
#line 325 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { }
#line 2651 "y.tab.c" /* yacc.c:1652  */
    break;

  case 66:
#line 327 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_start_assemble_mode((yyvsp[-1].a), NULL); }
#line 2657 "y.tab.c" /* yacc.c:1652  */
    break;

  case 67:
#line 329 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_disassemble_lines((yyvsp[-1].range)[0], (yyvsp[-1].range)[1]); }
#line 2663 "y.tab.c" /* yacc.c:1652  */
    break;

  case 68:
#line 331 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_disassemble_lines(BAD_ADDR, BAD_ADDR); }
#line 2669 "y.tab.c" /* yacc.c:1652  */
    break;

  case 69:
#line 335 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_memory_move((yyvsp[-3].range)[0], (yyvsp[-3].range)[1], (yyvsp[-1].a)); }
#line 2675 "y.tab.c" /* yacc.c:1652  */
    break;

  case 70:
#line 337 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_memory_compare((yyvsp[-3].range)[0], (yyvsp[-3].range)[1], (yyvsp[-1].a)); }
#line 2681 "y.tab.c" /* yacc.c:1652  */
    break;

  case 71:
#line 339 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_memory_fill((yyvsp[-3].range)[0], (yyvsp[-3].range)[1],(unsigned char *)(yyvsp[-1].str)); }
#line 2687 "y.tab.c" /* yacc.c:1652  */
    break;

  case 72:
#line 341 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_memory_hunt((yyvsp[-3].range)[0], (yyvsp[-3].range)[1],(unsigned char *)(yyvsp[-1].str)); }
#line 2693 "y.tab.c" /* yacc.c:1652  */
    break;

  case 73:
#line 343 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_memory_display((yyvsp[-3].rt), (yyvsp[-1].range)[0], (yyvsp[-1].range)[1], DF_PETSCII); }
#line 2699 "y.tab.c" /* yacc.c:1652  */
    break;

  case 74:
#line 345 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_memory_display(default_radix, (yyvsp[-1].range)[0], (yyvsp[-1].range)[1], DF_PETSCII); }
#line 2705 "y.tab.c" /* yacc.c:1652  */
    break;

  case 75:
#line 347 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_memory_display(default_radix, BAD_ADDR, BAD_ADDR, DF_PETSCII); }
#line 2711 "y.tab.c" /* yacc.c:1652  */
    break;

  case 76:
#line 349 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_memory_display_data((yyvsp[-1].range)[0], (yyvsp[-1].range)[1], 8, 8); }
#line 2717 "y.tab.c" /* yacc.c:1652  */
    break;

  case 77:
#line 351 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_memory_display_data(BAD_ADDR, BAD_ADDR, 8, 8); }
#line 2723 "y.tab.c" /* yacc.c:1652  */
    break;

  case 78:
#line 353 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_memory_display_data((yyvsp[-1].range)[0], (yyvsp[-1].range)[1], 24, 21); }
#line 2729 "y.tab.c" /* yacc.c:1652  */
    break;

  case 79:
#line 355 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_memory_display_data(BAD_ADDR, BAD_ADDR, 24, 21); }
#line 2735 "y.tab.c" /* yacc.c:1652  */
    break;

  case 80:
#line 357 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_memory_display(0, (yyvsp[-1].range)[0], (yyvsp[-1].range)[1], DF_PETSCII); }
#line 2741 "y.tab.c" /* yacc.c:1652  */
    break;

  case 81:
#line 359 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_memory_display(0, BAD_ADDR, BAD_ADDR, DF_PETSCII); }
#line 2747 "y.tab.c" /* yacc.c:1652  */
    break;

  case 82:
#line 361 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_memory_display(0, (yyvsp[-1].range)[0], (yyvsp[-1].range)[1], DF_SCREEN_CODE); }
#line 2753 "y.tab.c" /* yacc.c:1652  */
    break;

  case 83:
#line 363 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_memory_display(0, BAD_ADDR, BAD_ADDR, DF_SCREEN_CODE); }
#line 2759 "y.tab.c" /* yacc.c:1652  */
    break;

  case 84:
#line 365 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_memmap_zap(); }
#line 2765 "y.tab.c" /* yacc.c:1652  */
    break;

  case 85:
#line 367 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_memmap_show(-1,BAD_ADDR,BAD_ADDR); }
#line 2771 "y.tab.c" /* yacc.c:1652  */
    break;

  case 86:
#line 369 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_memmap_show((yyvsp[-1].i),BAD_ADDR,BAD_ADDR); }
#line 2777 "y.tab.c" /* yacc.c:1652  */
    break;

  case 87:
#line 371 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_memmap_show((yyvsp[-2].i),(yyvsp[-1].range)[0],(yyvsp[-1].range)[1]); }
#line 2783 "y.tab.c" /* yacc.c:1652  */
    break;

  case 88:
#line 373 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_memmap_save((yyvsp[-3].str),(yyvsp[-1].i)); }
#line 2789 "y.tab.c" /* yacc.c:1652  */
    break;

  case 89:
#line 377 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
                      if ((yyvsp[-3].i)) {
                          temp = mon_breakpoint_add_checkpoint((yyvsp[-2].range)[0], (yyvsp[-2].range)[1], TRUE, (yyvsp[-3].i), FALSE);
                      } else {
                          temp = mon_breakpoint_add_checkpoint((yyvsp[-2].range)[0], (yyvsp[-2].range)[1], TRUE, e_exec, FALSE);
                      }
                      mon_breakpoint_set_checkpoint_condition(temp, (yyvsp[-1].cond_node));
                  }
#line 2802 "y.tab.c" /* yacc.c:1652  */
    break;

  case 90:
#line 386 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_breakpoint_print_checkpoints(); }
#line 2808 "y.tab.c" /* yacc.c:1652  */
    break;

  case 91:
#line 389 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
                      mon_breakpoint_add_checkpoint((yyvsp[-1].range)[0], (yyvsp[-1].range)[1], TRUE, e_exec, TRUE);
                  }
#line 2816 "y.tab.c" /* yacc.c:1652  */
    break;

  case 92:
#line 393 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_breakpoint_print_checkpoints(); }
#line 2822 "y.tab.c" /* yacc.c:1652  */
    break;

  case 93:
#line 396 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
                      if ((yyvsp[-3].i)) {
                          temp = mon_breakpoint_add_checkpoint((yyvsp[-2].range)[0], (yyvsp[-2].range)[1], TRUE, (yyvsp[-3].i), FALSE);
                      } else {
                          temp = mon_breakpoint_add_checkpoint((yyvsp[-2].range)[0], (yyvsp[-2].range)[1], TRUE, e_load | e_store, FALSE);
                      }
                      mon_breakpoint_set_checkpoint_condition(temp, (yyvsp[-1].cond_node));
                  }
#line 2835 "y.tab.c" /* yacc.c:1652  */
    break;

  case 94:
#line 405 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_breakpoint_print_checkpoints(); }
#line 2841 "y.tab.c" /* yacc.c:1652  */
    break;

  case 95:
#line 408 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
                      if ((yyvsp[-3].i)) {
                          temp = mon_breakpoint_add_checkpoint((yyvsp[-2].range)[0], (yyvsp[-2].range)[1], FALSE, (yyvsp[-3].i), FALSE);
                      } else {
                          temp = mon_breakpoint_add_checkpoint((yyvsp[-2].range)[0], (yyvsp[-2].range)[1], FALSE, e_load | e_store, FALSE);
                      }
                      mon_breakpoint_set_checkpoint_condition(temp, (yyvsp[-1].cond_node));
                  }
#line 2854 "y.tab.c" /* yacc.c:1652  */
    break;

  case 96:
#line 417 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_breakpoint_print_checkpoints(); }
#line 2860 "y.tab.c" /* yacc.c:1652  */
    break;

  case 97:
#line 422 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_breakpoint_switch_checkpoint(e_ON, (yyvsp[-1].i)); }
#line 2866 "y.tab.c" /* yacc.c:1652  */
    break;

  case 98:
#line 424 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_breakpoint_switch_checkpoint(e_ON, -1); }
#line 2872 "y.tab.c" /* yacc.c:1652  */
    break;

  case 99:
#line 426 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_breakpoint_switch_checkpoint(e_OFF, (yyvsp[-1].i)); }
#line 2878 "y.tab.c" /* yacc.c:1652  */
    break;

  case 100:
#line 428 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_breakpoint_switch_checkpoint(e_OFF, -1); }
#line 2884 "y.tab.c" /* yacc.c:1652  */
    break;

  case 101:
#line 430 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_breakpoint_set_ignore_count((yyvsp[-1].i), -1); }
#line 2890 "y.tab.c" /* yacc.c:1652  */
    break;

  case 102:
#line 432 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_breakpoint_set_ignore_count((yyvsp[-3].i), (yyvsp[-1].i)); }
#line 2896 "y.tab.c" /* yacc.c:1652  */
    break;

  case 103:
#line 434 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_breakpoint_delete_checkpoint((yyvsp[-1].i)); }
#line 2902 "y.tab.c" /* yacc.c:1652  */
    break;

  case 104:
#line 436 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_breakpoint_delete_checkpoint(-1); }
#line 2908 "y.tab.c" /* yacc.c:1652  */
    break;

  case 105:
#line 438 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_breakpoint_set_checkpoint_condition((yyvsp[-3].i), (yyvsp[-1].cond_node)); }
#line 2914 "y.tab.c" /* yacc.c:1652  */
    break;

  case 106:
#line 440 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_breakpoint_set_checkpoint_command((yyvsp[-3].i), (yyvsp[-1].str)); }
#line 2920 "y.tab.c" /* yacc.c:1652  */
    break;

  case 107:
#line 442 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { return ERR_EXPECT_STRING; }
#line 2926 "y.tab.c" /* yacc.c:1652  */
    break;

  case 108:
#line 446 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { sidefx = (((yyvsp[-1].action) == e_TOGGLE) ? (sidefx ^ 1) : (yyvsp[-1].action)); }
#line 2932 "y.tab.c" /* yacc.c:1652  */
    break;

  case 109:
#line 448 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
                         mon_out("I/O side effects are %s\n",
                                   sidefx ? "enabled" : "disabled");
                     }
#line 2941 "y.tab.c" /* yacc.c:1652  */
    break;

  case 110:
#line 453 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { default_radix = (yyvsp[-1].rt); }
#line 2947 "y.tab.c" /* yacc.c:1652  */
    break;

  case 111:
#line 455 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
                         const char *p;

                         if (default_radix == e_hexadecimal)
                             p = "Hexadecimal";
                         else if (default_radix == e_decimal)
                             p = "Decimal";
                         else if (default_radix == e_octal)
                             p = "Octal";
                         else if (default_radix == e_binary)
                             p = "Binary";
                         else
                             p = "Unknown";

                         mon_out("Default radix is %s\n", p);
                     }
#line 2968 "y.tab.c" /* yacc.c:1652  */
    break;

  case 112:
#line 473 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { monitor_change_device((yyvsp[-1].i)); }
#line 2974 "y.tab.c" /* yacc.c:1652  */
    break;

  case 113:
#line 475 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_export(); }
#line 2980 "y.tab.c" /* yacc.c:1652  */
    break;

  case 114:
#line 477 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_quit(); YYACCEPT; }
#line 2986 "y.tab.c" /* yacc.c:1652  */
    break;

  case 115:
#line 479 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_exit(); YYACCEPT; }
#line 2992 "y.tab.c" /* yacc.c:1652  */
    break;

  case 116:
#line 481 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_maincpu_toggle_trace((yyvsp[-1].action)); }
#line 2998 "y.tab.c" /* yacc.c:1652  */
    break;

  case 117:
#line 485 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_drive_execute_disk_cmd((yyvsp[-1].str)); }
#line 3004 "y.tab.c" /* yacc.c:1652  */
    break;

  case 118:
#line 487 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_out("\t%d\n",(yyvsp[-1].i)); }
#line 3010 "y.tab.c" /* yacc.c:1652  */
    break;

  case 119:
#line 489 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_command_print_help(NULL); }
#line 3016 "y.tab.c" /* yacc.c:1652  */
    break;

  case 120:
#line 491 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_command_print_help((yyvsp[-1].str)); }
#line 3022 "y.tab.c" /* yacc.c:1652  */
    break;

  case 121:
#line 493 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_print_convert((yyvsp[-1].i)); }
#line 3028 "y.tab.c" /* yacc.c:1652  */
    break;

  case 122:
#line 495 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_change_dir((yyvsp[-1].str)); }
#line 3034 "y.tab.c" /* yacc.c:1652  */
    break;

  case 123:
#line 497 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_keyboard_feed((yyvsp[-1].str)); }
#line 3040 "y.tab.c" /* yacc.c:1652  */
    break;

  case 124:
#line 499 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_backtrace(); }
#line 3046 "y.tab.c" /* yacc.c:1652  */
    break;

  case 125:
#line 501 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_show_dir((yyvsp[-1].str)); }
#line 3052 "y.tab.c" /* yacc.c:1652  */
    break;

  case 126:
#line 503 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_show_pwd(); }
#line 3058 "y.tab.c" /* yacc.c:1652  */
    break;

  case 127:
#line 505 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_screenshot_save((yyvsp[-1].str),-1); }
#line 3064 "y.tab.c" /* yacc.c:1652  */
    break;

  case 128:
#line 507 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_screenshot_save((yyvsp[-3].str),(yyvsp[-1].i)); }
#line 3070 "y.tab.c" /* yacc.c:1652  */
    break;

  case 129:
#line 509 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_resource_get((yyvsp[-1].str)); }
#line 3076 "y.tab.c" /* yacc.c:1652  */
    break;

  case 130:
#line 511 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_resource_set((yyvsp[-2].str),(yyvsp[-1].str)); }
#line 3082 "y.tab.c" /* yacc.c:1652  */
    break;

  case 131:
#line 513 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { resources_load((yyvsp[-1].str)); }
#line 3088 "y.tab.c" /* yacc.c:1652  */
    break;

  case 132:
#line 515 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { resources_save((yyvsp[-1].str)); }
#line 3094 "y.tab.c" /* yacc.c:1652  */
    break;

  case 133:
#line 517 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_reset_machine(-1); }
#line 3100 "y.tab.c" /* yacc.c:1652  */
    break;

  case 134:
#line 519 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_reset_machine((yyvsp[-1].i)); }
#line 3106 "y.tab.c" /* yacc.c:1652  */
    break;

  case 135:
#line 521 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_tape_ctrl((yyvsp[-1].i)); }
#line 3112 "y.tab.c" /* yacc.c:1652  */
    break;

  case 136:
#line 523 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_cart_freeze(); }
#line 3118 "y.tab.c" /* yacc.c:1652  */
    break;

  case 137:
#line 525 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { }
#line 3124 "y.tab.c" /* yacc.c:1652  */
    break;

  case 138:
#line 527 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_stopwatch_reset(); }
#line 3130 "y.tab.c" /* yacc.c:1652  */
    break;

  case 139:
#line 529 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_stopwatch_show("Stopwatch: ", "\n"); }
#line 3136 "y.tab.c" /* yacc.c:1652  */
    break;

  case 140:
#line 533 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_file_load((yyvsp[-3].str), (yyvsp[-2].i), (yyvsp[-1].a), FALSE); }
#line 3142 "y.tab.c" /* yacc.c:1652  */
    break;

  case 141:
#line 535 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_file_load((yyvsp[-3].str), (yyvsp[-2].i), (yyvsp[-1].a), TRUE); }
#line 3148 "y.tab.c" /* yacc.c:1652  */
    break;

  case 142:
#line 537 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_file_save((yyvsp[-3].str), (yyvsp[-2].i), (yyvsp[-1].range)[0], (yyvsp[-1].range)[1], FALSE); }
#line 3154 "y.tab.c" /* yacc.c:1652  */
    break;

  case 143:
#line 539 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { return ERR_EXPECT_DEVICE_NUM; }
#line 3160 "y.tab.c" /* yacc.c:1652  */
    break;

  case 144:
#line 541 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { return ERR_EXPECT_ADDRESS; }
#line 3166 "y.tab.c" /* yacc.c:1652  */
    break;

  case 145:
#line 543 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_file_save((yyvsp[-3].str), (yyvsp[-2].i), (yyvsp[-1].range)[0], (yyvsp[-1].range)[1], TRUE); }
#line 3172 "y.tab.c" /* yacc.c:1652  */
    break;

  case 146:
#line 545 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { return ERR_EXPECT_ADDRESS; }
#line 3178 "y.tab.c" /* yacc.c:1652  */
    break;

  case 147:
#line 547 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_file_verify((yyvsp[-3].str),(yyvsp[-2].i),(yyvsp[-1].a)); }
#line 3184 "y.tab.c" /* yacc.c:1652  */
    break;

  case 148:
#line 549 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { return ERR_EXPECT_ADDRESS; }
#line 3190 "y.tab.c" /* yacc.c:1652  */
    break;

  case 149:
#line 551 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_drive_block_cmd(0,(yyvsp[-3].i),(yyvsp[-2].i),(yyvsp[-1].a)); }
#line 3196 "y.tab.c" /* yacc.c:1652  */
    break;

  case 150:
#line 553 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_drive_block_cmd(1,(yyvsp[-3].i),(yyvsp[-2].i),(yyvsp[-1].a)); }
#line 3202 "y.tab.c" /* yacc.c:1652  */
    break;

  case 151:
#line 555 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_drive_list(-1); }
#line 3208 "y.tab.c" /* yacc.c:1652  */
    break;

  case 152:
#line 557 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_drive_list((yyvsp[-1].i)); }
#line 3214 "y.tab.c" /* yacc.c:1652  */
    break;

  case 153:
#line 559 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_attach((yyvsp[-2].str),(yyvsp[-1].i)); }
#line 3220 "y.tab.c" /* yacc.c:1652  */
    break;

  case 154:
#line 561 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_detach((yyvsp[-1].i)); }
#line 3226 "y.tab.c" /* yacc.c:1652  */
    break;

  case 155:
#line 563 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_autostart((yyvsp[-1].str),0,1); }
#line 3232 "y.tab.c" /* yacc.c:1652  */
    break;

  case 156:
#line 565 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_autostart((yyvsp[-3].str),(yyvsp[-1].i),1); }
#line 3238 "y.tab.c" /* yacc.c:1652  */
    break;

  case 157:
#line 567 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_autostart((yyvsp[-1].str),0,0); }
#line 3244 "y.tab.c" /* yacc.c:1652  */
    break;

  case 158:
#line 569 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_autostart((yyvsp[-3].str),(yyvsp[-1].i),0); }
#line 3250 "y.tab.c" /* yacc.c:1652  */
    break;

  case 159:
#line 573 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_record_commands((yyvsp[-1].str)); }
#line 3256 "y.tab.c" /* yacc.c:1652  */
    break;

  case 160:
#line 575 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_end_recording(); }
#line 3262 "y.tab.c" /* yacc.c:1652  */
    break;

  case 161:
#line 577 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_playback_init((yyvsp[-1].str)); }
#line 3268 "y.tab.c" /* yacc.c:1652  */
    break;

  case 162:
#line 581 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_memory_fill((yyvsp[-2].a), BAD_ADDR, (unsigned char *)(yyvsp[-1].str)); }
#line 3274 "y.tab.c" /* yacc.c:1652  */
    break;

  case 163:
#line 583 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { printf("Not yet.\n"); }
#line 3280 "y.tab.c" /* yacc.c:1652  */
    break;

  case 164:
#line 587 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { yydebug = 1; }
#line 3286 "y.tab.c" /* yacc.c:1652  */
    break;

  case 165:
#line 590 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.str) = (yyvsp[0].str); }
#line 3292 "y.tab.c" /* yacc.c:1652  */
    break;

  case 166:
#line 593 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.str) = (yyvsp[0].str); }
#line 3298 "y.tab.c" /* yacc.c:1652  */
    break;

  case 167:
#line 594 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.str) = NULL; }
#line 3304 "y.tab.c" /* yacc.c:1652  */
    break;

  case 169:
#line 598 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { return ERR_EXPECT_FILENAME; }
#line 3310 "y.tab.c" /* yacc.c:1652  */
    break;

  case 171:
#line 602 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { return ERR_EXPECT_DEVICE_NUM; }
#line 3316 "y.tab.c" /* yacc.c:1652  */
    break;

  case 172:
#line 605 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[-1].i) | (yyvsp[0].i); }
#line 3322 "y.tab.c" /* yacc.c:1652  */
    break;

  case 173:
#line 606 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[0].i); }
#line 3328 "y.tab.c" /* yacc.c:1652  */
    break;

  case 174:
#line 609 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[0].i); }
#line 3334 "y.tab.c" /* yacc.c:1652  */
    break;

  case 175:
#line 610 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = 0; }
#line 3340 "y.tab.c" /* yacc.c:1652  */
    break;

  case 176:
#line 613 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
                                    if (!mon_register_valid(default_memspace, (yyvsp[0].reg))) {
                                        return ERR_INVALID_REGISTER;
                                    }
                                    (yyval.i) = new_reg(default_memspace, (yyvsp[0].reg));
                                }
#line 3351 "y.tab.c" /* yacc.c:1652  */
    break;

  case 177:
#line 619 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
                                    if (!mon_register_valid((yyvsp[-1].i), (yyvsp[0].reg))) {
                                        return ERR_INVALID_REGISTER;
                                    }
                                    (yyval.i) = new_reg((yyvsp[-1].i), (yyvsp[0].reg));
                                }
#line 3362 "y.tab.c" /* yacc.c:1652  */
    break;

  case 180:
#line 632 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (monitor_cpu_for_memspace[reg_memspace((yyvsp[-2].i))]->mon_register_set_val)(reg_memspace((yyvsp[-2].i)), reg_regid((yyvsp[-2].i)), (uint16_t) (yyvsp[0].i)); }
#line 3368 "y.tab.c" /* yacc.c:1652  */
    break;

  case 181:
#line 635 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[0].i); }
#line 3374 "y.tab.c" /* yacc.c:1652  */
    break;

  case 182:
#line 636 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { return ERR_EXPECT_CHECKNUM; }
#line 3380 "y.tab.c" /* yacc.c:1652  */
    break;

  case 184:
#line 640 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.range)[0] = (yyvsp[0].a); (yyval.range)[1] = BAD_ADDR; }
#line 3386 "y.tab.c" /* yacc.c:1652  */
    break;

  case 185:
#line 643 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.range)[0] = (yyvsp[-2].a); (yyval.range)[1] = (yyvsp[0].a); }
#line 3392 "y.tab.c" /* yacc.c:1652  */
    break;

  case 186:
#line 645 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { if (resolve_range(e_default_space, (yyval.range), (yyvsp[0].str))) return ERR_ADDR_TOO_BIG; }
#line 3398 "y.tab.c" /* yacc.c:1652  */
    break;

  case 187:
#line 647 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { if (resolve_range((yyvsp[-2].i), (yyval.range), (yyvsp[0].str))) return ERR_ADDR_TOO_BIG; }
#line 3404 "y.tab.c" /* yacc.c:1652  */
    break;

  case 188:
#line 650 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.a) = (yyvsp[0].a); }
#line 3410 "y.tab.c" /* yacc.c:1652  */
    break;

  case 189:
#line 651 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.a) = BAD_ADDR; }
#line 3416 "y.tab.c" /* yacc.c:1652  */
    break;

  case 190:
#line 655 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
             (yyval.a) = new_addr(e_default_space,(yyvsp[0].i));
             if (opt_asm) new_cmd = asm_mode = 1;
         }
#line 3425 "y.tab.c" /* yacc.c:1652  */
    break;

  case 191:
#line 660 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
             (yyval.a) = new_addr((yyvsp[-2].i), (yyvsp[0].i));
             if (opt_asm) new_cmd = asm_mode = 1;
         }
#line 3434 "y.tab.c" /* yacc.c:1652  */
    break;

  case 192:
#line 665 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
             temp = mon_symbol_table_lookup_addr(e_default_space, (yyvsp[0].str));
             if (temp >= 0)
                 (yyval.a) = new_addr(e_default_space, temp);
             else
                 return ERR_UNDEFINED_LABEL;
         }
#line 3446 "y.tab.c" /* yacc.c:1652  */
    break;

  case 195:
#line 678 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = e_comp_space; }
#line 3452 "y.tab.c" /* yacc.c:1652  */
    break;

  case 196:
#line 679 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = e_disk8_space; }
#line 3458 "y.tab.c" /* yacc.c:1652  */
    break;

  case 197:
#line 680 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = e_disk9_space; }
#line 3464 "y.tab.c" /* yacc.c:1652  */
    break;

  case 198:
#line 681 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = e_disk10_space; }
#line 3470 "y.tab.c" /* yacc.c:1652  */
    break;

  case 199:
#line 682 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = e_disk11_space; }
#line 3476 "y.tab.c" /* yacc.c:1652  */
    break;

  case 200:
#line 685 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[0].i); if (!CHECK_ADDR((yyvsp[0].i))) return ERR_ADDR_TOO_BIG; }
#line 3482 "y.tab.c" /* yacc.c:1652  */
    break;

  case 201:
#line 687 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[0].i); }
#line 3488 "y.tab.c" /* yacc.c:1652  */
    break;

  case 202:
#line 689 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[-2].i) + (yyvsp[0].i); }
#line 3494 "y.tab.c" /* yacc.c:1652  */
    break;

  case 203:
#line 690 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[-2].i) - (yyvsp[0].i); }
#line 3500 "y.tab.c" /* yacc.c:1652  */
    break;

  case 204:
#line 691 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[-2].i) * (yyvsp[0].i); }
#line 3506 "y.tab.c" /* yacc.c:1652  */
    break;

  case 205:
#line 692 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = ((yyvsp[0].i)) ? ((yyvsp[-2].i) / (yyvsp[0].i)) : 1; }
#line 3512 "y.tab.c" /* yacc.c:1652  */
    break;

  case 206:
#line 693 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[-1].i); }
#line 3518 "y.tab.c" /* yacc.c:1652  */
    break;

  case 207:
#line 694 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { return ERR_MISSING_CLOSE_PAREN; }
#line 3524 "y.tab.c" /* yacc.c:1652  */
    break;

  case 208:
#line 695 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[0].i); }
#line 3530 "y.tab.c" /* yacc.c:1652  */
    break;

  case 209:
#line 698 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.cond_node) = (yyvsp[0].cond_node); }
#line 3536 "y.tab.c" /* yacc.c:1652  */
    break;

  case 210:
#line 699 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.cond_node) = 0; }
#line 3542 "y.tab.c" /* yacc.c:1652  */
    break;

  case 211:
#line 702 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
               (yyval.cond_node) = new_cond; (yyval.cond_node)->is_parenthized = FALSE;
               (yyval.cond_node)->child1 = (yyvsp[-2].cond_node); (yyval.cond_node)->child2 = (yyvsp[0].cond_node); (yyval.cond_node)->operation = (yyvsp[-1].cond_op);
           }
#line 3551 "y.tab.c" /* yacc.c:1652  */
    break;

  case 212:
#line 707 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { return ERR_INCOMPLETE_COMPARE_OP; }
#line 3557 "y.tab.c" /* yacc.c:1652  */
    break;

  case 213:
#line 709 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.cond_node) = (yyvsp[-1].cond_node); (yyval.cond_node)->is_parenthized = TRUE; }
#line 3563 "y.tab.c" /* yacc.c:1652  */
    break;

  case 214:
#line 711 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { return ERR_MISSING_CLOSE_PAREN; }
#line 3569 "y.tab.c" /* yacc.c:1652  */
    break;

  case 215:
#line 713 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.cond_node) = (yyvsp[0].cond_node); }
#line 3575 "y.tab.c" /* yacc.c:1652  */
    break;

  case 216:
#line 716 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.cond_node) = new_cond;
                            (yyval.cond_node)->operation = e_INV;
                            (yyval.cond_node)->is_parenthized = FALSE;
                            (yyval.cond_node)->reg_num = (yyvsp[0].i); (yyval.cond_node)->is_reg = TRUE; (yyval.cond_node)->banknum=-1;
                            (yyval.cond_node)->child1 = NULL; (yyval.cond_node)->child2 = NULL;
                          }
#line 3586 "y.tab.c" /* yacc.c:1652  */
    break;

  case 217:
#line 722 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.cond_node) = new_cond;
                            (yyval.cond_node)->operation = e_INV;
                            (yyval.cond_node)->is_parenthized = FALSE;
                            (yyval.cond_node)->value = (yyvsp[0].i); (yyval.cond_node)->is_reg = FALSE; (yyval.cond_node)->banknum=-1;
                            (yyval.cond_node)->child1 = NULL; (yyval.cond_node)->child2 = NULL;
                          }
#line 3597 "y.tab.c" /* yacc.c:1652  */
    break;

  case 218:
#line 728 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {(yyval.cond_node)=new_cond;
                            (yyval.cond_node)->operation=e_INV;
                            (yyval.cond_node)->is_parenthized = FALSE;
                            (yyval.cond_node)->banknum=mon_banknum_from_bank(e_default_space,(yyvsp[-2].str)); (yyval.cond_node)->value = (yyvsp[0].a); (yyval.cond_node)->is_reg = FALSE;
                            (yyval.cond_node)->child1 = NULL; (yyval.cond_node)->child2 = NULL;  
                        }
#line 3608 "y.tab.c" /* yacc.c:1652  */
    break;

  case 221:
#line 740 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_add_number_to_buffer((yyvsp[0].i)); }
#line 3614 "y.tab.c" /* yacc.c:1652  */
    break;

  case 222:
#line 741 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_add_string_to_buffer((yyvsp[0].str)); }
#line 3620 "y.tab.c" /* yacc.c:1652  */
    break;

  case 225:
#line 748 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_add_number_to_buffer((yyvsp[0].i)); }
#line 3626 "y.tab.c" /* yacc.c:1652  */
    break;

  case 226:
#line 749 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_add_number_masked_to_buffer((yyvsp[0].i), 0x00); }
#line 3632 "y.tab.c" /* yacc.c:1652  */
    break;

  case 227:
#line 750 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { mon_add_string_to_buffer((yyvsp[0].str)); }
#line 3638 "y.tab.c" /* yacc.c:1652  */
    break;

  case 228:
#line 753 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[0].i); }
#line 3644 "y.tab.c" /* yacc.c:1652  */
    break;

  case 229:
#line 754 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (monitor_cpu_for_memspace[reg_memspace((yyvsp[0].i))]->mon_register_get_val)(reg_memspace((yyvsp[0].i)), reg_regid((yyvsp[0].i))); }
#line 3650 "y.tab.c" /* yacc.c:1652  */
    break;

  case 230:
#line 757 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[0].i); }
#line 3656 "y.tab.c" /* yacc.c:1652  */
    break;

  case 231:
#line 758 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = strtol((yyvsp[0].str), NULL, 10); }
#line 3662 "y.tab.c" /* yacc.c:1652  */
    break;

  case 232:
#line 759 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = strtol((yyvsp[0].str), NULL, 10); }
#line 3668 "y.tab.c" /* yacc.c:1652  */
    break;

  case 233:
#line 760 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = strtol((yyvsp[0].str), NULL, 10); }
#line 3674 "y.tab.c" /* yacc.c:1652  */
    break;

  case 234:
#line 763 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = resolve_datatype(B_NUMBER,(yyvsp[0].str)); }
#line 3680 "y.tab.c" /* yacc.c:1652  */
    break;

  case 235:
#line 764 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = resolve_datatype(O_NUMBER,(yyvsp[0].str)); }
#line 3686 "y.tab.c" /* yacc.c:1652  */
    break;

  case 236:
#line 765 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = resolve_datatype(D_NUMBER,(yyvsp[0].str)); }
#line 3692 "y.tab.c" /* yacc.c:1652  */
    break;

  case 237:
#line 768 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[0].i); }
#line 3698 "y.tab.c" /* yacc.c:1652  */
    break;

  case 238:
#line 769 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[0].i); }
#line 3704 "y.tab.c" /* yacc.c:1652  */
    break;

  case 239:
#line 770 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[0].i); }
#line 3710 "y.tab.c" /* yacc.c:1652  */
    break;

  case 240:
#line 771 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[0].i); }
#line 3716 "y.tab.c" /* yacc.c:1652  */
    break;

  case 241:
#line 772 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[0].i); }
#line 3722 "y.tab.c" /* yacc.c:1652  */
    break;

  case 245:
#line 780 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = 0;
                                                if ((yyvsp[-1].str)) {
                                                    (monitor_cpu_for_memspace[default_memspace]->mon_assemble_instr)((yyvsp[-1].str), (yyvsp[0].mode));
                                                } else {
                                                    new_cmd = 1;
                                                    asm_mode = 0;
                                                }
                                                opt_asm = 0;
                                              }
#line 3736 "y.tab.c" /* yacc.c:1652  */
    break;

  case 247:
#line 791 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { asm_mode = 0; }
#line 3742 "y.tab.c" /* yacc.c:1652  */
    break;

  case 248:
#line 794 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { if ((yyvsp[0].i) > 0xff) {
                          (yyval.mode).addr_mode = ASM_ADDR_MODE_IMMEDIATE_16;
                          (yyval.mode).param = (yyvsp[0].i);
                        } else {
                          (yyval.mode).addr_mode = ASM_ADDR_MODE_IMMEDIATE;
                          (yyval.mode).param = (yyvsp[0].i);
                        } }
#line 3754 "y.tab.c" /* yacc.c:1652  */
    break;

  case 249:
#line 801 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { if ((yyvsp[0].i) >= 0x10000) {
               (yyval.mode).addr_mode = ASM_ADDR_MODE_ABSOLUTE_LONG;
               (yyval.mode).param = (yyvsp[0].i);
             } else if ((yyvsp[0].i) < 0x100) {
               (yyval.mode).addr_mode = ASM_ADDR_MODE_ZERO_PAGE;
               (yyval.mode).param = (yyvsp[0].i);
             } else {
               (yyval.mode).addr_mode = ASM_ADDR_MODE_ABSOLUTE;
               (yyval.mode).param = (yyvsp[0].i);
             }
           }
#line 3770 "y.tab.c" /* yacc.c:1652  */
    break;

  case 250:
#line 812 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { if ((yyvsp[-2].i) >= 0x10000) {
                            (yyval.mode).addr_mode = ASM_ADDR_MODE_ABSOLUTE_LONG_X;
                            (yyval.mode).param = (yyvsp[-2].i);
                          } else if ((yyvsp[-2].i) < 0x100) { 
                            (yyval.mode).addr_mode = ASM_ADDR_MODE_ZERO_PAGE_X;
                            (yyval.mode).param = (yyvsp[-2].i);
                          } else {
                            (yyval.mode).addr_mode = ASM_ADDR_MODE_ABSOLUTE_X;
                            (yyval.mode).param = (yyvsp[-2].i);
                          }
                        }
#line 3786 "y.tab.c" /* yacc.c:1652  */
    break;

  case 251:
#line 823 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { if ((yyvsp[-2].i) < 0x100) {
                            (yyval.mode).addr_mode = ASM_ADDR_MODE_ZERO_PAGE_Y;
                            (yyval.mode).param = (yyvsp[-2].i);
                          } else {
                            (yyval.mode).addr_mode = ASM_ADDR_MODE_ABSOLUTE_Y;
                            (yyval.mode).param = (yyvsp[-2].i);
                          }
                        }
#line 3799 "y.tab.c" /* yacc.c:1652  */
    break;

  case 252:
#line 831 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { if ((yyvsp[-2].i) < 0x100) {
                            (yyval.mode).addr_mode = ASM_ADDR_MODE_STACK_RELATIVE;
                            (yyval.mode).param = (yyvsp[-2].i);
                          } else { /* 6809 */
                            (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
                            if ((yyvsp[-2].i) >= -16 && (yyvsp[-2].i) < 16) {
                                (yyval.mode).addr_submode = (yyvsp[0].i) | ((yyvsp[-2].i) & 0x1F);
                            } else if ((yyvsp[-2].i) >= -128 && (yyvsp[-2].i) < 128) {
                                (yyval.mode).addr_submode = 0x80 | (yyvsp[0].i) | ASM_ADDR_MODE_INDEXED_OFF8;
                                (yyval.mode).param = (yyvsp[-2].i);
                            } else if ((yyvsp[-2].i) >= -32768 && (yyvsp[-2].i) < 32768) {
                                (yyval.mode).addr_submode = 0x80 | (yyvsp[0].i) | ASM_ADDR_MODE_INDEXED_OFF16;
                                (yyval.mode).param = (yyvsp[-2].i);
                            } else {
                                (yyval.mode).addr_mode = ASM_ADDR_MODE_ILLEGAL;
                                mon_out("offset too large even for 16 bits (signed)\n");
                            }
                          }
                        }
#line 3823 "y.tab.c" /* yacc.c:1652  */
    break;

  case 253:
#line 850 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { if ((yyvsp[-2].i) < 0x100) {
                            (yyval.mode).addr_mode = ASM_ADDR_MODE_DOUBLE;
                            (yyval.mode).param = (yyvsp[0].i);
                            (yyval.mode).addr_submode = (yyvsp[-2].i);
                          }
                        }
#line 3834 "y.tab.c" /* yacc.c:1652  */
    break;

  case 254:
#line 856 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { if ((yyvsp[-1].i) < 0x100) {
                               (yyval.mode).addr_mode = ASM_ADDR_MODE_INDIRECT;
                               (yyval.mode).param = (yyvsp[-1].i);
                             } else {
                               (yyval.mode).addr_mode = ASM_ADDR_MODE_ABS_INDIRECT;
                               (yyval.mode).param = (yyvsp[-1].i);
                             }
                           }
#line 3847 "y.tab.c" /* yacc.c:1652  */
    break;

  case 255:
#line 864 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { if ((yyvsp[-3].i) < 0x100) {
                                           (yyval.mode).addr_mode = ASM_ADDR_MODE_INDIRECT_X;
                                           (yyval.mode).param = (yyvsp[-3].i);
                                         } else {
                                           (yyval.mode).addr_mode = ASM_ADDR_MODE_ABS_INDIRECT_X;
                                           (yyval.mode).param = (yyvsp[-3].i);
                                         }
                                       }
#line 3860 "y.tab.c" /* yacc.c:1652  */
    break;

  case 256:
#line 873 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_STACK_RELATIVE_Y; (yyval.mode).param = (yyvsp[-5].i); }
#line 3866 "y.tab.c" /* yacc.c:1652  */
    break;

  case 257:
#line 875 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_INDIRECT_Y; (yyval.mode).param = (yyvsp[-3].i); }
#line 3872 "y.tab.c" /* yacc.c:1652  */
    break;

  case 258:
#line 876 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_IND_BC; }
#line 3878 "y.tab.c" /* yacc.c:1652  */
    break;

  case 259:
#line 877 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_IND_DE; }
#line 3884 "y.tab.c" /* yacc.c:1652  */
    break;

  case 260:
#line 878 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_IND_HL; }
#line 3890 "y.tab.c" /* yacc.c:1652  */
    break;

  case 261:
#line 879 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_IND_IX; }
#line 3896 "y.tab.c" /* yacc.c:1652  */
    break;

  case 262:
#line 880 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_IND_IY; }
#line 3902 "y.tab.c" /* yacc.c:1652  */
    break;

  case 263:
#line 881 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_IND_SP; }
#line 3908 "y.tab.c" /* yacc.c:1652  */
    break;

  case 264:
#line 883 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_ABSOLUTE_A; (yyval.mode).param = (yyvsp[-3].i); }
#line 3914 "y.tab.c" /* yacc.c:1652  */
    break;

  case 265:
#line 885 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_ABSOLUTE_HL; (yyval.mode).param = (yyvsp[-3].i); }
#line 3920 "y.tab.c" /* yacc.c:1652  */
    break;

  case 266:
#line 887 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_ABSOLUTE_IX; (yyval.mode).param = (yyvsp[-3].i); }
#line 3926 "y.tab.c" /* yacc.c:1652  */
    break;

  case 267:
#line 889 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_ABSOLUTE_IY; (yyval.mode).param = (yyvsp[-3].i); }
#line 3932 "y.tab.c" /* yacc.c:1652  */
    break;

  case 268:
#line 890 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_IMPLIED; }
#line 3938 "y.tab.c" /* yacc.c:1652  */
    break;

  case 269:
#line 891 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_ACCUMULATOR; }
#line 3944 "y.tab.c" /* yacc.c:1652  */
    break;

  case 270:
#line 892 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_B; }
#line 3950 "y.tab.c" /* yacc.c:1652  */
    break;

  case 271:
#line 893 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_C; }
#line 3956 "y.tab.c" /* yacc.c:1652  */
    break;

  case 272:
#line 894 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_D; }
#line 3962 "y.tab.c" /* yacc.c:1652  */
    break;

  case 273:
#line 895 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_E; }
#line 3968 "y.tab.c" /* yacc.c:1652  */
    break;

  case 274:
#line 896 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_H; }
#line 3974 "y.tab.c" /* yacc.c:1652  */
    break;

  case 275:
#line 897 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_IXH; }
#line 3980 "y.tab.c" /* yacc.c:1652  */
    break;

  case 276:
#line 898 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_IYH; }
#line 3986 "y.tab.c" /* yacc.c:1652  */
    break;

  case 277:
#line 899 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_L; }
#line 3992 "y.tab.c" /* yacc.c:1652  */
    break;

  case 278:
#line 900 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_IXL; }
#line 3998 "y.tab.c" /* yacc.c:1652  */
    break;

  case 279:
#line 901 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_IYL; }
#line 4004 "y.tab.c" /* yacc.c:1652  */
    break;

  case 280:
#line 902 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_AF; }
#line 4010 "y.tab.c" /* yacc.c:1652  */
    break;

  case 281:
#line 903 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_BC; }
#line 4016 "y.tab.c" /* yacc.c:1652  */
    break;

  case 282:
#line 904 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_DE; }
#line 4022 "y.tab.c" /* yacc.c:1652  */
    break;

  case 283:
#line 905 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_HL; }
#line 4028 "y.tab.c" /* yacc.c:1652  */
    break;

  case 284:
#line 906 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_IX; }
#line 4034 "y.tab.c" /* yacc.c:1652  */
    break;

  case 285:
#line 907 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_IY; }
#line 4040 "y.tab.c" /* yacc.c:1652  */
    break;

  case 286:
#line 908 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_SP; }
#line 4046 "y.tab.c" /* yacc.c:1652  */
    break;

  case 287:
#line 910 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_DIRECT; (yyval.mode).param = (yyvsp[0].i); }
#line 4052 "y.tab.c" /* yacc.c:1652  */
    break;

  case 288:
#line 911 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {    /* Clash with addr,x addr,y addr,s modes! */
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        if ((yyvsp[-2].i) >= -16 && (yyvsp[-2].i) < 16) {
            (yyval.mode).addr_submode = (3 << 5) | ((yyvsp[-2].i) & 0x1F);
        } else if ((yyvsp[-2].i) >= -128 && (yyvsp[-2].i) < 128) {
            (yyval.mode).addr_submode = 0x80 | (3 << 5) | ASM_ADDR_MODE_INDEXED_OFF8;
            (yyval.mode).param = (yyvsp[-2].i);
        } else if ((yyvsp[-2].i) >= -32768 && (yyvsp[-2].i) < 32768) {
            (yyval.mode).addr_submode = 0x80 | (3 << 5) | ASM_ADDR_MODE_INDEXED_OFF16;
            (yyval.mode).param = (yyvsp[-2].i);
        } else {
            (yyval.mode).addr_mode = ASM_ADDR_MODE_ILLEGAL;
            mon_out("offset too large even for 16 bits (signed)\n");
        }
    }
#line 4072 "y.tab.c" /* yacc.c:1652  */
    break;

  case 289:
#line 926 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).addr_submode = 0x80 | (yyvsp[-1].i) | ASM_ADDR_MODE_INDEXED_INC1;
        }
#line 4081 "y.tab.c" /* yacc.c:1652  */
    break;

  case 290:
#line 930 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).addr_submode = 0x80 | (yyvsp[-2].i) | ASM_ADDR_MODE_INDEXED_INC2;
        }
#line 4090 "y.tab.c" /* yacc.c:1652  */
    break;

  case 291:
#line 934 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).addr_submode = 0x80 | (yyvsp[0].i) | ASM_ADDR_MODE_INDEXED_DEC1;
        }
#line 4099 "y.tab.c" /* yacc.c:1652  */
    break;

  case 292:
#line 938 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).addr_submode = 0x80 | (yyvsp[0].i) | ASM_ADDR_MODE_INDEXED_DEC2;
        }
#line 4108 "y.tab.c" /* yacc.c:1652  */
    break;

  case 293:
#line 942 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).addr_submode = 0x80 | (yyvsp[0].i) | ASM_ADDR_MODE_INDEXED_OFF0;
        }
#line 4117 "y.tab.c" /* yacc.c:1652  */
    break;

  case 294:
#line 946 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).addr_submode = 0x80 | (yyvsp[-1].i) | ASM_ADDR_MODE_INDEXED_OFFB;
        }
#line 4126 "y.tab.c" /* yacc.c:1652  */
    break;

  case 295:
#line 950 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).addr_submode = 0x80 | (yyvsp[-1].i) | ASM_ADDR_MODE_INDEXED_OFFA;
        }
#line 4135 "y.tab.c" /* yacc.c:1652  */
    break;

  case 296:
#line 954 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).addr_submode = 0x80 | (yyvsp[-1].i) | ASM_ADDR_MODE_INDEXED_OFFD;
        }
#line 4144 "y.tab.c" /* yacc.c:1652  */
    break;

  case 297:
#line 958 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).param = (yyvsp[-2].i);
        if ((yyvsp[-2].i) >= -128 && (yyvsp[-2].i) < 128) {
            (yyval.mode).addr_submode = ASM_ADDR_MODE_INDEXED_OFFPC8;
        } else if ((yyvsp[-2].i) >= -32768 && (yyvsp[-2].i) < 32768) {
            (yyval.mode).addr_submode = ASM_ADDR_MODE_INDEXED_OFFPC16;
        } else {
            (yyval.mode).addr_mode = ASM_ADDR_MODE_ILLEGAL;
            mon_out("offset too large even for 16 bits (signed)\n");
        }
    }
#line 4161 "y.tab.c" /* yacc.c:1652  */
    break;

  case 298:
#line 970 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        if ((yyvsp[-3].i) >= -16 && (yyvsp[-3].i) < 16) {
            (yyval.mode).addr_submode = (yyvsp[-3].i) & 0x1F;
        } else if ((yyvsp[-4].i) >= -128 && (yyvsp[-4].i) < 128) {
            (yyval.mode).addr_submode = ASM_ADDR_MODE_INDEXED_OFF8;
            (yyval.mode).param = (yyvsp[-3].i);
        } else if ((yyvsp[-3].i) >= -32768 && (yyvsp[-3].i) < 32768) {
            (yyval.mode).addr_submode = ASM_ADDR_MODE_INDEXED_OFF16;
            (yyval.mode).param = (yyvsp[-3].i);
        } else {
            (yyval.mode).addr_mode = ASM_ADDR_MODE_ILLEGAL;
            mon_out("offset too large even for 16 bits (signed)\n");
        }
    }
#line 4181 "y.tab.c" /* yacc.c:1652  */
    break;

  case 299:
#line 985 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).addr_submode = 0x80 | (yyvsp[-2].i) | ASM_ADDR_MODE_INDEXED_INC1;
        }
#line 4190 "y.tab.c" /* yacc.c:1652  */
    break;

  case 300:
#line 989 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).addr_submode = 0x80 | (yyvsp[-3].i) | ASM_ADDR_MODE_INDEXED_INC2;
        }
#line 4199 "y.tab.c" /* yacc.c:1652  */
    break;

  case 301:
#line 993 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).addr_submode = 0x80 | (yyvsp[-1].i) | ASM_ADDR_MODE_INDEXED_DEC1;
        }
#line 4208 "y.tab.c" /* yacc.c:1652  */
    break;

  case 302:
#line 997 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).addr_submode = 0x80 | (yyvsp[-1].i) | ASM_ADDR_MODE_INDEXED_DEC2;
        }
#line 4217 "y.tab.c" /* yacc.c:1652  */
    break;

  case 303:
#line 1001 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).addr_submode = 0x80 | (yyvsp[-1].i) | ASM_ADDR_MODE_INDEXED_OFF0;
        }
#line 4226 "y.tab.c" /* yacc.c:1652  */
    break;

  case 304:
#line 1005 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).addr_submode = 0x80 | (yyvsp[-2].i) | ASM_ADDR_MODE_INDEXED_OFFB;
        }
#line 4235 "y.tab.c" /* yacc.c:1652  */
    break;

  case 305:
#line 1009 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).addr_submode = 0x80 | (yyvsp[-2].i) | ASM_ADDR_MODE_INDEXED_OFFA;
        }
#line 4244 "y.tab.c" /* yacc.c:1652  */
    break;

  case 306:
#line 1013 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).addr_submode = 0x80 | (yyvsp[-2].i) | ASM_ADDR_MODE_INDEXED_OFFD;
        }
#line 4253 "y.tab.c" /* yacc.c:1652  */
    break;

  case 307:
#line 1017 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).param = (yyvsp[-3].i);
        if ((yyvsp[-3].i) >= -128 && (yyvsp[-3].i) < 128) {
            (yyval.mode).addr_submode = ASM_ADDR_MODE_INDEXED_OFFPC8_IND;
        } else if ((yyvsp[-3].i) >= -32768 && (yyvsp[-3].i) < 32768) {
            (yyval.mode).addr_submode = ASM_ADDR_MODE_INDEXED_OFFPC16_IND;
        } else {
            (yyval.mode).addr_mode = ASM_ADDR_MODE_ILLEGAL;
            mon_out("offset too large even for 16 bits (signed)\n");
        }
    }
#line 4270 "y.tab.c" /* yacc.c:1652  */
    break;

  case 308:
#line 1029 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).addr_submode = 0x80 | ASM_ADDR_MODE_EXTENDED_INDIRECT;
        (yyval.mode).param = (yyvsp[-1].i);
        }
#line 4280 "y.tab.c" /* yacc.c:1652  */
    break;

  case 309:
#line 1034 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDIRECT_LONG_Y;
        (yyval.mode).param = (yyvsp[-3].i);
        }
#line 4289 "y.tab.c" /* yacc.c:1652  */
    break;

  case 310:
#line 1042 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (0 << 5); printf("reg_x\n"); }
#line 4295 "y.tab.c" /* yacc.c:1652  */
    break;

  case 311:
#line 1043 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (1 << 5); printf("reg_y\n"); }
#line 4301 "y.tab.c" /* yacc.c:1652  */
    break;

  case 312:
#line 1044 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[0].i); }
#line 4307 "y.tab.c" /* yacc.c:1652  */
    break;

  case 313:
#line 1045 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (3 << 5); printf("reg_s\n"); }
#line 4313 "y.tab.c" /* yacc.c:1652  */
    break;

  case 314:
#line 1049 "vice/src/monitor/mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (2 << 5); printf("reg_u\n"); }
#line 4319 "y.tab.c" /* yacc.c:1652  */
    break;


#line 4323 "y.tab.c" /* yacc.c:1652  */
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
  return yyresult;
}
#line 1053 "vice/src/monitor/mon_parse.y" /* yacc.c:1918  */


void parse_and_execute_line(char *input)
{
   char *temp_buf;
   int i, rc;

   temp_buf = lib_malloc(strlen(input) + 3);
   strcpy(temp_buf,input);
   i = (int)strlen(input);
   temp_buf[i++] = '\n';
   temp_buf[i++] = '\0';
   temp_buf[i++] = '\0';

   make_buffer(temp_buf);
   mon_clear_buffer();
   if ( (rc =yyparse()) != 0) {
       mon_out("ERROR -- ");
       switch(rc) {
         case ERR_BAD_CMD:
           mon_out("Bad command:\n");
           break;
         case ERR_RANGE_BAD_START:
           mon_out("Bad first address in range:\n");
           break;
         case ERR_RANGE_BAD_END:
           mon_out("Bad second address in range:\n");
           break;
         case ERR_EXPECT_CHECKNUM:
           mon_out("Checkpoint number expected:\n");
           break;
         case ERR_EXPECT_END_CMD:
           mon_out("Unexpected token:\n");
           break;
         case ERR_MISSING_CLOSE_PAREN:
           mon_out("')' expected:\n");
           break;
         case ERR_INCOMPLETE_COMPARE_OP:
           mon_out("Compare operation missing an operand:\n");
           break;
         case ERR_EXPECT_FILENAME:
           mon_out("Expecting a filename:\n");
           break;
         case ERR_ADDR_TOO_BIG:
           mon_out("Address too large:\n");
           break;
         case ERR_IMM_TOO_BIG:
           mon_out("Immediate argument too large:\n");
           break;
         case ERR_EXPECT_STRING:
           mon_out("Expecting a string.\n");
           break;
         case ERR_UNDEFINED_LABEL:
           mon_out("Found an undefined label.\n");
           break;
         case ERR_EXPECT_DEVICE_NUM:
           mon_out("Expecting a device number.\n");
           break;
         case ERR_EXPECT_ADDRESS:
           mon_out("Expecting an address.\n");
           break;
         case ERR_INVALID_REGISTER:
           mon_out("Invalid register.\n");
           break;
         case ERR_ILLEGAL_INPUT:
         default:
           mon_out("Wrong syntax:\n");
       }
       mon_out("  %s\n", input);
       for (i = 0; i < last_len; i++)
           mon_out(" ");
       mon_out("  ^\n");
       asm_mode = 0;
       new_cmd = 1;
   }
   lib_free(temp_buf);
   free_buffer();
}

static int yyerror(char *s)
{
   fprintf(stderr, "ERR:%s\n", s);
   return 0;
}

static int resolve_datatype(unsigned guess_type, const char *num)
{
   /* FIXME: Handle cases when default type is non-numerical */
   if (default_radix == e_hexadecimal) {
       return strtol(num, NULL, 16);
   }

   if ((guess_type == D_NUMBER) || (default_radix == e_decimal)) {
       return strtol(num, NULL, 10);
   }

   if ((guess_type == O_NUMBER) || (default_radix == e_octal)) {
       return strtol(num, NULL, 8);
   }

   return strtol(num, NULL, 2);
}

/*
 * Resolve a character sequence containing 8 hex digits like "08001000".
 * This could be a lazy version of "0800 1000". If the default radix is not
 * hexadecimal, we handle it like a ordinary number, in the latter case there
 * is only one number in the range.
 */
static int resolve_range(enum t_memspace memspace, MON_ADDR range[2],
                         const char *num)
{
    char start[5];
    char end[5];
    long sa;

    range[1] = BAD_ADDR;

    switch (default_radix)
    {
    case e_hexadecimal:
        /* checked twice, but as the code must have exactly 8 digits: */
        if (strlen(num) == 8) {
            memcpy(start, num, 4);
            start[4] = '\0';
            memcpy(end, num + 4, 4);
            end[4] = '\0';
            sa = strtol(start, NULL, 16);
            range[1] = new_addr(memspace, strtol(end, NULL, 16));
        }
        else
            sa = strtol(num, NULL, 16);
        break;

    case e_decimal:
       sa = strtol(num, NULL, 10);
       break;

    case e_octal:
       sa = strtol(num, NULL, 8);
       break;

    default:
       sa = strtol(num, NULL, 2);
    }

    if (!CHECK_ADDR(sa))
        return ERR_ADDR_TOO_BIG;

    range[0] = new_addr(memspace, sa);
    return 0;
}
