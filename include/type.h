#ifndef TYPE_H
#define TYPE_H

#include <vector>
#include <cmath>

#include "constant.h"

struct qubit {
    double alpha = 1/sqrt(2);
    double beta = 1/sqrt(2);
    bool take = false;
};

struct item {
    double value = 0;
    double weight = 0;
};

using items_t = item[question_size];
using solution_t = std::vector<qubit>;
// using solution_t = qubit[question_size];

#endif