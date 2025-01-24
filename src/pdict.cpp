#include "sapy/pdict.h"

namespace sapy{

PString PDict::toString() const {
    PString result = "{";
    for(auto it = container_.begin(); it != container_.end(); it++){
        if(it->first.isString()){
            result += "\"" + it->first.toString() + "\"";
        }else{
            result += it->first.toString();
        }
        result += ": ";
        if(it->second.isString()){
            result += "\"" + it->second.toString() + "\"";
        }else{
            result += it->second.toString();
        }
        if(std::next(it) != container_.end()){
            result += ", ";
        }
    }
    result += "}";
    return result;
}

void PDict::_print(std::ostream &os) const {
    os << toString();
}

size_t PDict::HashFunc::operator()(const PAnyWrapper &obj) const {
    return obj.hash();
}

PAnyWrapper& PDict::operator[](const PAnyWrapper& key) {
    return container_[key];
}

const PAnyWrapper& PDict::operator[](const PAnyWrapper& key) const {
    auto it = container_.find(key);
    if (it == container_.end()) {
        throw std::out_of_range("Key not found in PDict");
    }
    return it->second;
}


}