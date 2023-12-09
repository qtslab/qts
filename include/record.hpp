#ifndef RECORD_HPP
#define RECORD_HPP

#include <fstream>

#include "type.h"
#include "constant.h"
#include "quantum_function.h"

int record_iter(std::ofstream& file, items_t& items, q_t& qindividuals, solution_t& best_fit, int iter) {
    file << iter << "," << calculate_values(items, best_fit) << std::endl;
    return 0;
}

#endif