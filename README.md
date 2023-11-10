# QTS 解決 0/1 背包問題

## 題目

conponents: C, N, w, v

給定一個背包，最多能裝重量為 `C` 的物品，
現有 `N` 個物品，
第 `i` 個物品的重量為 `w[i]`，
價值為 `v[i]`，
請問最多能裝多少價值的物品？

## QTS

conponents: MAX_GEN, Q(0), Q(1), ..., Q(MAX_GEN), tabu list T