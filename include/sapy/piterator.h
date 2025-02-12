#pragma once

#include "sapy/panywrapper.h"
#include <algorithm>
#include <iterator>

namespace sapy{
class PString;

template <typename Container>
class PIterator {
public:

    using IteratorType = typename Container::iterator;
    using ConstIteratorType = typename Container::const_iterator;
    using ValueType = typename Container::value_type;
    using ConstValueType = typename Container::const_value_type;

    PIterator(IteratorType iter) : _iter(iter) {}
    //PIterator(ConstIteratorType iter) : _iter(iter) {}

    ValueType operator*() {
        return *_iter;
    }

    const ValueType operator*() const {
        return *_iter;
    }


    PIterator& operator++() {
        ++_iter;
        return *this;
    }

    PIterator operator++(int) {
        PIterator temp = *this;
        ++(*this);
        return temp;
    }

    PIterator operator+(size_t n) {
        return PIterator(_iter + n);
    }

    bool operator!=(const PIterator& other) const {
        return _iter != other._iter;
    }

    bool operator==(const PIterator& other) const {
        return _iter == other._iter;
    }

    ConstValueType* operator->() const { return &(*_iter); }
    // virtual PString toString() const override {
    //     return PString("PIterator");
    // }

private:
    // virtual void _print(std::ostream& os) const override {
    //     os << toString();
    // }
    IteratorType _iter; 
};


template <typename Container>
class PConstIterator {
public:
    using ConstIteratorType = typename Container::const_iterator;
    using ValueType = typename Container::value_type;
    using ConstValueType = typename Container::const_value_type;

    PConstIterator(ConstIteratorType iter) : _iter(iter) {}

    const ValueType operator*() const {
        return *_iter;
    }


    PConstIterator& operator++() {
        ++_iter;
        return *this;
    }


    PConstIterator operator++(int) {
        PConstIterator temp = *this;
        ++(*this);
        return temp;
    }

    PConstIterator operator+(size_t n) {
        return PConstIterator(_iter + n);
    }

    bool operator!=(const PConstIterator& other) const {
        return _iter != other._iter;
    }

    bool operator==(const PConstIterator& other) const {
        return _iter == other._iter;
    }

    const ConstValueType* operator->() const {
        return &(*_iter);
    }

private:
    ConstIteratorType _iter; 
};

}