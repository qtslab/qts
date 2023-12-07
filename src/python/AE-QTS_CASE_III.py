# https://github.com/pedrolisboa/QTS-0-1-KnapsackProblem

from ast import expr
import time
import sys
import numpy as np
import matplotlib.pyplot as plt
from itertools import compress
from functools import reduce
from math import pi,sqrt,cos,sin
from statistics import mean

n_items = 2000
MaxWeight = 10.0
MinWeight = 1.0

# Generate array of possible items
# Real valued weights
items=np.mod(range(0,n_items),10)+1
#items = np.random.uniform(low=MinWeight, high=MaxWeight, size=(n_items,))
#print(items)

# Integer valued weights
# items = np.random.randint(low=MinWeight,high=MaxWeight, size=(n_items,))
# print(items)

# Bag maximum capacity
C = reduce(lambda x,y : x+y, items) / 2
# Profits array for each item. The item index corresponds to its associated profit value
values = np.vectorize(lambda x: x + 5)(items)

#print("Item search space: %s" % items)
#print("Item values %s" % values)
#print("Bag capacity: %i" % C)


def calculate_weights(_items, solution):
    """Calculate the weight of a solution"""
    return reduce(lambda x,y: x+y, compress(_items, solution), 0)



def measure(qindividuals):
    """Consecutive measures on the qbits in order to generate a classical solution"""
    return np.vectorize(lambda x,y : 0 if (x > np.power(y,2)) else 1)\
                        (np.random.rand(n_items), qindividuals[:, 1])


def gen_nbrs(qindividuals, N):
    """Apply n measures on the qbits to generate classical solutions"""
    neighbours = [np.array(measure(qindividuals)) for i in range(N)]
    return neighbours


def adjust_solution(solution, C):
    """Implements the repair method in order to respect the problem constraints.
       Lamarckian greedy repair, i.e. consecutive deletion of selected items until
       the constraints are  satisfied
    """
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
    """Make the necessary adjustments to keep the generated solutions valid"""
    new_neighbours = [np.array(adjust_solution(vizinho, C)) for vizinho in vizinhos]
    return new_neighbours


def new_best_fit(new_solution, best_fit):
    """Compare the new solution with the current best"""
    if (calculate_weights(values, new_solution) > calculate_weights(values, best_fit)):
        return new_solution
    return best_fit


def find_best_worst(neighbours, tmp, condition = 0):
    """Find the best and worst solution within a neighbourhood"""
    sort_index = np.argsort(tmp)
    return (neighbours[sort_index[(len(tmp)-1-condition)]], neighbours[sort_index[condition]])


def updateQ(best_sol, worst_sol, qindividuals, angle = 0.01):
    """Update the qbits population applying the quantum gate on each qbit.
       The movement is not made for those qbits on the tabu list"""
    theta = angle*np.pi

    for i in range(n_items):
        mod_sinal = best_sol[i] - worst_sol[i]
        # mod_sinal = best_sol[i] - np.mod((best_sol[i]+1),2)
        # Check on which quadrant kth qbit is located and modify theta accordingly
        if (qindividuals[i, 0]*qindividuals[i, 1] < 0) : mod_sinal *= -1
        temp = mod_sinal*theta
        A = np.cos(temp)*qindividuals[i, 0] - np.sin(temp)*qindividuals[i, 1]
        B = np.sin(temp)*qindividuals[i, 0] + np.cos(temp)*qindividuals[i, 1]
        qindividuals[i, 0] = A
        qindividuals[i, 1] = B
        '''
        Ugate = np.array([[cos(mod_sinal*theta), -sin(mod_sinal*theta)],
                          [sin(mod_sinal*theta),  cos(mod_sinal*theta)]])  # Rotation matrix
        qindividuals[i, :] = np.dot(Ugate, qindividuals[i, :])
        '''
    return qindividuals

N = 100  # Neighbourhood size

NumIter = 1000

expTime = 2 #實驗次數
rTime = int(N/2) #轉角度次數(依序優劣排序)
angle = 0.01
expRecord = np.zeros((expTime, NumIter)) #用來記錄結果並畫圖的矩陣
expRecord_new = np.zeros((expTime, NumIter))

iteration_record = np.zeros(expTime)
iteration_record_new = np.zeros(expTime)

