#ifndef SCANTYPE_H
#define SCANTYPE_H__DATE__ " " __TIME__

typedef struct Token Token;
struct Token {
    int tokenclass;         // class of token
    int linenum;            // mark line this token occured on
    char* token_str;        // value parsed into yytext
    const char* token_id;   // all caps token name as found in yacc
    double numValue;        // container for numbers we encounter
    int length;             // length of the string including a NUL terminal
};
#endif
