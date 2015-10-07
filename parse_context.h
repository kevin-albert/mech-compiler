#ifndef PARSE_CONTEXT_H
#define PARSE_CONTEXT_H

#include <iostream>
#include <algorithm>
#include <iterator>

#include "ast.h"

class mech_error {
    friend ostream &operator<<(ostream&, const mech_error&);
    public:
        mech_error(const string msg, const string file, int line, int col):
            msg(msg), file(file), line(line), col(col) {}
        int get_line() { return line; }
        int get_col() { return col; }
    private:
        const string msg;
        const string file;
        int line;
        int col;
};


class parse_context {
    public:
        parse_context(ast *syntax_tree, vector<mech_error> &errors):
                syntax_tree(syntax_tree), errors(errors) {}

        parse_context(parse_context &&ctx):
                syntax_tree(ctx.syntax_tree), errors(move(ctx.errors)) {
            ctx.syntax_tree = nullptr;
        }

        parse_context &operator=(parse_context &&ctx) {
            syntax_tree = ctx.syntax_tree;
            errors = move(ctx.errors);
            ctx.syntax_tree = nullptr;
            return *this;
        }

        ~parse_context() {
            if (syntax_tree) {
                delete syntax_tree;
            }
        }

        ast *get_syntax_tree() {
            return syntax_tree;
        }

        bool has_errors() {
            return !errors.empty();
        }

        void print_errors(ostream &out) {
            copy(errors.begin(), errors.end(), ostream_iterator<mech_error>(out, "\n"));
        }

        void print_syntax_tree(ostream &out) {
            if (syntax_tree) {
                syntax_tree->print(out);
            } else {
                out << "( empty )\n";
            }
        }

    private:
        ast *syntax_tree;
        vector<mech_error> errors;
        // scope, etc
};


#endif
