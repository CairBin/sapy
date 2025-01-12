
#include "sapy/pstring.h"
#include "sapy/plist.h"
namespace sapy{



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

PString PString::lower() const{
    std::u32string lowerStr;
    for(auto c : _data){
        lowerStr.push_back(std::towlower(c));
    }
    return PString(lowerStr);
}

PString PString::upper() const{
    std::u32string upperStr;
    for(auto c : _data){
        upperStr.push_back(std::towupper(c));
    }
    return PString(upperStr);
}


}

