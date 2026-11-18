
cmake_minimum_required(VERSION 3.28)
project(LOTW_2026 LANGUAGES CXX)

# Set before add_subdirectory so every quest inherits it
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)   # lets clangd understand your flags

add_subdirectory(q1)
# add_subdirectory(q2) ...

add_executable(lotw main.cpp Args.cpp)

target_link_libraries(lotw PRIVATE quest1)
