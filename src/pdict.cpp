#include "sapy/pdict.h"

namespace sapy{

PString PDict::toString() const {
    PString result = "{";
    for(auto it = cbegin(); it != cend(); it++){
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
        if(std::next(it) != cend()){
            result += ", ";
        }
    }
    result += "}";
    return result;
}

void PDict::_print(std::ostream &os) const {
    os << toString();
}


bool PDict::operator==(const PDict& other) const {
    if (count() != other.count()) {
        return false;
    }
    for (auto it = cbegin(); it != cend(); ++it) {
        // auto other_it = other.find(it->first);
        // if (other_it == other.cend() || it->second != other_it->second) {
        //     return false;
        // }
        if(other[it->first] != it->second)
            return false;
    }
    return true;
}

}