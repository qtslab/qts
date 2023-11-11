#ifndef TYPE_H
#define TYPE_H

#include <map>
#include <unordered_set>
struct qubit {
    double value = 0;
    double weight = 0;
    double alpha = 0.5;
    double beta = 0.5;
    bool take = false;
};

using question_t = std::vector<qubit>;

#endif