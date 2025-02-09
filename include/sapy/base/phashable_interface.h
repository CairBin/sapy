#pragma once

#include <iostream>
#include <functional>
#include <type_traits>

namespace sapy{
namespace base{

class PHashableInterface {
public:
    virtual size_t hash() const = 0; // 纯虚函数
};

template <typename T, typename = void>
struct has_hash_method : std::false_type {};

template <typename T>
struct has_hash_method<T, std::void_t<decltype(std::declval<T>().hash())>> : std::true_type {};


template <typename T>
class DefaultHashFunc {
public:
    size_t operator()(const T& key) const {
        if constexpr (has_hash_method<T>::value) {
            return key.hash(); 
        } else {
            std::hash<T> hasher;
            return hasher(key);
        }
    }
};

}
}