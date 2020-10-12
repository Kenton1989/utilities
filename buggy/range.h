/**
 * Name: range.h
 * 
 * Author: Kenton
 * 
 * Description:
 * Simulate range() function in Python
 * 
 * Main Functions:
 *     
*/
#ifndef KENTON_RANGE_H_INCLUDED
#define KENTON_RANGE_H_INCLUDED

#include <iterator>
#include <stddef.h>
#include <utility>

namespace Kenton {

using ::std::forward;

template <typename T>
class PreIncrement {
public:
    typedef T argument_type;
    typedef T result_type;
    T& operator()(T& x) const { return ++x; }
};

template <typename T>
class PostIncrement {
public:
    typedef T argument_type;
    typedef T result_type;
    T operator()(T& x) const { return x++; }
};

template <typename ValueType, typename DiffType>
class UniformIncrement {
public:
    typedef ValueType argument_type;
    typedef ValueType result_type;
    // Constructor
    UniformIncrement(const DiffType& diff): diff_(diff) {}
    UniformIncrement(DiffType&& diff): diff_(diff) {}
    // Copy
    UniformIncrement(const UniformIncrement&) = default;
    UniformIncrement(UniformIncrement&&) = default;
    UniformIncrement& operator=(const UniformIncrement&) = default;
    UniformIncrement& operator=(UniformIncrement&&) = default;

    ValueType& operator()(ValueType& val) const {
        return val += diff_; // TODO: consider when val doesn't support "+="
    }
private:
    DiffType diff_;
};

template<typename ValueType, typename Increment = PreIncrement<ValueType>>
class Range {
public:
    class const_iterator {
    public:
        // Iterator traits
        typedef std::forward_iterator_tag iterator_category;
        typedef ValueType                 value_type;
        typedef ptrdiff_t                 difference_type;
        typedef const ValueType*          pointer;
        typedef const ValueType&          reference;

        // Constructor, destructor
        const_iterator(const ValueType& val, Range *range): current_(val), range_(range) {}
        const_iterator(ValueType&& val, Range *range): current_(val), range_(range) {}
        ~const_iterator() = default;
        // Copy
        const_iterator(const const_iterator& that) = default;
        const_iterator(const_iterator&& that) = default;
        const_iterator& operator=(const const_iterator& that) = default;
        const_iterator& operator=(const_iterator&& that) = default;

        // Comparison
        bool operator==(const const_iterator& that) {
            return !(*this != that);
        }

        bool operator!=(const const_iterator& that) {
            if (range_->is_end_iter_(that)) {
                return current_ < that.current_;
            }
            return current_ != that.current_;
        }

        // Dereference
        reference operator*() { return current_; }
        pointer   operator->() { return &current_; }

        // Moving
        const_iterator& operator++() {
            range_->increase_(current_);
            return *this;
        }
        const_iterator  operator++(int) {
            const_iterator copy = *this;
            return ++copy;
        }

    private:
        friend Range;
        ValueType current_;
        const Range* range_;
    };
    typedef const_iterator iterator;
    // Constructor, destructor
    Range(const ValueType& end_val):
        beg_(), end_iter_(end_val, nullptr), increase_() {}
    Range(ValueType&& end_val):
        beg_(), end_iter_(end_val, nullptr), increase_() {}

    template <typename ValType>
    Range(ValType&& beg_val, ValType&& end_val):
        beg_(forward<ValType>(beg_val)), end_iter_(forward<ValType>(end_val), nullptr), increase_() {}

    template <typename ValType, typename IncType>
    Range(ValType&& beg_val, ValType&& end_val, IncType&& inc):
        beg_(forward<ValType>(beg_val)), end_iter_(forward<ValType>(end_val), nullptr),
        increase_(forward<IncType>(inc)) {}

    ~Range() = default;

    // Copy
    Range(const Range& that) = default;
    Range(Range&& that) = default;
    Range& operator=(const Range& that) = default;
    Range& operator=(Range&& that) = default;

    // Iterator
    iterator begin() { return iterator(beg_, this); }
    const_iterator begin() const { return const_iterator(beg_, this); }
    const iterator& end() const { return end_iter_; }

    const_iterator cbegin() const { return const_iterator(beg_, this); }
    const const_iterator& cend() const { return end_iter_; }
private:
    ValueType beg_;
    const_iterator end_iter_;
    Increment increase_;

    bool is_end_iter_(const const_iterator& iter) const {
        return iter.range_ == nullptr;
    }
};

template <typename ValueType>
Range<std::remove_reference_t<ValueType>>
range(ValueType&& end_val) {

    typedef std::remove_reference_t<ValueType> TrueValType;
    return Range<TrueValType>(forward<ValueType>(end_val));
}

template <typename ValueType>
Range<std::remove_reference_t<ValueType>>
range(ValueType&& beg_val, ValueType&& end_val) {

    typedef std::remove_reference_t<ValueType> TrueValType;
    return Range<TrueValType>(forward<ValueType>(beg_val),
                              forward<ValueType>(end_val));
}

template <typename ValueType, typename DiffType>
Range<std::remove_reference_t<ValueType>,
      UniformIncrement<std::remove_reference_t<ValueType>, std::remove_reference_t<DiffType>>>
range(ValueType&& beg_val, ValueType&& end_val, DiffType&& diff) {

    typedef std::remove_reference_t<ValueType> TrueValType;
    typedef std::remove_reference_t<DiffType> TrueDifType;

    return Range<TrueValType, UniformIncrement<TrueValType, TrueDifType>>
                    (forward<ValueType>(beg_val),
                     forward<ValueType>(end_val),
                     UniformIncrement<TrueValType, TrueDifType>(forward<DiffType>(diff)));
}

}

#endif // !KENTON_RANGE_H_INCLUDED
