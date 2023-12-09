#ifndef RECORD_HPP
#define RECORD_HPP

#include <fstream>

#include "type.h"
#include "constant.h"
#include "quantum_function.h"

int record_iter(std::ofstream& file, double value, int iter) {
    file << iter << "," << value << std::endl;
    return 0;
}

#endif