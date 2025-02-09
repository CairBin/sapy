#pragma once

#include "sapy/collection/pdict_interface.h"
#include <unordered_map>
#include "sapy/base/phashable_interface.h"

namespace sapy{

namespace collection{

template <typename TKey, typename TValue>
using PHashDictIterator = collection::FromStlIteratorBaseTemplate<typename std::unordered_map<TKey, TValue>::iterator, typename collection::PIteratorInterface<PKeyValuePair<const TKey, TValue>>, PKeyValuePair<const TKey, TValue>>;

template <typename TKey, typename TValue>
using PHashDictConstIterator = collection::FromStlConstIteratorBaseTemplate<typename std::unordered_map<TKey, TValue>::const_iterator, typename collection::PConstIteratorInterface<PKeyValuePair<const TKey, TValue>>, PKeyValuePair<const TKey, TValue>>;



template <typename TKey, typename TValue>
class PHashDict : public PDictInterface<TKey, TValue>{
public:
    virtual size_t count() const override{
        return container_.size();
    }

    void add(const PKeyValuePair<TKey, TValue> &item) override {
        container_.emplace(item);
    };

    void clear(){
        container_.clear();
    }

    bool contains(const PKeyValuePair<TKey, TValue> &item) const override{
        return container_.contains(item);
    }


    bool remove(const PKeyValuePair<TKey, TValue>& item) override {
        for (auto it = container_.begin(); it != container_.end(); ++it){
            if (*it == item){
                container_.erase(it);
                return true;
            }
        }
        return false;
    }

    void insert(const TKey &key, const TValue &val) override {
        container_.emplace(PKeyValuePair(key, val));
    }

    bool containsKey(const TKey &key) const override {
        size_t n = container_.count(key);
        return n!=0;
    }

    bool remove(const TKey &key) override {
        for(auto it = container_.begin(); it != container_.end(); ++it){
            if(it->first == key){
                container_.erase(it);
                return true;
            }
        }

        return false;
    }

    TValue& operator[](const TKey& key) override {
        return container_[key];
    }

    const TValue& operator[](const TKey& key) const override{
        return container_.at(key);
    }

public:
    /**
     * @description:  Determines whether the dict contains a specific value.
     * @param val {const TValue& val}
     * @return The value to locate in the dict. The value can be null for reference types.
     */
    bool containsValue(const TValue& val) const {
        for(auto it = container_.begin(); it != end(); ++it){
            if(it->second == val)
                return true;
        }

        return false;
    }

    /**
     * @description: Attempts to add the specified key and value to the dictionary.
     * @param key {const TKey&} The key of the element to add.
     * @param val {const TValue&} The value of the element to add.
     * @return true if the key/value pair was added to the dictionary successfully; otherwise, false.
     */
    bool tryAdd(const TKey& key, const TValue& val){
        if(container_.count(key)){
            return false;
        }

        this->insert(key, val);
        return true;
    }


public:
    PIteratorInterface<PKeyValuePair<const TKey, TValue>> begin() override{
        return (PIteratorInterface<PKeyValuePair<const TKey, TValue>>)PHashDictIterator<const TKey, TValue>(container_.begin());
    }

    PConstIteratorInterface<PKeyValuePair<const TKey, TValue>> cbegin() const override{
        return (PConstIteratorInterface<PKeyValuePair<const TKey, TValue>>)PHashDictConstIterator<const TKey, TValue>(container_.cbegin());
    }

    PIteratorInterface<PKeyValuePair<const TKey, TValue>> end() override{
        return (PIteratorInterface<PKeyValuePair<const TKey, TValue>>)PHashDictIterator<const TKey, TValue>(container_.end());
    }

    PConstIteratorInterface<PKeyValuePair<const TKey, TValue>> cend() const override{
        return (PConstIteratorInterface<PKeyValuePair<const TKey, TValue>>)PHashDictConstIterator<const TKey, TValue>(container_.cend());
    }

public:
    PHashDict() {}
    PHashDict(const std::unordered_map<TKey, TValue>& container)
        : container_(container) {}

    PHashDict(const std::initializer_list<PKeyValuePair<TKey, TValue>>& init){
        for(const auto& pair : init){
            container_.emplace(pair);
        }
    }

    PHashDict(std::unordered_map<TKey, TValue>::iterator begin, std::unordered_map<TKey, TValue>::iterator end)
        : container_(begin, end){}
    PHashDict(const PHashDict& dict)
        : container_(dict.container_){}
    PHashDict(PHashDictIterator<TKey, TValue> begin, PHashDictIterator<TKey, TValue> end){
        while(begin != end){
            container_.emplace(PKeyValuePair<TKey, TValue>(*begin));
            ++begin;
        }
    }

    PHashDict(PHashDictConstIterator<TKey, TValue> begin, PHashDictConstIterator<TKey, TValue> end){
        while(begin != end){
            container_.emplace(PKeyValuePair<TKey, TValue>(*begin));
            ++begin;
        }
    }

/********************************************* */

public:
    std::unordered_map<TKey, TValue>& toStdContainerRef(){
        return container_;
    }

    const std::unordered_map<TKey, TValue>& toStdContainerRef() const {
        return container_;
    }

private:
    std::unordered_map<TKey, TValue, base::DefaultHashFunc<TKey> > container_;
};

}

}