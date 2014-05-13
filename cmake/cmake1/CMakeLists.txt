# cmake 所需的最小版本
cmake_minimum_required (VERSION 2.6)

# 项目名称
project (CMAKE_TEST1)
message (STATUS "Project Name      : ${PROJECT_NAME}")
message (STATUS "Binary  Directory : ${PROJECT_BINARY_DIR}")

# 可执行文件输出地址
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
message (STATUS "Execute Directory : ${CMAKE_LIBRARY_PATH}")

set (CMAKE_LIBRARY_PATH "${CMAKE_BINARY_DIR}/lib")
# 动态库输出地址
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_PATH})
# 静态库输出地址
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_PATH})
link_directories (${CMAKE_LIBRARY_PATH})
message (STATUS "Lribrary Directory : ${CMAKE_LIBRARY_PATH}")

set (PROJECT_SOURCE_DIR "${PROJECT_BINARY_DIR}/src")
message (STATUS "Source  Directory : ${PROJECT_SOURCE_DIR}")


# 添加头文件位置目录
include_directories ("${PROJECT_BINARY_DIR}/include")
# 添加链接库
add_library (add "${PROJECT_SOURCE_DIR}/add.cpp")
# 编译成可执行文件
add_executable (main "${PROJECT_SOURCE_DIR}/main.cpp")
# 链接
target_link_libraries (main add)
