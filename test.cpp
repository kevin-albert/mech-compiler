#include <iostream>
using namespace std;

#include "parser.h"

int main(int argc, char **argv) {

    yydebug = 0;
    yy_flex_debug = 0;
    string infile = "-";

    if (argc == 1) {
        cout << "reading from stdin" << endl;
    } else {
        infile = argv[1];
        cout << "reading " << infile << endl;
    }

    parse_context ctx = parse_file(infile);
    if (ctx.has_errors()) {
        cout << "errors occurred while parsing:\n";
        ctx.print_errors(cerr);
        return 1;
    } else {
        ctx.print_syntax_tree(cout);
        return 0;
    }
}
