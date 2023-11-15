import time
import numpy as np
from itertools import compress
from functools import reduce
from math import pi,sqrt,cos,sin

N = 10  # Neighbourhood size
n_items = 100
MaxWeight = 10.0
MinWeight = 1.0
items = np.random.uniform(low=MinWeight, high=MaxWeight, size=(n_items,))
C = reduce(lambda x,y : x+y, items) / 2 # Bag maximum capacity
values = np.vectorize(lambda x: x + 5)(items)

def calculate_weights(items, solution):
    return reduce(lambda x,y: x+y, compress(items, solution), 0)

def measure(qindividuals):
    return np.vectorize(lambda x,y : 1 if (x > np.power(y,2)) else 0)\
                        (np.random.rand(n_items), qindividuals[:, 1])

def adjust_solution(solution, C):
    itemsSelected = solution.nonzero()[0]
    weight = calculate_weights(items, solution)
    while (weight > C):
        r = np.random.randint(0,itemsSelected.shape[0]-1)
        j = itemsSelected[r]
        solution[j] = 0
        weight = weight - items[j]
        itemsSelected = np.delete(itemsSelected, r)
    return solution

def adjust_neighbours(vizinhos, C):
    new_neighbours = [np.array(adjust_solution(vizinho, C)) for vizinho in vizinhos]
    return new_neighbours

def new_best_fit(new_solution, best_fit):
    if (calculate_weights(values, new_solution) > calculate_weights(values, best_fit)):
        return new_solution
    return best_fit

def find_best_worst(neighbours):
    tmp = [np.array(calculate_weights(values, vizinho)) for vizinho in neighbours]
    return (neighbours[np.argmax(tmp)], neighbours[np.argmin(tmp)])

def updateQ(worst_sol, best_sol, qindividuals):
    theta = 0.01*pi
    for i in range(n_items):
        mod_sinal = best_sol[i] - worst_sol[i]
        # Check on which quadrant kth qbit is located and modify theta accordingly
        if (qindividuals[i, 0]*qindividuals[i, 1] < 0) : mod_sinal *= -1

        Ugate = np.array([[cos(mod_sinal*theta), -sin(mod_sinal*theta)],
                          [sin(mod_sinal*theta),  cos(mod_sinal*theta)]])  # Rotation matrix
        qindividuals[i, :] = np.dot(Ugate, qindividuals[i, :])
    return qindividuals

qindividuals = np.zeros((n_items, 2))
qindividuals.fill(1 / sqrt(2))
solution = measure(qindividuals)
best_fit = solution
NumIter = 1000
best_fit = adjust_solution(best_fit, C)

i = 0
while i < NumIter:
    i = i + 1
    neighbours = [np.array(measure(qindividuals)) for i in range(N)]
    neighbours = adjust_neighbours(neighbours, C)
    (best_solution, worst_solution) = find_best_worst(neighbours)
    best_fit = new_best_fit(best_solution, best_fit)
    qindividuals = updateQ(best_solution, worst_solution, qindividuals)