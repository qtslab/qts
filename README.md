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
請到 `/src/main.cpp` 中的函式修改，
例如 `case_III(items, capacity, max_gen, N);`。

要修改旋轉角度的話，
QTS 呼叫的是在 `/src/quantum_function.cpp` 中使用多載的 `updateQ()` 函式(三個參數，參數中不含角度)，
AE-QTS 的 `updateQ()` 函式也在相同檔案中，使用多載的 `updateQ()` 函式(四個參數，參數中含角度)。

### 輸出檔案

輸出檔案為 `./csv/QTS.csv`，
第一欄為代數，
第二欄為 QTS 目前找到的最佳解，
第三欄為 AE-QTS 目前找到的最佳解。

可使用圖表功能生成圖表，
對比執行結果的收斂速度和最佳解。

## 使用這份程式的原因

### 架構

這份程式是尊從單一職責原則，
我使用大量的 header file 來將程式功能分開，
並且提升了整體程式碼的可讀性和可重用性，
也讓修改參數或邏輯變得更容易。

### 速度

相較於 Python 版本，
C++ 版本的程式執行速度較快，
同時我使用 thread 來讓測試可以一次使用多個執行緒，
不僅單個測試比起 Python 版本快了許多，
可以完整發揮 CPU 性能讓處理器使用率達到 100%，
藉此再進一步提升約 20~30 倍的執行速度，
如果核心數更高則可以省下更多時間。

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
