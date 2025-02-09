#pragma once

#include <ostream>
#include "sapy/base/phashable_interface.h"

namespace sapy{

class PString;

class PObject : public base::PHashableInterface{
public:
    PObject(){}
    virtual ~PObject() {}
    virtual PString toString() const = 0;
    virtual size_t hash() const {
        return reinterpret_cast<size_t>(this);
    }
private:  
    virtual void _print(std::ostream& os) const = 0;
    friend std::ostream& operator<<(std::ostream& os, const PObject& obj);

};


}