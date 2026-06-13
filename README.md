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
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

QTS 與 AE-QTS 各自編譯成一支獨立執行檔（`build/qts`、`build/ae_qts`），
共用的量子運算邏輯收在靜態函式庫 `qts_core`。拆開的目的是讓兩者的執行時間
可以用 shell 的 `time` 個別量測，方便和 GPU 版本做時間比較。

### 執行

```bash
./build/qts                    # QTS，預設讀取 ./config/case.conf
./build/ae_qts                 # AE-QTS
./build/qts path/to/my.conf    # 也可指定其他設定檔
```

每支執行檔跑「一次」該演算法並輸出收斂曲線 CSV。程式本身**不做計時、也不做重複**：
要量時間或重複多次，請用 `script/benchmark.sh`（內含 `time` 與 `for` 迴圈）。

### 修改參數

`N`、`max_gen`、`question_size`、`min_weight`、`max_weight` 等參數
都集中在 `config/case.conf`，格式為 `key = value`（`#` 之後為註解）。
**修改後直接重新執行即可生效，不需重新編譯。**

```conf
N = 10              # Neighbourhood size（鄰域大小）
min_weight = 1.0    # 物品重量下界（case_I 使用）
max_weight = 10.0   # 物品重量上界（case_I 使用）
max_gen = 1000      # 迭代代數 NumIter
question_size = 1000 # 物品數量 n_items
```

重複次數不再是參數：每次執行就是跑一次，要重複幾次交給 `script/benchmark.sh` 的
`for` 迴圈決定。

找不到設定檔時會印出警告並沿用內建預設值（見 `include/config.hpp` 的 `Config`）。

如果要修改不同的 case 來執行，
請到 `/include/experiment.hpp` 的 `run_experiment()` 中修改，
例如把 `case_I(items, capacity, cfg.min_weight, cfg.max_weight);`
換成 `case_II(items, capacity);` 或 `case_III(items, capacity);`。
此處為 QTS 與 AE-QTS 兩支執行檔共用的實驗流程，改一次兩邊同步生效。

要修改旋轉角度的話，
QTS 呼叫的是在 `/src/quantum_function.cpp` 中使用多載的 `updateQ()` 函式(三個參數，參數中不含角度)，
AE-QTS 的 `updateQ()` 函式也在相同檔案中，使用多載的 `updateQ()` 函式(四個參數，參數中含角度)。

### 計時（和 GPU 版本比較）

計時不再寫在程式裡，改用 `script/benchmark.sh`，以 shell 的 `time` 搭配 `for`
迴圈分別量測 `build/qts`、`build/ae_qts` 整支執行檔的牆鐘時間，並重複數次取平均。
這樣量到的就是「一支執行檔從頭到尾」的時間，和 GPU 版本用外部計時的方式一致。

```bash
script/benchmark.sh                      # 預設 config/case.conf，每支重複 5 次
script/benchmark.sh config/case.conf 10  # 指定設定檔與重複次數
```

### 輸出檔案

兩支執行檔各自輸出一份 CSV：
QTS 寫到 `./csv/QTS.csv`，AE-QTS 寫到 `./csv/AE-QTS.csv`。
每份 CSV：
第一欄為代數，
第二欄為該演算法該代目前找到的最佳解（單次執行），
第三欄為 DP 求得的最佳解（baseline，每代皆相同，於圖表中為一條水平基準線）。

兩份 CSV 的物品為各自隨機生成（case_I／case_II）。若要在同一組物品上比較
兩者的收斂曲線，請改用資料固定的 `case_III`。
可使用圖表功能生成圖表，對比執行結果的收斂速度和最佳解。

### DP baseline

`/include/DP.hpp` 以動態規劃求 0/1 背包的最佳解，作為 QTS / AE-QTS 收斂結果的對照。
採用以重量為索引的經典解法，時間複雜度 O(`question_size` × `C`)、空間 O(`C`)，
`C` 為取整後的背包容量，計算時間遠小於一次啟發式測試（毫秒等級）。

當所有物品重量為整數時（case_II、case_III）此為精確最佳解；
若重量為實數（case_I），會將重量四捨五入取整，得到的是近似 baseline。

## 使用這份程式的原因

### 架構

這份程式是尊從單一職責原則，
我使用大量的 header file 來將程式功能分開，
並且提升了整體程式碼的可讀性和可重用性，
也讓修改參數或邏輯變得更容易。

### 速度

相較於 Python 版本，C++ 版本的程式執行速度較快。
每支執行檔跑一次演算法，時間量測與重複都交給 `script/benchmark.sh`
（shell 的 `time` ＋ `for` 迴圈），量到的就是單次執行從頭到尾的牆鐘時間，
和 GPU 版本用外部計時的方式一致，方便直接對照。

## 比較

測試條件：`question_size = 1000`（物品數）、`max_gen = 1000`（迭代數）、
`N = 10`（鄰域大小）。
`time` 為以 `script/benchmark.sh` 量測單次執行的牆鐘時間（多次取平均）；
`answer` 為第 `max_gen` 代找到的最佳解（即 `./csv/QTS.csv` 最後一列第二欄）；
`space` 為單條 run 在執行期間持有的資料結構量級。
Case I、Case II 的物品為隨機生成，數值為某次代表性執行的結果，會隨機略有浮動；
Case III 為固定資料，結果穩定。
（下表 `time` 與 `answer` 為先前多次平行版本的代表值，改成單次執行後絕對數字會變，
相對關係——AE-QTS 略慢、解略好——不變。）

| CASE I    | QTS                  | AE-QTS               |
| --------- | -------------------- | -------------------- |
| time      | 8.65 s               | 10.34 s              |
| space     | O(N·n)，持有 N+4 個解向量 | O(N·n)，持有 N+2 個解向量 + N 個 fitness/索引 |
| answer    | 6081.87              | 6105.17              |

| CASE II   | QTS                  | AE-QTS               |
| --------- | -------------------- | -------------------- |
| time      | 8.70 s               | 10.69 s              |
| space     | O(N·n)，持有 N+4 個解向量 | O(N·n)，持有 N+2 個解向量 + N 個 fitness/索引 |
| answer    | 4650.66              | 4673.44              |

| CASE III  | QTS                  | AE-QTS               |
| --------- | -------------------- | -------------------- |
| time      | 8.62 s               | 10.41 s              |
| space     | O(N·n)，持有 N+4 個解向量 | O(N·n)，持有 N+2 個解向量 + N 個 fitness/索引 |
| answer    | 6136.26              | 6160.11              |

### 結論

- **時間**：QTS 每代只需挑出當代最佳與最差解兩條，AE-QTS 需對 `N` 條鄰域解
  排序並做 `N/2` 次旋轉更新，因此 AE-QTS 每個 case 約慢 20%。
- **空間**：兩者皆為 `O(N·n)`（`n` 為物品數），量級相同；QTS 另外保留 best/worst
  兩條解向量，AE-QTS 則改以 `N` 個 fitness 值與索引取代，差距極小。
- **解的品質**：三個 case 中 AE-QTS 的最佳解平均值都略高於 QTS
  （約 0.3~0.5%），代表 AE-QTS 以稍多的時間換得更好的收斂結果。
