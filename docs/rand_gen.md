# 隨機數產生器優化

## 問題

原本 `measure()` 與 `adjust_solution()` 每次被呼叫時，都會重新建立一組
`std::random_device` + `std::mt19937`：

```cpp
solution_t measure(q_t& qindividuals) {
    solution_t solution;
    std::random_device rd;  // 每次呼叫都重建
    std::mt19937 gen(rd()); // 624 個 word 的狀態初始化
    ...
}
```

兩個成本：

- `std::random_device` 取得亂數種子時可能涉及系統呼叫（syscall）。
- `std::mt19937` 的 seed 初始化要展開 624 個 word 的內部狀態。

以目前設定（`include/constant.h`）估算重建次數：

| 參數 | 值 |
| --- | --- |
| `test_times` | 1000 |
| `max_gen` | 1000 |
| `N` | 10 |
| `question_size` | 1000 |

每條執行緒每代呼叫 `measure()` 與 `adjust_solution()` 各約 `N` 次，
合計約 `1000 runs × 1000 gens × (10 measure + 10 adjust) ≈ 2000 萬次` RNG 重建。
這是 CPU 版的主要耗時來源，而非演算法本身。

## 修正

改用每個執行緒共用一個 `thread_local std::mt19937`，只在第一次呼叫時
透過 `random_device` 設定種子，之後所有呼叫共用同一個引擎：

```cpp
static std::mt19937& rng() {
    static thread_local std::mt19937 gen(std::random_device{}());
    return gen;
}
```

並把原本在迴圈內反覆建立的 distribution 移到迴圈外。

> 採用 `thread_local` 而非單純 `static` 是必要的：`main.cpp` 用
> `std::thread` 並行跑 `test_times` 條執行緒，共用單一 `static` 引擎會造成
> 資料競爭（data race）。每執行緒各持一份引擎可避免競爭，且 TLS 查找成本可忽略。

## 計時對比

- 環境：24 核心、`-DCMAKE_BUILD_TYPE=Release`
- 設定：`test_times=1000`、`max_gen=1000`、`question_size=1000`、`N=10`
- 各跑 3 次，時間取平均（程式內建 `QTS time` / `AE-QTS time` 輸出）

### 改前（每次重建 RNG）

| run | QTS | AE-QTS |
| --- | --- | --- |
| 1 | 33.854 s | 33.624 s |
| 2 | 33.851 s | 33.789 s |
| 3 | 33.578 s | 33.250 s |
| **平均** | **33.761 s** | **33.554 s** |

### 改後（thread_local RNG）

| run | QTS | AE-QTS |
| --- | --- | --- |
| 1 | 9.956 s | 10.410 s |
| 2 | 10.170 s | 10.409 s |
| 3 | 10.285 s | 10.602 s |
| **平均** | **10.137 s** | **10.474 s** |

### 結果

| 演算法 | 改前平均 | 改後平均 | 加速 | 縮短 |
| --- | --- | --- | --- | --- |
| QTS | 33.761 s | 10.137 s | **3.33×** | -70.0% |
| AE-QTS | 33.554 s | 10.474 s | **3.20×** | -68.8% |

RNG 重建確實是主要瓶頸；消除後整體耗時約降為原本的三分之一。
