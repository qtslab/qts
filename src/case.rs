use crate::types::{Items, problem};

use rand::Rng;

pub fn case_I(items: &mut Items, mut problem: problem) -> f64 {
    // weight = random(min_weight, max_weight)
    // value = weight + 5
    let mut rng = rand::thread_rng();
    items.resize(problem.size as usize, Default::default());
    for i in 0..problem.size {
        items[i as usize].weight = rng.gen_range(problem.min_weight..problem.max_weight);
        items[i as usize].value = items[i as usize].weight + 5.0;
        problem.capacity += items[i as usize].weight;
    }

    return problem.capacity / 2.0;
}
