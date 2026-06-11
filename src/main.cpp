#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <thread>
#include <fstream>

#include "constant.h"
#include "type.h"

#include "case.hpp"

#include "QTS.hpp"
#include "AE-QTS.hpp"
#include "DP.hpp"

int main(int argc, char* argv[]) {
    items_t items;
    double capacity = 0;
    // Case start
    case_I(items, capacity, max_gen, N); // set case
    // case end

    // print the items and capacity
    std::cout << "capacity: " << capacity << std::endl;
    std::cout << "items: " << std::endl;
    print_items(items);
    std::cout << std::endl << "Max generation: " << max_gen << std::endl << std::endl;

    // DP baseline：求精確（整數重量）/ 近似（實數重量）最佳解，作為收斂對照線
    auto DP_start = std::chrono::high_resolution_clock::now();
    double DP_optimal = DP(items, capacity);
    auto DP_end = std::chrono::high_resolution_clock::now();
    std::cout << "DP optimal:  " << DP_optimal << std::endl << std::endl;

    std::thread threads[test_times];
    // 維度是 [run][gen]：外層每條 run（test_times）各一個 vector，
    // 內層存該 run 每一代（max_gen）的紀錄。寫入端（record[gen]）與
    // 輸出端（records[run][gen]）都依此索引，故外層須為 test_times、內層 max_gen。
    std::vector<std::vector<double>> QTS_records(test_times, std::vector<double>(max_gen));
    std::vector<std::vector<double>> AE_QTS_records(test_times, std::vector<double>(max_gen));
    // start 必須放在 launch 迴圈之前：thread 一建立就開始執行，
    // 若放在 launch 之後才取時間，會漏算 launch 期間（含建立 thread 本身）
    // 已經完成的工作。
    auto QTS_start = std::chrono::high_resolution_clock::now();
    for (int i=0; i<test_times; i++) {
        threads[i] = std::thread(QTS, std::ref(items), capacity, max_gen, N, std::ref(QTS_records[i]));
    }

    for (int i=0; i<test_times; i++) {
        threads[i].join();
    }

    auto QTS_end = std::chrono::high_resolution_clock::now();

    auto AE_QTS_start = std::chrono::high_resolution_clock::now();
    for (int i=0; i<test_times; i++) {
        threads[i] = std::thread(AE_QTS, std::ref(items), capacity, max_gen, N, std::ref(AE_QTS_records[i]));
    }

    for (int i=0; i<test_times; i++) {
        threads[i].join();
    }

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
