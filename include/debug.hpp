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

void print_best_fit(items_t& items, solution_t& best_fit) {
    std::cout << "best_fit" << std::endl;
    print_solution(items, best_fit);
}

void print_best_solution(items_t& items, solution_t& best_solution) {
    std::cout << "best_solution" << std::endl;
    print_solution(items, best_solution);
}

void print_worst_solution(items_t& items, solution_t& worst_solution) {
    std::cout << "worst_solution" << std::endl;
    print_solution(items, worst_solution);
}

void print_qindividuals(items_t& items, solution_t& qindividuals) {
    std::cout << "qindividuals" << std::endl;
    print_solution(items, qindividuals);
}

#endif