#ifndef QUANTUM_FUNCTION_H
#define QUANTUM_FUNCTION_H

#include <set>

#include "type.h"

double calculate_weights(items_t& items, solution_t& solution);
solution_t measure(qubit qindividuals);
std::set<solution_t> gen_neighbors(qubit qindividuals, int index);
solution_t adjust_solution(solution_t& solution, int capacity);
solution_t new_best_fit(solution_t& new_solution, solution_t& best_fit);
std::set<solution_t> adjust_neighbors(std::set<solution_t>& vizinhos, int capacity);
solution_t find_best(std::set<solution_t>& neighbors);
solution_t find_worst(std::set<solution_t>& neighbors);
qubit update_q(solution_t& best_sol, solution_t& worst_sol, qubit qindividuals);

#endif