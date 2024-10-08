#ifndef AE_QTS_HPP
#define AE_QTS_HPP

#include <random>
#include <iostream>
#include <vector>
#include <fstream>

#include "constant.h"
#include "type.h"
#include "quantum_function.h"
#include "debug.hpp"
#include "record.hpp"

int AE_QTS(items_t& items, double capacity, int max_gen, int N, std::vector<double>& record) {
    q_t qindividuals(question_size);
    solution_t best_fit = measure(qindividuals);
    adjust_solution(items, best_fit, capacity);
    std::vector<solution_t> neighbors(N); // neighbors in loop
    for (int i=0; i<max_gen; i++) { // AE-QTS loop, i = t
        // std::cout << "AE-QTS loop: " << i << std::endl; // debug
        for (int j=0; j<N; j++) {
            neighbors[j] = measure(qindividuals);
            adjust_solution(items, neighbors[j], capacity);
        }

        std::vector<solution_t> sorted_neighbors = sort_solution(items, neighbors, N); // from best(index 0) to worst(index N-1)
        if (calculate_values(items, sorted_neighbors[0]) > calculate_values(items, best_fit)) {
            best_fit = sorted_neighbors[0];
        }

        for (int j=0; j<N/2; j++) {
            update_q(sorted_neighbors[j], sorted_neighbors[(N-1)-j], qindividuals, 0.01/(j+1));
        }

        record[i] = calculate_values(items, best_fit);
    }

    // print_result(items, qindividuals, best_fit);
    return 0;
}

#endif