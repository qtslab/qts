#ifndef QUESTION_GEN_HPP
#define QUESTION_GEN_HPP

#include <random>

#include "type.h"

question_type question_gen(int question_size) {
    const double min_value = 1.0;
    const double max_value = 10.0;
    const double min_weight = 1.0;
    const double max_weight = 10.0;

    question_type question;

    for (int i=0; i<question_size; i++) {
        question.insert(std::make_pair(
            // 1.0 < value <= 10.0
            min_value + (max_value - min_value) * (double)rand() / RAND_MAX,
            // 1.0 < weight <= 10.0
            min_weight + (max_weight - min_weight) * (double)rand() / RAND_MAX
        ));
    }

    return question;
}

#endif