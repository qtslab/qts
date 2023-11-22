#include <iostream>
#include <random>
#include <vector>

#include "constant.h"
#include "type.h"
#include "quantum_function.h"

double calculate_weights(items_t& items, solution_t& solution) {
    // Calculate the weights of the solution
    // std::cout << "calculate_weights" << std::endl;
    double weights = 0;
    std::cout << "solution.size(): " << solution.size() << std::endl;
    solution.resize(question_size);
    for (int i=0; i<question_size; i++) {
        if (solution[i].take) {
            weights += items[i].weight;
        }
    }

    return weights;
}

solution_t measure(solution_t& qindividuals) {
    // std::cout << "measure" << std::endl;
    solution_t solution(question_size);

    std::random_device rd;  // 取得隨機數種子
    std::mt19937 gen(rd()); // 使用 Mersenne Twister 引擎
    for (int i=0; i<question_size; i++) {
        std::uniform_real_distribution<double> dis(0.0, 1.0);
        double rand_observation = dis(gen);
        qubit q = qindividuals[i];
        if (rand_observation < (qindividuals[i].beta * qindividuals[i].beta)) {
            q.take = true;
            solution.push_back(q);
        } else {
            q.take = false;
            solution.push_back(q);
        }
    }

    return solution;
}

std::vector<solution_t> gen_neighbors(solution_t& qindividuals, int n) {
    // Apply n measures on the qubits to generate classical solutions
    // std::cout << "gen_neighbors" << std::endl;
    std::vector<solution_t> neighbors;
    for (int i=0; i<n; i++) {
        solution_t solution = measure(qindividuals);
        neighbors.push_back(solution);
    }

    return neighbors;
}

solution_t adjust_solution(items_t& items, solution_t& solution, double capacity) {
    // Adjust the solution to the capacity constraint
    // std::cout << "adjust_solution" << std::endl;
    double weights = calculate_weights(items, solution); // items not defined
    std::random_device rd;  // 取得隨機數種子
    std::mt19937 gen(rd()); // 使用 Mersenne Twister 引擎
    int times = 1;
    while (weights > capacity) {
        // randomly remove an item from the solution until fit the capacity
        std::uniform_int_distribution<int> dis(0, question_size-times);
        int rand_index = dis(gen);
        weights -= items[rand_index].weight;
        solution[rand_index].take = false;
        times++;
    }

    return solution;
}

int adjust_neighbors(items_t& items, std::vector<solution_t>& vizinhos, double capacity) {
    // std::cout << "adjust_neighbors" << std::endl;
    for (auto vizinho : vizinhos) {
        vizinho = adjust_solution(items, vizinho, capacity);
    }

    return 0;
}

solution_t new_best_fit(items_t& items, solution_t& new_solution, solution_t& best_fit) {
    // Compare the new solution with the best fit
    // std::cout << "new_best_fit" << std::endl;
    if (calculate_weights(items, new_solution) > calculate_weights(items, best_fit)) {
        return new_solution;
    }

    return best_fit;
}

solution_t find_best(items_t& items, std::vector<solution_t>& neighbors) {
    // Find the best solutions in the neighbors
    // std::cout << "find_best" << std::endl;
    solution_t best_sol = neighbors[0];
    for (auto neighbor : neighbors) {
        if (calculate_weights(items, neighbor) > calculate_weights(items, best_sol)) {
            best_sol = neighbor;
        }
    }

    return best_sol;
}

solution_t find_worst(items_t& items, std::vector<solution_t>& neighbors) {
    // Find the worst solutions in the neighbors
    // std::cout << "find_worst" << std::endl;
    solution_t worst_sol = neighbors[0];
    for (auto neighbor : neighbors) {
        if (calculate_weights(items, neighbor) < calculate_weights(items, worst_sol)) {
            worst_sol = neighbor;
        }
    }

    return worst_sol;
}


int update_q(solution_t& best_sol, solution_t& worst_sol, solution_t& qindividuals) {
    // Update the qubits popolation applying the quantum gate on each qubit
    // The movement is not made for those qubits on the tabu list
    // std::cout << "update_q" << std::endl;
    const double theta = 0.01 * PI;
    for (int i=0; i<question_size; i++) {
        int  mod_signal = best_sol[i].take - worst_sol[i].take; // best_sol[i].alpha - worst_sol[i].alpha;
        if (qindividuals[i].alpha * qindividuals[i].beta < 0) {
            mod_signal *= -1; // fix answer to 0~90 degree
        }

        qindividuals[i].alpha = cos(mod_signal*theta)*qindividuals[i].alpha - sin(mod_signal*theta)*qindividuals[i].beta;
        qindividuals[i].beta = sin(mod_signal*theta)*qindividuals[i].alpha + cos(mod_signal*theta)*qindividuals[i].beta;
    }

    // std::cout << "update_q end" << std::endl;
    return 0;
}
