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

    solution_t qindividuals(question_size);
    solution_t best_fit(question_size);
    best_fit = measure(qindividuals);
    best_fit = adjust_solution(items, best_fit, capacity);

    // QTS main loop
    std::cout << "QTS main loop" << std::endl;
    std::set<solution_t> neighbors; // neighbors in loop
    solution_t best_solution(question_size); // best solution in loop
    solution_t worst_solution(question_size); // worst solution in loop
    for (int i=0; i<max_gen; i++) { // QTS_loop, i = t
        std::cout << "QTS_loop: " << i << std::endl;
        neighbors = gen_neighbors(qindividuals, n);
        adjust_neighbors(items, neighbors, capacity);
        best_solution = find_best(items, neighbors);
        worst_solution = find_worst(items, neighbors);
        best_fit = new_best_fit(items, best_solution, best_fit);
        qindividuals = update_q(best_solution, worst_solution, qindividuals);
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
    for (int i=0; i<question_size; i++) {
        std::cout << i+1 << ": ";
        std::cout << "weight: " << items[i].weight << " value: " << items[i].value << " ";
        if (best_fit[i].take) {
            std::cout << "take" << std::endl;
        } else {
            std::cout << "not take" << std::endl;
        }
    }

    std::cout << "value: ";
    int total_value = 0;
    for (int i=0; i<question_size; i++) {
        total_value += items[i].value * best_fit[i].take;
    }

    std::cout << total_value << std::endl;
    std::cout << "weight: " << calculate_weights(items, best_fit) << std::endl;
    std::cout << "capacity: " << capacity << std::endl;

    return 0;
}

#endif