#include <iostream>
#include <vector>
#include <map>
#include <chrono>

#include "constant.h"
#include "type.h"

#include "QTS.hpp"
#include "PE-QTS.hpp"

int print_answer(items_t &items, solution_t answer) {
    // print all items
    for (int i=0; i<question_size; i++) {
        std::cout << "weight: " << items[i].weight << " value: " << items[i].value;
        if (answer[i].take) {
            std::cout << " take";
        } else {
            std::cout << " not take";
        }

        std::cout << std::endl;
    }

    // print value of the answer
    double value = 0;
    for (int i=0; i<question_size; i++) {
        if (answer[i].take) {
            value += items[i].value;
        }
    }

    std::cout << "value: " << value << std::endl;

    return 0;
}

int main(int argc, char* argv[]) {
    // generate question
    items_t items;
    solution_t solution;

    for (int i=0; i<question_size; i++) {
        items[i].value = min_value + (max_value - min_value) * (double)rand() / RAND_MAX;
        items[i].weight = min_weight + (max_weight - min_weight) * (double)rand() / RAND_MAX;
        solution[i].alpha = default_alpha;
        solution[i].beta = default_beta;
        solution[i].take = false;
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
        std::cout << items[i].weight << " " << items[i].value << std::endl;
    }

    std::cout << std::endl << "Max generation: " << max_gen << std::endl << std::endl;

    std::cout << "QTS: " << std::endl;
    auto QTS_start = std::chrono::high_resolution_clock::now();
    QTS(items, capacity, max_gen);
    auto QTS_end = std::chrono::high_resolution_clock::now();

    std::cout << "PE-QTS: " << std::endl;
    auto PE_QTS_start = std::chrono::high_resolution_clock::now();
    PE_QTS(items, capacity, max_gen);
    auto PE_QTS_end = std::chrono::high_resolution_clock::now();

    std::cout << "QTS time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(QTS_end - QTS_start).count() << "ns" << std::endl;
    std::cout << "PE-QTS time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(PE_QTS_end - PE_QTS_start).count() << "ns" << std::endl;

    return 0;
}
