#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include <atomic>
#include <thread>
#include <vector>

// 以固定數量的 worker thread 平行執行 count 次獨立工作（索引 0..count-1）。
// 取代「一次性開 count 條 OS thread」的寫法：當 count（test_times）遠大於
// 硬體邏輯執行緒數時，過多 thread 會造成大量 context switch 拖慢計時。
//
// 派工方式為動態搶單：每條 worker 以 atomic 計數器 fetch_add 取得下一個索引，
// 直到索引用盡。各次工作彼此獨立、寫入不同的 records[i]，故無需額外鎖。
template <typename F>
void parallel_for(int count, unsigned num_threads, F func) {
    if (num_threads < 1) {
        num_threads = 1;
    }

    std::atomic<int> next{0};
    std::vector<std::thread> pool;
    pool.reserve(num_threads);
    for (unsigned t=0; t<num_threads; t++) {
        pool.emplace_back([&]() {
            for (int i=next.fetch_add(1); i<count; i=next.fetch_add(1)) {
                func(i);
            }
        });
    }

    for (auto& th : pool) {
        th.join();
    }
}

// 可用的硬體邏輯執行緒數；偵測失敗（回傳 0）時退回 1。
inline unsigned hardware_threads() {
    unsigned n = std::thread::hardware_concurrency();
    return n == 0 ? 1 : n;
}

#endif
