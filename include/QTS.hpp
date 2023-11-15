#ifndef QTS_HPP
#define QTS_HPP

#include <map>
#include <random>
#include <Eigen/Dense>
#include <armadillo>

#include "constant.h"
#include "type.h"

#include "quantum_function.h"

int QTS(question_t question, double capacity, int max_gen) {
    int n = 10;

    // Initialize the best solution sb from P(t) by measuring Q(t), repairing and evaluating P(t)
    // for (int i = 0; i < question.size(); i++) {
        // Measure Q(t)
        // Repair P(t)
        // Evaluate P(t)
        // if (P[t][i] > sb) {
        //     sb = P[t][i];
        // }
    // }

    for (int i=0; i<max_gen; i++) { // QTS_loop, i = t
        // neighbours = gen_nbrs(qindividuals, N)
        // neighbours = adjust_neighbours(neighbours, C)
        // (best_solution, worst_solution) = find_best_worst(neighbours)
        // best_fit = new_best_fit(best_solution, best_fit)
        // qindividuals = updateQ(best_solution, worst_solution, qindividuals)
    }

    question_t answer;
    // get answer from question
    for (int i=0; i<question_size; i++) {
        std::random_device rd;  // 取得隨機數種子
        std::mt19937 gen(rd()); // 使用 Mersenne Twister 引擎
        std::uniform_real_distribution<double> dis(0.0, 1.0);
        double rand_observation = dis(gen); // 生成隨機數
        qubit q;
        if (rand_observation < question[i].alpha) {
            q.take = true;
        } else {
            q.take = false;
        }

        question[i].take = q.take;
    }

    return 0;
}

#endif