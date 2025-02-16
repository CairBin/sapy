#pragma once

#include "sapy/panywrapper.h"
#include "sapy/piterator.h"
#include "sapy/pstring.h"
#include "sapy/pconnection.h"
#include <algorithm>
#include <functional>

namespace sapy{


template <typename T>
class PListT: public PObject, public PConnection{
public:

    template<typename... Args>
    void append(Args&&... args) {
        (data_.emplace_back(std::forward<Args>(args)), ...);
    }

    inline void clear(){
        data_.clear();
    }

    inline bool remove(const T &elem){
        auto it = std::find(data_.begin(), data_.end(), elem);
        if(it == data_.end()) return false;

        data_.erase(it);
        return true;
    }

    virtual inline size_t size() const override{
        return data_.size(); 
    }


    inline bool contains(const T &elem) const{
        auto res = std::find(data_.begin(), data_.end(), elem);
        return res != data_.end();
    }

/***********************override operators************************ */
public:
    inline T &operator[](size_t index){
        return data_[index];
    }

    inline const T &operator[](size_t index) const{
        return data_[index];
    }

    inline bool operator==(const PListT &other) const{
        if (data_.size() != other.data_.size()) {
            return false;
        }
        for (size_t i = 0; i < data_.size(); i++) {
            if (data_[i] != other.data_[i]) {
                return false;
            }
        }
        return true;
    }

    inline bool operator!=(const PListT &other) const{
        return !(*this == other);
    }

    PListT operator+(const PListT& other) const{
        std::vector<T> result;
        result.insert(result.end(), data_.begin(), data_.end());
        result.insert(result.end(), other.data_.begin(), other.data_.end());
        return PListT(std::move(result));
    }

    PListT& operator+=(const PListT& other){
        this->extend(other);
        return *this;
    }

    PListT& operator=(const PListT& other){
        return *this;
    }

    bool operator<(const PListT& other) const{
        if(data_.size() < other.data_.size()){
            return true;
        }
        for(size_t i = 0; i < data_.size(); i++){
            if(data_[i] < other.data_[i]){
                return true;
            }
        }
        return false;
    }

    inline bool operator<=(const PListT& other) const{
        return (*this)<other || (*this)==other;
    }

    inline bool operator>(const PListT& other) const{
        return (!((*this)<other)) && !(*this == other);
    }

    inline bool operator>=(const PListT& other) const{
        return !((*this)<other);
    }

    operator PListT<PAnyWrapper>() const{
        PListT<PAnyWrapper> result;
        for(auto &elem: data_){
            result.append(elem);
        }
        return result;
    }

    operator bool() const{
        return data_.size() > 0;
    }

public:

    PListT() = default;
    PListT(const std::vector<T>& init) : data_(init.begin(), init.end()) {}
    PListT(const std::initializer_list<T>& init) : data_(init){};
    // template <typename... Args>
    // PListT(Args&&... args) {
    //     (data_.emplace_back(std::forward<Args>(args)), ...);
    // }

    PString toString() const {
    PString result = "[";
    for (size_t i = 0; i < data_.size(); i++) {
        PAnyWrapper elem = data_[i];
        if(elem.isString()){
            result += "\"";
            result += elem.toString();
            result += "\"";
        }else{
        result +=elem.toString();
        }
        if (i + 1 < data_.size()) {
            result += ", ";
        }
    }
    result += "]";
    return result;
}

    
    using iterator = std::vector<T>::iterator;
    using const_iterator = std::vector<T>::const_iterator;  
    using value_type = T;
    using const_value_type = const T;
    inline PIterator<PListT> begin(){
        return (data_.begin());
    }

    inline const PConstIterator<PListT> begin() const{
        return (data_.cbegin());
    }

    inline const PConstIterator<PListT> end() const{
        return (data_.cend());
    }

    inline PIterator<PListT> end(){
        return (data_.end());
    }
    inline const PConstIterator<PListT> cbegin() const{
        return (data_.cbegin());
    }
    inline const PConstIterator<PListT> cend() const{
        return (data_.cend());
    }

    size_t count(const T& elem) const {
        return std::count(data_.begin(), data_.end(), elem);
    }

    void extend(const PListT& other){
        data_.insert(data_.end(), other.data_.begin(), other.data_.end());
    }

    void extend(const std::initializer_list<T>& init){
        data_.insert(data_.end(), init);
    }

    inline void appendSingle(const T &item){
        data_.emplace_back(item);
    }

    T pop(int index = -1){
        if(index < 0){
            index = data_.size() + index;
        }
        if(index < 0 || index >= data_.size()){
            throw std::runtime_error("Index out of range.");
        }
        T result = data_[index];
        data_.erase(data_.begin() + index);
        return result;
    }

    size_t index(const T& elem, size_t start, size_t end) const {
        auto it = find(data_.begin() + start, data_.begin() + end, elem);
        if (it == data_.end())
            throw std::runtime_error("The elem is not in list.");

        return it - data_.begin() + start;
    }

    size_t index(const T& elem, size_t start) const {
        return index(elem, start, data_.size());
    }



    size_t index(const T& elem) const{
        return index(elem, 0, data_.size());
    }


    void insert(size_t pos, const T& elem){
        data_.insert(data_.begin() + pos, elem);
    }

    void reverse(){
        std::reverse(data_.begin(), data_.end());
    }

    inline void sort(
        std::function<bool(const T&, const T&)> cmp = nullptr,
        std::function<T(const T&)> key = nullptr,
        bool reverse = false
    ) {
        if (key) {
            if (cmp) {
                std::sort(data_.begin(), data_.end(), [&](const T& a, const T& b) {
                    T key_a = key(a);
                    T key_b = key(b);
                    return reverse ? cmp(key_b, key_a) : cmp(key_a, key_b);
                });
            } else {
                std::sort(data_.begin(), data_.end(), [&](const T& a, const T& b) {
                    T key_a = key(a);
                    T key_b = key(b);
                    return reverse ? key_b < key_a : key_a < key_b;
                });
            }
        } else {
            if (cmp) {
                std::sort(data_.begin(), data_.end(), [&](const T& a, const T& b) {
                    return reverse ? cmp(b, a) : cmp(a, b);
                });
            } else {
                if (reverse) {
                    std::sort(data_.begin(), data_.end(), std::greater<T>());
                } else {
                    std::sort(data_.begin(), data_.end(), std::less<T>());
                }
            }
        }
    }

private:
    virtual inline void _print(std::ostream &os) const override{
        os << toString();
    }

private:
    std::vector<T> data_; // container

};



}