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

static std::vector<int> v;

void vecotr_b(size_t){
    std::vector<int>v_b;
    for(size_t i = 0; i < BENCH_SIZE; i++){
        v_b.push_back(v[i]);
    }
}

void list_b(size_t){
    sapy::PList dut;
    for(size_t i = 0; i < BENCH_SIZE; i++){
        dut.append(v[i]);
    }
}

void listT_b(size_t){
    sapy::PListT<int> dut;
    for(size_t i = 0; i < BENCH_SIZE; i++){
        dut.append(v[i]);
    }
}
void list_bench(){
    srand(time(0));
    for(size_t i = 0; i < BENCH_SIZE; i++){
        v.push_back(rand());
    }
    std::cout << "-----------------------------------------" << std::endl;
    bench(vecotr_b, BENCH_SIZE, "STL Vector push_back()");
    bench(listT_b, BENCH_SIZE, "Sapy PListT append()");
    bench(list_b, BENCH_SIZE, "Sapy PList append()");
}

