use crate::types::{Items, Qubits, Solution};

use rand::Rng;

pub fn calculate_weights(items: &Items, solution: Solution) -> f64{
    let mut weight: f64 = 0.0;
    for i in 0..items.len() {
        if solution[i] {
            weight += items[i].weight;
        }
    }
    weight
}

pub fn calculate_values(items: &Items, solution: Solution) -> f64 {
    let mut value: f64 = 0.0;
    for i in 0..items.len() {
        if solution[i] {
            value += items[i].value;
        }
    }
    value
}

pub fn measure(qubits: &Qubits) -> Solution {
    let mut solution: Solution = Vec::new();
    for qubit in qubits {
        let mut rng = rand::thread_rng();
        let r: f64 = rng.gen();
        if r < qubit.alpha.powi(2) {
            solution.push(true);
        } else {
            solution.push(false);
        }
    }
    solution
}

pub fn adjust_solution(items: &Items, solution: Solution, qubits: &Qubits) -> i32 {
}

pub fn update_qubits(best_sol: Solution, worst_sol: Solution, qubits: &mut Qubits) -> i32 {
}

pub fn update_qubits(best_sol: Solution, worst_sol: Solution, qubits: &mut Qubits, angle: f64) -> i32 {

}

pub fn sort_soution(items: &Items, solutions: Vec<Solution>, N: i32) -> Vec<Solution> {
    let mut sorted_solutions: Vec<Solution> = solutions.clone();
    let mut values: Vec<f64> = Vec::new();
    for i..N {
        values.push(calculate_values(items, solutions[i]));
    }

    // sort the solutions by their values
    for i..N {
        for j..N {
            if values[i] > values[j] {
                values.swap(i, j);
                sorted_solutions.swap(i, j);
            }
        }
    }

    sorted_solutions;
}

