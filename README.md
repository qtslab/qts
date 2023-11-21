# QTS 解決 0/1 背包問題

## 問題

給定一個背包，最多能裝重量為 `C` 的物品，
現有 `N` 個物品，
第 `i` 個物品的重量為 `w[i]`，
價值為 `v[i]`，
請問最多能裝多少價值的物品？

問題：
    物品： q
        重量 weight
        價值 value
    背包：
        最大重量 capacity C
    問題：
        最大價值 b

QTS：
    量子位元陣列： Q(0), Q(1), ..., Q(N-1)
        量子位元： q
            量子態： alpha, beta

## 名稱

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


## QTS

conponents: MAX_GEN, Q(0), Q(1), ..., Q(MAX_GEN), tabu list T

## 比較

| CASE I    | QTS | PE-QTS |
| --------- | --- | ------ |
| time      |||
| space     |||
| answer    |||

| CASE II   | QTS | PE-QTS |
| --------- | --- | ------ |
| time      |||
| space     |||
| answer    |||

| CASE III  | QTS | PE-QTS |
| --------- | --- | ------ |
| time      |||
| space     |||
| answer    |||
