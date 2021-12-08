%{
#include <string>
#include <iostream>
#include "parser.tab.h"   // definitions from bison
#include "scanType.h"  // definition for tokens
#include "parseerror.cpp"

int line = 1; // line number used in bison
char* lastToken = NULL;
char* currentToken = NULL;
extern int numErrors;

// sets values in yylval which is passed from bison
static int setToken(int linenum, int tokenClass, char* tokenstr, char* token_id)
{
    yylval.tokenData = new Token;
    yylval.tokenData->tokenclass = tokenClass;
    yylval.tokenData->linenum = linenum;
    yylval.tokenData->token_str = strdup(tokenstr);
    yylval.tokenData->token_id = token_id;

    if(tokenClass == NUMCONST)
    {
        yylval.tokenData->numValue = atof(tokenstr);
    }else if(tokenClass == STRINGCONST){
        yylval.tokenData->length = strlen(tokenstr) - 2; // subtract quotation marks from length
    }

    lastToken = yylval.tokenData->token_str;

    return tokenClass;
}

%}

punc [,|+=\/().!?&*%$#@=:`~<>\\]|"^"|"-"|"_"|";"
lcomment "\/\/"({string}|{punc}|{dquote}|{squote}|{func_escape}|{escape_char})*"\n"
dquote "\""
squote "'"
lbracket "["
rbracket "]"
lbrace "{"
rbrace "}"
lparen "("
rparen ")"
letter [a-zA-Z]
string ({whitespace}|{letter}|{punc}|{lbrace}|{rbrace}|{lbracket}|{rbracket}|{number})*
func_escape  "\\n"|"\\0"
escape_char  (\\({punc}|{dquote}|{squote}|[a-mo-zA-MO-Z]|[0-9]))
whitespace ("\t"|" "|"\v"|"\r"|"\f"|"\b"|"\a")
number ([0-9]+)


%option noyywrap

%%
";"                                                             { char s[] = "SEMICOLON"; return setToken(line, SEMICOLON, yytext, s); }
":"                                                             { char s[] = "COLON"; return setToken(line, COLON, yytext, s); }
","                                                             { char s[] = "COMMA"; return setToken(line, COMMA, yytext, s); }
"{"                                                             { char s[] = "LBRACE"; return setToken(line, LBRACE, yytext, s); }
"}"                                                             { char s[] = "RBRACE"; return setToken(line, RBRACE, yytext, s); }
"["                                                             { char s[] = "LBRACKET"; return setToken(line, LBRACKET, yytext, s); }
"]"                                                             { char s[] = "RBRACKET"; return setToken(line, RBRACKET, yytext, s); }
"("                                                             { char s[] = "LPAREN"; return setToken(line, LPAREN, yytext, s); }
")"                                                             { char s[] = "RPAREN"; return setToken(line, RPAREN, yytext, s); }
{number}                                                        { char s[] = "NUMCONST"; return setToken(line, NUMCONST, yytext, s); }
"int"                                                           { char s[] = "INT"; return setToken(line, INT, yytext, s); }
"bool"                                                          { char s[] = "BOOL"; return setToken(line, BOOL, yytext, s); }
"or"                                                            { char s[] = "OR"; return setToken(line, OR, yytext, s); }
"not"                                                           { char s[] = "NOT"; return setToken(line, NOT, yytext, s); }
"and"                                                           { char s[] = "AND"; return setToken(line, AND, yytext, s); }
"static"                                                        { char s[] = "STATIC"; return setToken(line, STATIC, yytext, s); }
"if"                                                            { char s[] = "IF"; return setToken(line, IF, yytext, s); }
"then"                                                          { char s[] = "THEN"; return setToken(line, THEN, yytext, s); }
"else"                                                          { char s[] = "ELSE"; return setToken(line, ELSE, yytext, s); }
"char"                                                          { char s[] = "CHAR"; return setToken(line, CHAR, yytext, s); }
"while"                                                         { char s[] = "WHILE"; return setToken(line, WHILE, yytext, s); }
"for"                                                           { char s[] = "FOR"; return setToken(line, FOR, yytext, s); }
"do"                                                            { char s[] = "DO"; return setToken(line, DO, yytext, s); }
"to"                                                            { char s[] = "TO"; return setToken(line, TO, yytext, s); }
"by"                                                            { char s[] = "BY"; return setToken(line, BY, yytext, s); }
"break"                                                         { char s[] = "BREAK"; return setToken(line, BREAK, yytext, s); }
"return"                                                        { char s[] = "RETURN"; return setToken(line, RETURN, yytext, s); }
"<"                                                             { char s[] = "<"; return setToken(line, LT, yytext, s); }
">"                                                             { char s[] = ">"; return setToken(line, GT, yytext, s); }
"="                                                             { char s[] = "="; return setToken(line, EQ, yytext, s); }
">="                                                            { char s[] = "GEQ"; return setToken(line, GEQ, yytext, s); }
"<="                                                            { char s[] = "LEQ"; return setToken(line, LEQ, yytext, s); }
"><"                                                            { char s[] = "NEQ"; return setToken(line, NEQ, yytext, s); }
"?"                                                             { char s[] = "CONDITIONAL"; return setToken(line, CONDITIONAL, yytext, s); }
"--"                                                            { char s[] = "DEC"; return setToken(line, DEC, yytext, s); }
"++"                                                            { char s[] = "INC"; return setToken(line, INC, yytext, s); }
"+="                                                            { char s[] = "ADDASS"; return setToken(line, ADDASS, yytext, s); }
"-="                                                            { char s[] = "SUBASS"; return setToken(line, SUBASS, yytext, s); }
"*="                                                            { char s[] = "MULTASS"; return setToken(line, MULTASS, yytext, s);  }
"/="                                                            { char s[] = "DIVASS"; return setToken(line, DIVASS, yytext, s); }
":="                                                            { char s[] = "ASGN"; return setToken(line, ASGN, yytext, s); }
"+"                                                             { char s[] = "ADD"; return setToken(line, ADD, yytext, s); }
"-"                                                             { char s[] = "SUB"; return setToken(line, SUB, yytext, s); }
"*"                                                             { char s[] = "MULT"; return setToken(line, MULT, yytext, s);}
"/"                                                             { char s[] = "DIV"; return setToken(line, DIV, yytext, s); }
"%"                                                             { char s[] = "MOD"; return setToken(line, MOD, yytext, s); }
"true"|"false"                                                  { char s[] = "BOOLCONST"; return setToken(line, BOOLCONST, yytext, s); }
{letter}+([a-zA-Z0-9]*)                                         { char s[] = "ID"; return setToken(line, ID, yytext, s); }
'({letter}?{punc}?{dquote}?{escape_char}?{func_escape}?{whitespace}?[0-9]?(" ")?)*'    { char s[] = "CHARCONST"; return setToken(line, CHARCONST, yytext, s); }
{dquote}({func_escape}|{escape_char}|{string}|{squote})*{dquote}               { char s[] = "STRINGCONST"; return setToken(line, STRINGCONST, yytext, s); }
"\n"|"\0"                                                       { line++; /*lastToken = strdup(yytext);*/}
{whitespace}*                                                   { /* eating whitespace */}
{lcomment}                                                      { line++; /* do nothing */}
.                                                               { numErrors++; std::string token = std::string(yytext); throw_error(token); }
%%
