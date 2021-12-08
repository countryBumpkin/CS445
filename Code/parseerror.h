#ifndef _PARSEERROR_H_
#define _PARSEERROR_H_
void throw_error(std::string); // parses the token read by the parser and throws an error
extern int line; // line from parser
extern char* lastToken; // the last token read by the parser
#endif
