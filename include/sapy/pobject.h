#pragma once

#include <ostream>

namespace sapy{

class PString;

class PObject{
public:
    PObject(){}
    virtual ~PObject() {}
    virtual PObject* _clone() const = 0;
    virtual PString toString() const = 0;
private:  
    virtual void _print(std::ostream& os) const = 0;
    friend std::ostream& operator<<(std::ostream& os, const PObject& obj);
};

}