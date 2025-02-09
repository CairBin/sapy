#pragma once
#include "sapy/pobject.h"
#include "sapy/pstring.h"
#include <type_traits>
#include <functional>

namespace sapy{

// Determine whether it is the same object (rather than value)
bool is(const PObject &a, const PObject &b);

// hash function
size_t hash(const PObject& obj);

template<typename T>
size_t len(const collection::PCollectionInterface<T>& collection){
    return collection.count();
}

size_t len(const PString& str);



}