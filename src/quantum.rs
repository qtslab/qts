use crate::types::Items;

pub fn calculate_weights(items: &Items, solution: Solution) -> f64{
    println!("Calculating weights...");
}

pub fn calculate_values(items: &Items, solution: Solution) -> f64 {
    println!("Calculating values...");
}

pub fn measure(qubits: &Qubits) -> Solution {
    println!("Measuring...");
}

pub fn adjust_solution(items: &Items, solution: Solution, qubits: &Qubits) -> i32 {
    println!("Adjusting solution...");
}

pub fn update_qubits(best_sol: Solution, worst_sol: Solution, qubits: &mut Qubits) -> i32 {
    println!("Updating qubits...");
}

pub fn update_qubits(best_sol: Solution, worst_sol: Solution, qubits: &mut Qubits, angle: f64) -> i32 {
    println!("Updating qubits...");
}

pub fn sort_soution(items: &Items, solutions: Vec<Solution>) -> Vec<Solution> {
    println!("Sorting solution...");
}

