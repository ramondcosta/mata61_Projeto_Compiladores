/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
    T_DEF = 258,
    T_LET = 259,
    T_IF = 260,
    T_ELSE = 261,
    T_WHILE = 262,
    WHILE = 263,
    T_RETURN = 264,
    T_PARENTESE_ESQ = 265,
    T_CHAVE_ESQ = 266,
    T_COCHETE_ESQ = 267,
    T_COCHETE_DIR = 268,
    T_CHAVE_DIR = 269,
    T_PARENTESE_DIR = 270,
    T_VIRGULA = 271,
    T_IGUAL = 272,
    T_ADICAO = 273,
    T_SUBTRACAO = 274,
    T_PRODUTO = 275,
    T_DIVISAO = 276,
    T_MENOR = 277,
    T_MAIOR = 278,
    T_MENOR_IGUAL = 279,
    T_MAIOR_IGUAL = 280,
    T_IGUAL_IGUAL = 281,
    T_DIFERENTE = 282,
    T_E = 283,
    T_OU = 284,
    T_ID = 285,
    T_DEC = 286,
    T_NAO = 287,
    T_PRINT = 288,
    T_STMT = 289,
    T_TIPO = 290,
    TYPE = 291,
    STMT = 292,
    BLOCK = 293,
    DCVAR = 294,
    ASSIGNSTMT = 295,
    COMPPARAM = 296,
    COMPASSIGN = 297,
    EXPR = 298,
    RETURNSTMT = 299,
    STMTSTMT = 300,
    NEXPRFUNCCALL = 301,
    PARAMETROS = 302,
    VOLTASTMT = 303,
    STMTBREAK = 304,
    STMTIF = 305,
    STMTELSE = 306,
    STMTCONTINUE = 307,
    STMTFUNCCALL = 308,
    FUNCCALL = 309,
    FUNCNARGLIST = 310,
    FUNCNNARGLIST = 311,
    FUNCARGLIST = 312,
    NUMBER = 313,
    T_NOME = 314,
    T_CONTINUE = 315,
    T_BREAK = 316,
    T_PONTO_VIRGULA = 317,
    T_USUBTRACAO = 318
  };
#endif
/* Tokens.  */
#define T_DEF 258
#define T_LET 259
#define T_IF 260
#define T_ELSE 261
#define T_WHILE 262
#define WHILE 263
#define T_RETURN 264
#define T_PARENTESE_ESQ 265
#define T_CHAVE_ESQ 266
#define T_COCHETE_ESQ 267
#define T_COCHETE_DIR 268
#define T_CHAVE_DIR 269
#define T_PARENTESE_DIR 270
#define T_VIRGULA 271
#define T_IGUAL 272
#define T_ADICAO 273
#define T_SUBTRACAO 274
#define T_PRODUTO 275
#define T_DIVISAO 276
#define T_MENOR 277
#define T_MAIOR 278
#define T_MENOR_IGUAL 279
#define T_MAIOR_IGUAL 280
#define T_IGUAL_IGUAL 281
#define T_DIFERENTE 282
#define T_E 283
#define T_OU 284
#define T_ID 285
#define T_DEC 286
#define T_NAO 287
#define T_PRINT 288
#define T_STMT 289
#define T_TIPO 290
#define TYPE 291
#define STMT 292
#define BLOCK 293
#define DCVAR 294
#define ASSIGNSTMT 295
#define COMPPARAM 296
#define COMPASSIGN 297
#define EXPR 298
#define RETURNSTMT 299
#define STMTSTMT 300
#define NEXPRFUNCCALL 301
#define PARAMETROS 302
#define VOLTASTMT 303
#define STMTBREAK 304
#define STMTIF 305
#define STMTELSE 306
#define STMTCONTINUE 307
#define STMTFUNCCALL 308
#define FUNCCALL 309
#define FUNCNARGLIST 310
#define FUNCNNARGLIST 311
#define FUNCARGLIST 312
#define NUMBER 313
#define T_NOME 314
#define T_CONTINUE 315
#define T_BREAK 316
#define T_PONTO_VIRGULA 317
#define T_USUBTRACAO 318

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 30 "parser.y" /* yacc.c:1909  */

	int numero;
	char id[20];
	astNode *ASTPonteiro;

#line 186 "y.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
