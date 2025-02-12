#pragma once
#include "sapy/panywrapper.h"
#include "sapy/plistT.hpp"

namespace sapy{
class PAnyWrapper;
template <typename T>
class PListT;
using PList = PListT<PAnyWrapper>;

}