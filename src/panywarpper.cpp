#include "sapy/panywrapper.h"
#include "sapy/pstring.h"
#include "sapy/pset.h"
#include <string>
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
        return PString((std::any_cast<const char*>(data_)));
    } else if (ti == typeid(char)) {
        return PString(std::string(1, std::any_cast<char>(data_)));
    } else if (ti == typeid(PString)) {
        return std::any_cast<PString>(data_);
    } else if (ti == typeid(PList)) {
        return std::any_cast<PList>(data_).toString();
    } else if (ti == typeid(PDict)) {
        return std::any_cast<PDict>(data_).toString();
    } else if (ti == typeid(PSet)) {
        return std::any_cast<PSet>(data_).toString();
    }
    return PString(std::string("<type: ") + ti.name() + ">");
}

bool PAnyWrapper::isString() const {
    const std::type_info& ti = data_.type();
    return ti == typeid(std::string) || ti == typeid(const char*) || 
           ti == typeid(char) || ti == typeid(PString) ||
           ti == typeid(char32_t) || ti == typeid(std::u32string);
}

void PAnyWrapper::_print(std::ostream& os) const {
    os << toString();
}

size_t PAnyWrapper::hash() const {
    const std::type_info& ti = data_.type();
    if (ti == typeid(int)) {
        return std::hash<int>{}(std::any_cast<int>(data_));
    } else if (ti == typeid(double)) {
        return std::hash<double>{}(std::any_cast<double>(data_));
    } else if (ti == typeid(std::string)) {
        //return std::hash<std::string>{}(std::any_cast<std::string>(data_));
        return PString(std::any_cast<std::string>(data_)).hash();
    } else if (ti == typeid(const char*)) {
        //return std::hash<std::string>{}(std::any_cast<const char*>(data_));
        return PString(std::any_cast<const char*>(data_)).hash();
    } else if (ti == typeid(char)) {
        return std::hash<char>{}(std::any_cast<char>(data_));
    } else if (ti == typeid(PString)) {
        return std::any_cast<PString>(data_).hash();
    } else {
        return reinterpret_cast<size_t>(this);
    }
}

} // namespace sapy
