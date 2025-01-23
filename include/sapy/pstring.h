#pragma once 

#include "sapy/pobject.h"
#include <vector>
#include <cstdint>
#include <string>
#include <codecvt>
#include <locale>
#include <stdexcept>
#include <iostream>
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
    PString(const char32_t& c){
        _data.push_back(c);
    }

    virtual ~PString(){}

    virtual PString toString() const override{
        return PString("\"") + *this + "\"";
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

    PString lstrip(PString __strp_str = "\r\n\t ") const{
        size_t pos = _data.find_first_not_of(__strp_str._data);
        return PString(_data.substr(pos));
    }
    PString rstrip(PString __strp_str = "\r\n\t ") const{
        size_t pos = _data.find_last_not_of(__strp_str._data);
        return PString(_data.substr(0, pos + 1));
    }
    PString strip(PString __strp_str = "\r\n\t ") const{
        return lstrip(__strp_str).rstrip(__strp_str);
    }  

    bool startsWith(const PString& other) const{
        return _data.find(other._data) == 0;
    }

    bool startswith(const PString& other) const{
        return startsWith(other);
    }

    bool endsWith(const PString& other) const{
        return _data.rfind(other._data) == _data.length() - other._data.length();
    }

    bool endswith(const PString& other) const{
        return endsWith(other);
    }

    PString captilize() const{
        if (_data.length() == 0) return PString();
        return PString(static_cast<char32_t>(std::towupper(_data[0]))) + PString(_data.substr(1)).lower();
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

    PString& operator+=(const PString& other) {
        _data += other._data;
        return *this;
    }
    
    PString& operator+=(const char32_t& other) {
        _data += other;
        return *this;
    }
    PString& operator+=(const char* other) {
        _data += fromUTF8ToUTF32(std::string(other));
        return *this;
    }

    PString& operator+=(const char &other) {
        //_data += fromUTF8ToUTF32(std::string(1, other));
        _data += static_cast<char32_t>(other);
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

    size_t hash() const override {
        std::hash<std::u32string> hasher;
        return hasher(_data);
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
