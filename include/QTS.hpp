#ifndef QTS_HPP
#define QTS_HPP

#include <random>
#include <iostream>
#include <vector>

#include "constant.h"
#include "type.h"
#include "quantum_function.h"
#include "debug.hpp"

int QTS(items_t& items, double capacity, int max_gen, int N) {
    // initialize QTS
    q_t qindividuals(question_size);
    solution_t best_fit = measure(qindividuals);
    adjust_solution(items, best_fit, capacity);

    // QTS main loop
    std::vector<solution_t> neighbors(N); // neighbors in loop
    solution_t best_solution(question_size); // best solution in loop(one iteration)
    solution_t worst_solution(question_size); // worst solution in loop(one iteration)
    for (int i=0; i<max_gen; i++) { // QTS_loop, i = t
        std::cout << "QTS_loop: " << i << std::endl; // debug
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
        print_solution(items, qindividuals, best_fit); // debug
    }

    std::cout << "QTS end" << std::endl;

    // print answer from best_fit at the end of QTS
    print_solution(items, qindividuals, best_fit);

    std::cout << "value: " << calculate_values(items, best_fit) << std::endl;
    std::cout << "weight: " << calculate_weights(items, best_fit) << std::endl;
    std::cout << "capacity: " << capacity << std::endl;

    return 0;
}

#endif