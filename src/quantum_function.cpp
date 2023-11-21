#include <iostream>
#include <set>
#include <random>

#include "constant.h"
#include "type.h"
#include "quantum_function.h"

double calculate_weights(items_t& items, solution_t& solution) {
    // Calculate the weights of the solution
    // std::cout << "calculate_weights" << std::endl;
    double weights = 0;
    // for (int i=0; i<question_size; i++) {
    //     if (solution[i].take) {
    //         weights += items[i].weight;
    //     }
    // }

    return weights;
}

solution_t measure(solution_t& qindividuals) {
    // std::cout << "measure" << std::endl;
    solution_t solution(question_size);

    std::random_device rd;  // 取得隨機數種子
    std::mt19937 gen(rd()); // 使用 Mersenne Twister 引擎
    for (int i = 0; i < question_size; ++i) {
        std::uniform_real_distribution<double> dis(0.0, 1.0);
        double rand_observation = dis(gen);
        if (rand_observation < (qindividuals[i].beta * qindividuals[i].beta)) {
            solution.push_back(qubit{qindividuals[i].alpha, qindividuals[i].beta, true});
        } else {
            solution.push_back(qubit{qindividuals[i].alpha, qindividuals[i].beta, false});
        }
    }

    return solution;
}

std::set<solution_t> gen_neighbors(solution_t& qindividuals, int n) {
    // Apply n measures on the qubits to generate classical solutions
    // std::cout << "gen_neighbors" << std::endl;
    std::set<solution_t> neighbors;
    for (int i=0; i<n; i++) {
        // neighbors.insert(measure(qindividuals));
    }

    return neighbors;
}

solution_t adjust_solution(items_t& items, solution_t& solution, int capacity) {
    // Adjust the solution to the capacity constraint
    std::cout << "adjust_solution" << std::endl;
    double weights = calculate_weights(items, solution); // items not defined
    std::random_device rd;  // 取得隨機數種子
    std::mt19937 gen(rd()); // 使用 Mersenne Twister 引擎
    int times = 1;
    while (weights > capacity) {
        // randomly remove an item
        std::uniform_int_distribution<int> dis(0, question_size-times);
        int rand_index = dis(gen);
        item selected = items[rand_index];
        weights -= selected.weight;
        solution[rand_index].take = false;
        times++;
    }

    return solution;
}

std::set<solution_t> adjust_neighbors(items_t& items, std::set<solution_t>& vizinhos, int capacity) {
    // std::cout << "adjust_neighbors" << std::endl;
    for (auto vizinho : vizinhos) {
        vizinho = adjust_solution(items, vizinho, capacity);
    }

    return vizinhos;
}

solution_t new_best_fit(items_t& items, solution_t& new_solution, solution_t& best_fit) {
    // Compare the new solution with the best fit
    // std::cout << "new_best_fit" << std::endl;
    if (calculate_weights(items, new_solution) > calculate_weights(items, best_fit)) {
        return new_solution;
    }

    return best_fit;
}

solution_t find_best(items_t& items, std::set<solution_t>& neighbors) {
    // Find the best solutions in the neighbors
    // std::cout << "find_best" << std::endl;
    solution_t best_sol;

    for (auto neighbor : neighbors) {
        if (calculate_weights(items, neighbor) > calculate_weights(items, best_sol)) {
            best_sol = neighbor;
        }
    }

    return best_sol;
}

solution_t find_worst(items_t& items, std::set<solution_t>& neighbors) {
    // Find the worst solutions in the neighbors
    // std::cout << "find_worst" << std::endl;
    solution_t worst_sol;

    for (auto neighbor : neighbors) {
        if (calculate_weights(items, neighbor) < calculate_weights(items, worst_sol)) {
            worst_sol = neighbor;
        }
    }

    return worst_sol;
}


solution_t update_q(solution_t& best_sol, solution_t& worst_sol, solution_t& qindividuals) {
    // Update the qubits popolation applying the quantum gate on each qubit
    // The movement is not made for those qubits on the tabu list
    std::cout << "update_q" << std::endl;
    double theta = 0.01 * PI;

    double mod_signal;
    for (int i=0; i<question_size; i++) {
        mod_signal = 0; // best_sol[i].alpha - worst_sol[i].alpha;
        if (qindividuals[i].alpha * qindividuals[i].beta < 0) {
            mod_signal *= -1; // fix answer to 0~90 degree
        }

        solution_t Ugate = {{cos(mod_signal*theta), -sin(mod_signal*theta)},
                            {sin(mod_signal*theta), cos(mod_signal*theta)}};
        qindividuals[i].alpha = Ugate[i].alpha * qindividuals[i].alpha;
        qindividuals[i].beta = Ugate[i].beta * qindividuals[i].beta;
    }

    return qindividuals;
}
