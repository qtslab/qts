#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <iostream>

#include "constant.h"
#include "type.h"
#include "quantum_function.h"

void print_items(items_t& items) {
    for (int i=0; i<question_size; i++) {
        std::cout << i+1 << ": ";
        std::cout << "weight: " << items[i].weight << " value: " << items[i].value << std::endl;
    }
}

void print_solution(items_t& items, q_t& q, solution_t& solution) {
    for (int i=0; i<question_size; i++) {
        std::cout << i+1 << ": " << "\tweight: " << items[i].weight << "\tvalue: " << items[i].value << " ";
        if (solution[i]) {
            std::cout << "\ttake    ";
        } else {
            std::cout << "\tnot take";
        }

        std::cout << "\talpha: " << q[i].alpha*q[i].alpha << "\tbeta: " << q[i].beta*q[i].beta << std::endl;
    }

    std::cout << "total value: " << calculate_values(items, solution) << std::endl;
    std::cout << "total weight: " << calculate_weights(items, solution) << std::endl;
    double capacity = 0;
    for (int i=0; i<question_size; i++) {
        capacity += items[i].weight;
    }

    capacity /= 2;
    std::cout << "capacity: " << capacity << std::endl;
}

#endif