import random
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from functools import reduce
import csv

MAXITER = 1000#代數
ts_time = 1#幾次
n_items = 1000#物品數量

# 物品列表，每个物品包括重量和价值

MaxWeight = 10.0
MinWeight = 1.0

#畫圖區
y = []
x = []
x_values = []
ts_total = []

for _ in range(ts_time):
    y.append([None] * MAXITER)
for i in range(1,MAXITER+1):
    x_values.append(i)
    x.append(i)
#畫圖區

def ts_initial_solution():
    return [random.randint(0, 1) for _ in range(len(ts_items))]
# ts_current_solution = ts_initial_solution()

# ac = []

def tabu_search():
    tabu_list = []
    ts_best_solution = None
    ts_current_solution = ts_initial_solution()
    ts_current_solution = ts_adjust_solution(ts_current_solution, Max_weight, ts_items, n_items)
    ts_current_weight = sum(ts_current_solution[i] * ts_items[i][0] for i in range(len(ts_items)))
    ts_current_value = sum(ts_current_solution[i] * ts_items[i][1] for i in range(len(ts_items)))
    ts_best_solution = ts_current_solution
    x = ts_best_solution
    for i in range(MAXITER):
        #print(i)
        neighbors = ts_get_neighbors(ts_current_solution, tabu_list)
        candidate_set = [neighbor for neighbor in neighbors if neighbor not in tabu_list]

        best_candidate = ts_find_best_solution(candidate_set, tabu_list)

        if ts_evaluate_solution(best_candidate, ts_items) > ts_evaluate_solution(ts_current_solution, ts_items) and ts_evaluate_weight(best_candidate, ts_items) <= Max_weight:
            ts_current_solution = best_candidate
            ts_current_weight = ts_evaluate_weight(best_candidate, ts_items)
            ts_current_value = ts_evaluate_solution(best_candidate, ts_items)
        #elif ts_evaluate_solution(ts_current_solution, ts_items) > Max_weight and ts_evaluate_weight(best_candidate, ts_items) <= Max_weight:
        #    ts_current_solution = best_candidate
        #    ts_current_weight = ts_evaluate_weight(best_candidate, ts_items)
        #    ts_current_value = ts_evaluate_solution(best_candidate,ts_items)
        #print("BCW", ts_evaluate_weight(best_candidate, ts_items))
        #print("BCs", ts_evaluate_solution(best_candidate, ts_items))
        # if ts_evaluate_weight(best_candidate, ts_items) <= Max_weight:
        ts_update_tabu_list(tabu_list, best_candidate, ts_current_value, ts_items)
        # print("UTL")

        if ts_evaluate_solution(ts_current_solution, ts_items) > ts_evaluate_solution(ts_best_solution, ts_items): # ts_best_solution is None or
            ts_best_solution = ts_current_solution

        y[u][i] = ts_evaluate_solution(ts_best_solution, ts_items)
        # elif ts_best_solution is None and ts_evaluate_weight(ts_current_solution, items)<Max_weight:
        #     ts_best_solution = ts_current_solution

    print("最佳解: ", ts_best_solution)
    print("最佳解的总价值: ", ts_evaluate_solution(ts_best_solution, ts_items))
    print("最佳解的总重量: ", ts_evaluate_weight(ts_best_solution, ts_items))
    print("最大重量: ", Max_weight)
    print("items", ts_items)
    print("x", ts_evaluate_weight(x, ts_items))

# def ts_adjust_solution(solution, C):
#     """Implements the repair method in order to respect the problem constraints.
#        Lamarckian greedy repair, i.e. consecutive deletion of selected ts_items until
#        the constraints are  satisfied
#     """
#     itemsSelected = solution.nonzero()[0]
#     overfilled = False
#     weight = ts_evaluate_weight(solution, ts_items)
#     if weight > C:
#         overfilled = True
#     while (overfilled):
#         r = np.random.randint(0,itemsSelected.shape[0]-1)
#         i = itemsSelected[r]
#         solution[i] = 0
#         weight = weight - items[i]
#         itemsSelected = np.delete(itemsSelected, r)
#         if weight <= C:
#             overfilled = False

#     while (not overfilled):
#         j = np.random.randint(0,n_items-1)
#         while (solution[j]==1):
#             j = np.random.randint(0,n_items-1)
#         solution[j] = 1
#         weight = weight + ts_items[j]
#         if weight > C:
#             solution[j] = 0
#             overfilled = True
#     return solution

