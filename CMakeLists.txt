# 设置cmake最低版本
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)  


# 设置项目名称和语言
project(cmake_demo LANGUAGES C CXX)   


# 设置C++
set(CMAKE_CXX_STANDARD 11)  # 设置C++标准
set(CMAKE_CXX_EXTENSIONS OFF) # 关闭编译器的扩展
set(CMAKE_CXX_STANDARD_REQUIRED ON) # 设置C++标准为必须


# 添加模块路径
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake") 


# 设置颜色
include(colors) # 包含colors模块
define_colors() # 定义颜色
message(STATUS "FF, This is a normal message")
message(STATUS "${Red}FF, This is a red${ColourReset}")
message(STATUS "${BoldRed}FF, This is a bold red${ColourReset}")
message(STATUS "${Green}FF, This is a green${ColourReset}")
message(STATUS "${BoldMagenta}FF, This is bold${ColourReset}")


# 通过函数设置编译器标志
include(set_compiler_flag) # 包含compiler_flags模块
set_compiler_flag(
  working_compile_flag C REQUIRED
  "-foo"             # this should fail
  "-wrong"           # this should fail
  "-wrong"           # this should fail
  "-Wall"            # this should work with GNU
  "-warn all"        # this should work with Intel
  "-Minform=inform"  # this should work with PGI
  "-nope"            # this should fail
  )
message(STATUS "FF, working C compile flag: ${working_compile_flag}")
set_compiler_flag(
  working_compile_flag CXX REQUIRED
  "-foo"    # this should fail
  "-g"      # this should work with GNU, Intel, PGI
  "/RTCcsu" # this should work with MSVC
  )
message(STATUS "FF, working CXX compile flag: ${working_compile_flag}")




# 设置安装目录
include(GNUInstallDirs) 
message(STATUS "FF, GNUInstallDirs: ${GNUInstallDirs}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}) # 设置输出目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}) # 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}) # 设置输出目录
message(STATUS "FF, CMAKE_ARCHIVE_OUTPUT_DIRECTORY: ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
message(STATUS "FF, CMAKE_LIBRARY_OUTPUT_DIRECTORY: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
message(STATUS "FF, CMAKE_RUNTIME_OUTPUT_DIRECTORY: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")


# defines targets and sources
add_subdirectory(src)

# contains an "external" library we will link to
add_subdirectory(external)

# enable testing and define tests
enable_testing()
add_subdirectory(tests)

