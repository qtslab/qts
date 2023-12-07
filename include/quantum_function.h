#ifndef QUANTUM_FUNCTION_H
#define QUANTUM_FUNCTION_H

#include <vector>

#include "type.h"

double calculate_weights(items_t& items, solution_t& solution);
double calculate_values(items_t& items, solution_t& solution);
solution_t measure(q_t& qindividuals);
int adjust_solution(items_t& items, solution_t& solution, double capacity);
int update_q(solution_t& best_sol, solution_t& worst_sol, q_t& qindividuals);
int update_q(solution_t& best_sol, solution_t& worst_sol, q_t& qindividuals, double angle);
std::vector<solution_t> sort_solution(items_t& items, std::vector<solution_t>& solutions, int N);

#endif