#include <iostream>
#include <vector>
#include <string>
#include <ostream>
#include <memory>
#include <chrono>
#include <format>
#include <set>
#include <unordered_set>
#include "sapy/pstring.h"
#include "sapy/pset.h"
#include "bench.h"

static std::vector<int> v;

void unordered_set(size_t batch_size){
    std::unordered_set<int>v_b;
    for(size_t i = 0; i < batch_size; i++){
        v_b.insert(v[i]);
    }
}

void set_b(size_t batch_size){
    sapy::PSet dut;
    for(size_t i = 0; i < batch_size; i++){
        dut.add(v[i]);
    }
}

void setT_b(size_t batch_size){
    sapy::PSetT<int> dut;
    for(size_t i = 0; i < batch_size; i++){
        dut.add(v[i]);
    }
}
void set_bench(){
    srand(time(0));
    for(size_t i = 0; i < BENCH_SIZE/10; i++){
        v.push_back(rand());
    }
    std::cout << "-----------------------------------------" << std::endl;
    bench(unordered_set, BENCH_SIZE/10, "STL unordered_set push_back()");
    bench(setT_b, BENCH_SIZE/10, "Sapy PSetT add()");
    bench(set_b, BENCH_SIZE/10, "Sapy PSet add()");
}

