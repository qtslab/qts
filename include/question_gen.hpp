#ifndef QUESTION_GEN_HPP
#define QUESTION_GEN_HPP

#include <random>

#include "constant.h"
#include "type.h"

question_t question_gen(int question_size) {
    question_t question(question_size);

    for (auto itr = question.begin(); itr != question.end(); ++itr) {
        itr->value = min_value + (max_value - min_value) * (double)rand() / RAND_MAX;
        itr->weight = min_weight + (max_weight - min_weight) * (double)rand() / RAND_MAX;
        itr->alpha = default_alpha;
        itr->beta = default_beta;
        itr->take = false;
    }

    return question;
}

#endif