cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(demo VERSION 0.1.0 LANGUAGES C CXX)


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


# 测试
include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
