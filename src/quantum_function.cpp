#include <iostream>
#include <set>

#include "constant.h"
#include "type.h"
#include "quantum_function.h"

double calculate_weights(items_t& items, solution_t& solution) {
    // Calculate the weights of the solution
    std::cout << "calculate_weights" << std::endl;
    double weights = 0;
    for (int i=0; i<question_size; i++) {
        if (solution[i].take) {
            weights += items[i].weight;
        }
    }

    return weights;
}

solution_t measure(solution_t& qindividuals) {
    // Consecutive measurs on the qubit in order to generate a classical solution
    std::cout << "measure" << std::endl;
    solution_t solution;
    return solution;
}

std::set<solution_t> gen_neighbors(solution_t& qindividuals, int index) {
    // Apply n measures on the qubits to generate classical solutions
    std::cout << "gen_neighbors" << std::endl;
    std::set<solution_t> neighbors;
    for (int i=0; i<question_size; i++) {
        // neighbors[i].alpha = 1/sqrt(2);
        // neighbors[i].beta = 1/sqrt(2);
        // neighbors[i].take = false;
    }

    return neighbors;
}

solution_t adjust_solution(solution_t& solution, int capacity) {
    // Adjust the solution to the capacity constraint
    std::cout << "adjust_solution" << std::endl;
    solution_t item_selected = solution;
    // double weights = calculate_weights(items, solution); // items not defined
    // while (weights > capacity) {
        // not done
    // }

    return solution;
}

std::set<solution_t> adjust_neighbors(std::set<solution_t>& vizinhos, int capacity) {
    std::cout << "adjust_neighbors" << std::endl;
    return vizinhos;
}

solution_t new_best_fit(solution_t& new_solution, solution_t& best_fit) {
    // Compare the new solution with the best fit
    std::cout << "new_best_fit" << std::endl;
    // if (calculate_weights(items, new_solution) > calculate_weights(items, best_fit)) {
    //     return new_solution;
    // }

    return best_fit;
}

solution_t find_best(std::set<solution_t>& neighbors) {
    // Find the best solutions in the neighbors
    std::cout << "find_best" << std::endl;
    solution_t best_sol;



    return best_sol;
}

solution_t find_worst(std::set<solution_t>& neighbors) {
    // Find the worst solutions in the neighbors
    std::cout << "find_worst" << std::endl;
    solution_t worst_sol;

    return worst_sol;
}


solution_t update_q(solution_t& best_sol, solution_t& worst_sol, solution_t& qindividuals) {
    // Update the qubits popolation applying the quantum gate on each qubit
    // The movement is not made for those qubits on the tabu list
    std::cout << "update_q" << std::endl;
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