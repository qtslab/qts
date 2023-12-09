#ifndef CASE_HPP
#define CASE_HPP

#include <random>

#include "type.h"
#include "constant.h"

int case_I(items_t& items, double& capacity, int max_gen, int N) {
    items_t items;
    for (int i=0; i<question_size; i++) {
        int value = (i % 10) + 1;
        items[i].weight = value;
        items[i].value = value + 5;
    }

    for (int i=0; i<question_size; i++) {
        capacity += items[i].weight;
    }

    capacity /= 2;

    return 0;
}

int case_II(items_t& items, double& capacity, int max_gen, int N) {
    items_t items;
    std::random_device rd;  // 取得隨機數種子
    std::mt19937 gen(rd()); // 使用 Mersenne Twister 引擎
    for (int i=0; i<question_size; i++) {
        std::uniform_real_distribution<double> value_dis(min_value, max_value);
        std::uniform_real_distribution<double> weight_dis(min_weight, max_weight);
        items[i].weight = weight_dis(gen);
        items[i].value = items[i].weight + 5;
    }

    for (int i=0; i<question_size; i++) {
        capacity += items[i].weight;
    }

    capacity /= 2;

    return 0;
}

int case_III(items_t& items, double capacity, int max_gen, int N) {
    items_t items;
    for (int i=0; i<question_size; i++) {
        int value = (i % 10) + 1;
        items[i].weight = value;
        items[i].value = value + 5;
    }

    for (int i=0; i<question_size; i++) {
        capacity += items[i].weight;
    }

    capacity /= 2;

    return 0;
}

#endif