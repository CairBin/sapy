#pragma once 

#include "sapy/pobject.h"
#include "sapy/pstring.h"
#include <iostream>
#include "sapy/collection/phashset.h"
#include "sapy/panywrapper.h"

namespace sapy {

class PSet : public PObject, public collection::PHashSet<PAnyWrapper>{
    
/********************PObject***************************** */
public:
    size_t hash() const override;
    PString toString() const override;

public:
    inline size_t size() const {
        return count();
    }
    PSet copy() const;
    PSet difference(const PSet& other) const;
    void difference_update(const PSet& other);
    void discard(const PAnyWrapper& elem);
    PSet intersection(const PSet& other) const;
    void intersection_update(const PSet& other);
    bool isdisjoint(const PSet& other) const;
    bool issubset(const PSet &other) const;
    bool issuperset(const PSet &other) const;
    PAnyWrapper pop();
    PSet symmetric_difference(const PSet& other) const;
    void symmetric_difference_update(const PSet& other);
    PSet union_(const PSet &other) const;
    void update(const PSet &other);
    PSet operator-(const PSet &other) const;
    PSet operator-(const PAnyWrapper &other) const;
    bool operator==(const PSet &other) const;
    inline bool operator!=(const PSet& other) const{
        return !(*this == other);
    }
    inline bool operator<(const PSet& other) const {
        return issubset(other) && size() < other.size();
    }
    inline bool operator>(const PSet& other) const {
        return !(*this <= other);
    }
    inline bool operator<=(const PSet& other) const {
        return issubset(other);
    }
public:
    using collection::PHashSet<PAnyWrapper>::PHashSet;

private:
    virtual void _print(std::ostream& os) const override;
};

}