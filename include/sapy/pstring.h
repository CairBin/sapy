#pragma once 

#include "sapy/pobject.h"
#include <vector>
#include <cstdint>
#include <string>
#include <codecvt>
#include <locale>
#include <stdexcept>

namespace sapy{
class PList;
class PString : public PObject{
public:
    
    PString() {}
    PString(const PString&) = default;
    PString(const char* str) {
        _data = fromUTF8ToUTF32(std::string(str));    
    }
    PString(const std::u32string& str) : _data(str) {}
    PString(const std::string& str){
        _data = fromUTF8ToUTF32(str);
    }

    virtual ~PString(){}

    virtual PString toString() const override{
        return PString("\"") + *this + "\"";
    }
    
    PString* _clone() const override {
        return new PString(*this);
    }

    std::string toStdString() const{
        return fromUTF32ToUTF8(_data);;
    }
    
    PString lower() const;
    PString upper() const;
    PList split(const PString& delimiter)const;

    int toInt(){
        return std::stoi(toStdString());
    }

    size_t length() const{
        return _data.length();
    }

    bool startsWith(const PString& other) const{
        return _data.find(other._data) == 0;
    }

    bool endsWith(const PString& other) const{
        return _data.rfind(other._data) == _data.length() - other._data.length();
    }

    bool operator==(const PString& other) const {
        return _data == other._data;
    }

    bool operator!=(const PString& other) const {
        return !(*this == other);
    }
    PString operator[](size_t index) const {
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
        return PString(convert.to_bytes(_data[index]));
    }

    PString operator+(const PString& other) const {
        return PString(_data + other._data);
    }

    PString operator+(const char32_t& other) const {
        return PString(_data + other);
    }

    PString operator+(const char* other) const {
        return PString(_data + fromUTF8ToUTF32(std::string(other)));
    }
    PString operator+(const std::string& other) const {
        return PString(_data + fromUTF8ToUTF32(other));
    }

    PString operator+(const char& other) const {
        return PString(_data + fromUTF8ToUTF32(std::string(1, other)));
    }

    PString operator+=(const PString& other) {
        _data += other._data;
        return *this;
    }

    static std::u32string fromUTF8ToUTF32(const std::string& utf8Str) {
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
        return converter.from_bytes(utf8Str);
    }

    static std::string fromUTF32ToUTF8(const std::u32string& utf32Str) {
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
        return converter.to_bytes(utf32Str);
    }
private:
    virtual void _print(std::ostream& os) const override{
        os << toStdString();
    }
    std::u32string _data;
};


inline PString operator+(const char* lhs, const PString& rhs) {
    return PString(lhs) + rhs;  
}

inline PString operator+(const std::string& lhs, const PString& rhs) {
    return PString(lhs) + rhs;  
}


}
