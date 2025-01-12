#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <type_traits> // std::is_arithmetic_v
#include <utility>     // std::move
#include "sapy/pstring.h"

namespace sapy{

template <typename T>
class PListModel : public PObject {
public:
    explicit PListModel(const T& val) : data_(val) {}
    explicit PListModel(T&& val)      : data_(std::move(val)) {}

    PString toString() const override {
        if constexpr (std::is_same_v<T, const char> || 
                          std::is_same_v<T, char>        ) {
            return PString("\'" + std::string(1, data_) + "\'");
        }
        else if constexpr (std::is_arithmetic_v<T>) {
            return PString(std::to_string(data_));

        }
        else if constexpr (std::is_same_v<T, std::string> || 
                          std::is_same_v<T, const char*>  ||
                          std::is_same_v<T, char*>        ) {
            return PString(data_).toString();
        }
        else {
            return data_.toString();
        }
    }

private:
    void _print(std::ostream& os) const override{
        os << toString().toStdString();
    }
    T data_;
};


class PListAnyWrapper {
public:
    template <typename T>
    PListAnyWrapper(T val)
        : self_(std::make_shared<PListModel<T>>(std::move(val))) {}

    PString toString() const {
        return self_->toString();
    }

private:
    std::shared_ptr<const PObject> self_;
};


class PList : public PObject {
public:
    template<typename... Args>
    void append(Args&&... args) {
    (data_.emplace_back(std::forward<Args>(args)), ...);
    }

    PString toString() const;
private:
    virtual void _print(std::ostream& os) const override{
        os << toString();
    }
    std::vector<PListAnyWrapper> data_;
};



}