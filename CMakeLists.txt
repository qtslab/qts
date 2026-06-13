cmake_minimum_required(VERSION 3.20.0)
project(qts VERSION 0.0.0)

set(CMAKE_CXX_STANDARD 23)

include_directories(./include)

# 共用的量子運算實作，兩支執行檔共用
add_library(qts_core STATIC src/quantum_function.cpp)

# QTS / AE-QTS 各自獨立編譯成一支執行檔，方便用 shell 的 time 個別量測時間，
# 和 GPU 版本做比較（計時與重複次數見 script/benchmark.sh）。
add_executable(qts src/qts_main.cpp)
target_link_libraries(qts PRIVATE qts_core)

add_executable(ae_qts src/ae_qts_main.cpp)
target_link_libraries(ae_qts PRIVATE qts_core)
