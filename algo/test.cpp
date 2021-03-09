#include "fenwick_arr.h"
#include <iostream>

int main(int argc, char const *argv[])
{
    using Kenton::FenwickArr;
    constexpr int SZ = 10;
    FenwickArr<int, SZ> arr(5);
    for (int i = 0; i < SZ; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i <= SZ; ++i) {
        std::cout << arr.getSum(i) << " ";
    }
    std::cout << std::endl;

    arr.set(5, 1000);
    arr.set(2, 100);
    
    for (int i = 0; i < SZ; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i <= SZ; ++i) {
        std::cout << arr.getSum(i) << " ";
    }
    std::cout << std::endl;

    return 0;
}
