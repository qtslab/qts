#include <iostream>
#include <vector>
#include <map>
#include <chrono>

#include "constant.h"
#include "type.h"

#include "QTS.hpp"
#include "PE-QTS.hpp"

int main(int argc, char* argv[]) {
    // generate question
    items_t items;
    // initialize items

    std::random_device rd;  // 取得隨機數種子
    std::mt19937 gen(rd()); // 使用 Mersenne Twister 引擎
    for (int i=0; i<question_size; i++) {
        std::uniform_real_distribution<double> value_dis(min_value, max_value);
        std::uniform_real_distribution<double> weight_dis(min_weight, max_weight);
        items[i].value = value_dis(gen);
        items[i].weight = weight_dis(gen);
    }

    // calculate capacity
    double capacity = 0;
    for (int i=0; i<question_size; i++) {
        capacity += items[i].weight;
    }

    capacity /= 2;

    // print question
    std::cout << "Question: " << std::endl;
    for (int i=0; i<question_size; i++) {
        std::cout << i+1 << ": " << items[i].weight << " " << items[i].value << std::endl;
    }

    std::cout << std::endl << "Max generation: " << max_gen << std::endl << std::endl;

    std::cout << "QTS: " << std::endl;
    auto QTS_start = std::chrono::high_resolution_clock::now();
    QTS(items, capacity, max_gen, N);
    auto QTS_end = std::chrono::high_resolution_clock::now();

    std::cout << "PE-QTS: " << std::endl;
    auto PE_QTS_start = std::chrono::high_resolution_clock::now();
    PE_QTS(items, capacity, max_gen, N);
    auto PE_QTS_end = std::chrono::high_resolution_clock::now();

    std::cout << "QTS time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(QTS_end - QTS_start).count() << "ns" << std::endl;
    std::cout << "PE-QTS time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(PE_QTS_end - PE_QTS_start).count() << "ns" << std::endl;

    return 0;
}
