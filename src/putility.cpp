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


PListT<int> range(int start){
    return range(0, start);
}

PListT<int> range(int start, int end, int step){
    PListT<int> result;
    if(step == 0){
        std::runtime_error("range() arg 3 must not be zero");
    }
    for(int i = start; step > 0 ? i < end : i > end; i+=step){
        result.append(i);
    }
    return result;
}

}