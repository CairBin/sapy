#include <string>
#include <vector>
#include <cstdint>
#include <codecvt>
#include <locale>

namespace sapy{
namespace base{

using PByte = char;

class PBytes : public std::string{
public:
    PBytes(const std::vector<uint8_t>& data)
        : std::string(data.begin(), data.end()){}

    // PBytes(std::vector<uint8_t> &data)
    //     : std::string(data.begin(), data.end()) {}

    PBytes(const PBytes& other)
        : std::string(other.begin(), other.end()){}
    
};

}
}