#ifndef QUANTUM_FUNCTION_H
#define QUANTUM_FUNCTION_H

#include <math.h>

#include "type.h"

inline double calculate_weights(items_t items, solution_t solution);
inline double measure(qubit q);
inline solution_t gen_neighbours(int index, int items_size);
solution_t adjust_solution(solution_t solution, int capacity);
inline solution_t aujust_neighbours(solution_t solution, int capacity);
inline solution_t new_best_fit(solution_t solution, solution_t best_fit, int capacity);
inline solution_t find_best_worst(solution_t neighbours);
qubit update_q(qubit q, int items_size);

#endif