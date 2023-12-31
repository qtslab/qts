import numpy as np
import matplotlib.pyplot as plt
from itertools import compress
from functools import reduce
from math import pi,sqrt,cos,sin
from statistics import mean

n_items = 2000
MaxWeight = 10.0
MinWeight = 1.0

items = np.random.uniform(low=MinWeight, high=MaxWeight, size=(n_items,))

C = reduce(lambda x,y : x+y, items) / 2
values = np.vectorize(lambda x: x + 5)(items)

def calculate_weights(_items, solution):
    return reduce(lambda x,y: x+y, compress(_items, solution), 0)

def measure(qindividuals):
    return np.vectorize(lambda x,y : 0 if (x > np.power(y,2)) else 1)\
                        (np.random.rand(n_items), qindividuals[:, 1])

def gen_nbrs(qindividuals, N):
    neighbours = [np.array(measure(qindividuals)) for i in range(N)]
    return neighbours

def adjust_solution(solution, C):
    itemsSelected = solution.nonzero()[0]
    overfilled = False
    weight = calculate_weights(items, solution)
    if weight > C:
        overfilled = True
    while (overfilled):
        r = np.random.randint(0,itemsSelected.shape[0])
        i = itemsSelected[r]
        solution[i] = 0
        weight = weight - items[i]
        itemsSelected = np.delete(itemsSelected, r)
        if weight <= C:
            overfilled = False

    while (not overfilled):
        j = np.random.randint(0,n_items)
        while (solution[j]==1):
            j = np.random.randint(0,n_items)
        solution[j] = 1
        weight = weight + items[j]
        if weight > C:
            solution[j] = 0
            overfilled = True
    return solution


def adjust_neighbours(vizinhos, C):
    new_neighbours = [np.array(adjust_solution(vizinho, C)) for vizinho in vizinhos]
    return new_neighbours

def new_best_fit(new_solution, best_fit):
    if (calculate_weights(values, new_solution) > calculate_weights(values, best_fit)):
        return new_solution
    return best_fit

def find_best_worst(neighbours, tmp, condition = 0):
    sort_index = np.argsort(tmp)
    return (neighbours[sort_index[(len(tmp)-1-condition)]], neighbours[sort_index[condition]])

def updateQ(best_sol, worst_sol, qindividuals, angle = 0.01):
    theta = angle*pi

    for i in range(n_items):
        mod_sinal = best_sol[i] - worst_sol[i]
        # mod_sinal = best_sol[i] - np.mod((best_sol[i]+1),2)
        # Check on which quadrant kth qbit is located and modify theta accordingly
        if (qindividuals[i, 0]*qindividuals[i, 1] < 0) : mod_sinal *= -1

        A = cos(mod_sinal*theta)*qindividuals[i, 0] - sin(mod_sinal*theta)*qindividuals[i, 1]
        B = sin(mod_sinal*theta)*qindividuals[i, 0] + cos(mod_sinal*theta)*qindividuals[i, 1]
        qindividuals[i, 0] = A
        qindividuals[i, 1] = B
    return qindividuals

N = 100  # Neighbourhood size

NumIter = 100
angle = 0.01

qindividuals = np.zeros((n_items, 2))
qindividuals.fill(1 / sqrt(2))
solution = measure(qindividuals)
best_fit = solution
i = 0
best_fit = adjust_solution(best_fit, C)
while i < NumIter:
    neighbours = gen_nbrs(qindividuals, N)
    neighbours = adjust_neighbours(neighbours, C)
    tmp = [np.array(calculate_weights(values, vizinho)) for vizinho in neighbours]
    (best_solution, worst_solution) = find_best_worst(neighbours, tmp)
    best_fit = new_best_fit(best_solution, best_fit)
    qindividuals = updateQ(best_solution, worst_solution, qindividuals)
    i = i + 1

print("QTS: ", calculate_weights(values, best_fit))