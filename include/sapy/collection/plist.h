#pragma once

#include "sapy/collection/plist_interface.h"

#include <vector>
#include <algorithm>
#include <functional>

namespace sapy{

namespace collection{

template <typename T>
using PListIterator = collection::FromStlIteratorBaseTemplate<typename std::vector<T>::iterator, typename collection::PIteratorInterface<T>, T>;

template <typename T>
using PListConstIterator = collection::FromStlConstIteratorBaseTemplate<typename std::vector<T>::const_iterator, typename collection::PConstIteratorInterface<T>, T>;

template <typename T>
using PListReverseIterator = collection::FromStlIteratorBaseTemplate<typename std::vector<T>::reverse_iterator, typename collection::PReverseIteratorInterface<T>, T>;

template <typename T>
using PListConstReverseIterator = collection::FromStlConstIteratorBaseTemplate<typename std::vector<T>::const_reverse_iterator , typename collection::PConstReverseIteratorInterface<T>, T>;


template <typename T>
class PList : public virtual PListInterface<T>{
public:
    size_t count() const override{
        return container_.size();
    }

    void add(const T& item) override{
        container_.emplace_back(item);
    }

    void clear() override{
        container_.clear();
    }

    bool contains(const T& elem) const override{
        auto it = std::find(container_.begin(), container_.end(), elem);
        return it != container_.end();
    }

    void copyTo(T* array, size_t index) const{
        for(size_t i = 0; i < container_.size(); ++i){
            array[index + i] = container_[i];
        }
    }

    bool remove(const T& item) override{
        for (auto it = container_.begin(); it != container_.end(); ++it){
            if (*it == item){
                container_.erase(it);
                return true;
            }
        }
        return false;
    }

    int indexOf(const T& item) const override{
        auto it = std::find(container_.begin(), container_.end(), item);
        if(it == container_.end()) return -1;

        return (int)(it - container_.begin());
    }

    void insert(size_t index, const T& item) override{
        container_.insert(container_.begin() + index, item);
    }

    void removeAt(size_t index) override{
        container_.erase(container_.begin() + index);
    }

    T& operator[](size_t index) override{
        return container_[index];
    }

    const T& operator[](size_t index) const override{
        return container_[index];
    }

    PIteratorInterface<T> begin() override{
        return (PIteratorInterface<T>)PListIterator<T>(container_.begin());
    }

    PConstIteratorInterface<T> cbegin() const override{
        return (PConstIteratorInterface<T>)PListConstIterator<T>(container_.cbegin());
    }

    PIteratorInterface<T> end() override{
        return (PIteratorInterface<T>)PListIterator<T>(container_.end());
    }

    PConstIteratorInterface<T> cend() const override{
        return (PConstIteratorInterface<T>)PListConstIterator<T>(container_.cend());
    }

    PReverseIteratorInterface<T> rbegin() override{
        return (PReverseIteratorInterface<T>)PListReverseIterator<T>(container_.rbegin());
    }

    PReverseIteratorInterface<T> rend() override{
        return (PReverseIteratorInterface<T>)PListReverseIterator<T>(container_.rend());
    }

    PConstReverseIteratorInterface<T> crbegin() const override{
        return (PConstReverseIteratorInterface<T>)PListConstReverseIterator<T>(container_.crbegin());
    }

    PConstReverseIteratorInterface<T> crend() const override{
        return (PConstReverseIteratorInterface<T>)PListConstReverseIterator<T>(container_.crend());
    }


public:
    /**
     * @description: Adds the elements of the specified collection to the end of the PList<T>.
     * @param collection {const PIterableInterface<T, T>&} The collection whose elements should be added to the end of the PList<T>.
     */
    void addRange(const PIterableInterface<T, T>& collection){
        for(auto it = collection.cbegin(); it != collection.cend(); ++it){
            container_.emplace_back(*it);
        }
    }

    /**
     * @description: Performs the specified action on each element of the PList<T>.
     * @param action {std::function<void(T&)>} call-back function
     */
    void forEach(std::function<void(T&)> action){
        for(auto it = container_.begin(); it != container_.end(); ++it){
            action(*it);
        }
    }

