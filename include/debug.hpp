#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <iostream>

#include "type.h"

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
            std::cout << "\ttake" << std::endl;
        } else {
            std::cout << "\tnot take" << std::endl;
        }

        std::cout << "\talpha: " << q[i].alpha*q[i].alpha << "\tbeta: " << q[i].beta*q[i].beta << std::endl;
    }
}

#endif