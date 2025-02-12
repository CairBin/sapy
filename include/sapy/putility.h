#pragma once
#include "sapy/pobject.h"
#include "sapy/pstring.h"
#include "sapy/pconnection.h"

namespace sapy{

// Determine whether it is the same object (rather than value)
bool is(const PObject &a, const PObject &b);

// hash function
size_t hash(const PObject& obj);

size_t len(const PString &str);


size_t len(const PConnection& container);


}