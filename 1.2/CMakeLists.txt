# set minimum cmake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# project name and language
project(recipe-02 LANGUAGES CXX)

add_executable(hello-world hello-world.cpp)

# 需要先安装Ninja, sudo apt install ninja-build, 需要区别下make和ninja的区别
# cmake -G Ninja ..
# cmake --build .