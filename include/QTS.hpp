#ifndef QTS_HPP
#define QTS_HPP

#include <random>
#include <iostream>
#include <set>
// #include <Eigen/Dense>
// #include <armadillo>

#include "constant.h"
#include "type.h"
#include "quantum_function.h"

int QTS(items_t& items, double capacity, int max_gen) {
    // initialize QTS
    int n = 10; // Neighbourhood size

    solution_t qindividuals;
    solution_t best_fit;
    best_fit = measure(qindividuals);
    best_fit = adjust_solution(best_fit, capacity);

    // QTS main loop
    std::cout << "QTS main loop" << std::endl;
    std::set<solution_t> neighbors; // neighbors in loop
    solution_t best_solution; // best solution in loop
    solution_t worst_solution; // worst solution in loop
    for (int i=0; i<max_gen; i++) { // QTS_loop, i = t
        neighbors = gen_neighbors(qindividuals, n);
        neighbors = adjust_neighbors(neighbors, capacity);
        best_solution = find_best(neighbors);
        worst_solution = find_worst(neighbors);
        best_fit = new_best_fit(best_solution, best_fit);
        qindividuals = update_q(best_solution, worst_solution, qindividuals);
    }

    std::cout << "QTS end" << std::endl;
    // get answer from best_fit at the end of QTS
    for (int i=0; i<question_size; i++) {
        std::random_device rd;  // 取得隨機數種子
        std::mt19937 gen(rd()); // 使用 Mersenne Twister 引擎
        std::uniform_real_distribution<double> dis(0.0, 1.0);
        double rand_observation = dis(gen); // 生成隨機數
        if (rand_observation < best_fit[i].alpha) {
            best_fit[i].take = true;
        } else {
            best_fit[i].take = false;
        }
    }

    return 0;
}

#endif