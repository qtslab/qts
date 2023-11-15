#include <iostream>
#include <vector>
#include <map>
#include <chrono>

#include "constant.h"
#include "type.h"

#include "QTS.hpp"
#include "PE-QTS.hpp"

int print_answer(question_t answer) {
    /* print all items
    for (auto itr = answer.begin(); itr != answer.end(); ++itr) {
        std::cout << "weight: " << itr->weight << " value: " << itr->value;
        if (itr->take) {
            std::cout << " take";
        } else {
            std::cout << " not take";
        }

        std::cout << std::endl;
    }
    */

    // print value of the answer
    double value = 0;
    for (int i=0; i<question_size; i++) {
        if (answer[i].take) {
            value += answer[i].value;
        }
    }

    std::cout << "value: " << value << std::endl;

    return 0;
}

int main(int argc, char* argv[]) {
    // generate question
    question_t question;

    for (int i=0; i<question_size; i++) {
        question[i].value = min_value + (max_value - min_value) * (double)rand() / RAND_MAX;
        question[i].weight = min_weight + (max_weight - min_weight) * (double)rand() / RAND_MAX;
        question[i].alpha = default_alpha;
        question[i].beta = default_beta;
        question[i].take = false;
    }

    // print question
    std::cout << "Question: " << std::endl;
    for (int i=0; i<question_size; i++) {
        std::cout << question[i].weight << " " << question[i].value << std::endl;
    }

    std::cout << std::endl << "Max generation: " << max_gen << std::endl << std::endl;

    question_t answer;

    std::cout << "QTS: " << std::endl;
    auto QTS_start = std::chrono::high_resolution_clock::now();
    QTS(question, max_gen);
    auto QTS_end = std::chrono::high_resolution_clock::now();

    std::cout << "PE-QTS: " << std::endl;
    auto PE_QTS_start = std::chrono::high_resolution_clock::now();
    PE_QTS(question, max_gen);
    auto PE_QTS_end = std::chrono::high_resolution_clock::now();

    std::cout << "QTS time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(QTS_end - QTS_start).count() << "ns" << std::endl;
    std::cout << "PE-QTS time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(PE_QTS_end - PE_QTS_start).count() << "ns" << std::endl;

    return 0;
}