def ts_adjust_solution(solution, C, ts_items, n_items):
    itemsSelected = [i for i, x in enumerate(solution) if x == 1]
    overfilled = False
    ts_weight = ts_evaluate_weight(solution, ts_items)

    if ts_weight > C:
        overfilled = True

    while overfilled:
        r = random.randint(0, len(itemsSelected) - 1)
        i = itemsSelected[r]
        solution[i] = 0
        ts_weight -= ts_items[i][0]  # 更新重量，使用正确的项目索引

        itemsSelected.pop(r)

        if ts_weight <= C:
            overfilled = False

    while not overfilled:
        j = random.randint(0, n_items - 1)
        while solution[j] == 1:
            j = random.randint(0, n_items - 1)

        solution[j] = 1
        ts_weight += ts_items[j][0]  # 更新重量，使用正确的项目索引
        if ts_weight > C:
            solution[j] = 0
            overfilled = True

    return solution

def ts_get_neighbors(solution, tabu_list):
    neighbors = []
    for i in range(len(solution)):
        neighbor = solution[:]
        neighbor[i] = 1 - neighbor[i]
        neighbor = ts_adjust_solution(neighbor, Max_weight, ts_items, n_items)
        if neighbor not in tabu_list:
            neighbors.append(neighbor)
    return neighbors

def ts_find_best_solution(candidate_set, tabu_list):
    #print("ac",ac)
    if len(candidate_set) < 10 and len(ac)!=0 :
        candidate_set.append(ac[0])
    #print("0000", len(candidate_set))
    ts_best_solution = candidate_set[0]
    ts_best_value = ts_evaluate_solution(ts_best_solution, ts_items)
    for candidate in candidate_set:
        value = ts_evaluate_solution(candidate, ts_items)
        if value > ts_best_value:
            ts_best_solution = candidate
            ts_best_value = value
    return ts_best_solution

def ts_evaluate_solution(solution, ts_items):
    return sum(solution[i] * ts_items[i][1] for i in range(len(solution)))

def ts_evaluate_weight(solution, ts_items):
    return sum(solution[i] * ts_items[i][0] for i in range(len(solution)))

def ts_update_tabu_list(tabu_list, solution, ts_current_value, ts_items):
    tabu_list.append(solution)
    if len(tabu_list) > 10:
        tabu_list.pop(0)

    if len(ac) < 3:
        for i in range(len(tabu_list)):
            if ts_evaluate_weight(tabu_list[i], ts_items) <= Max_weight and len(ac) < 3:
                ac.append(tabu_list[0])
    elif ts_evaluate_weight(tabu_list[0],ts_items)>ts_current_value and ts_evaluate_weight(tabu_list[0], ts_items) <= Max_weight:
        ac.append(tabu_list[0])
    if len(ac)>10:
        ac.pop(0)
    #print(len(tabu_list))
    #print(tabu_list)

for u in range(ts_time):
    # 物品列表，每个物品包括重量和价值
    # array1 = np.mod(range(0,n_items),10)+1
    # array2 = np.vectorize(lambda x: x + 5)(array1)
    # ts_items = list(zip(array1, array2))
    array1 = np.random.uniform(low=MinWeight, high=MaxWeight, size=(n_items,))
    Max_weight = reduce(lambda x,y : x+y, array1) / 2
    l = np.random.uniform(0,5,size=(n_items,))
    array2 = array1+l
    ts_items = list(zip(array1, array2))
    # items = [(random.randint(1, 10), random.randint(1, 10)) for _ in range(n_items)]
    # 修改每个元组，使价值等于重量加上一个随机数
    # for i, item in enumerate(items):
    #     weight, value = item
    #     random_value = weight + random.randint(0, 5)
    #     items[i] = (weight, random_value)  # 使用索引更新元组
    #Max_weight = reduce(lambda x,y : x+y, array1) / 2  # 背包的最大容量
    ac = []
    tabu_search()

csv_file_path = "TS特殊.csv"
with open(csv_file_path, 'a', newline='',encoding='utf-8') as file:
    writer = csv.writer(file)
    #writer.writerow([f"PSO_c1:{c1}_c2:{c2}_w:{w}_pcls:{pcls}"])
    for f in range(ts_time):
        writer.writerow(y[f][:])

    print(f"CSV文件已成功写入到 {csv_file_path}")

for p in range(MAXITER):
    xx = 0
    for x in range(ts_time):
        if x <= ts_time-1:
            xx = xx + y[x][p]
            if x == ts_time-1:
                xx = round(xx / ts_time)
                ts_total.append(xx)
plt.plot(x_values, ts_total, color='red', linestyle='-',label='250_case2')
plt.legend(loc = 'lower right')
plt.show()
