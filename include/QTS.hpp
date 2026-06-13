#ifndef QTS_HPP
#define QTS_HPP

#include <random>
#include <iostream>
#include <vector>
#include <fstream>

#include "type.h"
#include "quantum_function.h"
#include "debug.hpp"
#include "record.hpp"

int QTS(items_t& items, double capacity, int max_gen, int N, std::vector<double>& record) {
    q_t qindividuals(items.size());
    solution_t best_fit = measure(qindividuals);
    adjust_solution(items, best_fit, capacity);
    double best_fit_value = calculate_values(items, best_fit); // fitness 在 repair 後算一次後快取
    std::vector<solution_t> neighbors(N); // neighbors in loop
    solution_t best_solution(items.size()); // best solution in loop(one iteration)
    solution_t worst_solution(items.size()); // worst solution in loop(one iteration)
    for (int i=0; i<max_gen; i++) { // QTS_loop, i = t
        // std::cout << "QTS_loop: " << i << std::endl; // debug
        double best_value = 0, worst_value = 0;
        for (int j=0; j<N; j++) {
            neighbors[j] = measure(qindividuals);
            adjust_solution(items, neighbors[j], capacity);
            double value = calculate_values(items, neighbors[j]); // repair 完成，算一次即存起來
            if (j == 0) {
                best_solution = neighbors[j];
                worst_solution = neighbors[j];
                best_value = value;
                worst_value = value;
            } else if (value > best_value) {
                best_solution = neighbors[j];
                best_value = value;
            } else if (value < worst_value) {
                worst_solution = neighbors[j];
                worst_value = value;
            }
        }

        if (best_value > best_fit_value) {
            best_fit = best_solution;
            best_fit_value = best_value;
        }

        update_q(best_solution, worst_solution, qindividuals);
        record[i] = best_fit_value;
    }

    // print_result(items, qindividuals, best_fit);
    return 0;
}

#endif