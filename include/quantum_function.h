#ifndef QUANTUM_FUNCTION_H
#define QUANTUM_FUNCTION_H

#include <vector>

#include "type.h"

double calculate_weights(items_t& items, solution_t& solution);
double calculate_values(items_t& items, solution_t& solution);
solution_t measure(q_t& qindividuals);
int adjust_solution(items_t& items, solution_t& solution, double capacity);
int update_q(solution_t& best_sol, solution_t& worst_sol, q_t& qindividuals);
int sort_solution(items_t& items, std::vector<solution_t>& solutions, std::vector<solution_t>& sorted_solutions);

#endif