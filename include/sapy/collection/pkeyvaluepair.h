#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <utility>

namespace sapy{

namespace collection{

template <typename TKey, typename TValue>
using PKeyValuePair = std::pair<TKey, TValue>;

}
}