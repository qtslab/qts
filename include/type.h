#ifndef TYPE_H
#define TYPE_H

#include <map>
#include <math.h>
#include <unordered_set>

#include "constant.h"

struct qubit {
    double value = 0;
    double weight = 0;
    double alpha = 1/sqrt(2);
    double beta = 1/sqrt(2);
    bool take = false;
};

using question_t = qubit[question_size];
using solution_t = qubit[question_size];

#endif