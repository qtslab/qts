#ifndef QTS_HPP
#define QTS_HPP

#include <map>
#include <random>

#include "type.h"

question_type Q(question_type question) {
    question_type updated;
    // Make P(t) with N solutions by measuring Q(t - 1)
    int p = question.size(); // The number of solutions in P(t)
    int q = 10; // The number of solutions in Q(t)
    int sb = 0; // The best solution in P(t)
    int b = 0; // The best solution in P(t)
    for (int i = 0; i < question.size(); i++) {
        // Measure Q(t - 1)
    }

    // Repair P(t)
    for (int i = 0; i < question.size(); i++) {
        // Repair P(t)
    }

    // Evaluate P(t)
    for (int i = 0; i < question.size(); i++) {
        // Evaluate P(t)
    }

    // Update Q(t) by P(t) // ▷ The difference from QTS
    for (int i = 0; i < question.size(); i++) {
        // Update Q(t) by P(t)
    }

    // Select the best solution b from P(t)
    for (int i = 0; i < question.size(); i++) {
        if (P[t][i] > b) {
            b = P[t][i];
        }
    }

    if (b > sb) {
        sb = b;
    }

    return updated;
}

answer_type QTS(question_type question, int max_gen) {
    int n = 10;
    const double alpha = 0.5;
    const double beta = 0.5;
    int P[t][p];
    int Q[t][q];

    // Initialize P(t)
    for (int i = 0; i < question.size(); i++) {
        P[t][i] = alpha;
    }

    // Initialize Q(t)
    for (int i = 0; i < q; i++) {
        Q[t][i] = beta;
    }

    // Initialize the best solution sb from P(t) by measuring Q(t), repairing and evaluating P(t)
    for (int i = 0; i < question.size(); i++) {
        // Measure Q(t)
        // Repair P(t)
        // Evaluate P(t)
        if (P[t][i] > sb) {
            sb = P[t][i];
        }
    }

    for (int i=0; i<max_gen; i++) { // QTS_loop, i = t
        question = Q(question);
    }

    answer_type answer;

    for (auto i : question) {
        std::random_device rd;  // 取得隨機數種子
        std::mt19937 gen(rd()); // 使用 Mersenne Twister 引擎

        std::uniform_real_distribution<double> dis(0.0, 1.0);

        double rand_observation = dis(gen); // 生成隨機數

        if (rand_observation < i.second * sb) {
            answer.insert(std::make_pair(i.first, 1));
        } else {
            answer.insert(std::make_pair(i.first, 0));
        }
    }

    return answer;
}

#endif