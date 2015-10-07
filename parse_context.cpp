#include <string>
#include <iostream>

using namespace std;

#include "parse_context.h"

ostream &operator<<(ostream &out, const mech_error &err) {
    out << err.file << " " << err.line << ":" << err.col << " - " << err.msg;
    return out;
}

