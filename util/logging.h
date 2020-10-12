/**
 * Name: logging.h
 * 
 * Author: Kenton
 * 
 * Description:
 * Provide two logging function: logs, logln
 *     If the macro DEBUG is not defined before includeing the file, logs and logln will do nothing.
 *     If the macro DEBUG is defined, logs and logln can be used to print debug message.
 * 
 * Main Functions:
 *     logln(values...):
 *         if DEBUG is defined:
 *         print values one by one using std::cout.
 *         space (' ') is printed after each values.
 *         new line ('\n') is printed at the end of printing.
 *     logs(values...):
 *         if DEBUG is defined:
 *         print values one by one using std::cout.
 *         space (' ') is printed after each values.
 *         printing will end with a space (' ').
*/

#ifndef KENTON_LOGGING_H_INCLUDED
#define KENTON_LOGGING_H_INCLUDED

#include <iostream>

namespace Kenton {

#ifdef DEBUG

template<char endch>
inline void log_impl() {
    // if statement shall be eliminated with proper compiler optimization.
    if (endch != ' ') std::cout << endch;
}

template<char endch, typename T, typename... Ts>
inline void log_impl(T&& val, Ts... vals) {
    std::cout << val << ' ';
    log_impl<endch>(vals...);
}

// using #define, or I need to define 6 function
#define logs ::Kenton::log_impl<' '>  // log space
#define logln ::Kenton::log_impl<'\n'> // log line

#else

template<typename... Ts>
inline void logging_nothing(Ts... vals) {
    // Do nothing
}
#define logs logging_nothing // log space
#define logln logging_nothing // log line

#endif // DEBUG

} // namespace Kenton





#endif // !KENTON_LOGGING_H_INCLUDED