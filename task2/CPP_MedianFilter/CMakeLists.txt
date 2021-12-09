cmake_minimum_required(VERSION 3.20)
project(CPP_MedianFilter)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib)

add_executable(CPP_MedianFilter main.cpp)

target_link_libraries(CPP_MedianFilter PUBLIC MedianFilterLib)

target_include_directories(CPP_MedianFilter PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/lib"
        )


