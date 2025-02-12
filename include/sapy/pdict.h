#pragma once 

#include "sapy/pdictT.hpp"
#include "sapy/panywrapper.h"

namespace sapy{

class PAnyWrapper;
template <typename KeyType,typename ValueType>
class PDictT;
using PDict = PDictT<PAnyWrapper, PAnyWrapper>;

}