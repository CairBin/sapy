#pragma once 


#include "sapy/panywrapper.h"
#include "sapy/piterator.h"
#include "sapy/pobject.h"
#include "sapy/pstring.h"
#include "sapy/pconnection.h"
#include <unordered_set>
#include <iostream>

namespace sapy {

template <typename T>
class PSetT : public PObject, public PConnection{
public:

    // template <typename... Args>
    // inline void append(Args &&...args) {
    //     container_.insert(std::forward<Args>(args)...);
    // }

    inline void clear() {
        container_.clear();
    }

    virtual inline size_t size() const override{
        return container_.size();
    }

    inline bool remove(const T &elem) {
        return container_.erase(elem);
    }

    inline bool contains(const T &elem) const {
        return container_.find(elem) != container_.end();
    }


    struct HashFunc {
        // can be optimized!!!
        inline size_t operator()(const PAnyWrapper &obj) const{
            return obj.hash();
        }
    };

public: 
    PSetT() = default;
    PSetT(const PSetT& other) : container_(other.container_){};
    PSetT(std::initializer_list<PAnyWrapper> init) : container_(init){};
    inline size_t hash() const override{
        size_t result = 0;
        for (auto it = container_.begin(); it != container_.end(); ++it) {
            result ^= it->hash();
        }
        return result;
    }
    PString toString() const override{
        if(container_.empty()){
            return "set()";
        }
        PString result = "{";
        for (auto it = container_.begin(); it != container_.end(); ++it) {
            PAnyWrapper elem = *it;
            result += (elem.isString()?  "\"" + elem.toString() + "\"" : elem.toString());
            if (std::next(it) != container_.end()) {
                result += ", ";
            }
        }
        result += "}";
        return result;
    }
    inline void add(const PAnyWrapper& elem){
        container_.insert(elem);
    }
    inline PSetT copy() const{
        PSetT result;
        for (auto it = container_.begin(); it != container_.end(); ++it) {
            result.add(*it);
        }
        return result;
    }
    inline PSetT difference(const PSetT& other) const{
        PSetT result;
        for (auto it = container_.begin(); it != container_.end(); ++it) {
            if (!other.contains(*it)) {
                result.add(*it);
            }
        }
        return result;
    }
    inline void difference_update(const PSetT& other){
        for (auto it = container_.begin(); it != container_.end(); ) {
            if (other.contains(*it)) {
                it = container_.erase(it);
            } else {
                ++it;
            }
        }
    }
    inline void discard(const PAnyWrapper& elem){
        container_.erase(elem);
    }
    inline PSetT intersection(const PSetT& other) const{
        PSetT result;
        for (auto it = container_.begin(); it != container_.end(); ++it) {
            if (other.contains(*it)) {
                result.add(*it);
            }
        }
        return result;
    }
    inline void intersection_update(const PSetT& other){
        for (auto it = container_.begin(); it != container_.end(); ) {
            if (!other.contains(*it)) {
                it = container_.erase(it);
            } else {
                ++it;
            }
        }
    }
    inline bool isdisjoint(const PSetT& other) const{
        for (auto it = container_.begin(); it != container_.end(); ++it) {
            if (other.contains(*it)) {
                return false;
            }
        }
        return true;
    }
    inline bool issubset(const PSetT& other) const{
        for (auto it = container_.begin(); it != container_.end(); ++it) {
            if (!other.contains(*it)) {
                return false;
            }
        }
        return true;
    }
    inline bool issuperset(const PSetT& other) const{
        return other.issubset(*this);
    }
    inline T pop(){
        if (container_.empty()) {
            throw std::out_of_range("pop from an empty set");
        }
        auto it = container_.begin();
        T result = *it;
        container_.erase(it);
        return result;
    }
    PSetT symmetric_difference(const PSetT& other) const{
        auto s1 = difference(other);
        auto s2 = other.difference(*this);
        return s1.union_(s2);
    }
    void symmetric_difference_update(const PSetT& other){
        auto s1 = difference(other);
        auto s2 = other.difference(*this);
        update(s1.union_(s2));
    }
    PSetT union_(const PSetT& other) const{
        PSetT result = copy();
        for (auto it = other.container_.begin(); it != other.container_.end(); ++it) {
            result.add(*it);
        }
        return result;
    }
    void update(const PSetT& other){
        for (auto it = other.container_.begin(); it != other.container_.end(); ++it) {
            add(*it);
        }
    }
    
    PSetT operator-(const PSetT& other) const{
        return difference(other);
    }
    PSetT operator-(const T& other) const{
        PSetT result = copy();
        result.discard(other);
        return result;
    }
    PSetT& operator-= (const PSetT& other){
        difference_update(other);
        return *this;
    }
    PSetT& operator-= (const T& other){
        discard(other);
        return *this;
    }
    bool operator==(const PSetT& other) const{
        if (container_.size() != other.container_.size()) {
            return false;
        }
        for (auto it = container_.begin(); it != container_.end(); ++it) {
            if (!other.contains(*it)) {
                return false;
            }
        }
        return true;
    }
    inline bool operator!=(const PSetT& other) const {
        return !(*this == other);
    }
    inline bool operator<(const PSetT& other) const {
        return issubset(other) && size() < other.size();
    }
    inline bool operator<=(const PSetT& other) const {
        return issubset(other);
    }
    inline bool operator>(const PSetT& other) const {
        return !(*this <= other);
    }
    inline bool operator>=(const PSetT& other) const {
        return !(*this < other);
    }


    using iterator = std::unordered_set<PAnyWrapper, HashFunc>::iterator;
    using const_iterator = std::unordered_set<PAnyWrapper, HashFunc>::const_iterator;
    using value_type = PAnyWrapper;
    using const_value_type = const PAnyWrapper;
    inline PIterator<PSetT> begin(){
        return container_.begin();
    }
    inline PIterator<PSetT> end(){
        return container_.end();
    }
    inline const PConstIterator<PSetT> cbegin() const{
        return container_.begin();
    }
    inline const PConstIterator<PSetT> cend() const{
        return container_.end();
    }

private:
    inline virtual void _print(std::ostream& os) const override{
        os << toString();
    }
    std::unordered_set<PAnyWrapper, HashFunc> container_;

};
}