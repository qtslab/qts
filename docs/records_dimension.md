# records 維度修正（潛伏 bug）

## 問題

`src/main.cpp` 的紀錄陣列原本配置成：

```cpp
std::vector<std::vector<double>> QTS_records(max_gen, std::vector<double>(test_times));
// 外層 = max_gen、內層 = test_times，即 [gen][run]
```

但實際使用方式全部是 `[run][gen]`：

- **寫入端**：launch 迴圈以 run 為索引傳入 `QTS_records[i]`（`i ∈ [0, test_times)`），
  進到 `QTS()` 後寫 `record[gen]`（`gen ∈ [0, max_gen)`）。
  → 期望外層是 run、內層是 gen。
- **輸出端**：

  ```cpp
  for (int i=0; i<max_gen; i++)          // i = gen
      for (int j=0; j<test_times; j++)   // j = run
          QTS_sum += QTS_records[j][i];  // [run][gen]
  ```

  → 同樣以 `[run][gen]` 讀取。

配置是 `[gen][run]`，使用卻是 `[run][gen]`，兩者相反。

現在沒爆，是因為 `max_gen == test_times == 1000`，外內層長度恰好相等，
存取等同操作一個方陣，索引方向寫反也讀寫一致。**只要把任一參數改掉
（例如 `max_gen = 500`），就會越界存取或讀到錯誤的資料。**

舉例：若 `test_times = 1000`、`max_gen = 500`，外層只有 500 個 vector，
但寫入端 `QTS_records[i]` 的 `i` 會跑到 999 → 越界。

## 修正

把配置改成與使用方式一致的 `[run][gen]`：外層 `test_times`、內層 `max_gen`。

```cpp
std::vector<std::vector<double>> QTS_records(test_times, std::vector<double>(max_gen));
std::vector<std::vector<double>> AE_QTS_records(test_times, std::vector<double>(max_gen));
```

寫入端 `QTS_records[run][gen]`、輸出端 `QTS_records[run][gen]` 皆正確對應，
之後調整 `max_gen` 或 `test_times` 為不同值也不會越界。

## 驗證

- `-DCMAKE_BUILD_TYPE=Release` 建置通過。
- 在目前 `max_gen == test_times == 1000` 的設定下，新舊配置的存取結果完全相同
  （只是把方陣的索引意義導正），故 `csv/QTS.csv` 輸出不變。
- 這是純正確性／可維護性修正，不影響演算法與效能，計時數字不變。
