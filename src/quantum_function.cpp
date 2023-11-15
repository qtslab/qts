#include "constant.h"
#include "type.h"
#include "quantum_function.h"

inline double calculate_weights(question_t question, solution_t solution) {
    
    return 0;
}

inline double measure(qubit q) {
    return 0;
}

inline void gen_neighbours(int index, int items_size) {
    return ;
}

void adjust_solution(solution_t solution, int capacity) {
    return ;
}

inline void aujust_neighbours(solution_t solution, int capacity) {
    return ;
}

inline void new_best_fit(solution_t solution, int capacity) {
    return ;
}

inline void find_best_worst(solution_t neighbours) {
    return ;
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