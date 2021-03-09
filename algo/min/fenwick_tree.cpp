typedef long long LL;

// Initialize a Fenwick tree with size n with in_arr as original array
// the Fenwick tree will be stored in the out_arr
// in_arr has size n and out_arr has size n+1
void initFenwick(LL in_arr[], LL out_arr[], int n) {
    out_arr[0] = 0;
    for (int i = 0; i < n; ++i) {
        out_arr[i+1] = out_arr[i] + in_arr[i];
    }
    for (int i = n; i > 0; --i) {
        out_arr[i] -= out_arr[i & (i-1)];
    }
    
}

// Get the sum of first n elements (from 0 to pos-1) in original array
LL getSum(LL fenwick[], int n, int pos) {
    LL ans = 0;
    while (pos > 0) {
        ans += fenwick[pos];
        pos = pos & (pos - 1);
    }
    return ans;
}

// Update the value of element at postition pos (0-index)
// of original array by diff.
LL update(LL fenwick[], int n, int pos, LL diff) {
    ++pos;
    do {
        fenwick[pos] += diff;
        pos = (pos | (pos-1)) + 1;
    } while (pos <= n);
}

#include <iostream>

int fenwick_tree_test() {
    constexpr int SZ = 10;
    LL arr[SZ], fen[SZ+1];
    for (int i = 0; i < SZ; ++i) {
        arr[i] = 5;
    }
    initFenwick(arr, fen, SZ);

    for (int i = 0; i < SZ; ++i) {
        std::cout << getSum(fen, SZ, i+1) << " ";
    }
    std::cout << std::endl;

    update(fen, SZ, 5, 2);
    for (int i = 0; i < SZ; ++i) {
        std::cout << getSum(fen, SZ, i+1) << " ";
    }
    std::cout << std::endl;

    update(fen, SZ, 3, -10);
    for (int i = 0; i < SZ; ++i) {
        std::cout << getSum(fen, SZ, i+1) << " ";
    }
    std::cout << std::endl;

    return 0;
}

int main(int argc, char const *argv[]) { return fenwick_tree_test(); }
