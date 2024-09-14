use std::f64::consts::SQRT_2;

struct qubit {
    alpha: f64,
    beta: f64,
}

struct item {
    value: f64,
    weight: f64,
    qubit: qubit,
}

impl item {
    fn new(value: f64, weight: f64) -> item {
        item {
            value,
            weight,
            // qubit: qubit {
            //     alpha: 1.0 / SQRT_2,
            //     beta: 1.0 / SQRT_2,
            // },
        }
    }
}

// define a alias for a vector of qubits(for a qubit register)
type Qubits = Vec<qubit>;
// define a alias for a vector of bools(for a solution)
type Solution = Vec<bool>;
// define a alias for a vector of items(for a problem)
type Items = Vec<item>;