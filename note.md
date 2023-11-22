# note

## variable name

| 虛擬碼中的名稱 | C++ 原始碼中的名稱  | Python 中的名稱 | 中文名稱                 |
| -------------- | ------------------- | --------------- | ------------------------ |
| C              | capacity            | C               | 背包容量                 |
| N              | question_size       | n_items         | 問題大小(總物品量)       |
|                | items               | items           | 問題中的物品             |
|                | item                |                 | 問題中的單個物品         |
| w              | item.weight         |                 | 單個物品重量             |
| v              | item.value          |                 | 單個物品價值             |
| q              | qubit               |                 | 量子位元(解答中單個物品) |
| alpha          | qubit.alpha         |                 | 量子態 alpha             |
| beta           | qubit.beta          |                 | 量子態 beta              |
| b              | qubit.take          |                 | 是否拿取                 |
| s^b            | best_solution       |                 | 最佳解                   |
| s^w            | worst_solution      |                 | 最差解                   |
|                | neighbors           | neighbours      | 鄰居解                   |
|                |                     | N               | 鄰居解大小               |
| MAX_GEN        |                     | NumIter         | 總迭代次數               |
| i              | i                   | i               | 當前迭代次數             |

## variable data type in Python

__name__: <class 'str'>
__doc__: <class 'NoneType'>
__package__: <class 'NoneType'>
__loader__: <class '_frozen_importlib_external.SourceFileLoader'>
__spec__: <class 'NoneType'>
__annotations__: <class 'dict'>
__builtins__: <class 'module'>
__file__: <class 'str'>
__cached__: <class 'NoneType'>
np: <class 'module'>
compress: <class 'type'>
reduce: <class 'builtin_function_or_method'>
pi: <class 'float'>
sqrt: <class 'builtin_function_or_method'>
cos: <class 'builtin_function_or_method'>
sin: <class 'builtin_function_or_method'>
N: <class 'int'>
n_items: <class 'int'>
MaxWeight: <class 'float'>
MinWeight: <class 'float'>
items: <class 'numpy.ndarray'>
C: <class 'numpy.float64'>
values: <class 'numpy.ndarray'>
calculate_weights: <class 'function'>
measure: <class 'function'>
gen_nbrs: <class 'function'>
adjust_solution: <class 'function'>
adjust_neighbours: <class 'function'>
new_best_fit: <class 'function'>
find_best_worst: <class 'function'>
updateQ: <class 'function'>
qindividuals: <class 'numpy.ndarray'>
solution: <class 'numpy.ndarray'>
best_fit: <class 'numpy.ndarray'>
NumIter: <class 'int'>
i: <class 'int'>
neighbours: <class 'list'>
best_solution: <class 'numpy.ndarray'>
worst_solution: <class 'numpy.ndarray'>
variables: <class 'dict'>
