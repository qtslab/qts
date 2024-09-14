mod qts;
mod types;
mod case;
mod quantum;
mod debug;

use crate::qts::qts;
use crate::types::{problem, Items};
use crate::case::case_I;

use crate::debug::print_items;

fn main() {
    let mut items: Items = Vec::new();
    let problem = problem::default();
    let capacity: f64 = case_I(&mut items, problem) as f64;

    print_items(&items);

    let max_gen: i32 = 10;
    qts(&items, capacity, max_gen, 10);
}
