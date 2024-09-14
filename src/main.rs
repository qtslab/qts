mod qts;
mod types;
mod case;
mod quantum;

use crate::qts::qts;
use crate::types::{problem, Items};
use crate::case::case_I;

fn main() {
    let mut items: Items = Vec::new();
    let capacity: f64 = case_I(&mut items, problem {
        size: 20,
        capacity: 0.0,
        max_weight: 10.0,
        max_value: 10.0,
        min_weight: 1.0,
        min_value: 1.0,
    });

    let max_gen: i32 = 10;
    qts(&items, capacity, max_gen, 10);
}
