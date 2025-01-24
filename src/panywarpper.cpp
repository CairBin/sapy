#include "sapy/panywrapper.h"
#include "sapy/pstring.h"
namespace sapy {

PString PAnyWrapper::toString() const {
    const std::type_info& ti = data_.type();

    if (ti == typeid(int)) {
        int val = std::any_cast<int>(data_);
        return PString(std::to_string(val));
    } else if (ti == typeid(double)) {
        double val = std::any_cast<double>(data_);
        return PString(std::to_string(val));
    } else if (ti == typeid(std::string)) {
        return PString(std::any_cast<std::string>(data_));
    } else if (ti == typeid(const char*)) {
        return PString(std::string(std::any_cast<const char*>(data_)));
    } else if (ti == typeid(char)) {
        return PString(std::string(1, std::any_cast<char>(data_)));
    } else if (ti == typeid(PString)) {
        return std::any_cast<PString>(data_).toString();
    } else if (ti == typeid(PList)) {
        return std::any_cast<PList>(data_).toString();
    }
    return PString(std::string("<type: ") + ti.name() + ">");
}

void PAnyWrapper::_print(std::ostream& os) const {
    os << toString();
}

} // namespace sapy
