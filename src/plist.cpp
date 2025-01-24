#include "sapy/plist.h"
namespace sapy{


void PList::_print(std::ostream& os) const{
    os << toString();
}

PString PList::toString() const {
    PString result = "[";
    for (size_t i = 0; i < data_.size(); i++) {
        result += data_[i].toString();
        if (i + 1 < data_.size()) {
            result += ", ";
        }
    }
    result += "]";
    return result;
}
}