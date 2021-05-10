#include <cmath>
#include <iostream>

namespace Kenton {

template <typename DataType, typename UpDataType, int decimalSize,
          int dataSize = sizeof(DataType) * 8>
class __FixedPoint {
    using DType = DataType;
    using UpType = UpDataType;

    static constexpr int FULL_SZ = dataSize;
    static constexpr int VAL_SZ = FULL_SZ - 1;  // 1 bit as signed bit
    static constexpr int DECI_SZ = decimalSize;
    static constexpr int INT_SZ = VAL_SZ - DECI_SZ;
    static constexpr DType DEVISOR = DType(1) << DECI_SZ;

    static_assert(DECI_SZ > 0);
    static_assert(FULL_SZ > DECI_SZ);

   public:
    static const __FixedPoint MAX;
    static const __FixedPoint MIN;
    static const __FixedPoint EPS;

    __FixedPoint() : value(0) {}
    __FixedPoint(const __FixedPoint& val) : value(val.value) {}
    __FixedPoint(long double val) : value(val * DEVISOR) {}
    __FixedPoint(DType intPart, DType deciPart)
        : value((intPart << DECI_SZ) | deciPart) {}

    explicit operator long double() const {
        return (long double)value / DEVISOR;
    }

    const DType getRaw() const { return value; }
    static __FixedPoint fromRaw(DType rawVal) {
        __FixedPoint a;
        a.value = rawVal;
        return a;
    }

    __FixedPoint& operator=(const __FixedPoint& a) { value = a.value; }

    __FixedPoint operator-() const { return __FixedPoint::fromRaw(-value); }

    __FixedPoint& operator+=(const __FixedPoint& a) { value += a.value; }
    __FixedPoint& operator-=(const __FixedPoint& a) { value -= a.value; }
    __FixedPoint& operator*=(const __FixedPoint& a) { *this = *this * a; }
    __FixedPoint& operator/=(const __FixedPoint& a) { *this = *this / a; }

    friend __FixedPoint operator+(const __FixedPoint& a,
                                  const __FixedPoint& b) {
        return __FixedPoint::fromRaw(a.getRaw() + b.getRaw());
    }
    friend __FixedPoint operator-(const __FixedPoint& a,
                                  const __FixedPoint& b) {
        return __FixedPoint::fromRaw(a.getRaw() - b.getRaw());
    }
    friend __FixedPoint operator*(const __FixedPoint& a,
                                  const __FixedPoint& b) {
        return __FixedPoint::fromRaw((UpType)a.getRaw() * b.getRaw() >>
                                     DECI_SZ);
    }
    friend __FixedPoint operator/(const __FixedPoint& a,
                                  const __FixedPoint& b) {
        return __FixedPoint::fromRaw(((UpType)a.getRaw() << DECI_SZ) /
                                     b.getRaw());
    }

    friend bool operator==(const __FixedPoint& a, const __FixedPoint& b) {
        return a.getRaw() == b.getRaw();
    }
    friend bool operator!=(const __FixedPoint& a, const __FixedPoint& b) {
        return !(a == b);
    }

    friend bool operator<(const __FixedPoint& a, const __FixedPoint& b) {
        return a.getRaw() < b.getRaw();
    }
    friend bool operator>(const __FixedPoint& a, const __FixedPoint& b) {
        return b < a;
    }
    friend bool operator<=(const __FixedPoint& a, const __FixedPoint& b) {
        return !(a > b);
    }
    friend bool operator>=(const __FixedPoint& a, const __FixedPoint& b) {
        return !(a < b);
    }

    friend std::ostream& operator<<(std::ostream& os, const __FixedPoint& a) {
        return os << (long double)a;
    }

    friend __FixedPoint abs(const __FixedPoint& a) {
        return __FixedPoint(abs(a.getRaw()));
    }

   private:
    DType value;
};

template <typename T, typename U, int deciSz, int dataSz>
const __FixedPoint<T, U, deciSz, dataSz>
    __FixedPoint<T, U, deciSz, dataSz>::MAX((T(1) << INT_SZ) - 1,
                                            (T(1) << DECI_SZ) - 1);

template <typename T, typename U, int deciSz, int dataSz>
const __FixedPoint<T, U, deciSz, dataSz>
    __FixedPoint<T, U, deciSz, dataSz>::MIN(DType(-1) << INT_SZ, 0);

template <typename T, typename U, int deciSz, int dataSz>
const __FixedPoint<T, U, deciSz, dataSz>
    __FixedPoint<T, U, deciSz, dataSz>::EPS(0, 1);

template <int deciSize>
using FixedPoint32 = __FixedPoint<int, long long, deciSize>;

#ifdef __GNUC__
template <int deciSize>
using FixedPoint64 = __FixedPoint<long long, __int128, deciSize>;
#endif  // __GNUC__

}  // namespace Kenton