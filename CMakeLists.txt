cmake_minimum_required(VERSION 3.5 FATAL_ERROR)  # 设置cmake最低版本


project(cmake_demo LANGUAGES CXX)   # 设置项目名称和语言


set(CMAKE_CXX_STANDARD 11)  # 设置C++标准
set(CMAKE_CXX_EXTENSIONS OFF) # 关闭编译器的扩展
set(CMAKE_CXX_STANDARD_REQUIRED ON) # 设置C++标准为必须


list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake") # 添加模块路径
include(colors) # 包含colors模块
define_colors() # 定义颜色
message(STATUS "FF, This is a normal message")
message(STATUS "${Red}FF, This is a red${ColourReset}")
message(STATUS "${BoldRed}FF, This is a bold red${ColourReset}")
message(STATUS "${Green}FF, This is a green${ColourReset}")
message(STATUS "${BoldMagenta}FF, This is bold${ColourReset}")


include(GNUInstallDirs) # 设置安装目录
message(STATUS "FF, GNUInstallDirs: ${GNUInstallDirs}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}) # 设置输出目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}) # 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}) # 设置输出目录
message(STATUS "FF, CMAKE_ARCHIVE_OUTPUT_DIRECTORY: ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
message(STATUS "FF, CMAKE_LIBRARY_OUTPUT_DIRECTORY: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
message(STATUS "FF, CMAKE_RUNTIME_OUTPUT_DIRECTORY: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")


add_subdirectory(src)   # 添加src目录

enable_testing()    # 启用测试
add_subdirectory(tests) # 添加tests目录
