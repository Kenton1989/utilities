/**
 * Name: mk_pair_t.h
 * Author: Kenton
 * Description:
 *     Full name: Make Pair Type
 *     quickly create a class with property of std::pair
 *     add getters, to make the field name meaningful (rather than "first" and "second")
*/

#ifndef KENTON_MK_PAIR_T_H_INCLUDED
#define KENTON_MK_PAIR_T_H_INCLUDED

#include <utility>

#define mk_pair_t(ClassName, Type1, name1, Type2, name2)\
struct ClassName: std::pair<Type1, Type2> {\
    (Type1)& name1() { return this->first; }\
    (Type2)& name2() { return this->second; }\
}

#endif // !KENTON_MK_PAIR_T_H_INCLUDED
