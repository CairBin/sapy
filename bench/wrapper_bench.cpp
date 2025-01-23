#include <iostream>
#include <vector>
#include <string>
#include <ostream>
#include <memory>
#include <chrono>
#include <format>
#include "sapy/pstring.h"
#include "sapy/plist.h"
#include "bench.h"
#include "sapy/pmodel.h"




static std::vector<int> v;

void assign_b(size_t)__attribute__((optimize("O0")));
void wrap_b(size_t)__attribute__((optimize("O0")));

void assign_b(size_t){ 
    int ref;
    for(size_t i = 0; i < BENCH_SIZE; i++){
        ref = (v[i]);
    }
}

void wrap_b(size_t){
    for(size_t i = 0; i < BENCH_SIZE; i++){
        sapy::PAnyWrapper dut = v[i];
    }
}

void wrap_bench(){
    srand(time(0));
    for(size_t i = 0; i < BENCH_SIZE; i++){
        v.push_back(rand());
    }

    bench(assign_b, BENCH_SIZE, "Directly Assign");
    bench(wrap_b, BENCH_SIZE, "PAnyWrapper Assign");
}

