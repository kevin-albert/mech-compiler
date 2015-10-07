#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
using namespace std;

#include "parser.h"
#include "parse_context.h"
#include "grammar.h"
#include "ast.h"
#include "util.h"

static vector<mech_error> errors;
static ast *parse_root;
static string current_file;
static int line;
static int col;

extern int yyleng;

void add_error(const string msg) {
    errors.push_back(mech_error(msg, current_file, line, col));
}

parse_context parse_file(const string filename) {
    errors.clear();

    if (filename == "-") {
        current_file = "stdin";
        yyin = stdin;
    } else {
        current_file = filename;
        yyin = fopen(filename.c_str(), "r");
    }

    line = 0;
    col = 0;

    if (yyin == NULL) {
        add_error("error: unable to open " + filename + " for parsing");
        parse_context ctx(new ast(T_ERR, "(error)", current_file, line, col), errors);
        return ctx;
    } else {
        line = 1;
        yyparse();
        parse_context ctx(parse_root, errors);
        return ctx;
    }
}

// lexical error
void yyerror(const string msg) {
    add_error(msg);
}

void scanner_newline() {
    ++line;
}

void scanner_useraction() {
    col += yyleng;
}

int scan_token(int code) {
    yylval = new ast(code, yytext, current_file, line, col);
    return code;
}

int bad_token(const string msg, int replacement)  {
    add_error("invalid token: " + msg);
    return replacement;
}

void set_parse_root(ast *root) {
    parse_root = root;
}

ast *adopt(ast *root, ast* c0) {
    return root->adopt(c0);
}

ast *adopt(ast *root, ast* c0, ast *c1) {
    return root->adopt(c0)
               ->adopt(c1);
}

ast *buildv(ast *from, int code) {
    return new ast(code, from->get_text(), from->get_file(), from->get_line(), from->get_col());
}

ast *buildv(ast *from, int code, ast *c0) {
    return adopt(buildv(from, code), c0);
}

ast *buildv(ast *from, int code, ast *c0, ast *c1) {
    return adopt(buildv(from, code), c0, c1);
}

void parse_error(ast* fail) {
    add_error("parse error: " + to_string<ast*>(fail));
}