qts_time = np.zeros(expTime)
newqts_time = np.zeros(expTime)

print('Multiple rotation experiment')
print(f'CASE III: {n_items} items, {expTime} experiments, {rTime} times rotation')

start_time = time.time()

k = 0
while k < expTime:
    #改過的QTS(將次佳與次差也拿進去轉角度，等於轉了兩次角度)
    start_time_newqts = time.time()
    qindividuals = np.zeros((n_items, 2))
    qindividuals.fill(1 / sqrt(2))
    solution = measure(qindividuals)
    best_fit = solution
    i = 0
    best_fit = adjust_solution(best_fit, C)
    expRecord_new[k][i] = calculate_weights(values, best_fit)
    while i < NumIter:
        neighbours = gen_nbrs(qindividuals, N)
        neighbours = adjust_neighbours(neighbours, C)
        tmp = [np.array(calculate_weights(values, vizinho)) for vizinho in neighbours]
        (best_solution, worst_solution) = find_best_worst(neighbours, tmp)
        best_fit = new_best_fit(best_solution, best_fit)
        expRecord_new[k][i] = calculate_weights(values, best_fit)
        j = 0
        while j < rTime: #用迴圈跑要更新角度的次數
            (best_solution, worst_solution) = find_best_worst(neighbours, tmp, j)
            qindividuals = updateQ(best_solution, worst_solution, qindividuals, angle/(j+1))#更新角度
            j = j + 1
        i = i + 1
    newqts_time[k] = time.time() - start_time_newqts
    best_fit = None
    ii = 1
    while ii < NumIter:
        if expRecord_new[k][ii-1] < expRecord_new[k][ii]:
            iteration_record_new[k] = ii
        ii = ii + 1


    #原始的QTS
    start_time_qts = time.time()
    qindividuals = np.zeros((n_items, 2))
    qindividuals.fill(1 / sqrt(2))
    solution = measure(qindividuals)
    best_fit = solution
    i = 0
    best_fit = adjust_solution(best_fit, C)
    expRecord[k][i] = calculate_weights(values, best_fit)
    while i < NumIter:
        neighbours = gen_nbrs(qindividuals, N)
        neighbours = adjust_neighbours(neighbours, C)
        tmp = [np.array(calculate_weights(values, vizinho)) for vizinho in neighbours]
        (best_solution, worst_solution) = find_best_worst(neighbours, tmp)
        best_fit = new_best_fit(best_solution, best_fit)
        expRecord[k][i] = calculate_weights(values, best_fit)
        qindividuals = updateQ(best_solution, worst_solution, qindividuals)
        i = i + 1
    qts_time[k] = time.time() - start_time_qts
    best_fit = None
    ii = 1
    while ii < NumIter:
        if expRecord[k][ii-1] < expRecord[k][ii]:
            iteration_record[k] = ii
        ii = ii + 1



    k = k + 1

    #print("Best solution profit %f" % calculate_weights(values, best_fit))
    #print("Best solution weight: %f" % calculate_weights(items, best_fit))
    if (k-1) % 5 == 0:
        sys.stdout.write(f"Exp time: {(k-1)}, running time : {round((time.time() - start_time))} s\n")
        sys.stdout.flush()

print("Running time : %.2f seconds" % (time.time() - start_time))
print(expRecord[:,999])
print(expRecord_new[:,999])
print("The average final update iteration of QTS: %.2f" % mean(iteration_record))
print("The average final update iteration of AE-QTS: %.2f" % mean(iteration_record_new))
print("The average time of QTS: %.2f s" % mean(qts_time))
print("The average time of new QTS: %.2f s" % mean(newqts_time))
print("The time gap of QTS and new QTS: %.2f s" % abs(mean(qts_time)-mean(newqts_time)))

plt.plot(range(0,NumIter),np.average(expRecord, axis=0),'--')
plt.plot(range(0,NumIter),np.average(expRecord_new, axis=0))
plt.title(f'CASE III: {n_items} items, {expTime} experiments, \n{rTime} times rotation, angle: {angle}, total time: {round(time.time() - start_time)}s\n')
plt.legend(['QTS','AE-QTS'], loc='lower right')
plt.xlabel('Iteration')
plt.ylabel('Profit')
plt.show()

#print(qindividuals)