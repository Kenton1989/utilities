#ifndef KENTON_MIN_LOGGING_H_INCLUDED
#define KENTON_MIN_LOGGING_H_INCLUDED

#include <iostream>
using namespace std;

template<char endch>
inline void log_impl() {
    if (endch != ' ') cout << endch;
}

template<char endch, typename T, typename... Ts>
inline void log_impl(T&& val, Ts... vals) {
    cout << val;
    log_impl<endch>(vals...);
}

#define logs log_impl<' '>  // log space
#define logln log_impl<'\n'> // log line

#endif // !KENTON_MIN_LOGGING_H_INCLUDED
