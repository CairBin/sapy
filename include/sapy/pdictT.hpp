#pragma once 

#include "sapy/pobject.h"
#include <unordered_map>
#include "sapy/putility.h"
#include <initializer_list>
#include "sapy/piterator.h"
#include "sapy/panywrapper.h"
#include "sapy/pconnection.h"
#include "sapy/pstring.h"

namespace sapy{
class PAnyWrapper;
template <typename KeyType,typename ValueType>
class PDictT : public PObject, public PConnection{
public:
    inline void clear(){
        container_.clear();
    }

    inline bool remove(const KeyType &key){
        auto it = container_.find(key);
        if (it == container_.end())
            return false;

        container_.erase(it);
        return true;
    }

    virtual inline size_t size() const override{
        return container_.size();
    }

    inline bool contains(const KeyType &key) const{
        return container_.find(key) != container_.end();  
    }
    struct HashFunc {
        // Can be optimized!!!
        size_t operator()(const PAnyWrapper &obj) const{
            return obj.hash();
        }
    };
public:
    PDictT() = default;
    inline PDictT(std::initializer_list<std::pair<KeyType, ValueType>> init){
        for (const auto &pair : init){
            container_[pair.first] = pair.second;
        }
    }
    virtual PString toString() const override{
        PString result = "{";
        for(auto it = container_.begin(); it != container_.end(); it++){
            PAnyWrapper first = it->first;
            PAnyWrapper second = it->second;
            if(first.isString()){
                result += "\"" + first.toString() + "\"";
            }else{
                result += first.toString();
            }
            result += ": ";
            if( second.isString()){
                result += "\"" + second.toString() + "\"";
            }else{
                result += second.toString();
            }
            if(std::next(it) != container_.end()){
                result += ", ";
            }
        }
        result += "}";
        return result;
    }
    
    inline KeyType& operator[](const KeyType& key){
        return container_[key];
    }
    inline const KeyType& operator[](const KeyType& key) const{
        auto it = container_.find(key);
        if (it == container_.end()) {
            throw std::out_of_range("Key not found in PDict");
        }
        return it->second;
    }

    inline bool operator==(const PDictT& other) const{
                if (container_.size() != other.container_.size()) {
            return false;
        }
        for (auto it = container_.begin(); it != container_.end(); ++it) {
            auto other_it = other.container_.find(it->first);
            if (other_it == other.container_.end() || it->second != other_it->second) {
                return false;
            }
        }
        return true;
    }
    inline bool operator!=(const PDictT& other) const {
        return !(*this == other);
    }

    inline bool operator<(const PDictT& other) const {
        throw std::runtime_error("Unsupported type for PDictT < operator");
        return false;
    }
    inline bool operator>(const PDictT& other) const {
        throw std::runtime_error("Unsupported type for PDictT > operator");
        return false;
    }
    inline bool operator<=(const PDictT& other) const {
        throw std::runtime_error("Unsupported type for PDictT <= operator");
        return false;
    }
    inline bool operator>=(const PDictT& other) const {
        throw std::runtime_error("Unsupported type for PDictT >= operator");
        return false;
    }
    
    using iterator = std::unordered_map<KeyType, ValueType, HashFunc>::iterator;
    using const_iterator = std::unordered_map<KeyType, ValueType, HashFunc>::const_iterator;  
    using value_type = std::pair<KeyType, ValueType>;
    using const_value_type = const std::pair<const KeyType, ValueType>;
    inline PIterator<PDictT> begin(){
        return (container_.begin());
    }

    inline PIterator<PDictT> end(){
        return (container_.end());
    }
    inline const PConstIterator<PDictT> begin() const{
        return (container_.cbegin());
    }
    inline const PConstIterator<PDictT> end() const{
        return (container_.cend());
    }

    inline const PConstIterator<PDictT> cbegin() const{
        return (container_.cbegin());
    }
    inline const PConstIterator<PDictT> cend() const{
        return (container_.cend());
    }


    inline iterator find(const KeyType& key){
        return iterator(container_.find(key));
    }
    

    inline const_iterator find(const KeyType& key) const{
        return const_iterator(container_.find(key));
    }


private:
    
    virtual void _print(std::ostream &os) const override{
        os << toString();
    }
    std::unordered_map<KeyType, ValueType, HashFunc> container_;
};

}