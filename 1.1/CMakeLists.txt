# set minimum cmake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# project name and language
project(recipe-01 LANGUAGES CXX)

add_executable(hello-world hello-world.cpp)

# cmake -H. -Bbuild -DCMAKE_INSTALL_PREFIX=install -DCMAKE_BUILD_TYPE=Release 
# cmake --build build