#ifndef TYPE_H
#define TYPE_H

#include <map>
#include <math.h>
#include <unordered_set>
struct qubit {
    double value = 0;
    double weight = 0;
    double alpha = 1/sqrt(2);
    double beta = 1/sqrt(2);
    bool take = false;
};

using question_t = std::vector<qubit>;
using solution_t = std::vector<qubit>;

#endif