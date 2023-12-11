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

int main(int argc, char* argv[]) {
    items_t items;
    double capacity = 0;
    /// Case III
    for (int i=0; i<question_size; i++) {
        int value = (i % 10) + 1;
        items[i].weight = value;
        items[i].value = value + 5;
    }

    for (int i=0; i<question_size; i++) {
        capacity += items[i].weight;
    }

    capacity /= 2;
    /// case end

    // print the items and capacity
    std::cout << "capacity: " << capacity << std::endl;
    std::cout << "items: " << std::endl;
    print_items(items);
    std::cout << std::endl << "Max generation: " << max_gen << std::endl << std::endl;

    std::thread threads[test_times];
    std::vector<std::vector<double>> QTS_records(max_gen, std::vector<double>(test_times));
    std::vector<std::vector<double>> AE_QTS_records(max_gen, std::vector<double>(test_times));
    for (int i=0; i<test_times; i++) {
        threads[i] = std::thread(QTS, std::ref(items), capacity, max_gen, N, std::ref(QTS_records[i]));
    }

    auto QTS_start = std::chrono::high_resolution_clock::now();
    for (int i=0; i<test_times; i++) {
        threads[i].join();
    }

    auto QTS_end = std::chrono::high_resolution_clock::now();
    for (int i=0; i<test_times; i++) {
        threads[i] = std::thread(AE_QTS, std::ref(items), capacity, max_gen, N, std::ref(AE_QTS_records[i]));
    }

    auto AE_QTS_start = std::chrono::high_resolution_clock::now();
    for (int i=0; i<test_times; i++) {
        threads[i].join();
    }

    auto AE_QTS_end = std::chrono::high_resolution_clock::now();

    std::cout << "QTS time:    " << std::chrono::duration_cast<std::chrono::nanoseconds>(QTS_end - QTS_start).count() << "ns" << std::endl;
    std::cout << "AE-QTS time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(AE_QTS_end - AE_QTS_start).count() << "ns" << std::endl;

    std::ofstream fout("csv/QTS.csv");
    for (int i=0; i<max_gen; i++) {
        double QTS_sum = 0, AE_QTS_sum = 0;
        for (int j=0; j<test_times; j++) {
            QTS_sum += QTS_records[j][i];
            AE_QTS_sum += AE_QTS_records[j][i];
        }

        fout << i << "," << QTS_sum/test_times << "," << AE_QTS_sum/test_times << std::endl;
    }

    fout.close();
    return 0;
}
