#include <sstream>
#include <iostream>
using namespace std;
int main(void) {
    stringstream s;
    s << 100;
    int x;
    s >> x;
    cout << "x: " << x << "\n";
    s >> x;
    cout << "x: " << x << "\n";
    return 0;
}
