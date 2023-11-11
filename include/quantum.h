#ifndef QUANTUM_H
#define QUANTUM_H

#include <math.h>

#include "type.h"

qubit update_q(qubit q, int items_size) {
    const double angle = 0.01;

    q.alpha = q.value / (q.value + q.weight);
    q.beta = q.weight / (q.value + q.weight);

    double theta = angle * PI;

    for (int i=0; i<items_size; i++) {
        
    }

    return q;
}

#endif