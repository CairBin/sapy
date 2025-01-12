#include <iostream>
#include <vector>
#include <string>
#include <ostream>
#include <memory>
#include <chrono>
#include <format>
#include "sapy/pstring.h"
#include "sapy/plist.h"

using namespace sapy;
using namespace std;

#define BATCH_SIZE 10000000ul


int main(){
    srand(time(0));
    vector<int> v;
    for(size_t i = 0; i < BATCH_SIZE; i++){
        v.push_back(rand());
    }
    // 
    auto time_start = chrono::high_resolution_clock::now();

    vector<int> ref;
    for(size_t i = 0; i < BATCH_SIZE; i++){
        ref.push_back(v[i]);
    }
    auto time_end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::milliseconds>(time_end - time_start);

    std::cout << std::format("STL Vector: Time taken for push_back() {} elements: {} ms\n", BATCH_SIZE, duration.count());

    auto time_start2 = chrono::high_resolution_clock::now();
    PList dut;
    for(size_t i = 0; i < BATCH_SIZE; i++){
        dut.append(v[i]);
    }
    auto time_end2 = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::milliseconds>(time_end2 - time_start2);
    std::cout << std::format("Sapy PList: Time taken for append() {} elements: {} ms\n", BATCH_SIZE, duration2.count());

    return 0;
}
