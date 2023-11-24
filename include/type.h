#ifndef TYPE_H
#define TYPE_H

#include <vector>
#include <cmath>
#include <bitset>

#include "constant.h"

struct qubit {
    double alpha = 1/sqrt(2);
    double beta = 1/sqrt(2);
};

struct item {
    double value = 0;
    double weight = 0;
};

using items_t = item[question_size];
using q_t = std::vector<qubit>;
using solution_t = std::bitset<question_size>;

#endif