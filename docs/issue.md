# 演算法實作檢查：值得注意的問題

對 QTS / AE-QTS / 量子旋轉 / 修復 / DP baseline 做過一輪檢查。
**核心量子演算法邏輯正確**（旋轉方向、象限修正、保範數、best/worst 追蹤、
排序配對與遞減旋轉角都已逐一驗算）。以下是值得注意的問題，依重要性排列。

## 1. DP baseline 對 case_I 不是有效上界（已修正）

`include/DP.hpp` 原本對每件物品重量用 `std::llround`（四捨五入）。
`llround` 對部分物品會**往下取整**，等於放寬重量限制，於是 DP 算出的「最佳值」
在真實實數重量下可能**根本裝不下**。結果：對 case_I（實數重量），這條
baseline 可能畫在**真實最佳解之上**，QTS/AE-QTS 永遠碰不到，會誤導收斂判讀。

**修正方向**：把重量改用 `std::floor`（容量本來就是 `floor`）。
因為 `floor(w_i) ≤ w_i`，任何在真實重量下可行的解，在取整後重量下也必可行：

```
sum(floor(w_i)·x_i) ≤ sum(w_i·x_i) ≤ C
```

且左式為整數，故 `≤ floor(C)`。relaxed 可行域是真實可行域的超集，
所以 `DP(floored) ≥ true optimum`，是**有效上界**。
對 case_II / case_III（整數重量）`floor(w_i) = w_i`，仍為精確最佳解。
詳見本檔最後與 `DP.hpp` 內註解。

## 2. `adjust_solution` 只做溢出修復，未做 underfill

`src/quantum_function.cpp` 的 greedy 補滿段落被註解掉了。這是設計選擇而非
bug，但代表解通常處於「未裝滿」狀態，完全依賴量子機率逼近，收斂較慢。
若為刻意則無妨，僅記錄。

## 3. 資源：一次啟動 1000 條 OS thread

`src/main.cpp` 用 `std::thread threads[test_times]`（test_times = 1000）一次性
建立 1000 條執行緒，QTS / AE-QTS 各一輪。多數機器的實體核心遠少於此，會造成
大量 context switch。非正確性問題，但若要乾淨的計時比較，建議改用執行緒池或
限制併發數至核心數量級。

## 4. 微小效能點（非 bug）

- `measure()` 每次呼叫都重建 `std::uniform_real_distribution`（無狀態，可提到
  迴圈外或設為 static）。
- `adjust_solution()` 的 `std::uniform_int_distribution` 同理。

## 已確認沒問題

- 量子旋轉 `update_q`：四種 bit 組合 × 各象限方向都正確，旋轉保範數，
  `beta²` 始終為合法機率。
- QTS 的 best/worst 追蹤：雖用 `else if`，但 `best_value ≥ worst_value` 恆成立，
  一個值不可能同時 `> best` 又 `< worst`，邏輯正確。
- AE-QTS：排序配對 `order[j]` ↔ `order[N-1-j]` 與遞減旋轉角 `0.01/(j+1)` 正確。
- `records[run][gen]` 維度配置與讀寫一致（見 `records_dimension.md`）。
- 各執行緒 thread_local RNG 以 `random_device` 設種子、彼此獨立，適合做平均統計。
