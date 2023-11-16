#include "constant.h"
#include "type.h"
#include "quantum_function.h"

double calculate_weights(items_t *items, solution_t solution) {
    double weights = 0;
    for (int i=0; i<question_size; i++) {
        if (solution[i].take) {
            weights += items[i]->weight;
        }
    }

    return weights;
}

inline solution_t measure(solution_t qindividuals) {

    return qindividuals;
}

inline solution_t gen_neighbours(solution_t qindividuals, int index) {
    solution_t neighbours;
    for (int i=0; i<question_size; i++) {
        neighbours[i].alpha = 1/sqrt(2);
        neighbours[i].beta = 1/sqrt(2);
        neighbours[i].take = false;
    }

    return neighbours;
}

solution_t adjust_solution(solution_t solution, int capacity) {
    solution_t item_selected = solution;
    // double weights = calculate_weights(items, solution); // items not defined
    // while (weights > capacity) {
        // not done
    // }

    return solution;
}

inline solution_t adjust_neighbours(solution_t vizinhos, int capacity) {

    return vizinhos;
}

solution_t new_best_fit(solution_t new_solution, solution_t best_fit) {
    // if (calculate_weights(items, new_solution) > calculate_weights(items, best_fit)) {
    //     return new_solution;
    // }

    return best_fit;
}

inline solution_t find_best_worst(solution_t neighbours) {

    return neighbours;
}

solution_t update_q(solution_t best_sol, solution_t worst_sol, solution_t qindividuals) {
    const double angle = 0.01;
    double theta = angle * PI;

    double mod_signal = 0;
    for (int i=0; i<question_size; i++) {
        mod_signal = best_sol[i].alpha - worst_sol[i].alpha;
        if (qindividuals[i].alpha * qindividuals[i].beta < 0) {
            mod_signal *= -1;
        }

        solution_t Ugate = {{cos(mod_signal*theta), -sin(mod_signal*theta)}, {sin(mod_signal*theta), cos(mod_signal*theta)}};
        qindividuals[i].alpha = Ugate[i].alpha * qindividuals[i].alpha;
    }

    return qindividuals;
}