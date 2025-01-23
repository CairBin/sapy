#pragma once 

#include "sapy/pobject.h"
#include <vector>
#include <cstdint>
#include <string>
#include <codecvt>
#include <locale>
#include <stdexcept>
#include <iostream>
#include <format>
#include "sapy/pbytes.h"
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

    PString caseflod() const{
        return lower();
    }

    PString center(size_t width, char fillchar=' ') const{
        auto fill = PString(fillchar);
        if (width <= _data.length()) return *this;
        size_t pad = width - _data.length();
        size_t pad_left = pad / 2;
        size_t pad_right = pad - pad_left;
        return fill * pad_left + *this + fill * pad_right;
    }

    PString substr(size_t start, size_t end=std::u32string::npos) const{
        return PString(_data.substr(start, end-start));
    }

    size_t count(const PString& sub, size_t start=0, size_t end=std::u32string::npos) const{
        size_t count = 0;
        size_t pos = start;
        std::cout << "_data = " << PString(_data) << std::endl;
        std::cout << "sub = " << PString(sub._data) << std::endl;
        std::cout << "start = " << start << std::endl;
        std::cout << "end = " << end << std::endl;
        std::cout << "_data.substr = " << PString(_data.substr(start, end-start)) << std::endl;
        while((pos = _data.substr(start, end-start).find(sub._data, pos)) != std::u32string::npos){
            if (pos >= end) break;
            count++;
            pos += sub._data.length();
        }
        return count;
    }

    // PBytes encode(const PString& encoding="utf-8", const PString& errors="strict") const{
    //     // if(encoding == "utf-8"){
    //     //     std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
    //     // }
    //     throw std::runtime_error("Not implemented");
    // }

    size_t find(const PString& sub, size_t start=0, size_t end=std::u32string::npos) const{
        size_t pos = _data.substr(start, end-start).find(sub._data);
        if (pos == std::u32string::npos) return -1;
        return pos;
    }

    template <typename... Args>
    PString format(Args&&... args) const{
        return PString(std::vformat(this->toStdString(), std::make_format_args(args...)));
    }

    size_t index(const PString& sub, size_t start=0, size_t end=std::u32string::npos) const{
        size_t pos = find(sub, start, end);
        if (pos == -1) throw std::runtime_error("substring not found");
        return pos;
    }

    bool isalnum() const{
        if(_data.length() == 0) return false;
        for(auto c : _data){
            if (!std::iswalnum(c)) return false;
        }
        return true;
    }

    bool isalpha() const{
        if(_data.length() == 0) return false;
        for(auto c : _data){
            if (!std::iswalpha(c)) return false;
        }
        return true;
    }

    bool isascii() const{
        if(_data.length() == 0) return false;
        for(auto c : _data){
            if (c > 0x7f) return false;
        }
        return true;
    }

    bool isdecimal() const{
        if(_data.length() == 0) return false;
        for(auto c : _data){
            if (!std::iswdigit(c)) return false;  // TODO
        }
        return true;
    }

    bool isdigit() const{
        if(_data.length() == 0) return false;
        for(auto c : _data){
            if (!std::iswdigit(c)) return false;
        }
    }

    bool isidentifier() const{
        if(_data.length() == 0) return false;
        if (std::iswdigit(_data[0])) return false;
        for(auto c : _data.substr(1)){
            if (!std::iswalnum(c) && c != '_') return false;
        }
        return true;
    }

    bool islower() const{
        if(_data.length() == 0) return false;
        bool cased = false;
        for(auto c : _data){
            if(std::iswalpha(c)){
                if(!std::iswlower(c)) return false;
                cased = true;
            }
        }
        return cased;
    }

    bool isnumeric() const{
        if(_data.length() == 0) return false;
        for(auto c : _data){
            if (!std::iswdigit(c)) return false;  // TODO
        }
        return true;
    }

    bool isprintable() const{
        if(_data.length() == 0) return true;
        for(auto c : _data){
            if (!std::iswprint(c)) return false;
        }
        return true;
    }

    bool isspace() const{
        if(_data.length() == 0) return false;
        for(auto c : _data){
            if (!std::iswspace(c)) return false;
        }
        return true;
    }

    bool istitle() const{
        bool cased = false;
        for(size_t i=0; i< _data.size(); i++){
            if(!std::iswalpha(_data[i])){
                cased = false;
                continue;
            }
            if (std::iswupper(_data[i])){
                if (cased) return false;
                cased = true;
            }
            else if (std::iswlower(_data[i])){
                if (!cased) return false;
            }
        }
        return cased;
    }

    bool isupper() const{
        if(_data.length() == 0) return false;
        bool cased = false;
        for(auto c : _data){
            if (std::iswalpha(c)){
                if(!std::iswupper(c)) return false;
                cased = true;
            }
        }
        return cased;
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

    PString operator*(size_t n) const {
        std::u32string newStr;
        for(size_t i = 0; i < n; i++){
            newStr += _data;
        }
        return PString(newStr);
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

    PString& operator*= (size_t n){
        std::u32string newStr;
        for(size_t i = 0; i < n; i++){
            newStr += _data;
        }
        _data = newStr;
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
