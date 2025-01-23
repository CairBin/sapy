#pragma once
#include "sapy/pobject.h"
#include "sapy/pstring.h"
#include <memory>
#include <type_traits> // std::is_arithmetic_v
#include <utility>     // std::move
#include <any>
#include <typeinfo>
#include <stdexcept>

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
        : data_(std::move(val)) {}



    template <typename T>
    T unwrap() const
    {
        // 如果存的类型不是T，会抛出std::bad_any_cast异常
        return std::any_cast<T>(data_);
    }


    template <typename U>
    operator U() const
    {
        return unwrap<U>();
    }

    PString toString() const override
    {
        const std::type_info& ti = data_.type();

        if (ti == typeid(int)) {
            int val = std::any_cast<int>(data_);
            return PString(std::to_string(val));
        }
        else if (ti == typeid(double)) {
            double val = std::any_cast<double>(data_);
            return PString(std::to_string(val));
        }
        else if (ti == typeid(std::string)) {
            return PString(std::any_cast<std::string>(data_));
        }
        else if (ti == typeid(const char*)) {
            return PString(std::string(std::any_cast<const char*>(data_)));
        }
        else if (ti == typeid(char)) {
            return PString(std::string(1, std::any_cast<char>(data_)));
        }
        else if (ti == typeid(PString)) {
            return PString(std::any_cast<PString>(data_));
        }
        return PString(std::string("<type: ") + ti.name() + ">");
    }
private: 
    virtual void _print(std::ostream& os) const override{
        os << toString();
    }
    std::any data_;
};

// class PAnyWrapper : public PObject{
// public:
//     template <typename T>
//     PAnyWrapper(T val)
//         : self_(std::make_shared<PModel<T>>(std::move(val))) {}

//     PString toString() const{
//         return self_->toString();
//     }

//     size_t hash() const override{
//         return self_->hash();
//     }

//     auto getData(){
        
//     }

// private:
//     void _print(std::ostream& os) const override{
//         os << toString().toStdString();
//     }

// private:
//     std::shared_ptr<const PObject> self_;
// };

}