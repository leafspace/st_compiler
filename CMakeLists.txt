cmake_minimum_required(VERSION 3.15)
project(st_compiler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含头文件目录
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/deci
)

# 源文件
file(GLOB SRC
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_executable(st_compiler ${SRC})

# 测试部分
enable_testing()
add_subdirectory(test)