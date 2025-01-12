project(sapy_bench)

# -O2
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} APP_SRC)
include_directories(${CMAKE_SOURCE_DIR}/include)

#target_link_directories(${CMAKE_SOURCE_DIR}/lib)
add_executable(${PROJECT_NAME} ${APP_SRC})
target_link_libraries(${PROJECT_NAME} sapy)
