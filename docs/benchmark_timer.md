# 計時器位置修正

## 問題

`src/main.cpp` 原本的計時順序是「先 launch 全部 thread，才取 start」：

```cpp
for (int i=0; i<test_times; i++) {
    threads[i] = std::thread(QTS, ...); // thread 一建立就開始跑
}

auto QTS_start = std::chrono::high_resolution_clock::now(); // 太晚了
for (int i=0; i<test_times; i++) {
    threads[i].join();
}
auto QTS_end = std::chrono::high_resolution_clock::now();
```

`std::thread` 在建構當下就開始執行。launch 迴圈要建立 `test_times = 1000` 條
thread，這段期間：

- 建立 thread 本身的成本沒被計入。
- 先啟動的 thread 已經跑掉的工作沒被計入（最早那批可能已完成相當部分）。

所以量到的時間是「launch 完成 → 全部 join 完」，系統性地**低估**了真實的
wall-clock 耗時。AE-QTS 段落有相同問題（先 launch 再取 `AE_QTS_start`）。

## 修正

把 `start` 移到 launch 迴圈之前，涵蓋「建立 thread → 全部 join 完」的完整區間：

```cpp
auto QTS_start = std::chrono::high_resolution_clock::now();
for (int i=0; i<test_times; i++) {
    threads[i] = std::thread(QTS, ...);
}
for (int i=0; i<test_times; i++) {
    threads[i].join();
}
auto QTS_end = std::chrono::high_resolution_clock::now();
```

這只改變「量測方式」，不改演算法，因此既有優化（RNG、fitness 快取）的
**相對加速比仍然成立**，只是絕對數字會比之前略高（補回漏算的部分）。

## 計時對比

- 環境：24 核心、`-DCMAKE_BUILD_TYPE=Release`
- 設定：`test_times=1000`、`max_gen=1000`、`question_size=1000`、`N=10`
- 程式碼基準：已含 `thread_local` RNG 與 fitness 快取
- 各跑 3 次，時間取平均

### 計時器修正前（start 放在 launch 之後）

| run | QTS | AE-QTS |
| --- | --- | --- |
| 1 | 8.401 s | 10.241 s |
| 2 | 8.466 s | 10.441 s |
| 3 | 8.518 s | 10.289 s |
| **平均** | **8.462 s** | **10.324 s** |

### 計時器修正後（start 放在 launch 之前）

| run | QTS | AE-QTS |
| --- | --- | --- |
| 1 | 8.808 s | 10.576 s |
| 2 | 8.826 s | 10.849 s |
| 3 | 9.049 s | 10.970 s |
| **平均** | **8.894 s** | **10.798 s** |

### 結果

| 演算法 | 修正前 | 修正後 | 差距 |
| --- | --- | --- | --- |
| QTS | 8.462 s | 8.894 s | +0.43 s（+5.1%） |
| AE-QTS | 10.324 s | 10.798 s | +0.47 s（+4.6%） |

漏算的時間約 0.4～0.5 s，對應建立 1000 條 thread 與先啟動者在 launch 期間
已完成的工作。修正後的數字才是公平的 baseline。
