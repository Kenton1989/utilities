#include <iostream>
#include <iomanip>
#include <utility>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cmath>
#include <climits>
#include <ctime>
#include <algorithm>
#include <numeric>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <string>
using namespace std;

#ifdef OI_DEBUG
template<char endch, typename T>
void log_impl(T&& val) { cout << val << endch; }
template<char endch, typename T, typename... Ts>
void log_impl(T &&val, Ts &&...vals) {
    cout << val << ' ';
    log_impl<endch>(vals...);
}
#define logs log_impl<' '>
#define logln log_impl<'\n'>
#else
template<typename... Ts> void do_nothing(Ts &&...vals) {}
#define logs do_nothing
#define logln do_nothing
#endif // OI_DEBUG

#define MKPR make_pair
#define ALL(c) begin(c), end(c)
#define ALLn(arr, n) arr, arr+n
#define FILL0(arr) memset(arr, 0, sizeof(arr))
#define FILL1(arr) memset(arr, -1, sizeof(arr))

typedef unsigned long long ULL;
typedef long long LL;
typedef unsigned int Uint;
typedef unsigned char Byte;
typedef pair<int, int> Pii;
typedef pair<LL, LL> Pll;

constexpr LL MOD = 1000000007;
constexpr int INF = 0x7f7f7f7f;
constexpr double EPS = 1e-8;

inline bool diffsign(LL a, LL b) { return a ^ b < 0; }
inline bool isodd(LL a) { return a & 1; }
inline bool iseven(LL a) { return !isodd(a); }
inline LL pow2(LL pow, LL n = 1) { return n << pow; }

//Common variables
constexpr LL SZ = 100000;

template<typename T1, typename T2>
ostream &operator <<(ostream& os, const pair<T1, T2>& p) {
    cout << "{" <<p.first << "," << p.second << "}";
}

template <typename Iter>
void showRange(Iter i0, Iter i1) {
    cout << "[ ";
    while (i0 != i1) {
        cout << *(i0++) << " ";
    }
    cout << "]" << endl;
}

template <typename C>
void showContainer(const C& c) {
    showRange(c.begin(), c.end());
}

int main(int argn, char **argv) {
    multimap<int, int> m;
    m.emplace(1, 1);
    showContainer(m);
    m.emplace(1, 2);
    showContainer(m);
    m.emplace(1, 1);
    showContainer(m);
    m.emplace(1, 3);
    showContainer(m);
    showContainer(m);
    std::list<int> l;
    
}