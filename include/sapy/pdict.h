#pragma once
#include "sapy/panywrapper.h"
#include "sapy/pobject.h"
#include "sapy/collection/phashdict.h"
#include <unordered_map>
#include <initializer_list>
#include <algorithm>

#include "sapy/panywrapper.h"

namespace sapy{


class PDict : public PObject, public collection::PHashDict<PAnyWrapper, PAnyWrapper>{
public:
    PDict() {}
public:
    PString toString() const override;
public:
    inline size_t size() const{
        return this->count();
    }
    
    inline bool contains(const PAnyWrapper& key) const{
        return containsKey(key);
    }

    bool operator==(const PDict& other) const;
    inline bool operator!=(const PDict& other) const{
        return !(*this == other);
    }

    inline bool operator<(const PDict &other) const
    {
        throw std::runtime_error("Unsupported type for PDict < operator");
        return false;
    }
    inline bool operator>(const PDict &other) const
    {
        throw std::runtime_error("Unsupported type for PDict > operator");
        return false;
    }
    inline bool operator<=(const PDict &other) const
    {
        throw std::runtime_error("Unsupported type for PDict <= operator");
        return false;
    }
    inline bool operator>=(const PDict &other) const
    {
        throw std::runtime_error("Unsupported type for PDict >= operator");
        return false;
    }
public:
    using collection::PHashDict<PAnyWrapper, PAnyWrapper>::PHashDict;

private:
    virtual void _print(std::ostream &os) const override;
};

    
}