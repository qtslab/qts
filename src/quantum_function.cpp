#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

#include "constant.h"
#include "type.h"
#include "quantum_function.h"

double calculate_weights(items_t& items, solution_t& solution) {
    // Calculate the weights of the solution
    double weights = 0;
    for (int i=0; i<question_size; i++) {
        weights += items[i].weight * solution[i];
    }

    return weights;
}

double calculate_values(items_t& items, solution_t& solution) {
    // Calculate the values of the solution
    double values = 0;
    for (int i=0; i<question_size; i++) {
        values += items[i].value * solution[i];
    }

    return values;
}

solution_t measure(q_t& qindividuals) {
    solution_t solution;
    std::random_device rd;  // 取得隨機數種子
    std::mt19937 gen(rd()); // 使用 Mersenne Twister 引擎
    for (int i=0; i<question_size; i++) {
        std::uniform_real_distribution<double> dis(0.0, 1.0);
        double rand_observation = dis(gen);
        if (rand_observation > (qindividuals[i].beta * qindividuals[i].beta)) {
            solution.set(i, false);
        } else {
            solution.set(i, true);
        }
    }

    return solution;
}

int adjust_solution(items_t& items, solution_t& solution, double capacity) {
    // Adjust the solution to the capacity constraint
    double weights = calculate_weights(items, solution);
    std::random_device rd;  // 取得隨機數種子
    std::mt19937 gen(rd()); // 使用 Mersenne Twister 引擎
    while (weights > capacity) { // overfilled
        // randomly remove an item from the solution until fit the capacity
        std::uniform_int_distribution<int> dis(0, question_size-1);
        int rand_index = dis(gen);
        if (!solution[rand_index]) {
            continue;
        }

        weights -= items[rand_index].weight;
        solution.set(rand_index, false);
    }

    // while (weights < capacity) { // underfilled
    //     // randomly add an item from the solution until fit the capacity
    //     std::uniform_int_distribution<int> dis(0, question_size-1);
    //     int rand_index = dis(gen);
    //     if (solution[rand_index] || weights + items[rand_index].weight > capacity) {
    //         continue;
    //     }

    //     weights += items[rand_index].weight;
    //     solution.set(rand_index, true);
    // }

    return 0;
}

int update_q(solution_t& best_sol, solution_t& worst_sol, q_t& qindividuals) {
    // Update the qubits popolation applying the quantum gate on each qubit
    // The movement is not made for those qubits on the tabu list
    const double theta = 0.01 * M_PI;
    for (int i=0; i<question_size; i++) {
        int  mod_signal = best_sol[i] -worst_sol[i];
        if (qindividuals[i].alpha * qindividuals[i].beta < 0) {
            mod_signal *= -1; // fix answer to 0~90 degree
        }

        double a = cos(mod_signal*theta)*qindividuals[i].alpha - sin(mod_signal*theta)*qindividuals[i].beta;
        double b = sin(mod_signal*theta)*qindividuals[i].alpha + cos(mod_signal*theta)*qindividuals[i].beta;

        qindividuals[i].alpha = a;
        qindividuals[i].beta = b;
    }

    return 0;
}

int update_q(solution_t& best_sol, solution_t& worst_sol, q_t& qindividuals, double angle) {
    // Update the qubits popolation applying the quantum gate on each qubit
    // The movement is not made for those qubits on the tabu list
    const double theta = angle * M_PI;
    for (int i=0; i<question_size; i++) {
        int  mod_signal = best_sol[i] - worst_sol[i];
        if (qindividuals[i].alpha * qindividuals[i].beta < 0) {
            mod_signal *= -1; // fix answer to 0~90 degree
        }

        double a = cos(mod_signal*theta)*qindividuals[i].alpha - sin(mod_signal*theta)*qindividuals[i].beta;
        double b = sin(mod_signal*theta)*qindividuals[i].alpha + cos(mod_signal*theta)*qindividuals[i].beta;

        qindividuals[i].alpha = a;
        qindividuals[i].beta = b;
    }

    return 0;
}

std::vector<solution_t> sort_solution(items_t& items, std::vector<solution_t>& solutions, int N) {
    // Sort the solutions by their values
    std::vector<solution_t> sorted_solutions(N);
    std::vector<double> values(N);
    for (int i=0; i<N; i++) {
        values[i] = calculate_values(items, solutions[i]);
    }

    std::vector<int> index(N);
    for (int i=0; i<N; i++) {
        index[i] = i;
    }

    std::sort(index.begin(), index.end(), [&values](int i1, int i2) {return values[i1] > values[i2];});

    for (int i=0; i<N; i++) {
        sorted_solutions[i] = solutions[index[i]];
        // std::cout << "solution " << i << ": " << values[index[i]] << std::endl;
    }

    return sorted_solutions;
}
