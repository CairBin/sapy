#pragma once

#include "sapy/panywrapper.h"
#include "sapy/pcollection_interface.h"
#include <algorithm>
#include <iterator>

namespace sapy{
class PString;

template <typename Container>
class PIterator {
public:

    using IteratorType = typename Container::iterator;
    using ValueType = typename Container::value_type;

    PIterator(IteratorType iter) : _iter(iter) {}


    ValueType& operator*() {
        return *_iter;
    }


    const ValueType& operator*() const {
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


    bool operator!=(const PIterator& other) const {
        return _iter != other._iter;
    }

    bool operator==(const PIterator& other) const {
        return _iter == other._iter;
    }

    // virtual PString toString() const override {
    //     return PString("PIterator");
    // }

private:
    // virtual void _print(std::ostream& os) const override {
    //     os << toString();
    // }

    IteratorType _iter;  
};

}