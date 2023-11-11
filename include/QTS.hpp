#ifndef QTS_HPP
#define QTS_HPP

#include <map>
#include <random>

#include "constant.h"
#include "type.h"

question_t Q(question_t question) {
    for (auto i : question) {

    }

    return question;
}

question_t QTS(question_t question, int max_gen) {
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
        question = Q(question);
    }

    question_t answer;

    for (auto i : question) {
        std::random_device rd;  // 取得隨機數種子
        std::mt19937 gen(rd()); // 使用 Mersenne Twister 引擎

        std::uniform_real_distribution<double> dis(0.0, 1.0);

        double rand_observation = dis(gen); // 生成隨機數

        qubit q;
        if (rand_observation < i.alpha) {
            q.take = true;
        } else {
            q.take = false;
        }

        answer.push_back(i);
    }

    return answer;
}

#endif