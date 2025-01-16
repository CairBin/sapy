#pragma once
#include "sapy/pobject.h"
#include "sapy/pstring.h"
#include <memory>
#include <type_traits> // std::is_arithmetic_v
#include <utility>     // std::move

namespace sapy{
template <typename T>
class PModel : public PObject{
public:
    explicit PModel(const T& val) : data_(val) {}
    explicit PModel(const T&& val) : data_(std::move(val)) {}
    PModel() = delete;

    PString toString() const override{

        if constexpr (std::is_same_v<T, const char> ||
                      std::is_same_v<T, char>){
            return PString("\'" + std::string(1, data_) + "\'");
        }
        else if constexpr (std::is_arithmetic_v<T>){
            return PString(std::to_string(data_));
        }
        else if constexpr (std::is_same_v<T, std::string> ||
                           std::is_same_v<T, const char *> ||
                           std::is_same_v<T, char *>){
            return PString(data_).toString();
        } else {
            return data_.toString();
        }

    }

    size_t hash() const override {
        if constexpr (std::is_same_v<T, const char> ||
                      std::is_same_v<T, char> ||
                      std::is_arithmetic_v<T>){
            std::hash<T> hasher;
            return hasher(data_);
        }
        else if constexpr (std::is_same_v<T, std::string> ||
                           std::is_same_v<T, const char *> ||
                           std::is_same_v<T, char *>){
            return PString(data_).hash();
        }
        else{
            return PObject::hash();
        }
    }
private:
    void _print(std::ostream& os) const override{
        os << toString().toStdString();
    }
    
    T data_;
};

class PAnyWrapper : public PObject{
public:
    template <typename T>
    PAnyWrapper(T val)
        : self_(std::make_shared<PModel<T>>(std::move(val))) {}

    PString toString() const{
        return self_->toString();
    }

    size_t hash() const override{
        return self_->hash();
    }

private:
    std::shared_ptr<const PObject> self_;
};

}