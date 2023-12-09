#ifndef QTS_HPP
#define QTS_HPP

#include <random>
#include <iostream>
#include <vector>
#include <fstream>

#include "constant.h"
#include "type.h"
#include "quantum_function.h"
#include "debug.hpp"
#include "record.hpp"

int QTS(items_t& items, double capacity, int max_gen, int N) {
    std::ofstream fout("csv/QTS.csv");

    q_t qindividuals(question_size);
    solution_t best_fit = measure(qindividuals);
    adjust_solution(items, best_fit, capacity);
    std::vector<solution_t> neighbors(N); // neighbors in loop
    solution_t best_solution(question_size); // best solution in loop(one iteration)
    solution_t worst_solution(question_size); // worst solution in loop(one iteration)
    for (int i=0; i<max_gen; i++) { // QTS_loop, i = t
        // std::cout << "QTS_loop: " << i << std::endl; // debug
        for (int j=0; j<N; j++) {
            neighbors[j] = measure(qindividuals);
            adjust_solution(items, neighbors[j], capacity);
            if (j == 0) {
                best_solution = neighbors[j];
                worst_solution = neighbors[j];
            }

            if (calculate_values(items, neighbors[j]) > calculate_values(items, best_solution)) {
                best_solution = neighbors[j];
            } else if (calculate_values(items, neighbors[j]) < calculate_values(items, worst_solution)) {
                worst_solution = neighbors[j];
            }
        }

        if (calculate_values(items, best_solution) > calculate_values(items, best_fit)) {
            best_fit = best_solution;
        }

        update_q(best_solution, worst_solution, qindividuals);
        // print_solution(items, qindividuals, best_solution); // debug
        record_iter(fout, calculate_values(items, best_fit), i); // record
    }

    // print_result(items, qindividuals, best_fit);
    fout.close();
    return 0;
}

#endif