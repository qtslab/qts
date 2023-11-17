#ifndef QTS_HPP
#define QTS_HPP

#include <map>
#include <random>
// #include <Eigen/Dense>
// #include <armadillo>

#include "constant.h"
#include "type.h"
#include "quantum_function.h"

int QTS(items_t& items, double capacity, int max_gen) {
    // initialize QTS
    int n = 10; // Neighbourhood size

    solution_t qindividuals;
    for (int i=0; i<question_size; i++) {
        qindividuals[i].alpha = 1/sqrt(2);
        qindividuals[i].beta = 1/sqrt(2);
        qindividuals[i].take = false;
    }

    solution_t best_fit;
    best_fit = measure(qindividuals);
    best_fit = adjust_solution(best_fit, capacity);

    // QTS main loop
    solution_t neighbours; // neighbours in loop
    solution_t best_solution; // best solution in loop
    solution_t worst_solution; // worst solution in loop
    for (int i=0; i<max_gen; i++) { // QTS_loop, i = t
        // neighbours = gen_nbrs(qindividuals, N)
        neighbours = gen_neighbours(neighbours, n);
        // neighbours = adjust_neighbours(neighbours, C)
        neighbours = adjust_neighbours(neighbours, capacity);
        // (best_solution, worst_solution) = find_best_worst(neighbours)
        best_solution = find_best(neighbours);
        worst_solution = find_worst(neighbours);
        // best_fit = new_best_fit(best_solution, best_fit)
        best_fit = new_best_fit(best_solution, best_fit);
        // qindividuals = updateQ(best_solution, worst_solution, qindividuals)
        qindividuals = update_q(best_solution, worst_solution, qindividuals);
    }

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