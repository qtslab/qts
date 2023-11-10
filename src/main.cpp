#include <iostream>
#include <vector>
#include <map>
#include <chrono>

#include "type.h"

#include "question_gen.hpp"
#include "QTS.hpp"
#include "PE-QTS.hpp"

int print_answer(answer_type answer) {
    for (auto itr = answer.begin(); itr != answer.end(); ++itr) {
        std::cout << itr->first << " " << itr->second << std::endl;
    }

    return 0;
}

int main(int argc, char* argv[]) {
    const int max_gen = 100; // The number of generations, MAX GEN
    const int question_size = 100; // The number of items, undefined
    const int capacity = 6; // The capacity of the knapsack, C

    question_type question = question_gen(question_size);

    std::cout << "Question" << std::endl;
    for (auto itr = question.begin(); itr != question.end(); ++itr) {
        std::cout << itr->first << " " << itr->second << std::endl;
    }

    answer_type answer;


    std::cout << "QTS" << std::endl;
    auto QTS_start = std::chrono::high_resolution_clock::now();
    answer = QTS(question, max_gen);
    auto QTS_end = std::chrono::high_resolution_clock::now();
    print_answer(answer);

    std::cout << "PE-QTS" << std::endl;
    auto PE_QTS_start = std::chrono::high_resolution_clock::now();
    answer = PE_QTS(question, max_gen);
    auto PE_QTS_end = std::chrono::high_resolution_clock::now();
    print_answer(answer);

    std::cout << "QTS time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(QTS_end - QTS_start).count() << "ns" << std::endl;
    std::cout << "PE-QTS time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(PE_QTS_end - PE_QTS_start).count() << "ns" << std::endl;

    return 0;
}
