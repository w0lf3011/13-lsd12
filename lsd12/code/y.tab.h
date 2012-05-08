
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     PRINT = 258,
     READ = 259,
     WRITE = 260,
     PLUS = 261,
     MINUS = 262,
     TIMES = 263,
     ADD = 264,
     AND = 265,
     NOT = 266,
     LT = 267,
     EQUAL = 268,
     OR = 269,
     LE = 270,
     TO = 271,
     FUNCTION = 272,
     REF = 273,
     REMOVE = 274,
     FROM = 275,
     PROG = 276,
     FORWARD = 277,
     LP = 278,
     RP = 279,
     COMMA = 280,
     AFFECT = 281,
     CARDINAL = 282,
     TWOPOINT = 283,
     IF = 284,
     FI = 285,
     THEN = 286,
     ELSE = 287,
     WHILE = 288,
     DO = 289,
     OD = 290,
     RETURN = 291,
     BEG = 292,
     END = 293,
     FIN = 294,
     VAR = 295,
     NB = 296,
     BOOLEAN = 297,
     TYPE = 298,
     DIVISE = 299
   };
#endif
/* Tokens.  */
#define PRINT 258
#define READ 259
#define WRITE 260
#define PLUS 261
#define MINUS 262
#define TIMES 263
#define ADD 264
#define AND 265
#define NOT 266
#define LT 267
#define EQUAL 268
#define OR 269
#define LE 270
#define TO 271
#define FUNCTION 272
#define REF 273
#define REMOVE 274
#define FROM 275
#define PROG 276
#define FORWARD 277
#define LP 278
#define RP 279
#define COMMA 280
#define AFFECT 281
#define CARDINAL 282
#define TWOPOINT 283
#define IF 284
#define FI 285
#define THEN 286
#define ELSE 287
#define WHILE 288
#define DO 289
#define OD 290
#define RETURN 291
#define BEG 292
#define END 293
#define FIN 294
#define VAR 295
#define NB 296
#define BOOLEAN 297
#define TYPE 298
#define DIVISE 299




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 26 "lsd12.y"

  int ival;
  char *sval;
  ASTTREE tval;



/* Line 1676 of yacc.c  */
#line 148 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


