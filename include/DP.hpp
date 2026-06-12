#ifndef DP_HPP
#define DP_HPP

#include <vector>
#include <cmath>
#include <algorithm>

#include "constant.h"
#include "type.h"

// 以動態規劃求 0/1 背包的最佳解，作為 QTS / AE-QTS 收斂結果的 baseline。
// 採用「重量為索引」的經典解法：dp[c] = 重量預算為 c 時可得到的最大價值，
// 每件物品由後往前更新以確保只被選取一次。
// 時間 O(question_size * C)、空間 O(C)，C 為取整後的背包容量。
//
// 有效上界：重量一律以 floor 取整、容量亦以 floor 取整。因為 floor(w_i) ≤ w_i，
// 任何在真實重量下可行的解，在取整後的重量下也必可行：
//     sum(floor(w_i)·x_i) ≤ sum(w_i·x_i) ≤ capacity
// 且左式為整數故 ≤ floor(capacity) = C。relaxed 可行域是真實可行域的超集，
// 因此 DP(floored) ≥ 真實最佳解，是貨真價實的「上界」基準線。
//
// 精確性：當所有物品重量為整數時（case_II、case_III）floor(w_i) = w_i，
// 此為精確最佳解；重量為實數時（case_I）則為有效上界（可能略鬆但不會低於真值）。
double DP(items_t& items, double capacity) {
    int C = static_cast<int>(std::floor(capacity));
    if (C < 0) {
        C = 0;
    }

    std::vector<double> dp(C + 1, 0.0);
    for (int i=0; i<question_size; i++) {
        int w = static_cast<int>(std::floor(items[i].weight));
        double v = items[i].value;
        if (w <= 0) {
            // 重量取整後為 0 的物品必拿，價值直接加進每個狀態
            for (int c=0; c<=C; c++) {
                dp[c] += v;
            }

            continue;
        }

        for (int c=C; c>=w; c--) {
            dp[c] = std::max(dp[c], dp[c - w] + v);
        }
    }

    return dp[C];
}

#endif
