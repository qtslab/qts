#include <string>

#include "experiment.hpp"
#include "QTS.hpp"

// QTS 獨立執行檔。參數一律由設定檔讀入（預設 config/case.conf，可由第一個
// 命令列引數覆寫），調整參數不需重新編譯。計時請用 benchmark.sh。
int main(int argc, char* argv[]) {
    const std::string config_path = (argc > 1) ? argv[1] : "config/case.conf";
    return run_experiment("QTS", config_path, "csv/QTS.csv", QTS);
}
