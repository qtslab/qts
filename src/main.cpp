#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <thread>
#include <fstream>

#include "config.hpp"
#include "type.h"

#include "case.hpp"
#include "thread_pool.hpp"

#include "QTS.hpp"
#include "AE-QTS.hpp"
#include "DP.hpp"

int main(int argc, char* argv[]) {
    // 參數一律由設定檔讀入（預設 config/case.conf，可由第一個命令列引數覆寫），
    // 調整參數不需重新編譯。
    const std::string config_path = (argc > 1) ? argv[1] : "config/case.conf";
    const Config cfg = load_config(config_path);
    const int N = cfg.N;
    const int max_gen = cfg.max_gen;
    const int test_times = cfg.test_times;

    items_t items(cfg.question_size);
    double capacity = 0;
    // Case start
    case_I(items, capacity, cfg.min_weight, cfg.max_weight); // set case
    // case end

    // print the items and capacity
    std::cout << "capacity: " << capacity << std::endl;
    std::cout << "items: " << std::endl;
    print_items(items);
    std::cout << std::endl << "Max generation: " << max_gen << std::endl << std::endl;

    // DP baseline：求精確（整數重量）/ 有效上界（實數重量）最佳解，作為收斂對照線
    auto DP_start = std::chrono::high_resolution_clock::now();
    double DP_optimal = DP(items, capacity);
    auto DP_end = std::chrono::high_resolution_clock::now();
    std::cout << "DP optimal:  " << DP_optimal << std::endl << std::endl;

    // 用與硬體邏輯執行緒數相同的 worker thread 跑完 test_times 次 run，
    // 避免一次性開 test_times 條 OS thread 造成的 context switch 開銷。
    const unsigned num_threads = hardware_threads();
    std::cout << "worker threads: " << num_threads << std::endl << std::endl;
    // 維度是 [run][gen]：外層每條 run（test_times）各一個 vector，
    // 內層存該 run 每一代（max_gen）的紀錄。寫入端（record[gen]）與
    // 輸出端（records[run][gen]）都依此索引，故外層須為 test_times、內層 max_gen。
    std::vector<std::vector<double>> QTS_records(test_times, std::vector<double>(max_gen));
    std::vector<std::vector<double>> AE_QTS_records(test_times, std::vector<double>(max_gen));
    // start 必須放在派工之前：worker 一建立就開始執行，若放在之後才取時間，
    // 會漏算建立 thread 與已完成工作的時間。
    auto QTS_start = std::chrono::high_resolution_clock::now();
    parallel_for(test_times, num_threads, [&](int i) {
        QTS(items, capacity, max_gen, N, QTS_records[i]);
    });

    auto QTS_end = std::chrono::high_resolution_clock::now();

    auto AE_QTS_start = std::chrono::high_resolution_clock::now();
    parallel_for(test_times, num_threads, [&](int i) {
        AE_QTS(items, capacity, max_gen, N, AE_QTS_records[i]);
    });

    auto AE_QTS_end = std::chrono::high_resolution_clock::now();

    std::cout << "QTS time:    " << std::chrono::duration_cast<std::chrono::nanoseconds>(QTS_end - QTS_start).count() << "ns" << std::endl;
    std::cout << "AE-QTS time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(AE_QTS_end - AE_QTS_start).count() << "ns" << std::endl;
    std::cout << "DP time:     " << std::chrono::duration_cast<std::chrono::nanoseconds>(DP_end - DP_start).count() << "ns" << std::endl;

    std::ofstream fout("csv/QTS.csv");
    for (int i=0; i<max_gen; i++) {
        double QTS_sum = 0, AE_QTS_sum = 0;
        for (int j=0; j<test_times; j++) {
            QTS_sum += QTS_records[j][i];
            AE_QTS_sum += AE_QTS_records[j][i];
        }

        // 第 4 欄為 DP 最佳解，每代皆相同，於圖表中為一條水平基準線
        fout << i << "," << QTS_sum/test_times << "," << AE_QTS_sum/test_times << "," << DP_optimal << std::endl;
    }

    fout.close();
    return 0;
}
