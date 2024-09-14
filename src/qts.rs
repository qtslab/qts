use crate::types::{Items, Qubits, Solution};
use crate::quantum::{
    calculate_weights,
    calculate_values,
    measure,
    adjust_solution,
    update_qubits
};

pub fn qts(items: &Items, capacity: f64, max_gen: i32, N: i32) -> Solution {
    let mut qubits: Qubits = Qubits::new();
    let mut best_fit: Solution = Vec::new();
    adjust_solution(&items, &best_fit, capacity);
    let mut neighbors: Vec<Solution> = vec![Vec::new(); N as usize];
    let mut best_solution: Solution = Vec::new();
    let mut worst_solution: Solution = Vec::new();
    for i in 0..max_gen {
        for j in 0..N {
            neighbors[j as usize] = measure(&qubits);
            adjust_solution(items, &neighbors[j as usize], capacity);
            if j == 0 {
                best_solution = neighbors[j as usize].clone();
                worst_solution = neighbors[j as usize].clone();
            }

            if calculate_values(items, &neighbors[j as usize]) > calculate_values(items, &best_solution) {
                best_solution = neighbors[j as usize].clone();
            } else if calculate_values(items, &neighbors[j as usize]) < calculate_values(items, &worst_solution) {
                worst_solution = neighbors[j as usize].clone();
            }
        }

        if calculate_values(items, &best_solution) > calculate_values(items, &worst_solution) {
            best_fit = best_solution.clone();
        }

        update_qubits(best_solution.clone(), worst_solution.clone(), &mut qubits);
    }

    best_fit
}

