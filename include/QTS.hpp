#ifndef QTS_HPP
#define QTS_HPP

#include <random>
#include <iostream>
#include <vector>

#include "constant.h"
#include "type.h"
#include "quantum_function.h"
#include "debug.hpp"

int QTS(items_t& items, double capacity, int max_gen) {
    // initialize QTS
    int n = 10; // Neighbourhood size

    solution_t qindividuals(question_size);
    solution_t best_fit = measure(qindividuals);
    adjust_solution(items, best_fit, capacity);

    // QTS main loop
    std::vector<solution_t> neighbors(n); // neighbors in loop
    solution_t best_solution(question_size); // best solution in loop(one iteration)
    solution_t worst_solution(question_size); // worst solution in loop(one iteration)
    for (int i=0; i<max_gen; i++) { // QTS_loop, i = t
        std::cout << "QTS_loop: " << i << std::endl; // debug
        for (int j=0; j<n; j++) {
            neighbors[j] = measure(qindividuals);
            adjust_solution(items, neighbors[j], capacity);
        }

        best_solution = find_best(items, neighbors);
        worst_solution = find_worst(items, neighbors);
        if (calculate_values(items, best_solution) > calculate_values(items, best_fit)) {
            best_fit = best_solution;
        }

        update_q(best_solution, worst_solution, qindividuals);
        // print_solution(items, best_fit); // debug
        print_solution(items, qindividuals); // debug
    }

    std::cout << "QTS end" << std::endl;

    // print answer from best_fit at the end of QTS
    print_solution(items, best_fit);

    std::cout << "value: " << calculate_values(items, best_fit) << std::endl;
    std::cout << "weight: " << calculate_weights(items, best_fit) << std::endl;
    std::cout << "capacity: " << capacity << std::endl;

    return 0;
}

#endif