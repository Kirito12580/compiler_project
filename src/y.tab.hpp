/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_Y_TAB_HPP_INCLUDED
# define YY_YY_Y_TAB_HPP_INCLUDED
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
    ADD = 258,
    SUB = 259,
    MUL = 260,
    DIV = 261,
    SEMICOLON = 262,
    NUM = 263,
    ID = 264,
    LPAREN = 265,
    RPAREN = 266,
    AND = 267,
    OR = 268,
    NOT = 269,
    GREATER = 270,
    LESS = 271,
    GREATER_EQ = 272,
    LESS_EQ = 273,
    EQUAL = 274,
    NOT_EQUAL = 275,
    ASSIGN = 276,
    LET = 277,
    COLON = 278,
    COMMA = 279,
    LBRACKET = 280,
    RBRACKET = 281,
    LBRACE = 282,
    RBRACE = 283,
    STRUCT = 284,
    FN = 285,
    ARROW = 286,
    RETURN = 287,
    DOT = 288,
    CONTINUE = 289,
    BREAK = 290,
    IF = 291,
    ELSE = 292,
    WHILE = 293,
    INT = 294
  };
#endif
/* Tokens.  */
#define ADD 258
#define SUB 259
#define MUL 260
#define DIV 261
#define SEMICOLON 262
#define NUM 263
#define ID 264
#define LPAREN 265
#define RPAREN 266
#define AND 267
#define OR 268
#define NOT 269
#define GREATER 270
#define LESS 271
#define GREATER_EQ 272
#define LESS_EQ 273
#define EQUAL 274
#define NOT_EQUAL 275
#define ASSIGN 276
#define LET 277
#define COLON 278
#define COMMA 279
#define LBRACKET 280
#define RBRACKET 281
#define LBRACE 282
#define RBRACE 283
#define STRUCT 284
#define FN 285
#define ARROW 286
#define RETURN 287
#define DOT 288
#define CONTINUE 289
#define BREAK 290
#define IF 291
#define ELSE 292
#define WHILE 293
#define INT 294

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 19 "parser.yacc"

  A_pos pos;
  
  //开始
  A_type type;
  A_tokenId tokenId;
  A_tokenNum tokenNum;
  A_rightValList rightValList;
  A_fnCall fnCall;
  
  A_indexExpr indexExpr;
  A_arrayExpr arrayExpr;
  A_memberExpr memberExpr;
  A_exprUnit exprUnit;

  A_arithBiOpExpr arithBiOpExpr;
  A_arithUExpr arithUExpr;
  A_arithExpr arithExpr;
  A_boolBiOpExpr boolBiOpExpr;
  A_boolUOpExpr boolUOpExpr;
  A_boolExpr boolExpr;
  A_comExpr comExpr;
  A_boolUnit boolUnit;

  A_rightVal rightVal;
  A_leftVal leftVal;
  A_assignStmt assignStmt;

  A_varDeclList varDeclList;
  A_varDeclStmt varDeclStmt;
  A_varDefScalar varDefScalar;
  A_varDeclScalar varDeclScalar;
  A_varDeclArray varDeclArray;
  A_varDecl varDecl;
  A_varDefArray varDefArray;
  A_varDef varDef;

  A_structDef structDef;
  A_fnDecl fnDecl;
  A_fnDef fnDef;
  A_fnDeclStmt fnDeclStmt;
  A_paramDecl paramDecl;

  A_codeBlockStmtList codeBlockStmtList;
  A_codeBlockStmt codeBlockStmt;

  A_ifStmt ifStmt;
  A_whileStmt whileStmt;
  A_callStmt callStmt;
  A_returnStmt returnStmt;

  A_programElement programElement;
  A_programElementList programElementList;
  A_program program;

#line 191 "y.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_HPP_INCLUDED  */
