#include "sapy/plist.h"
namespace sapy{

PString PList::toString() const{
    PString str = "[";
    for(size_t i = 0; i < _data.size(); i++){
        str = str + _data[i]->toString();
        if(i != _data.size() - 1){
            str = str +  ", ";
        }
    }
    str = str + "]";
    return str;
}
}