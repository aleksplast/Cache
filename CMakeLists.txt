cmake_minimum_required(VERSION 3.0)
project(cache VERSION 0.1.0)

add_executable(lfu ${CMAKE_CURRENT_SOURCE_DIR}/src/LFU.cpp)
target_include_directories(lfu PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(perfect ${CMAKE_CURRENT_SOURCE_DIR}/src/PerfectCache.cpp)
target_include_directories(perfect PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
