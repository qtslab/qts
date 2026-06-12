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

## 2. `adjust_solution` 只做溢出修復，未做 underfill（這是設計的預期行爲，不是 bug）

`src/quantum_function.cpp` 的 greedy 補滿段落被註解掉了。這是設計選擇而非
bug，但代表解通常處於「未裝滿」狀態，完全依賴量子機率逼近，收斂較慢。
若為刻意則無妨，僅記錄。

## 3. 資源：一次啟動 1000 條 OS thread（已修正）

`src/main.cpp` 原本用 `std::thread threads[test_times]`（test_times = 1000）一次性
建立 1000 條執行緒，QTS / AE-QTS 各一輪。多數機器的實體核心遠少於此，會造成
大量 context switch，污染計時比較。

**修正方向**：改用 `include/thread_pool.hpp` 的 `parallel_for`，以
`std::thread::hardware_concurrency()`（偵測失敗退回 1）數量的 worker thread
動態搶單跑完 test_times 次 run。各 run 寫入不同的 `records[i]`、彼此獨立，
故無需鎖。

## 4. 微小效能點（實測後判定不修改）

原本懷疑這兩處每次呼叫重建分布物件會拖慢效能：

- `measure()` 每次呼叫都重建 `std::uniform_real_distribution`。
- `adjust_solution()` 的 `std::uniform_int_distribution` 同理。

**實測結論：不應修改。** 把兩者改成 `static thread_local` 後，以 HEAD 為對照、
兩版二進位**交替順序**跑 8 輪（抵銷熱漂移）量測：

| 版本 | QTS | AE-QTS |
| ---- | --- | ------ |
| 原本（區域變數，每次建立） | 8998 ms | 10772 ms |
| 改成 `static thread_local` | 9215 ms | 11092 ms |

改完反而**慢約 2–3%**，且幾乎每一輪配對都是改後較慢，是訊號不是雜訊。

原因：`uniform_real_distribution` / `uniform_int_distribution` 的建構極廉價
（只在 stack 上存兩個參數、無配置），本來就沒東西可省；改成 `static thread_local`
卻讓每次呼叫都要做一次初始化 guard 檢查（分支 + TLS 存取），而 measure /
adjust 全程被呼叫約 10⁷ 次，guard 成本反而超過原本的建構成本。故維持原樣。

## 已確認沒問題

- 量子旋轉 `update_q`：四種 bit 組合 × 各象限方向都正確，旋轉保範數，
  `beta²` 始終為合法機率。
- QTS 的 best/worst 追蹤：雖用 `else if`，但 `best_value ≥ worst_value` 恆成立，
  一個值不可能同時 `> best` 又 `< worst`，邏輯正確。
- AE-QTS：排序配對 `order[j]` ↔ `order[N-1-j]` 與遞減旋轉角 `0.01/(j+1)` 正確。
- `records[run][gen]` 維度配置與讀寫一致（見 `records_dimension.md`）。
- 各執行緒 thread_local RNG 以 `random_device` 設種子、彼此獨立，適合做平均統計。
