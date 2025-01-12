#include <iostream>
#include "sapy/pstring.h"
#include "bench.h"
#include <chrono>

size_t bench(bench_dut dut, size_t bench_size, sapy::PString desp){
    auto time_start = std::chrono::high_resolution_clock::now();
    dut(bench_size);
    auto time_end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start);
    std::cout << std::format("Time taken for {} with {} elements: {} ms\n", desp.toStdString(), bench_size, duration.count());
    return duration.count();
    
}
