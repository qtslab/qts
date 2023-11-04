#include <iostream>

int main(int argc, char* argv[]) {
    int t = 0;
    int max_gen = 100;
    int n = 10;
    int p = 10; // The number of solutions in P(t)
    int q = 10; // The number of solutions in Q(t)
    int sb = 0; // The best solution in P(t)
    int b = 0; // The best solution in P(t)
    int P[t][p];
    int Q[t][q];

    // Initialize P(t)
    for (int i = 0; i < p; i++) {
        P[t][i] = 0;
    }

    // Initialize Q(t)
    for (int i = 0; i < q; i++) {
        Q[t][i] = 0;
    }

    // Initialize the best solution sb from P(t) by measuring Q(t), repairing and evaluating P(t)
    for (int i = 0; i < p; i++) {
        // Measure Q(t)
        // Repair P(t)
        // Evaluate P(t)
        if (P[t][i] > sb) {
            sb = P[t][i];
        }
    }

    while (t < max_gen) {
        t++;

        // Make P(t) with N solutions by measuring Q(t - 1)
        for (int i = 0; i < p; i++) {
            // Measure Q(t - 1)
        }

        // Repair P(t)
        for (int i = 0; i < p; i++) {
            // Repair P(t)
        }

        // Evaluate P(t)
        for (int i = 0; i < p; i++) {
            // Evaluate P(t)
        }

        // Update Q(t) by P(t) // ▷ The difference from QTS
        for (int i = 0; i < p; i++) {
            // Update Q(t) by P(t)
        }

        // Select the best solution b from P(t)
        for (int i = 0; i < p; i++) {
            if (P[t][i] > b) {
                b = P[t][i];
            }
        }

        if (b > sb) {
            sb = b;
        }
    }

    return 0;
}

/*
    1 : t ← 0
    2 : initialize Q(t)
    3 : initialize the best solution sb from P (t) by measuring Q(t), repairing and evaluating P (t)
    4 : while t < MAX GEN do
    5 :     t ← t + 1
    6 :     make P (t) with N solutions by measuring Q(t - 1)
    7 :     repair P (t)
    8 :     evaluate P (t)
    9 :     update Q(t) by P (t) // ▷ The difference from QTS
    10:     select the best solution b from P (t)
    11:     if b > sb then
    12:         sb ← b
    13:     end if
    14: end while
*/