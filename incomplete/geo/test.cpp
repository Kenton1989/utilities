#include <iostream>

#include "geo_2d.hpp"

using namespace std;

int main() {
    int n;
    for (int i = 0; i < 10; ++i) {
        cin >> n;
        cout << (-(n < 0) | bool(n)) << endl;
    }
    return 0;
}