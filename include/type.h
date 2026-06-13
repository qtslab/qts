#ifndef TYPE_H
#define TYPE_H

#include <cmath>
#include <cstddef>
#include <vector>

struct qubit {
    double alpha = 1/sqrt(2);
    double beta = 1/sqrt(2);
};

struct item {
    double value = 0;
    double weight = 0;
};

// 動態大小的解（取代舊有 std::bitset<question_size>），讓問題規模 question_size
// 可於執行期由設定檔決定。以 std::vector<bool> 位元封裝節省記憶體，
// 並保留原本程式碼使用到的 .set(i, v) / operator[] / .size() 介面。
struct solution_t {
    std::vector<bool> bits;

    solution_t() = default;
    explicit solution_t(std::size_t n) : bits(n, false) {}

    std::size_t size() const { return bits.size(); }
    void set(std::size_t i, bool v) { bits[i] = v; }
    std::vector<bool>::reference operator[](std::size_t i) { return bits[i]; }
    bool operator[](std::size_t i) const { return bits[i]; }
};

using items_t = std::vector<item>;
using q_t = std::vector<qubit>;

#endif
