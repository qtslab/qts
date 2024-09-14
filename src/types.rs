use std::f64::consts::SQRT_2;

pub struct qubit {
    pub alpha: f64,
    pub beta: f64,
}

pub struct item {
    pub value: f64,
    pub weight: f64,
}

pub struct problem {
    pub size: i32,
    pub capacity: f64,
    pub max_weight: f64,
    pub max_value: f64,
    pub min_weight: f64,
    pub min_value: f64,
}

impl item {
    fn new(value: f64, weight: f64) -> item {
        item {
            value,
            weight,
        }
    }
}

impl qubit {
    fn new(alpha: f64, beta: f64) -> qubit {
        qubit {
            alpha: 1.0 / SQRT_2,
            beta: 1.0 / SQRT_2,
        }
    }
}

// define a alias for a vector of qubits(for a qubit register)
pub type Qubits = Vec<qubit>;
// define a alias for a vector of bools(for a solution)
pub type Solution = Vec<bool>;
// define a alias for a vector of items(for a problem)
pub type Items = Vec<item>;
