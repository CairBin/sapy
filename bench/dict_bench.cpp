#include <iostream>
#include <vector>
#include <string>
#include <ostream>
#include <memory>
#include <chrono>
#include <format>
#include <map>
#include <unordered_map>
#include "sapy/pstring.h"
#include "sapy/pdict.h"
#include "bench.h"

static std::vector<int> v;

void unordered_map_b(size_t) {
    std::unordered_map<int, int> dict;
    for (size_t i = 0; i < BENCH_SIZE; i++) {
        dict[i] = v[i];
    }
}

void dict_b(size_t) {
    sapy::PDict dict;
    for (size_t i = 0; i < BENCH_SIZE; i++) {
        dict[i] = i;
    }
}

void dictT_b(size_t) {
    sapy::PDictT<int, int> dict;
    for (size_t i = 0; i < BENCH_SIZE; i++) {
        dict[i] = v[i];
    }
}


void dict_bench(){
    srand(time(0));
    for(size_t i = 0; i < BENCH_SIZE; i++){
        v.push_back(rand());
    }
    std::cout << "-----------------------------------------" << std::endl;
    bench(unordered_map_b, BENCH_SIZE, "STL unordered_map<int,int> add data");
    bench(dictT_b, BENCH_SIZE, "Sapy PDictT<int,int> add data");
    bench(dict_b, BENCH_SIZE, "Sapy PDict add data");
}

