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
    std::vector<solution_t> neighbors; // neighbors in loop
    solution_t best_solution(question_size); // best solution in loop(one iteration)
    solution_t worst_solution(question_size); // worst solution in loop(one iteration)
    for (int i=0; i<max_gen; i++) { // QTS_loop, i = t
        std::cout << "QTS_loop: " << i << std::endl; // debug
        neighbors = gen_neighbors(qindividuals, n);
        // print_neighbors(items, neighbors); // debug
        adjust_neighbors(items, neighbors, capacity);
        // print_neighbors(items, neighbors); // debug
        best_solution = find_best(items, neighbors);
        // print_solution(items, best_solution); // debug
        worst_solution = find_worst(items, neighbors);
        // print_solution(items, worst_solution); // debug
        best_fit = new_best_fit(items, best_solution, best_fit);
        // print_solution(items, best_fit); // debug
        update_q(best_solution, worst_solution, qindividuals);
        print_solution(items, best_fit); // debug
    }

    std::cout << "QTS end" << std::endl;
    // get answer from best_fit at the end of QTS
    std::random_device rd;  // 取得隨機數種子
    std::mt19937 gen(rd()); // 使用 Mersenne Twister 引擎
    for (int i=0; i<question_size; i++) {
        std::uniform_real_distribution<double> dis(0.0, 1.0);
        double rand_observation = dis(gen); // 生成隨機數
        if (rand_observation < best_fit[i].alpha) {
            best_fit[i].take = true;
        } else {
            best_fit[i].take = false;
        }
    }

    // print answer
    print_solution(items, best_fit);

    std::cout << "value: " << calculate_values(items, best_fit) << std::endl;
    std::cout << "weight: " << calculate_weights(items, best_fit) << std::endl;
    std::cout << "capacity: " << capacity << std::endl;

    return 0;
}

#endif