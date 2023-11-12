#ifndef QUANTUM_FUNCTION_H
#define QUANTUM_FUNCTION_H

#include <math.h>

#include "type.h"

inline double calculate_weights(question_t question, solution_t solution);
inline double measure(qubit q);
inline void gen_neighbours(int index, int items_size);
void adjust_solution(solution_t solution, int capacity);
inline void aujust_neighbours(solution_t solution, int capacity);
inline void new_best_fit(solution_t solution, int capacity);
inline void find_best_worst(solution_t neighbours);
qubit update_q(qubit q, int items_size);

#endif