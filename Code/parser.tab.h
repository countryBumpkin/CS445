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

#line 116 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
