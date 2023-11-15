cmake_minimum_required(VERSION 3.20.0)
project(qts VERSION 0.0.0)

set(CMAKE_CXX_STANDARD 23)

include_directories(/opt/homebrew/include/eigen3)
include_directories(/opt/homebrew/include/armadillo_bits)

include_directories(./include)

file(GLOB_RECURSE SRC_FILES ./src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})