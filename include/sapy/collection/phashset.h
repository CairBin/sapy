#pragma once
#include "sapy/collection/pset_interface.h"
#include <unordered_set>

namespace sapy{

namespace collection{

// template <typename T>
// using PHashSetIterator = collection::FromStlConstIteratorBaseTemplate<typename std::unordered_set<T>::iterator, typename collection::PConstIteratorInterface<T>, T>;

template <typename T>
using PHashSetConstIterator = collection::FromStlConstIteratorBaseTemplate<typename std::unordered_set<T>::const_iterator, typename collection::PConstIteratorInterface<T>, T>;


template <typename T>
class PHashSet : public PSetInterface<T>{
public:
    size_t count() const override {
        return container_.size();
    }

    void add(const T& item) override {
        container_.emplace(item);
    }

    void clear() override {
        container_.clear();
    }

    bool contains(const T& elem) const override {
        return container_.contains(elem);
    }


    bool remove(const T& item) override{
        auto it = container_.erase(item);
        return it != 0;
    }

    bool insert(const T& item) override{
        if(contains(item)) return false;
        container_.emplace(item);
        return true;
    }

    void exceptWith(const PSetInterface<T>& other) override{
        for (auto it = other.cbegin(); it != other.cend(); ++it){
            remove(*it);
        }
    }

    void intersectWith(const PSetInterface<T>& other) override{
        for(auto it = container_.begin(); it != container_.end(); ++it){
            if (other.contains(*it)) continue;

            it = container_.erase(it);
        }
    }

    bool isProperSubsetOf(const PSetInterface<T>& other) const override{
        size_t thisSize = count();
        size_t otherSize = other.count();
        if (thisSize >= otherSize) return false;

        for (auto it = container_.begin(); it != container_.end(); ++it){
            if (!other.contains(*it)) return false;
        }

        return true;
    }

    bool isProperSupersetOf(const PSetInterface<T>& other) const override{
        return other.isProperSubsetOf(*this);
    }

    bool isSubsetOf(const PSetInterface<T>& other) const override{
        size_t thisSize = count();
        size_t otherSize = other.count();

        if (thisSize > otherSize) return false;
        for (auto it = container_.begin(); it != container_.end(); ++it){
            if (!other.contains(*it))
                return false;
        }

        return true;
    }

    bool isSupersetOf(const PSetInterface<T>& other) const override{
        return other.isSubsetOf(*this);
    }

    bool overlaps(const PSetInterface<T>& other) const override{
        size_t thisSize = count();
        size_t otherSize = other.count();

        if (thisSize <= otherSize){
            for (auto it = container_.cbegin(); it != container_.cend(); ++it){
                if (other.contains(*it))
                    return true;
            }
            return false;
        }

        for (auto it = other.cbegin(); it != other.cend(); ++it){
            if (container_.contains(*it))
                return true;
        }

        return false;
    }

    bool setEquals(const PSetInterface<T>& other) const override{
        return isSubsetOf(other) && other.isSubsetOf(*this);
    }

    void symmetricExceptWith(const PSetInterface<T>& other) override{
        // A - (A ∩ B)
        // A is this, B is other
        size_t thisSize = count();
        size_t otherSize = other.count();

        // one of the two is an empty set 
        if (!thisSize || !otherSize) return;
        for(auto it = container_.begin(); it != container_.end(); ++it){
            if (container_.contains(*it) && other.contains(*it))
                it = container_.erase(it);
        }
    }

    void unionWith(const PSetInterface<T>& other){
        // A ∪ B
        // A is this, B is other
        size_t otherSize = other.count();
        // other is an empty set
        if (!otherSize) return;

        for (auto it = other.cbegin(); it != other.cend(); ++it){
            add(*it);
        }
    }

public:
    PIteratorInterface<T> begin() override{
        throw std::runtime_error("Cannot allow non-const iterator.");
        // return (PIteratorInterface<T>)PHashSetIterator<T>(container_.begin());
    }

    PConstIteratorInterface<T> cbegin() const override{
        return (PConstIteratorInterface<T>)PHashSetConstIterator<T>(container_.cbegin());
    }

    PIteratorInterface<T> end() override{
        throw std::runtime_error("Cannot allow non-const iterator.");
        // return (PIteratorInterface<T>)PHashSetIterator<T>(container_.end());
    }

    PConstIteratorInterface<T> cend() const override{
        return (PConstIteratorInterface<T>)PHashSetConstIterator<T>(container_.cend());
    }

public:
    PHashSet() {}
    PHashSet(const std::initializer_list<T> &init)
        : container_(init) {}
    PHashSet(const std::unordered_set<T> &st)
        : container_(st) {}
    PHashSet(std::unordered_set<T>::iterator begin, std::unordered_set<T>::iterator end)
        : container_(begin, end) {}
    PHashSet(std::unordered_set<T>::const_iterator cbegin, std::unordered_set<T>::const_iterator cend)
        : container_(cbegin, cend) {}


    PHashSet(PIteratorInterface<T> begin, PIteratorInterface<T> end)
    {
        while (begin != end)
        {
            container_.emplace(*begin);
            ++begin;
        }
    }

    PHashSet(PConstIteratorInterface<T> cbegin, PConstIteratorInterface<T> cend)
    {
        while (cbegin != cend)
        {
            container_.emplace(*cbegin);
            ++cbegin;
        }
    }


    PHashSet(const PHashSet<T> &other)
        : container_(other.container_) {}

    PHashSet &operator=(const PHashSet<T> &other){
        container_ = other.container_;
        return *this;
    }

/********************************************* */

public:
    std::unordered_set<T>& toStdContainerRef(){
        return container_;
    }

    const std::unordered_set<T>& toStdContainerRef() const {
        return container_;
    }

private:
    std::unordered_set<T, base::DefaultHashFunc<T> > container_;
};

}
}