cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(demo VERSION 0.1.0 LANGUAGES C CXX Fortran)


# 打印cmake配置信息, cmake所有的配置信息都会被打印到文件中
# $ cmake --system-information information.txt


# 操作系统(2. 检测环境)
message(STATUS "FF, Configuring on/for ${CMAKE_SYSTEM_NAME}")
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "FF, Configuring on/for Linux")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message(STATUS "FF, Configuring on/for macOS")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "FF, Configuring on/for Windows")
elseif(CMAKE_SYSTEM_NAME STREQUAL "AIX")
    message(STATUS "FF, Configuring on/for IBM AIX")
else()
    message(STATUS "FF, Configuring on/for ${CMAKE_SYSTEM_NAME}")
endif()


# 构建类型
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()
message(STATUS "FF, Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "FF, C flags, Debug configuration: ${CMAKE_C_FLAGS_DEBUG}")
message(STATUS "FF, C flags, Release configuration: ${CMAKE_C_FLAGS_RELEASE}")
message(STATUS "FF, C flags, Release configuration with Debug info: ${CMAKE_C_FLAGS_RELWITHDEBINFO}")
message(STATUS "FF, C flags, minimal Release configuration: ${CMAKE_C_FLAGS_MINSIZEREL}")
message(STATUS "FF, C++ flags, Debug configuration: ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "FF, C++ flags, Release configuration: ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "FF, C++ flags, Release configuration with Debug info: ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
message(STATUS "FF, C++ flags, minimal Release configuration: ${CMAKE_CXX_FLAGS_MINSIZEREL}")


# 设置编译器选项, 配合target_compile_options使用
set(COMPILER_FLAGS)
set(COMPILER_FLAGS_DEBUG)
set(COMPILER_FLAGS_RELEASE)
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
  list(APPEND CXX_FLAGS "-fno-rtti" "-fno-exceptions")
  list(APPEND CXX_FLAGS_DEBUG "-Wsuggest-final-types" "-Wsuggest-final-methods" "-Wsuggest-override")
  list(APPEND CXX_FLAGS_RELEASE "-O3" "-Wno-unused")
endif()
if(CMAKE_CXX_COMPILER_ID MATCHES Clang)
  list(APPEND CXX_FLAGS "-fno-rtti" "-fno-exceptions" "-Qunused-arguments" "-fcolor-diagnostics")
  list(APPEND CXX_FLAGS_DEBUG "-Wdocumentation")
  list(APPEND CXX_FLAGS_RELEASE "-O3" "-Wno-unused")
endif()


# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
message(STATUS "FF, C++ standard: ${CMAKE_CXX_STANDARD}")


# 编译选项
include(CMakeDependentOption)
option(USE_LIBRARY "Compile sources into a library" OFF)
message(STATUS "FF, Compile sources into a library? ${USE_LIBRARY}")
# second option depends on the value of the first
cmake_dependent_option(
  MAKE_STATIC_LIBRARY "Compile sources into a static library" OFF
  "USE_LIBRARY" ON
  )

# third option depends on the value of the first
cmake_dependent_option(
  MAKE_SHARED_LIBRARY "Compile sources into a shared library" ON
  "USE_LIBRARY" ON
)


# --------------------------- main ---------------------------
# 第三方库
find_package(Eigen3 3.3 REQUIRED CONFIG)
message(STATUS "FF, Eigen3 found: ${Eigen3_DIR}")
message(STATUS "FF, Eigen3 version: ${Eigen3_VERSION}")
message(STATUS "FF, Eigen3 include dirs: ${EIGEN3_INCLUDE_DIR}")


# 设置源文件
list(APPEND _sources Message.hpp Message.cpp)


# 设置源文件属性
message(STATUS "FF, Setting source properties using IN LISTS syntax:")
foreach(__source IN LISTS _sources)
  set_source_files_properties(${__source} PROPERTIES COMPILE_FLAGS -O2)
  message(STATUS "FF, Appending -O2 flag for ${__source}")
endforeach()
message(STATUS "FF, Querying sources properties using plain syntax:")
foreach(__source ${_sources})
  get_source_file_property(_flags ${__source} COMPILE_FLAGS)
  message(STATUS "FF, Source ${__source} has the following extra COMPILE_FLAGS: ${_flags}")
endforeach()


# 生成可执行文件
if(USE_LIBRARY)
  message(STATUS "FF, Compile sources into a STATIC library? ${MAKE_STATIC_LIBRARY}")
  message(STATUS "FF, Compile sources into a SHARED library? ${MAKE_SHARED_LIBRARY}")

  if(MAKE_SHARED_LIBRARY)
    add_library(message SHARED ${_sources})

    add_executable(demo main.cpp)

    target_link_libraries(demo message Eigen3::Eigen)
  elseif(MAKE_STATIC_LIBRARY)
    add_library(message STATIC ${_sources})

    add_executable(demo main.cpp)

    target_link_libraries(demo message Eigen3::Eigen)
  else()
    add_library(message ${_sources})

    add_executable(demo main.cpp)

    target_link_libraries(demo message Eigen3::Eigen)
  endif()
else()
  add_executable(demo main.cpp ${_sources})
endif()

# 设置编译选项
target_compile_options(demo
  PRIVATE
  ${CXX_FLAGS}
  "$<$<CONFIG:Debug>:${CXX_FLAGS_DEBUG}>"
  "$<$<CONFIG:Release>:${CXX_FLAGS_RELEASE}>"
)
# ----------------------------------------------


# 检测python解析器(3. 检测外部库和程序)
find_package(PythonInterp REQUIRED)
message(STATUS "FF, Python interpreter found: ${PYTHON_EXECUTABLE}")
execute_process(
  COMMAND
      ${PYTHON_EXECUTABLE} "-c" "print('Hello, world!')"
  RESULT_VARIABLE _status
  OUTPUT_VARIABLE _hello_world
  ERROR_QUIET
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
message(STATUS "FF, RESULT_VARIABLE is: ${_status}")
message(STATUS "FF, OUTPUT_VARIABLE is: ${_hello_world}")


# 检测Python库(3. 检测外部库和程序)
find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED)
message(STATUS "FF, Python version: ${PYTHONLIBS_VERSION_STRING}")
message(STATUS "FF, Python include dirs: ${PYTHON_INCLUDE_DIRS}")
message(STATUS "FF, Python libraries: ${PYTHON_LIBRARIES}")
add_executable(hello-embedded-python hello-embedded-python.c)
target_include_directories(hello-embedded-python
  PRIVATE
    ${PYTHON_INCLUDE_DIRS}
)
target_link_libraries(hello-embedded-python
  PRIVATE
    ${PYTHON_LIBRARIES}
)


# 检测Python模块和包(3. 检测外部库和程序)
find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED)
# 正确打包的Python模块，指定安装位置和版本
execute_process(
  COMMAND
      ${PYTHON_EXECUTABLE} "-c" "import re, numpy; print(re.compile('/__init__.py.*').sub('',numpy.__file__))"
  RESULT_VARIABLE _numpy_status
  OUTPUT_VARIABLE _numpy_location
  ERROR_QUIET
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
# 如果找到NumPy，则_numpy_status变量为整数，否则为错误的字符串，而_numpy_location将包含NumPy模块的路径。
# 如果找到NumPy，则将它的位置保存到一个名为NumPy的新变量中。
# 注意，新变量被缓存，这意味着CMake创建了一个持久性变量，用户稍后可以修改该变量
if(NOT _numpy_status)
    set(NumPy ${_numpy_location} CACHE STRING "Location of NumPy")
endif()
# 下一步是检查模块的版本
execute_process(
  COMMAND
      ${PYTHON_EXECUTABLE} "-c" "import numpy; print(numpy.__version__)"
  OUTPUT_VARIABLE _numpy_version
  ERROR_QUIET
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
# FindPackageHandleStandardArgs的CMake包以正确的格式设置NumPy_FOUND变量和输出信息
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(NumPy
  FOUND_VAR NumPy_FOUND
  REQUIRED_VARS NumPy
  VERSION_VAR _numpy_version
)
# 一旦正确的找到所有依赖项，我们就可以编译可执行文件，并将其链接到Python库
add_executable(pure-embedding "")
target_sources(pure-embedding
  PRIVATE
      Py${PYTHON_VERSION_MAJOR}-pure-embedding.cpp
  )
target_include_directories(pure-embedding
  PRIVATE
      ${PYTHON_INCLUDE_DIRS}
  )
target_link_libraries(pure-embedding
  PRIVATE
      ${PYTHON_LIBRARIES}
  )
# 我们还必须保证use_numpy.py在build目录中可用
add_custom_command(
  OUTPUT
      ${CMAKE_CURRENT_BINARY_DIR}/use_numpy.py
  COMMAND
      ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/use_numpy.py
      ${CMAKE_CURRENT_BINARY_DIR}/use_numpy.py
  DEPENDS
      ${CMAKE_CURRENT_SOURCE_DIR}/use_numpy.py
  )
# make sure building pure-embedding triggers the above custom command
target_sources(pure-embedding
  PRIVATE
      ${CMAKE_CURRENT_BINARY_DIR}/use_numpy.py
  )
# ./pure-embedding use_numpy print_ones 2 3


# 检测BLAS和LAPACK(3. 检测外部库和程序)
# https://www.netlib.org/lapack/
# https://blog.csdn.net/liang_baikai/article/details/125808997
# 找到BLAS和LAPACK
message(STATUS "FF, Searching for BLAS and LAPACK")
# SET(BLAS_LIBRARIES  /usr/local/lib/)
# SET(LAPACK_DIR /usr/local/lib/cmake/lapack-3.12.0/)
include(FortranCInterface)
FortranCInterface_VERIFY(CXX)
FortranCInterface_HEADER(
  fc_mangle.h
  MACRO_NAMESPACE "FC_"
  SYMBOLS DSCAL DGESV
  )
find_package(BLAS REQUIRED)
find_package(LAPACK REQUIRED)
message(STATUS "FF, BLAS libraries: ${BLAS_LIBRARIES}")
message(STATUS "FF, LAPACK libraries: ${LAPACK_LIBRARIES}")
# 添加一个库，其中包含BLAS和LAPACK包装器的源代码，并链接到LAPACK_LIBRARIES
add_library(math "")
target_sources(math
  PRIVATE
    CxxBLAS.cpp
    CxxLAPACK.cpp
)
# 注意，目标的包含目录和链接库声明为PUBLIC，因此任何依赖于数学库的附加目标也将在其包含目录中。
target_include_directories(math
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)
target_link_libraries(math
  PUBLIC
      ${LAPACK_LIBRARIES}
      ${BLAS_LIBRARIES}
      gfortran
)
add_executable(linear-algebra "")
target_sources(linear-algebra
  PRIVATE
      linear-algebra.cpp
)
target_link_libraries(linear-algebra
  PRIVATE
      math
)
# ./linear-algebra 1000


# 检测OpenMP(3. 检测外部库和程序)
find_package(OpenMP REQUIRED)
add_executable(example-openmp example.cpp)
target_link_libraries(example-openmp
  PUBLIC
      OpenMP::OpenMP_CXX
)
include(CMakePrintHelpers)
cmake_print_properties(
    TARGETS
        OpenMP::OpenMP_CXX
    PROPERTIES
        INTERFACE_COMPILE_OPTIONS
        INTERFACE_INCLUDE_DIRECTORIES
        INTERFACE_LINK_LIBRARIES
    )
# ./example-openmp 1000000000


# 检测Eigen(3. 检测外部库和程序)
find_package(OpenMP REQUIRED)
find_package(Eigen3 3.3 REQUIRED CONFIG)
if(TARGET Eigen3::Eigen)
  message(STATUS "FF, Eigen3 v${EIGEN3_VERSION_STRING} found in ${EIGEN3_INCLUDE_DIR}")
endif()
add_executable(linear-algebra-eigen linear-algebra-eigen.cpp)
find_package(BLAS)
if(BLAS_FOUND)
  message(STATUS "Eigen will use some subroutines from BLAS.")
  message(STATUS "See: http://eigen.tuxfamily.org/dox-devel/TopicUsingBlasLapack.html")
  target_compile_definitions(linear-algebra
    PRIVATE
        EIGEN_USE_BLAS
    )
  target_link_libraries(linear-algebra
    PUBLIC
        ${BLAS_LIBRARIES}
    )
else()
    message(STATUS "BLAS not found. Using Eigen own functions")
endif()
target_link_libraries(linear-algebra-eigen
  PUBLIC
    Eigen3::Eigen
    OpenMP::OpenMP_CXX
  )


# 检测Boost(3. 检测外部库和程序)
# https://blog.csdn.net/qq_41854911/article/details/119454212 , 安装
find_package(Boost 1.54 REQUIRED COMPONENTS filesystem)
add_executable(path-info path-info.cpp)
target_link_libraries(path-info
  PUBLIC
      Boost::filesystem
)
# ./path-info /root/work


# 处理与平台相关的源代码(2. 检测环境)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  target_compile_definitions(demo PUBLIC "IS_LINUX")
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  target_compile_definitions(demo PUBLIC "IS_MACOS")
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  target_compile_definitions(demo PUBLIC "IS_WINDOWS")
endif()


# 处理与编译器相关的源代码(2. 检测环境)
target_compile_definitions(demo PUBLIC "COMPILER_NAME=\"${CMAKE_CXX_COMPILER_ID}\"")
if(CMAKE_CXX_COMPILER_ID MATCHES Intel)
  target_compile_definitions(demo PUBLIC "IS_INTEL_CXX_COMPILER")
endif()
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
  target_compile_definitions(demo PUBLIC "IS_GNU_CXX_COMPILER")
endif()
if(CMAKE_CXX_COMPILER_ID MATCHES PGI)
  target_compile_definitions(demo PUBLIC "IS_PGI_CXX_COMPILER")
endif()
if(CMAKE_CXX_COMPILER_ID MATCHES XL)
  target_compile_definitions(demo PUBLIC "IS_XL_CXX_COMPILER")
endif()


# 检测处理器体系结构(2. 检测环境)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  target_compile_definitions(demo PUBLIC "IS_64_BIT_ARCH")
  message(STATUS "FF, Target is 64 bits")
else()
  target_compile_definitions(demo PUBLIC "IS_32_BIT_ARCH")
  message(STATUS "FF, Target is 32 bits")
endif()

if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "i386")
    message(STATUS "FF, i386 architecture detected")
elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "i686")
    message(STATUS "FF, i686 architecture detected")
elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86_64")
    message(STATUS "FF, x86_64 architecture detected")
else()
    message(STATUS "FF, host processor architecture is unknown")
endif()
target_compile_definitions(demo
  PUBLIC "ARCHITECTURE=${CMAKE_HOST_SYSTEM_PROCESSOR}"
)


# 检测处理器指令集(2. 检测环境)
target_include_directories(demo
  PRIVATE
       ${PROJECT_BINARY_DIR}
  )
foreach(key
  IN ITEMS
    NUMBER_OF_LOGICAL_CORES
    NUMBER_OF_PHYSICAL_CORES
    TOTAL_VIRTUAL_MEMORY
    AVAILABLE_VIRTUAL_MEMORY
    TOTAL_PHYSICAL_MEMORY
    AVAILABLE_PHYSICAL_MEMORY
    IS_64BIT
    HAS_FPU
    HAS_MMX
    HAS_MMX_PLUS
    HAS_SSE
    HAS_SSE2
    HAS_SSE_FP
    HAS_SSE_MMX
    HAS_AMD_3DNOW
    HAS_AMD_3DNOW_PLUS
    HAS_IA64
    OS_NAME
    OS_RELEASE
    OS_VERSION
    OS_PLATFORM
  )
  cmake_host_system_information(RESULT _${key} QUERY ${key})
endforeach()

configure_file(config.h.in config.h @ONLY)


# 创建一个简单得测试单元(4. 创建和运行测试)
find_package(PythonInterp REQUIRED)
find_program(BASH_EXECUTABLE NAMES bash REQUIRED)
# example library
add_library(sum_integers sum_integers.cpp)
# main code
add_executable(sum_up sum_integs_main.cpp)
target_link_libraries(sum_up sum_integers)
# testing binary
add_executable(cpp_test sum_integs_test.cpp)
target_link_libraries(cpp_test sum_integers)
enable_testing()
message(STATUS "FF, CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "FF, BASH_EXECUTABLE: ${BASH_EXECUTABLE}")
add_test(
  NAME bash_test
  COMMAND ${BASH_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test.sh $<TARGET_FILE:sum_up>
  ) # 这个测试在vscode中无法运行, 但是在终端中可以运行
add_test(
  NAME cpp_test
  COMMAND $<TARGET_FILE:cpp_test>
  )
add_test(
  NAME python_test_long
  COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/sum_integs_test.py --executable $<TARGET_FILE:sum_up>
  )
add_test(
  NAME python_test_short
  COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/sum_integs_test.py --short --executable $<TARGET_FILE:sum_up>
  )
# ./sum_up 1 2 3 4 5


# 使用Catch2测试框架(4. 创建和运行测试) 
# 安装Catch2: 自己找教程
find_package(Catch2 REQUIRED)
add_executable(cpp_test2 sum_integs_test2.cpp)
target_link_libraries(cpp_test2
  PUBLIC
  Catch2::Catch2 
  sum_integers 
)
add_test(
  NAME catch_test
  COMMAND $<TARGET_FILE:cpp_test2> --success
)


# 使用Google Test测试框架(4. 创建和运行测试)
# 安装Google Test: 自己找教程
find_package(GTest REQUIRED)
add_executable(cpp_test3 sum_integs_test3.cpp)
target_link_libraries(cpp_test3
  PUBLIC
  GTest::GTest
  GTest::Main
  sum_integers
)
add_test(
  NAME gtest_test
  COMMAND $<TARGET_FILE:cpp_test3>
)


# 使用Boost.Test测试框架(4. 创建和运行测试)
# 安装Boost: 自己找教程
find_package(Boost 1.54 REQUIRED COMPONENTS unit_test_framework)
add_executable(cpp_test4 sum_integs_test4.cpp)
target_link_libraries(cpp_test4
  PUBLIC
  Boost::unit_test_framework
  sum_integers
)
add_test(
  NAME boost_test
  COMMAND $<TARGET_FILE:cpp_test4>
)


# 使用动态分析工具来检测内存缺陷(4. 创建和运行测试)
# https://senlinzhan.github.io/2017/12/31/valgrind/, valgrind安装, 使用
add_library(example_library leaky_implementation.cpp)
add_executable(cpp_test_leaky leaky_implementation_main.cpp)
target_link_libraries(cpp_test_leaky example_library)
find_program(MEMORYCHECK_COMMAND NAMES valgrind)  # 查找valgrind，并将MEMORYCHECK_COMMAND设置为其绝对路径
set(MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full")
# add memcheck test action
include(CTest)
enable_testing()
add_test(
  NAME cpp_test_leaky_memcheck
  COMMAND $<TARGET_FILE:cpp_test_leaky>
  )
# ctest
# ctest -T memcheck


# 预期测试失败(4. 创建和运行测试)
find_package(PythonInterp REQUIRED)
add_test(example_test_fail ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test_fail.py)
set_tests_properties(example_test_fail PROPERTIES WILL_FAIL TRUE)


# 使用超时测试运行时间长得测试(4. 创建和运行测试)
find_package(PythonInterp REQUIRED)
add_test(example_test_timeout ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test_timeout.py)
set_tests_properties(example_test_timeout PROPERTIES TIMEOUT 10)


# 并行测试(4. 创建和运行测试)
find_package(PythonInterp REQUIRED)
add_test(a ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test/a.py)
add_test(b ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test/b.py)
add_test(c ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test/c.py)
add_test(d ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test/d.py)
set_tests_properties(a b c d PROPERTIES COST 0.5)

add_test(e ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test/e.py)
add_test(f ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test/f.py)
set_tests_properties(e f PROPERTIES COST 1.5)

add_test(g ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test/g.py)
set_tests_properties(g PROPERTIES COST 2.5)

add_test(h ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test/h.py)
set_tests_properties(h PROPERTIES COST 3.5)
# ctest
# ctest --parallel 4



# ctest
# include(CTest)
# enable_testing()

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
