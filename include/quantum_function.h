#ifndef QUANTUM_FUNCTION_H
#define QUANTUM_FUNCTION_H

#include <vector>

#include "type.h"

double calculate_weights(items_t& items, solution_t& solution);
double calculate_values(items_t& items, solution_t& solution);
solution_t measure(solution_t& qindividuals);
int adjust_solution(items_t& items, solution_t& solution, double capacity);
solution_t find_best(items_t& items, std::vector<solution_t>& neighbors);
solution_t find_worst(items_t& items, std::vector<solution_t>& neighbors);
int update_q(solution_t& best_sol, solution_t& worst_sol, solution_t& qindividuals);

#endif