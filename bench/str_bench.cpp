#include "bench.h"

static std::vector<char> v;


void std_str_add_c_b(size_t){
    std::string std_str_b;
    for(size_t i = 0; i < BENCH_SIZE; i++){
        std_str_b += v[i];
    }
}

void pstring_add_c_b(size_t){
    sapy::PString dut;
    for(size_t i = 0; i < BENCH_SIZE; i++){
        dut = dut + v[i];
    }
}

void std_str_add_b(size_t){
    std::string std_str_b;
    std::string add_str = "abc";
    for(size_t i = 0; i < BENCH_SIZE; i++){
        std_str_b += add_str;
    }
}

void pstring_add_b(size_t){
    sapy::PString dut;
    sapy::PString add_str = "abc";
    for(size_t i = 0; i < BENCH_SIZE; i++){
        dut += add_str;
    }
}

void str_bench(){
    srand(time(0));
    for(size_t i = 0; i < BENCH_SIZE; i++){
        v.push_back(rand()%26 + 'a');
    }

    bench(std_str_add_b, BENCH_SIZE, "STL String += string");
    bench(pstring_add_b, BENCH_SIZE, "Sapy PString += string");

    bench(std_str_add_c_b, BENCH_SIZE, "STL String += char");
    bench(pstring_add_c_b, BENCH_SIZE, "Sapy PString += char");
}