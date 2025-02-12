#include "sapy/putility.h"

namespace sapy{
bool is(const PObject &a, const PObject &b){
    return &a == &b;
}

size_t hash(const PObject &obj){
    return obj.hash();
}

size_t len(const PString &str){
    return str.length();
}

size_t len(const PConnection& container){
    return container.size();
}

}