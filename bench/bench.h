#pragma once 

#include "sapy/pstring.h"

#define BENCH_SIZE 100000ul

using bench_dut = void(*)(size_t);

size_t bench(bench_dut dut, size_t bench_size, sapy::PString desp);