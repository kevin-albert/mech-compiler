#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <utility>
#include "ast.h"
#include "parse_context.h"

#define YYSTYPE_IS_DECLARED 1
typedef ast* YYSTYPE;
extern YYSTYPE yylval;

parse_context parse_file(const string);

extern int yylex();
extern int yyparse();
extern FILE *yyin;
extern char *yytext;
void yyerror(const string);

extern int yy_flex_debug;
extern int yydebug;
extern char *yytext;

void scanner_useraction();
void scanner_newline();
int scan_token(int code);
int bad_token(const string, int replacement);
string yy_name(int code);
void set_parse_root(ast *);

// actual parsing
ast *build(int);
ast *build(int, ast*);
ast *build(int, ast*, ast*);

ast *adopt(ast*, ast*);
ast *adopt(ast*, ast*, ast*);

ast *buildv(ast*, int);
ast *buildv(ast*, int, ast*);
ast *buildv(ast*, int, ast*, ast*);

void parse_error(ast*);

#endif
