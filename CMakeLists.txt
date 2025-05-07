cmake_minimum_required(VERSION 3.20.0)
project(qts VERSION 0.0.0)

set(CMAKE_CXX_STANDARD 23)

include_directories(./include)

file(GLOB_RECURSE SRC_FILES ./src/*.cpp)

find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} ${MPI_LIBRARIES})
target_compile_options(${PROJECT_NAME} PRIVATE ${MPI_CXX_COMPILE_FLAGS})
