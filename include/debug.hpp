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

void print_solution(items_t& items, solution_t& solution) {
    for (int i=0; i<question_size; i++) {
        std::cout << i+1 << ": ";
        std::cout << "weight: " << items[i].weight << " value: " << items[i].value << " ";
        if (solution[i].take) {
            std::cout << "take" << std::endl;
        } else {
            std::cout << "not take" << std::endl;
        }
    }
}

void print_neighbors(items_t& items, std::vector<solution_t>& neighbors) {
    for (int i=0; i<neighbors.size(); i++) {
        std::cout << "neighbor " << i << std::endl;
        print_solution(items, neighbors[i]);
    }
}

#endif