# Fitness 重複計算優化

## 問題

`calculate_values()` 是 O(n)，要掃過 `question_size = 1000` 個 item。
但同一條解的 fitness 在一代之內被重算很多次：

QTS（`include/QTS.hpp`）內層迴圈每個 neighbor 比較時：

```cpp
if (calculate_values(items, neighbors[j]) > calculate_values(items, best_solution)) {
    best_solution = neighbors[j];
} else if (calculate_values(items, neighbors[j]) < calculate_values(items, worst_solution)) {
    worst_solution = neighbors[j];
}
```

- `neighbors[j]` 的值最多算兩次（`>` 與 `<` 各一次）。
- `best_solution` / `worst_solution` 明明沒變，卻每個 `j` 都重算一次。
- 選出 best 後再算一次比較，最後 `record[i] = calculate_values(items, best_fit)` 每代又算一次。

AE-QTS（`include/AE-QTS.hpp`）則是 `sort_solution()` 內部把 N 條 neighbor 的值全部重算，
排序後又對 `sorted_neighbors[0]` 與 `best_fit` 各算一次，`record[i]` 再算一次。

以 QTS 為例，每代約 `N × (2 + 1 + 1) + 3 ≈ 44` 次 `calculate_values`，
其中真正必要的只有每條 neighbor 算一次，共 `N = 10` 次。

這同時是 baseline 公平性問題，也直接對應 GPU 版的設計：
fitness 本來就應該是 measurement / repair kernel 的輸出，算一次即可。

## 修正

在 `adjust_solution()`（repair）完成的當下，把 fitness 算一次存進變數／陣列，
之後比較、挑 best/worst、寫 `record` 全部沿用存好的值。

QTS：每條 neighbor 算一次 `value`，用 `best_value` / `worst_value` 追蹤，
`best_fit_value` 快取最佳解的值，`record[i]` 直接寫快取值。

AE-QTS：repair 後把每條 neighbor 的值存進 `values[]`，
改用 `std::sort` 對索引（`order[]`）依 `values` 排序，
不再呼叫會重算的 `sort_solution()`：

```cpp
for (int j=0; j<N; j++) {
    neighbors[j] = measure(qindividuals);
    adjust_solution(items, neighbors[j], capacity);
    values[j] = calculate_values(items, neighbors[j]); // repair 完成，算一次即存起來
}

std::iota(order.begin(), order.end(), 0);
std::sort(order.begin(), order.end(), [&values](int a, int b) {return values[a] > values[b];});
```

> `sort_solution()` 本身保留不動（`include/TS.hpp` 仍會用到），
> 只是 AE-QTS 不再透過它來取得排序，藉此消除其內部的重算。

## 計時對比

- 環境：24 核心、`-DCMAKE_BUILD_TYPE=Release`
- 設定：`test_times=1000`、`max_gen=1000`、`question_size=1000`、`N=10`
- 基準已含 `thread_local` RNG 優化（見 `rand_gen.md`），此處只比較 fitness 快取
- 各跑 3 次，時間取平均（程式內建 `QTS time` / `AE-QTS time` 輸出）

### 改前（fitness 重複計算）

| run | QTS | AE-QTS |
| --- | --- | --- |
| 1 | 10.397 s | 10.800 s |
| 2 | 10.380 s | 10.666 s |
| 3 | 10.430 s | 11.018 s |
| **平均** | **10.402 s** | **10.828 s** |

### 改後（fitness 快取）

| run | QTS | AE-QTS |
| --- | --- | --- |
| 1 | 8.401 s | 10.241 s |
| 2 | 8.466 s | 10.441 s |
| 3 | 8.518 s | 10.289 s |
| **平均** | **8.462 s** | **10.324 s** |

### 結果

| 演算法 | 改前平均 | 改後平均 | 加速 | 縮短 |
| --- | --- | --- | --- | --- |
| QTS | 10.402 s | 8.462 s | **1.23×** | -18.7% |
| AE-QTS | 10.828 s | 10.324 s | **1.05×** | -4.7% |

QTS 改善明顯，因為原本每個 neighbor 都重算、且 best/worst 每代重算多次；
AE-QTS 改善較小，是因為它的主要耗時仍在 `measure()` / `adjust_solution()`
（RNG 與 1000 個 item 的 bitset 操作），fitness 佔比相對低。
