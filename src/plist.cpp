#include "sapy/plist.h"
namespace sapy{



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