#include <iostream>

#include "fixed_point.h"

using namespace std;

int main() {
    using FixedPoint32 = Kenton::FixedPoint32<8>;
    FixedPoint32 a(10);
    cout << a / 20 << endl;
    cout << a.MAX / 4 * 2 << endl;
    cout << a.MAX << endl;
}