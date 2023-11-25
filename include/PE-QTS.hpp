#ifndef PE_QTS_HPP
#define PE_QTS_HPP

#include <random>
#include <iostream>
#include <vector>

#include "constant.h"
#include "type.h"
#include "quantum_function.h"
#include "debug.hpp"

int PE_QTS(items_t& items, double capacity, int max_gen, int N) {
    q_t qindividuals(question_size);
    solution_t best_fit = measure(qindividuals);
    adjust_solution(items, best_fit, capacity);
    std::vector<solution_t> neighbors(N); // neighbors in loop
    std::vector<solution_t> sorted_neighbors(N); // value sorted solution
    for (int i=0; i<max_gen; i++) { // PE-QTS loop, i = t
        // std::cout << "PE-QTS loop: " << i << std::endl; // debug
        for (int j=0; j<N; j++) {
            neighbors[j] = measure(qindividuals);
            adjust_solution(items, neighbors[j], capacity);
        }

        sort_solution(items, neighbors, sorted_neighbors);
        if (calculate_values(items, sorted_neighbors[question_size-1]) > calculate_values(items, best_fit)) {
            best_fit = sorted_neighbors[question_size-1];
        }

        for (int j=0; j<N/2; j++) {
            update_q(sorted_neighbors[question_size-j-1], sorted_neighbors[j], qindividuals , 0.01/(j+1));
        }

        // print_solution(items, qindividuals, best_fit); // debug
    }

    // print_result(items, qindividuals, best_fit);
    return 0;
}

#endif