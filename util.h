#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <sstream>

template<typename T>
string to_string(T thing) {
    stringstream s;
    s << thing;
    return s.str();
}

template<typename T>
T from_string(string str) {
    stringstream s;
    s << str;
    T thing;
    s >> thing;
    return thing;
}

#endif
