# note

## variable name

| 虛擬碼中的名稱 | C++ 原始碼中的名稱  | Python 中的名稱 | 中文名稱                 | C++ 中的形態   | Python 中的形態 |
| -------------- | ------------------- | --------------- | ------------------------ | -------------- | --------------- |
| C              | capacity            | C               | 背包容量                 | double         | numpy.float64   |
|                | question_size       | n_items         | 問題大小(總物品量)       | int            | int             |
|                | items               | items           | 問題中的物品             | item_t[]       | numpy.ndarray   |
|                | item                |                 | 問題中的單個物品         | item_t         | numpy.ndarray   |
| w              | item.weight         |                 | 單個物品重量             | double         |                 |
| v              | item.value          |                 | 單個物品價值             | double         |                 |
| q              | qubit               |                 | 量子位元(解答中單個物品) | qubit_t        |                 |
| alpha          | qubit.alpha         |                 | 量子態 alpha             | double         |                 |
| beta           | qubit.beta          |                 | 量子態 beta              | double         |                 |
| b              | solution            |                 | 是否拿取                 | bitset<>       | numpy.ndarray   |
| $s^b$          | best_solution       |                 | 最佳解                   | bit(in bitset) | numpy.ndarray   |
| $s^w$          | worst_solution      |                 | 最差解                   | bit(in bitset) | numpy.ndarray   |
|                | neighbors           | neighbours      | 鄰居解                   | vector<item_t> | list            |
| N              | N                   | N               | 鄰居解大小               | int            | int             |
| MAX_GEN        | max_gen             | NumIter         | 總迭代次數               | int            | int             |
| i              | i                   | i               | 當前迭代次數             | int            | int             |

## variable data type in Python

compress: <class 'type'>
reduce: <class 'builtin_function_or_method'>
MaxWeight: <class 'float'>
MinWeight: <class 'float'>
qindividuals: <class 'numpy.ndarray'>
solution: <class 'numpy.ndarray'>
best_fit: <class 'numpy.ndarray'>
variables: <class 'dict'>
