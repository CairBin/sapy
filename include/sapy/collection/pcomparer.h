#pragma once

#include <functional>

namespace sapy{

namespace collection{

template <typename T>
using PComparer = std::function<bool(const T&, const T&)>; 

}

}