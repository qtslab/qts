#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// 執行期參數集合。取代舊有 include/constant.h 的編譯期常數，
// 改由 config/case.conf 在啟動時讀入，調整參數不必重新編譯。
struct Config {
    int N = 10;                  // Neighbourhood size
    double min_value = 1.0;
    double max_value = 10.0;
    double min_weight = 1.0;
    double max_weight = 10.0;
    int max_gen = 1000;          // NumIter
    int question_size = 1000;    // n_items
};

// 解析 "key = value" 格式的設定檔，'#' 之後視為註解，空白行略過。
// 未列出的鍵沿用 Config 的預設值；無法開啟檔案時印出警告並回傳預設值，
// 讓程式仍可在沒有設定檔的情況下執行。
inline Config load_config(const std::string& path) {
    Config cfg;
    std::ifstream fin(path);
    if (!fin) {
        std::cerr << "warning: cannot open config file '" << path
                  << "', using default parameters" << std::endl;
        return cfg;
    }

    std::string line;
    while (std::getline(fin, line)) {
        // 去除註解
        if (auto pos = line.find('#'); pos != std::string::npos) {
            line.erase(pos);
        }

        auto eq = line.find('=');
        if (eq == std::string::npos) {
            continue; // 非 key=value 行（含空白行）
        }

        std::string key = line.substr(0, eq);
        std::string value = line.substr(eq + 1);
        auto trim = [](std::string& s) {
            const char* ws = " \t\r\n";
            auto b = s.find_first_not_of(ws);
            auto e = s.find_last_not_of(ws);
            s = (b == std::string::npos) ? "" : s.substr(b, e - b + 1);
        };
        trim(key);
        trim(value);
        if (key.empty() || value.empty()) {
            continue;
        }

        std::istringstream vs(value);
        if (key == "N") {
            vs >> cfg.N;
        } else if (key == "min_value") {
            vs >> cfg.min_value;
        } else if (key == "max_value") {
            vs >> cfg.max_value;
        } else if (key == "min_weight") {
            vs >> cfg.min_weight;
        } else if (key == "max_weight") {
            vs >> cfg.max_weight;
        } else if (key == "max_gen") {
            vs >> cfg.max_gen;
        } else if (key == "question_size") {
            vs >> cfg.question_size;
        } else {
            std::cerr << "warning: unknown config key '" << key << "' ignored" << std::endl;
        }
    }

    return cfg;
}

#endif
