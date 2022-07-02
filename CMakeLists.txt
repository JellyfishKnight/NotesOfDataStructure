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
        ${PROJECT_SOURCE_DIR}/AVLTree
        ${PROJECT_SOURCE_DIR}/SplayTree
        ${PROJECT_SOURCE_DIR}/BSubTree
        ${PROJECT_SOURCE_DIR}/RedBlack
        ${PROJECT_SOURCE_DIR}/StringAlthorigm
)

add_subdirectory(./BinaryTree)
add_subdirectory(./Stack)
add_subdirectory(./Graph)
add_subdirectory(./SearchTree)
add_subdirectory(./List)
add_subdirectory(./Queue)
add_subdirectory(./Vector)
add_subdirectory(./AVLTree)
add_subdirectory(./SplayTree)
add_subdirectory(./BSubTree)
add_subdirectory(./RedBlack)
add_subdirectory(./StringAlthorigm)

set(TARGET BinaryTree Stack Graph SearchTree List Queue Vector AVLTree SplayTree BSubTree)

add_executable(DataStructure ${TARGET} main.cpp)

target_link_libraries(
        ${PROJECT_NAME} ${TARGET}
)
