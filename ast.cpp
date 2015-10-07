#include <iostream>
using namespace std;

#include "ast.h"
#include "parser.h"

void ast::print(ostream &out, int depth) const {
    for (int i = 0; i < depth; ++i) {
        out << "  ";
    }
    out << this << "\n";
    for (ast *child: children) {
        child->print(out, depth + 1);
    }
}

ostream &operator <<(ostream &out, const ast *tree) {
    out << yy_name(tree->code) << " " 
        << tree->text << " (" 
        << tree->file << ":" 
        << tree->line << ":" 
        << tree->col << ")";
    return out;
}

