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
// 精確性：當所有物品重量為整數時（case_II、case_III）此為精確最佳解；
// 若重量為實數（case_I），會將重量四捨五入取整，得到的是近似 baseline。
double DP(items_t& items, double capacity) {
    int C = static_cast<int>(std::floor(capacity));
    if (C < 0) {
        C = 0;
    }

    std::vector<double> dp(C + 1, 0.0);
    for (int i=0; i<question_size; i++) {
        int w = static_cast<int>(std::llround(items[i].weight));
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
