#ifndef CASE_HPP
#define CASE_HPP

#include <random>

#include "type.h"

// 各 case 假設 items 已由呼叫端配置為 question_size 大小（見 main.cpp），
// 故一律以 items.size() 走訪。物品數量由設定檔的 question_size 決定。

int case_I(items_t& items, double& capacity, double min_weight, double max_weight) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> weight_dis(min_weight, max_weight);
    for (std::size_t i=0; i<items.size(); i++) {
        items[i].weight = weight_dis(gen);
    }

    for (std::size_t i=0; i<items.size(); i++) {
        items[i].value = items[i].weight + 5;
    }

    for (std::size_t i=0; i<items.size(); i++) {
        capacity += items[i].weight;
    }

    capacity /= 2;
    return 0;
}

int case_II(items_t& items, double& capacity) {
    for (std::size_t i=0; i<items.size(); i++) {
        items[i].weight = i%10 + 1;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    for (std::size_t i=0; i<items.size(); i++) {
        std::uniform_real_distribution<double> value_dis(0, 5);
        items[i].value = items[i].weight + value_dis(gen);
    }

    for (std::size_t i=0; i<items.size(); i++) {
        capacity += items[i].weight;
    }

    capacity /= 2;
    return 0;
}

int case_III(items_t& items, double& capacity) {
    for (std::size_t i=0; i<items.size(); i++) {
        items[i].weight = (i % 10) + 1;
        items[i].value = items[i].weight + 5;
    }

    for (std::size_t i=0; i<items.size(); i++) {
        capacity += items[i].weight;
    }

    capacity /= 2;
    return 0;
}

#endif
