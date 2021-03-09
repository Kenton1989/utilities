#ifndef KENTON_FENWICK_ARRAY_H_
#define KENTON_FENWICK_ARRAY_H_
#include <stddef.h>
#include <algorithm>
#include <iterator>

namespace Kenton
{
    template <typename T, size_t SZ>
    class FenwickArr
    {
    public:
        FenwickArr(T val = T()) {
            using namespace std;
            fill(begin(arr_), end(arr_), val);
            initFen_();
        }

        const T& get(size_t pos) const {
            return arr_[pos];
        }

        const T& operator[](size_t pos) const {
            return arr_[pos];
        }

        T getSum(size_t len) const {
            T ans = fen_[0];
            while (len > 0) {
                ans += fen_[len];
                len &= len-1;
            }
            return ans;
        }

        void set(size_t pos, const T& val) {
            update(pos, val-get(pos));
        }

        void update(size_t pos, const T& diff) {
            arr_[pos] += diff;
            ++pos;
            do {
                fen_[pos] += diff;
                pos = (pos | (pos-1)) + 1;
            } while (pos <= SZ);
        }
    private:
        mutable T arr_[SZ];
        mutable T fen_[SZ+1];

        void initFen_() {
            fen_[0] = T();
            for (size_t i = 0; i < SZ; i++) {
                fen_[i+1] = fen_[i] + arr_[i];
            }
            for (size_t i = SZ; i > 0; --i) {
                fen_[i] -= fen_[i & (i-1)];
            }
        }
    };

} // namespace Kenton

#endif // !KENTON_FENWICK_ARRAY_H_