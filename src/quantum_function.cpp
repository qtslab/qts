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
    for (int i=0; i<question_size; i++) {
        weights += items[i].weight * solution[i].take;
    }

    return weights;
}

double calculate_values(items_t& items, solution_t& solution) {
    // Calculate the values of the solution
    // std::cout << "calculate_values" << std::endl;
    double values = 0;
    for (int i=0; i<question_size; i++) {
        values += items[i].value * solution[i].take;
    }

    return values;
}

solution_t measure(solution_t& qindividuals) {
    // std::cout << "measure" << std::endl;
    solution_t solution;

    std::random_device rd;  // 取得隨機數種子
    std::mt19937 gen(rd()); // 使用 Mersenne Twister 引擎
    for (int i=0; i<question_size; i++) {
        std::uniform_real_distribution<double> dis(0.0, 1.0);
        double rand_observation = dis(gen);
        // std::cout << "rand_observation in measure: " << rand_observation << std::endl;
        // std::cout << "qindividuals[" << i << "].beta^2: " << qindividuals[i].beta * qindividuals[i].beta << std::endl;

        if (rand_observation > (qindividuals[i].beta * qindividuals[i].beta)) {
            solution.push_back({qindividuals[i].alpha, qindividuals[i].beta, true});
        } else {
            solution.push_back({qindividuals[i].alpha, qindividuals[i].beta, false});
        }
    }

    // for (int i=0; i<question_size; i++) {
    //     std::cout << "solution[" << i << "].take: " << solution[i].take << std::endl;
    // }

    return solution;
}

int adjust_solution(items_t& items, solution_t& solution, double capacity) {
    // Adjust the solution to the capacity constraint
    // std::cout << "adjust_solution" << std::endl;
    double weights = calculate_weights(items, solution);
    std::random_device rd;  // 取得隨機數種子
    std::mt19937 gen(rd()); // 使用 Mersenne Twister 引擎
    int times = 1;

    // std::cout << "weights before: " << weights << std::endl; // debug
    while (weights > capacity) { // overfilled
        // randomly remove an item from the solution until fit the capacity
        std::uniform_int_distribution<int> dis(0, question_size-times);
        int rand_index = dis(gen);
        weights -= items[rand_index].weight;
        // std::cout << "weights: " << weights << std::endl;
        solution[rand_index].take = false;
        times++;
    }

    // std::cout << "weights after: " << weights << std::endl; // debug
    return 0;
}

solution_t find_best(items_t& items, std::vector<solution_t>& neighbors) {
    // Find the best solutions in the neighbors
    // std::cout << "find_best" << std::endl;
    solution_t best_sol = neighbors[0];
    for (auto neighbor : neighbors) {
        if (calculate_values(items, neighbor) > calculate_values(items, best_sol)) {
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
        if (calculate_values(items, neighbor) < calculate_values(items, worst_sol)) {
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
        int  mod_signal = best_sol[i].take - worst_sol[i].take;
        if (qindividuals[i].alpha * qindividuals[i].beta < 0) {
            mod_signal *= -1; // fix answer to 0~90 degree
        }

        // std::cout << "mod_signal: " << mod_signal << std::endl;
        qindividuals[i].alpha = cos(mod_signal*theta)*qindividuals[i].alpha - sin(mod_signal*theta)*qindividuals[i].beta;
        qindividuals[i].beta = sin(mod_signal*theta)*qindividuals[i].alpha + cos(mod_signal*theta)*qindividuals[i].beta;
        // std::cout << "qindividuals[" << i << "].alpha: " << qindividuals[i].alpha << std::endl;
        // std::cout << "qindividuals[" << i << "].beta: " << qindividuals[i].beta << std::endl;
    }

    // std::cout << "update_q end" << std::endl;
    return 0;
}
