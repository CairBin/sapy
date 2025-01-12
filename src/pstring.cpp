
#include "sapy/pstring.h"
#include "sapy/plist.h"
namespace sapy{

int PString::toInt(){
    return std::stoi(toStdString());
}


PList PString::split(const PString& delimiter) const{
    size_t pos = 0;
    size_t prevPos = 0;
    PList result;
    while((pos = _data.find(delimiter._data, prevPos)) != std::u32string::npos){
        result.append(PString(_data.substr(prevPos, pos - prevPos)));
        prevPos = pos + delimiter._data.length();
    }
    result.append(PString(_data.substr(prevPos)));
    return result;
}

}

