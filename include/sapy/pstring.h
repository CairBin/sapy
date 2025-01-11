#pragma once 

#include "sapy/pobject.h"

namespace sapy{

class PString : public PObject{
public:
    PString(const std::string& str) : str(str){}
    virtual ~PString(){}

    virtual PString toString() const override{
        return *this;
    }
    
    std::string toStdString() const{
        return str;
    }
    
    int toInt();  
    
private:
    virtual void _print(std::ostream& os) const override{
        os << str;
    }
    std::string str;
};
}
