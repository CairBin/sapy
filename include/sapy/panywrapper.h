#pragma once

#include <memory>
#include <type_traits> // std::is_arithmetic_v
#include <utility>     // std::move
#include <any>
#include <typeinfo>
#include <stdexcept>
#include "sapy/pobject.h"
#include "sapy/pstring.h"

namespace sapy{

class PAnyWrapper : public PObject{
public:
    template <typename T>
    PAnyWrapper(T val)
        : data_(std::move(val)) {}



    template <typename T>
    T unwrap() const{
        return std::any_cast<T>(data_);
    }


    template <typename U>
    operator U() const{
        return unwrap<U>();
    }

    virtual PString toString() const override;
    bool isString() const;
    PString getString() const;
private: 
    virtual void _print(std::ostream& os) const override;
    std::any data_;
};

}