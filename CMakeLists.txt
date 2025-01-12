cmake_minimum_required(VERSION 3.10)

project(sapy)

set(CMAKE_CXX_STANDARD 20)

find_package(reflectcpp REQUIRED)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)


add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(bench)

