cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(P1_Computron)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(P1_Computron src/computron.cpp src/main.cpp)

add_executable(my_test src/computron.cpp test/test.cpp)

enable_testing()