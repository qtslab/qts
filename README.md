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

## 使用說明

### 編譯

```bash
cmake -B build
cmake --build build
```

### 執行

```bash
./build/qts
```

### 修改參數

除了旋轉角度外的參數都可以在 `/include/constant.cpp` 中修改，
修改完畢請重新編譯。

如果要修改不同的 case 來執行，
請到 `main.cpp` 中的函式修改，
例如 `case_III(items, capacity, max_gen, N);`。

### 輸出檔案

輸出檔案為 `./csv/QTS.csv`，
第一欄為代數，
第二欄為 QTS 目前找到的最佳解，
第三欄為 AE-QTS 目前找到的最佳解。

可使用圖表功能生成圖表，
對比執行結果的收斂速度和最佳解。

## 比較

| CASE I    | QTS | AE-QTS |
| --------- | --- | ------ |
| time      |||
| space     |||
| answer    |||

| CASE II   | QTS | AE-QTS |
| --------- | --- | ------ |
| time      |||
| space     |||
| answer    |||

| CASE III  | QTS | AE-QTS |
| --------- | --- | ------ |
| time      |||
| space     |||
| answer    |||
