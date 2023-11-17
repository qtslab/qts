#ifndef QUANTUM_FUNCTION_H
#define QUANTUM_FUNCTION_H

#include "type.h"

double calculate_weights(items_t *items, solution_t solution);
solution_t measure(solution_t qindividuals);
solution_t gen_neighbours(solution_t qindividuals, int index);
solution_t adjust_solution(solution_t solution, int capacity);
solution_t new_best_fit(solution_t new_solution, solution_t best_fit);
solution_t adjust_neighbours(solution_t vizinhos, int capacity);
solution_t find_best(solution_t neighbours);
solution_t find_worst(solution_t neighbours);
solution_t update_q(solution_t best_sol, solution_t worst_sol, solution_t qindividuals);

#endif