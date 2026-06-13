#!/usr/bin/env bash
# 用 shell 的 time + for 迴圈重現原本程式內建的計時。
#
# QTS / AE-QTS 已拆成兩支獨立執行檔（build/qts、build/ae_qts），這支腳本分別
# 量測整支執行檔的牆鐘時間，並重複數次取平均，方便和 GPU 版本做時間比較。
# 程式本身不再做計時，計時只發生在這裡。
#
# 用法（可從任何目錄執行，路徑一律以專案根目錄為基準）：
#   script/benchmark.sh [config 路徑] [重複次數]
# 範例：
#   script/benchmark.sh                      # 預設 config/case.conf，重複 5 次
#   script/benchmark.sh config/case.conf 10  # 指定設定檔與重複次數
set -euo pipefail

# 切到專案根目錄（本腳本位於 script/ 之下），讓相對路徑不受呼叫時的 CWD 影響
cd "$(dirname "${BASH_SOURCE[0]}")/.."

config="${1:-config/case.conf}"
repeat="${2:-5}"
build_dir="build"

# 量測單一執行檔重複 repeat 次的時間，印出每次與平均
bench() {
    local exe="$1"
    local label="$2"
    local path="${build_dir}/${exe}"

    if [[ ! -x "${path}" ]]; then
        echo "找不到執行檔 ${path}，請先執行：cmake -B build && cmake --build build" >&2
        exit 1
    fi

    echo "=== ${label}（重複 ${repeat} 次，config=${config}）==="
    local sum=0
    for ((i=1; i<=repeat; i++)); do
        local elapsed
        # bash 內建 time 的輸出走 stderr；'%R' 只印牆鐘秒數。
        # 程式自身的 stdout/stderr 一律丟掉，只留下計時數字。
        elapsed=$( { TIMEFORMAT='%R'; time "${path}" "${config}" >/dev/null 2>&1; } 2>&1 )
        printf '  run %d: %s s\n' "${i}" "${elapsed}"
        sum=$(awk "BEGIN{print ${sum} + ${elapsed}}")
    done

    awk "BEGIN{printf \"  平均: %.3f s\\n\", ${sum} / ${repeat}}"
    echo
}

bench qts    "QTS"
bench ae_qts "AE-QTS"
