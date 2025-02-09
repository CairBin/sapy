#pragma once
#include "sapy/pobject.h"
#include "sapy/collection/plist.h"
#include "sapy/collection/psorter.h"

namespace sapy{

class PAnyWrapper;
class PString;


class PList : public PObject, public collection::PList<PAnyWrapper>{
public:
    template<typename... Args>
    void append(Args&&... args) {
        (this->add(std::forward<Args>(args)), ...);
    }

    inline void appendSingle(const PAnyWrapper& item){
        this->add(item);
    }

    inline size_t size() const {
        return this->count();
    }

    inline void extend(const PList& other){
        this->addRange(other);
    }

    template <typename T>
    size_t index(const T& elem, size_t start, size_t end) const {
        size_t cnt = 0;
        for(auto it = cbegin() + start; it != cbegin() + end; ++it){
            if(*it == elem)
                return cnt;
            ++cnt;
        }

        return -1;
    }

    template <typename T>
    size_t index(const T &elem, size_t start) const
    {
        return index(elem, start, count());
    }

    template <typename T>
    size_t index(const T& elem) const{
        return index(elem, 0, count());
    }


    /*******************************************override operators******************************************* */
public:
    bool operator==(const PList& other) const;

    inline bool operator!=(const PList& other) const{
        return !(*this == other);
    }

    PList operator+(const PList& other) const {
        PList result;
        result.addRange(*this);
        result.addRange(other);
        return result;
    }

    PList& operator+=(const PList& other){
        this->addRange(other);
        return *this;
    }

    PList& operator=(const PList& other){
        return *this;
    }

    bool operator<(const PList& other) const;

    inline bool operator<=(const PList& other) const {
        return (*this) == other || (*this) < other;
    }

    inline bool operator>(const PList& other) const {
        return !(*this <= other);
    }

    inline bool operator>=(const PList& other) const {
        return !(*this < other);
    }

public:
    using collection::PList<PAnyWrapper>::PList;
public:
    void sort(
        std::function<PAnyWrapper(const PAnyWrapper&)> key = nullptr,
        bool reverse = false
    );

    PString toString() const override;
    

private:
    void _print(std::ostream &os) const override;
    
};



}