    /**
     * @description: Inserts the elements of a collection into the PList<T> at the specified index.
     * @param index {size_t} The zero-based index at which the new elements should be inserted.
     * @param collection {const PIterableInterface<T, T>&} The collection whose elements should be inserted into the PList<T>.
     */
    void insertRange(size_t index, const PIterableInterface<T, T>& collection){
        for (auto it = container_.begin(); it != container_.end(); ++it){
            insert(index++, *it);
        }
    }

    /**
     * @description: Removes a range of elements from the PList<T>.
     * @param remove {size_t} The zero-based starting index of the range of elements to remove.
     * @param count {size_t} The number of elements to remove.
     */
    void removeRange(size_t index, size_t count){
        container_.erase(container_.begin() + index, container_.begin() + index + count);
    }

    /**
     * @description: Reverses the order of the elements.
     */
    void reverse(){
        std::reverse(container_.begin(), container_.end());
    }

    /**
     * @description: Reverses the order of the elements in the specified range.
     * @param start {size_t} The zero-based starting index of the range to reverse.
     * @param count {size_t} The number of elements in the range to reverse.
     */
    void reverse(size_t start, size_t count){
        reverse(container_.begin() + start, container_.begin() + start + count);
    }

    /**
     * @description: Creates a shallow copy of a range of elements in the source List<T>.
     * @param list {PList<T>& list} target
     * @param start {size_t} The zero-based PList<T> index at which the range starts.
     * @param length {size_t} The length of the range.
     */
    void slice(PList<T>& list, size_t start, size_t length){
        auto it = container_.begin() + start;
        for(size_t i = 0; i < length; ++i){
            list.add(*it);
            ++it;
        }
    }

    /**
     * @description: Determines whether every element in the PList<T> matches the conditions defined by the specified predicate.
     * @param match {std::function<bool(const T&)>} condition call-back
     * @return true if every element in the PList<T> matches the conditions defined by the specified predicate; otherwise, false. If the list has no elements, the return value is true.
     */
    bool trueForAll(std::function<bool(const T&)> match) const{
        for(auto it = container_.begin(); it != container_.end(); ++it){
            if (!match(*it))
                return false;
        }
        return true;
    }

public:
    PList() = default;
    PList(const std::initializer_list<T>& init)
        : container_(init){}
    PList(const std::vector<T>& vec)
        : container_(vec){}
    PList(std::vector<T>::iterator begin, std::vector<T>::iterator end)
        : container_(begin, end){}
    PList(std::vector<T>::reverse_iterator rbegin, std::vector<T>::reverse_iterator rend)
        : container_(rbegin, rend){}
    PList(std::vector<T>::const_iterator cbegin, std::vector<T>::const_iterator cend)
        :container_(cbegin, cend){}
    PList(std::vector<T>::const_reverse_iterator crbegin, std::vector<T>::const_reverse_iterator crend)
        : container_(crbegin, crend) {}

    PList(PIteratorInterface<T> begin, PIteratorInterface<T> end){
        while(begin != end){
            container_.emplace_back(*begin);
            ++begin;
        }
    }

    PList(PConstIteratorInterface<T> cbegin, PConstIteratorInterface<T> cend){
        while(cbegin != cend){
            container_.emplace_back(*cbegin);
            ++cbegin;
        }
    }

    PList(PReverseIteratorInterface<T> rbegin, PReverseIteratorInterface<T> rend){
        while(rbegin != rend){
            container_.emplace_back(*rbegin);
            ++rbegin;
        }
    }

    PList(PConstReverseIteratorInterface<T> crbegin, PConstReverseIteratorInterface<T> crend){
        while(crbegin != crend){
            container_.emplace_back(*crbegin);
            ++crbegin;
        }
    }

    // PList()
    PList(const PList<T>& other)
        : container_(other.container_){}
    PList& operator=(const PList<T>& other){
        container_ = other.container_;
        return *this;
    }
    
/********************************************* */

public:
    std::vector<T>& toStdContainerRef(){
        return container_;
    }

    const std::vector<T>& toStdContainerRef() const {
        return container_;
    }

private: 
    std::vector<T> container_;
};

}

}