/**
 * Name: bigint.h
 * 
 * Author: Kenton
 * 
 * Description:
 * provide integer class with infinite digit limit.
 * 
 * Main Functions:
 *      
*/
#ifndef KENTON_BIGINT_H_INCLUDED
#define KENTON_BIGINT_H_INCLUDED

#include <string>
#include <vector>

class BigInt {
public:
    BigInt();
    BigInt(long long n);
    BigInt(std::string n, int base = DIG_MAX);

    operator bool() const;
    explicit operator long long() const;
    explicit operator std::string() const;

    BigInt& operator+=(const BigInt& a);
    BigInt& operator-=(const BigInt& a);
    BigInt& operator*=(const BigInt& a);
    BigInt& operator+=(int a);
    BigInt& operator-=(int a);
    BigInt& operator*=(int a);

    BigInt& operator++();
    BigInt& operator--();
    BigInt operator++(int) {
        BigInt copy = *this;
        ++*this;
        return copy;
    }
    BigInt operator--(int) {
        BigInt copy = *this;
        --*this;
        return copy;
    }
private:
    using DigitT = unsigned int;
    static constexpr DigitT DIG_MAX = 1e9;
    std::vector<DigitT> data;
    bool sign;
};


bool operator==(const BigInt& a, const BigInt& b);
bool operator<(const BigInt& a, const BigInt& b);
inline bool operator!=(const BigInt& a, const BigInt& b) { return !(a==b);}
inline bool operator>(const BigInt& a, const BigInt& b) { return a < b; }
inline bool operator<=(const BigInt& a, const BigInt& b) { return !(a > b); }
inline bool operator>=(const BigInt& a, const BigInt& b) { return !(a < b); }

BigInt operator+(const BigInt& a, const BigInt& b);
BigInt operator-(const BigInt& a, const BigInt& b);
BigInt operator*(const BigInt& a, const BigInt& b);
std::ostream& operator<<(std::ostream& os, const BigInt& n);

#endif // !KENTON_BIGINT_H_INCLUDED