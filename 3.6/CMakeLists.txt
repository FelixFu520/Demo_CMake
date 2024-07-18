# set minimum cmake version
cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

# project name and language
project(recipe-06 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 安装教程: https://blog.csdn.net/MOONLIGHT003/article/details/107472463
find_package(MPI REQUIRED)

add_executable(hello-mpi hello-mpi.cpp)

target_link_libraries(hello-mpi
  PUBLIC
    MPI::MPI_CXX
  )
