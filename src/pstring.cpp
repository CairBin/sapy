#include "sapy/pstring.h"
#include "sapy/plist.h" 
#include <codecvt>
#include <locale>
#include <stdexcept>
#include <iostream>
#include <format>

namespace sapy {



PString::PString() {}

PString::PString(const char* str) {
    _data = fromUTF8ToUTF32(std::string(str));
}

PString::PString(const std::u32string& str)
    : _data(str) {}

PString::PString(const std::string& str) {
    _data = fromUTF8ToUTF32(str);
}

PString::PString(char32_t c) {
    _data.push_back(c);
}

PString::~PString() {}




PString PString::toString() const {
    return PString("\"") + *this + "\"";
}

std::string PString::toStdString() const {
    return fromUTF32ToUTF8(_data);
}

int PString::toInt() const {
    return std::stoi(toStdString());
}

size_t PString::length() const {
    return _data.size();
}



PString PString::lstrip(const PString& __strp_str) const{
        size_t pos = _data.find_first_not_of(__strp_str._data);
        return PString(_data.substr(pos));
}

PString PString::rstrip(const PString& __strp_str) const{
    size_t pos = _data.find_last_not_of(__strp_str._data);
    return PString(_data.substr(0, pos + 1));
}
PString PString::strip(const PString& __strp_str) const{
    return lstrip(__strp_str).rstrip(__strp_str);
}  

bool PString::startsWith(const PString& other) const {
    return _data.rfind(other._data, 0) == 0;
}

bool PString::endsWith(const PString& other) const {

    if (other._data.size() > _data.size()) {
        return false;
    }
    return _data.compare(_data.size() - other._data.size(),
                         other._data.size(),
                         other._data) == 0;
}

PString PString::lower() const {
    std::u32string lowerStr;
    for (char32_t c : _data) {
        lowerStr.push_back(static_cast<char32_t>(std::towlower(static_cast<wint_t>(c))));
    }
    return PString(lowerStr);
}

PString PString::upper() const {
    std::u32string upperStr;
    for (char32_t c : _data) {
        upperStr.push_back(static_cast<char32_t>(std::towupper(static_cast<wint_t>(c))));
    }
    return PString(upperStr);
}



PList PString::split(const PString& delimiter) const {

    size_t pos = 0;
    size_t prevPos = 0;
    PList result;
    while ((pos = _data.find(delimiter._data, prevPos)) != std::u32string::npos) {
        result.append(PString(_data.substr(prevPos, pos - prevPos)));
        prevPos = pos + delimiter._data.size();
    }
    if (prevPos <= _data.size()) {
        result.append(PString(_data.substr(prevPos)));
    }
    return result;
}

PString PString::captilize() const {
    if (_data.empty()) {
        return PString();
    }
    return PString(std::towupper(_data[0])) + PString(_data.substr(1)).lower();
}

PString PString::caseflod() const {
    return lower(); // TODO
}

PString PString::center(size_t width, char fillchar) const {
    if (width <= _data.size()) {
        return *this;
    }
    size_t padSize = width - _data.size();
    size_t padLeft = padSize / 2;
    size_t padRight = padSize - padLeft;
    return PString(std::u32string(padLeft, fillchar) + _data + std::u32string(padRight, fillchar));
}

PString PString::substr(size_t start, size_t end) const {
    if (end == std::u32string::npos) {
        return PString(_data.substr(start));
    }
    return PString(_data.substr(start, end - start));
}

size_t PString::count(const PString& sub, size_t start, size_t end) const {
    size_t count = 0;
    size_t pos = start;
    while((pos = _data.substr(start, end-start).find(sub._data, pos)) != std::u32string::npos){
        if (pos >= end) break;
        count++;
        pos += sub._data.length();
    }
    return count;
}

size_t PString::find(const PString& sub, size_t start, size_t end) const {
    size_t pos = _data.substr(start, end-start).find(sub._data);
    if (pos == std::u32string::npos) return -1;
    return pos;
}

size_t PString::index(const PString& sub, size_t start, size_t end) const {
    size_t pos = find(sub, start, end);
    if (pos == -1) throw std::runtime_error("substring not found");
    return pos;
}

bool PString::isalnum() const{
    if(_data.length() == 0) return false;
    for(auto c : _data){
        if (!std::iswalnum(c)) return false;
    }
    return true;
}

bool PString::isalpha() const{
    if(_data.length() == 0) return false;
    for(auto c : _data){
        if (!std::iswalpha(c)) return false;
    }
    return true;
}

bool PString::isascii() const{
    if(_data.length() == 0) return false;
    for(auto c : _data){
        if (c > 0x7f) return false;
    }
    return true;
}

bool PString::isdecimal() const{
    if(_data.length() == 0) return false;
    for(auto c : _data){
        if (!std::iswdigit(c)) return false;  // TODO
    }
    return true;
}

bool PString::isdigit() const{
    if(_data.length() == 0) return false;
    for(auto c : _data){
        if (!std::iswdigit(c)) return false;
    }
    return true;
}

bool PString::isidentifier() const{
    if(_data.length() == 0) return false;
    if (std::iswdigit(_data[0])) return false;
    for(auto c : _data.substr(1)){
        if (!std::iswalnum(c) && c != '_') return false;
    }
    return true;
}

bool PString::islower() const{
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

bool PString::isnumeric() const{
    if(_data.length() == 0) return false;
    for(auto c : _data){
        if (!std::iswdigit(c)) return false;  // TODO
    }
    return true;
}

bool PString::isprintable() const{
    if(_data.length() == 0) return true;
    for(auto c : _data){
        if (!std::iswprint(c)) return false;
    }
    return true;
}

bool PString::isspace() const{
    if(_data.length() == 0) return false;
    for(auto c : _data){
        if (!std::iswspace(c)) return false;
    }
    return true;
}

bool PString::istitle() const{
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

bool PString::isupper() const{
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

PString PString::ljust(size_t width, char fillchar) const {
    if (width <= _data.size()) {
        return *this;
    }
    size_t padSize = width - _data.size();
    return PString(_data + std::u32string(padSize, fillchar));
}

PString PString::rjust(size_t width, char fillchar) const {
    if (width <= _data.size()) {
        return *this;
    }
    size_t padSize = width - _data.size();
    return PString(std::u32string(padSize, fillchar) + _data);
}

PDict PString::maketrans(PDict& x) {
    return x; // TODO
}



PDict PString::maketrans(const PString& x, const PString& y) {
    PDict result;
    if(x.length() != y.length()){
        throw std::runtime_error("the first two maketrans arguments must have equal length");
    }
    for (size_t i = 0; i < x.length(); i++) {
        result[x[i]] = y[i];
    }
    return result;
}

PDict PString::maketrans(const PString& x, const PString& y, const PString &z) {
    PDict result;
    if(x.length() != y.length() || x.length() != z.length()){
        throw std::runtime_error("the first two maketrans arguments must have equal length");
    }
    for(size_t i = 0; i < x.length(); i++){
        result[x[i]] = y[i];
    }
    for(size_t i = 0; i < z.length(); i++){
        result[z[i]] = PString();
    }
    return result;
}

PString PString::translate(const PDict& table) const{
    // PString result;
    // for(auto c : _data){
    //     auto it = table.find(PString(c));
    //     if(it == table.end()){
    //         result += c;
    //     }else{
    //         result += it->second;
    //     }
    // }
    // return result;
    return PString(); // TODO
}
PList PString::partition(const PString& sep) const{
    PList result;
    size_t pos = find(sep);
    if (pos == -1){
        result.append(*this, PString(), PString());
        return result;
    }
    result.append(substr(0, pos), sep, substr(pos + sep.length()));
    return result;
}

PString PString::remoteprefix(const PString& prefix) const{
    if (startsWith(prefix)){
        return substr(prefix.length());
    }
    return *this;
}

PString PString::removesuffix(const PString& suffix) const{
    if (endsWith(suffix)){
        return substr(0, length() - suffix.length());
    }
    return *this;
}

PString PString::replace(const PString& old, const PString& new_, size_t count) const{
    PString result;
    size_t pos = 0;
    size_t prevPos = 0;
    while ((pos = _data.find(old._data, prevPos)) != std::u32string::npos) {
        result += PString(_data.substr(prevPos, pos - prevPos));
        result += new_;
        prevPos = pos + old._data.size();
        if (count != std::u32string::npos) {
            count--;
            if (count == 0) {
                break;
            }
        }
    }
    if (prevPos <= _data.size()) {
        result += PString(_data.substr(prevPos));
    }
    return result;
}

std::u32string PString::fromUTF8ToUTF32(const std::string& utf8Str) {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
    return converter.from_bytes(utf8Str);
}

std::string PString::fromUTF32ToUTF8(const std::u32string& utf32Str) {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
    return converter.to_bytes(utf32Str);
}




bool PString::operator==(const PString& other) const {
    return _data == other._data;
}

bool PString::operator!=(const PString& other) const {
    return !(*this == other);
}

PString PString::operator[](size_t index) const {
    if (index >= _data.size()) {
        throw std::out_of_range("PString: index out of range");
    }

    auto singleChar32 = _data[index];
    std::u32string tmp(1, singleChar32);
    return PString(tmp);
}


PString PString::operator+(const PString& other) const {
    return PString(_data + other._data);
}

PString PString::operator+(char32_t other) const {
    return PString(_data + std::u32string(1, other));
}

PString PString::operator+(const char* other) const {
    return *this + PString(other);
}

PString PString::operator+(const std::string& other) const {
    return *this + PString(other);
}

PString PString::operator+(char other) const {
    std::u32string tmp = _data + std::u32string(1, static_cast<char32_t>(other));
    return PString(tmp);
}

PString PString::operator*(size_t n) const {
    std::u32string newStr;
    newStr.reserve(_data.size() * n);
    for (size_t i = 0; i < n; i++) {
        newStr += _data;
    }
    return PString(newStr);
}

PString& PString::operator*=(size_t n) {
    std::u32string newStr;
    newStr.reserve(_data.size() * n);
    for (size_t i = 0; i < n; i++) {
        newStr += _data;
    }
    _data = newStr;
    return *this;
}

// +=
PString& PString::operator+=(const PString& other) {
    _data += other._data;
    return *this;
}

PString& PString::operator+=(char32_t other) {
    _data.push_back(other);
    return *this;
}

PString& PString::operator+=(const char* other) {
    *this = *this + PString(other);
    return *this;
}

PString& PString::operator+=(char other) {
    _data.push_back(static_cast<char32_t>(other));
    return *this;
}

PString& PString::operator+=(const PAnyWrapper& other) {
    *this += other.toString();
    return *this;
}

PString& PString::operator+=(const std::string& other) {
    *this = *this + PString(other);
    return *this;
}


PString::iterator PString::begin() {
    return _data.begin();
}
PString::iterator PString::end() {
    return _data.end();
}

PString::const_iterator PString::begin() const {
    return _data.begin();
}

PString::const_iterator PString::end() const {
    return _data.end();
}


size_t PString::hash() const {
    std::hash<std::u32string> hasher;
    return hasher(_data);
}


void PString::_print(std::ostream& os) const {
    os << toStdString();
}



PString operator+(const char* lhs, const PString& rhs) {
    return PString(lhs) + rhs;
}

PString operator+(const std::string& lhs, const PString& rhs) {
    return PString(lhs) + rhs;
}

} // namespace sapy
