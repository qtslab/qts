#include <iostream>
#include <vector>
#include <map>
#include <chrono>

#include "constant.h"
#include "type.h"

#include "question_gen.hpp"
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
    for (auto itr = answer.begin(); itr != answer.end(); ++itr) {
        if (itr->take) {
            value += itr->value;
        }
    }

    std::cout << "value: " << value << std::endl;

    return 0;
}

int main(int argc, char* argv[]) {
    question_t question = question_gen(question_size);

    std::cout << "Question: " << std::endl;
    for (auto itr = question.begin(); itr != question.end(); ++itr) {
        std::cout << itr->weight << " " << itr->value << std::endl;
    }

    std::cout << std::endl << "Max generation: " << max_gen << std::endl << std::endl;

    question_t answer(question_size);

    std::cout << "QTS: " << std::endl;
    auto QTS_start = std::chrono::high_resolution_clock::now();
    answer = QTS(question, max_gen);
    auto QTS_end = std::chrono::high_resolution_clock::now();
    print_answer(answer);

    std::cout << "PE-QTS: " << std::endl;
    auto PE_QTS_start = std::chrono::high_resolution_clock::now();
    answer = PE_QTS(question, max_gen);
    auto PE_QTS_end = std::chrono::high_resolution_clock::now();
    print_answer(answer);

    std::cout << "QTS time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(QTS_end - QTS_start).count() << "ns" << std::endl;
    std::cout << "PE-QTS time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(PE_QTS_end - PE_QTS_start).count() << "ns" << std::endl;

    return 0;
}
