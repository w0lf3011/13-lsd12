
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
     MODULO = 261,
     PLUS = 262,
     MINUS = 263,
     TIMES = 264,
     ADD = 265,
     AND = 266,
     NOT = 267,
     LT = 268,
     GT = 269,
     EQUAL = 270,
     OR = 271,
     LE = 272,
     GE = 273,
     TO = 274,
     FUNCTION = 275,
     REF = 276,
     REMOVE = 277,
     FROM = 278,
     PROG = 279,
     FORWARD = 280,
     LP = 281,
     RP = 282,
     COMMA = 283,
     AFFECT = 284,
     CARDINAL = 285,
     TWOPOINT = 286,
     IF = 287,
     FI = 288,
     THEN = 289,
     ELSE = 290,
     WHILE = 291,
     DO = 292,
     OD = 293,
     RETURN = 294,
     BEG = 295,
     END = 296,
     FIN = 297,
     VAR = 298,
     NB = 299,
     BOOLEAN = 300,
     TYPE = 301,
     DIVISE = 302
   };
#endif
/* Tokens.  */
#define PRINT 258
#define READ 259
#define WRITE 260
#define MODULO 261
#define PLUS 262
#define MINUS 263
#define TIMES 264
#define ADD 265
#define AND 266
#define NOT 267
#define LT 268
#define GT 269
#define EQUAL 270
#define OR 271
#define LE 272
#define GE 273
#define TO 274
#define FUNCTION 275
#define REF 276
#define REMOVE 277
#define FROM 278
#define PROG 279
#define FORWARD 280
#define LP 281
#define RP 282
#define COMMA 283
#define AFFECT 284
#define CARDINAL 285
#define TWOPOINT 286
#define IF 287
#define FI 288
#define THEN 289
#define ELSE 290
#define WHILE 291
#define DO 292
#define OD 293
#define RETURN 294
#define BEG 295
#define END 296
#define FIN 297
#define VAR 298
#define NB 299
#define BOOLEAN 300
#define TYPE 301
#define DIVISE 302




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 26 "lsd12.y"

        int ival;
        char *sval;
        ASTTREE tval;



/* Line 1676 of yacc.c  */
#line 154 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


