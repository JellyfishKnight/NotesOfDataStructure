cmake_minimum_required(VERSION 3.22)
project(DataStructure)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        ${PROJECT_SOURCE_DIR}/BinaryTree
        ${PROJECT_SOURCE_DIR}/Stack
        ${PROJECT_SOURCE_DIR}/Graph
        ${PROJECT_SOURCE_DIR}/SearchTree
        ${PROJECT_SOURCE_DIR}/List
        ${PROJECT_SOURCE_DIR}/Queue
        ${PROJECT_SOURCE_DIR}/Vector
)

add_subdirectory(./BinaryTree)
add_subdirectory(./Stack)
add_subdirectory(./Graph)
add_subdirectory(./SearchTree)
add_subdirectory(./List)
add_subdirectory(./Queue)
add_subdirectory(./Vector)

set(TARGET BinaryTree Stack Graph SearchTree List Queue Vector)

add_executable(DataStructure ${TARGET} main.cpp)

target_link_libraries(
        ${PROJECT_NAME} ${TARGET}
)
