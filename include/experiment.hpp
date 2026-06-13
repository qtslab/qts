#ifndef EXPERIMENT_HPP
#define EXPERIMENT_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "config.hpp"
#include "type.h"
#include "case.hpp"
#include "DP.hpp"

// QTS 與 AE-QTS 共用的實驗流程：載入設定、生成 case、跑 DP baseline、
// 跑「一次」某個演算法，最後輸出該次的收斂曲線 CSV。
//
// 這裡不做計時、也不做重複：
//   - 計時交給 shell 的 `time`（見 script/benchmark.sh），量整支執行檔的牆鐘時間，
//     和 GPU 版本用外部計時的方式一致。
//   - 重複次數交給 benchmark.sh 的 for 迴圈，跑幾次就呼叫幾次執行檔。
template <typename Algo>
int run_experiment(const std::string& name, const std::string& config_path,
                   const std::string& csv_path, Algo algo) {
    const Config cfg = load_config(config_path);

    items_t items(cfg.question_size);
    double capacity = 0;
    // Case start
    case_I(items, capacity, cfg.min_weight, cfg.max_weight); // set case
    // case end

    std::cout << name
              << " | items: " << cfg.question_size
              << "  capacity: " << capacity
              << "  max_gen: " << cfg.max_gen
              << "  N: " << cfg.N << std::endl;

    // DP baseline：求精確（整數重量）/ 有效上界（實數重量）最佳解，作為收斂對照線
    const double DP_optimal = DP(items, capacity);
    std::cout << "DP optimal: " << DP_optimal << std::endl;

    // 跑一次演算法，record[gen] 記錄該代目前找到的最佳解
    std::vector<double> record(cfg.max_gen);
    algo(items, capacity, cfg.max_gen, cfg.N, record);

    // 第三欄為 DP 最佳解，每代皆相同，於圖表中為一條水平基準線
    std::ofstream fout(csv_path);
    for (int i=0; i<cfg.max_gen; i++) {
        fout << i << "," << record[i] << "," << DP_optimal << std::endl;
    }

    fout.close();
    return 0;
}

#endif
