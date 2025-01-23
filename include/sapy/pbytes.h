// #pragma once 

// #include "sapy/pobject.h"
// #include "sapy/pstring.h"
// #include <iostream>

// namespace sapy{
// class PString;

// class PBytes : public PObject{
// public: 
//     PBytes() = default;
//     PBytes(const std::vector<uint8_t>& data)
//         : _data(data) {}
//     PBytes(const PBytes& other)
//         : _data(other._data) {}


//     PString toString() const override{
//         return PString("PBytes");
//     }
// private:
//     virtual void _print(std::ostream& os) const override{
//         os << toString();
//     }
//     std::vector<uint8_t> _data;
// };

// }