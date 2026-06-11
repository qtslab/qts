#ifndef AE_QTS_HPP
#define AE_QTS_HPP

#include <random>
#include <iostream>
#include <vector>
#include <fstream>

#include <algorithm>
#include <numeric>

#include "constant.h"
#include "type.h"
#include "quantum_function.h"
#include "debug.hpp"
#include "record.hpp"

int AE_QTS(items_t& items, double capacity, int max_gen, int N, std::vector<double>& record) {
    q_t qindividuals(question_size);
    solution_t best_fit = measure(qindividuals);
    adjust_solution(items, best_fit, capacity);
    double best_fit_value = calculate_values(items, best_fit); // fitness 在 repair 後算一次後快取
    std::vector<solution_t> neighbors(N); // neighbors in loop
    std::vector<double> values(N);        // 每條 neighbor 的 fitness，repair 後算一次
    std::vector<int> order(N);            // 依 fitness 排序後的索引
    for (int i=0; i<max_gen; i++) { // AE-QTS loop, i = t
        // std::cout << "AE-QTS loop: " << i << std::endl; // debug
        for (int j=0; j<N; j++) {
            neighbors[j] = measure(qindividuals);
            adjust_solution(items, neighbors[j], capacity);
            values[j] = calculate_values(items, neighbors[j]); // repair 完成，算一次即存起來
        }

        // 用已存好的 fitness 排序索引，from best(index 0) to worst(index N-1)，不再重算
        std::iota(order.begin(), order.end(), 0);
        std::sort(order.begin(), order.end(), [&values](int a, int b) {return values[a] > values[b];});

        if (values[order[0]] > best_fit_value) {
            best_fit = neighbors[order[0]];
            best_fit_value = values[order[0]];
        }

        for (int j=0; j<N/2; j++) {
            update_q(neighbors[order[j]], neighbors[order[(N-1)-j]], qindividuals, 0.01/(j+1));
        }

        record[i] = best_fit_value;
    }

    // print_result(items, qindividuals, best_fit);
    return 0;
}

#endif