#include "constant.h"
#include "type.h"
#include "global.h"
#include "quantum_function.h"

double calculate_weights(solution_t solution) {
    double weights = 0;
    for (int i=0; i<question_size; i++) {
        if (solution[i].take) {
            weights += items[i].weight;
        }
    }

    return weights;
}

inline double measure(qubit q) {

    return 0;
}

inline solution_t gen_neighbours(int index, int items_size) {
    solution_t neighbours;
    return neighbours;
}

solution_t adjust_solution(solution_t solution, int capacity) {
    
    return solution;
}

inline solution_t adjust_neighbours(solution_t solution, int capacity) {
    
    return solution;
}

inline solution_t new_best_fit(solution_t solution, solution_t best_fit, int capacity) {
    if (calculate_weights(solution) > calculate_weights(best_fit)) {
        return solution;
    }

    return best_fit;
}

inline solution_t find_best_worst(solution_t neighbours) {
    
    return neighbours;
}

qubit update_q(solution_t best_sol, solution_t worst_sol, qubit q, int items_size) {
    const double angle = 0.01;
    double theta = angle * PI;

    double mod_signal = 0;
    for (int i=0; i<items_size; i++) {
        mod_signal = best_sol[i].alpha - worst_sol[i].alpha;
        if (1) {
            mod_signal *= -1;
        }
    }

    return q;
}