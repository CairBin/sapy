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


PRange range(int end){
    return range(0, end);
}



PRange range(int start, int end, int step){
    if(step == 0){
        std::runtime_error("range() arg 3 must not be zero");
    }
    return PRange (start,end, step);;
}

}