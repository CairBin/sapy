#include "sapy/pbytes.h"

namespace sapy{

PString PBytes::toString() const {
    return PString(*this);
}

void PBytes::_print(std::ostream &os) const{
    os << toString();
}
}