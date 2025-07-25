cmake_minimum_required(VERSION 3.20.0)
project(qts VERSION 0.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)

# 選擇執行後端（可選 OpenMP, CUDA, HIP, SERIAL 等）
# set(Kokkos_ENABLE_SERIAL ON)
set(Kokkos_ENABLE_OPENMP ON)
# set(Kokkos_ENABLE_CUDA ON)
# set(Kokkos_ENABLE_HIP ON)

include_directories(./include)

# 加入 Kokkos
add_subdirectory(external/kokkos)

file(GLOB_RECURSE SRC_FILES ./src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})

# 連結 Kokkos
target_link_libraries(${PROJECT_NAME} Kokkos::kokkos)
