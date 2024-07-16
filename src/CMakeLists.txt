set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)  # 设置接口中包含当前目录

add_library(sum_integers sum_integers.cpp)  # 添加库

add_executable(sum_up main.cpp) # 添加可执行文件

target_link_libraries(sum_up sum_integers) # 链接库
