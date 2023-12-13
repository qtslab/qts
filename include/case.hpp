#ifndef CASE_HPP
#define CASE_HPP

#include <random>

#include "type.h"
#include "constant.h"

int case_I(items_t& items, double& capacity, int max_gen, int N) {
    std::random_device rd;
    std::mt19937 gen(rd());
    for (int i=0; i<question_size; i++) {
        std::uniform_real_distribution<double> weight_dis(min_weight, max_weight);
        items[i].weight = weight_dis(gen);
    }

    for (int i=0; i<question_size; i++) {
        items[i].value = items[i].weight + 5;
    }

    for (int i=0; i<question_size; i++) {
        capacity += items[i].weight;
    }

    capacity /= 2;
    return 0;
}

int case_II(items_t& items, double& capacity, int max_gen, int N) {
    for (int i=0; i<question_size; i++) {
        items[i].weight = i%10 + 1;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    for (int i=0; i<question_size; i++) {
        std::uniform_real_distribution<double> value_dis(0, 5);
        items[i].value = items[i].weight + value_dis(gen);
    }

    for (int i=0; i<question_size; i++) {
        capacity += items[i].weight;
    }

    capacity /= 2;
    return 0;
}

int case_III(items_t& items, double& capacity, int max_gen, int N) {
    for (int i=0; i<question_size; i++) {
        items[i].weight = (i % 10) + 1;
        items[i].value = items[i].weight + 5;
    }

    for (int i=0; i<question_size; i++) {
        capacity += items[i].weight;
    }

    capacity /= 2;
    return 0;
}

#endif