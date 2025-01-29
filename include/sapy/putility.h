#pragma once
#include "sapy/pobject.h"
#include "sapy/pcollection_interface.h"
#include "sapy/pstring.h"
#include <type_traits>

namespace sapy{

// Determine whether it is the same object (rather than value)
bool is(const PObject &a, const PObject &b);

// hash function
size_t hash(const PObject& obj);

template<typename T>
size_t len(const PCollectionInterface<T>& collection){
    return collection.size();
}

size_t len(const PString& str);

template <typename T>
T reversed(T obj){
    // PReversableInterface is base of T
    /*
    * class PReversableInterface{};
    * class T : public PReversableInterface{};
    */
    if(!std::is_base_of_v<PReversableInterface, T>){
        throw std::runtime_error("Not implement PReversableInterface");
    }

    obj.reverse();
    return obj;
}

}