#ifndef KENTON_MIN_PTR_OP_WAPPER_H_INCLUDED
#define KENTON_MIN_PTR_OP_WAPPER_H_INCLUDED

#include <type_traits>
#include <utility>
#include <stddef.h>

namespace Kenton {

namespace Impl {

using One = char;
using Two = struct { char a[2]; };
using std::declval;

template<typename T>
class IsUnaryFunctor {
    template <typename U> One
        f(typename U::argument_type*,
          decltype(declval<U>()(declval<typename U::argument_type>()))*);
    template <typename U> Two f(...);
public:
    bool value = sizeof(One) == sizeof(f<T>(0, 0));
};

template<typename T>
class IsBinaryFunctor {
    template <typename U> One
        f(typename U::first_argument_type*,
          typename U::second_argument_type*,
          decltype(declval<U>()(
              declval<typename U::first_argument_type>(),
              declval<typename U::second_argument_type>()
          ))*);
    template <typename U> Two f(...);
public:
    bool value = sizeof(One) == sizeof(f<T>(0, 0, 0));
};

}


template<typename Functor>
class PtrOp {
public:
    PtrOp() = default;
    PtrOp(const PtrOp&) = default;
    PtrOp(PtrOp&&) = default;
    PtrOp& operator=(const PtrOp&) = default;
    PtrOp& operator=(PtrOp&&) = default;
    
    template<typename... Ts>
    PtrOp(Ts... args): f_(std::forward<Ts>(args)...) {}

    template<typename... Ts>
    auto operator()(Ts... args) -> decltype(std::declval<Functor>()(*args...)) {
        return f_(*args...);
    }
private:
    Functor f_;
};

// template<typename Functor>
// class PtrOp<Functor, true, true>;

// template<typename Functor>
// class PtrOp<Functor, true, false> {
//     using result_type = typename Functor::result_type;
//     using argument_type = typename Functor::argument_type*;
// };

// template<typename Functor>
// class PtrOp<Functor, false, true> {
//     using result_type = typename Functor::result_type;
//     using first_argument_type = typename Functor::first_argument_type*;
//     using second_argument_type = typename Functor::second_argument_type*;
// };

} // namespace Kenton




#endif // !KENTON_MIN_PTR_OP_WAPPER_H_INCLUDED
