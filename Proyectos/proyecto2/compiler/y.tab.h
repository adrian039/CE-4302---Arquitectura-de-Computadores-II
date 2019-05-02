/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    vaddition = 258,
    vsubtra = 259,
    vmultiple = 260,
    vload = 261,
    vstore = 262,
    vxor = 263,
    vrot = 264,
    vadditions = 265,
    vadditioni = 266,
    vsubtras = 267,
    vsubtrai = 268,
    vxors = 269,
    vxori = 270,
    vmultiples = 271,
    vmultiplei = 272,
    vrotr = 273,
    smove = 274,
    vreg = 275,
    sreg = 276,
    immediate = 277,
    commentary = 278,
    number = 279,
    vrepeat = 280,
    vendrepeat = 281
  };
#endif
/* Tokens.  */
#define vaddition 258
#define vsubtra 259
#define vmultiple 260
#define vload 261
#define vstore 262
#define vxor 263
#define vrot 264
#define vadditions 265
#define vadditioni 266
#define vsubtras 267
#define vsubtrai 268
#define vxors 269
#define vxori 270
#define vmultiples 271
#define vmultiplei 272
#define vrotr 273
#define smove 274
#define vreg 275
#define sreg 276
#define immediate 277
#define commentary 278
#define number 279
#define vrepeat 280
#define vendrepeat 281

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 48 "vCompiler.y" /* yacc.c:1909  */

  char* id;
  int num;

#line 111 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
