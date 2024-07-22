# set minimum cmake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# project name and language
project(recipe-08 LANGUAGES CXX)

message("C++ compiler flags: ${CMAKE_CXX_FLAGS}")

list(APPEND flags "-fPIC" "-Wall")
if(NOT WIN32)
  list(APPEND flags "-Wextra" "-Wpedantic")
endif()

add_library(geometry
  STATIC
    geometry_circle.cpp
    geometry_circle.hpp
    geometry_polygon.cpp
    geometry_polygon.hpp
    geometry_rhombus.cpp
    geometry_rhombus.hpp
    geometry_square.cpp
    geometry_square.hpp
  )

target_compile_options(geometry
  PRIVATE
    ${flags}
  )

add_executable(compute-areas compute-areas.cpp)

target_compile_options(compute-areas
  PRIVATE
    "-fPIC"
  )

target_link_libraries(compute-areas geometry)

# if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
#   list(APPEND CMAKE_CXX_FLAGS "-fno-rtti" "-fno-exceptions")
#   list(APPEND CMAKE_CXX_FLAGS_DEBUG "-Wsuggest-final-types" "-Wsuggest-final-methods" "-Wsuggest-override")
#   list(APPEND CMAKE_CXX_FLAGS_RELEASE "-O3" "-Wno-unused")
# endif()
# if(CMAKE_CXX_COMPILER_ID MATCHES Clang)
#   list(APPEND CMAKE_CXX_FLAGS "-fno-rtti" "-fno-exceptions" "-Qunused-arguments" "-fcolor-diagnostics")
#   list(APPEND CMAKE_CXX_FLAGS_DEBUG "-Wdocumentation")
#   list(APPEND CMAKE_CXX_FLAGS_RELEASE "-O3" "-Wno-unused")
# endif()


# set(COMPILER_FLAGS)
# set(COMPILER_FLAGS_DEBUG)
# set(COMPILER_FLAGS_RELEASE)
# if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
#   list(APPEND CXX_FLAGS "-fno-rtti" "-fno-exceptions")
#   list(APPEND CXX_FLAGS_DEBUG "-Wsuggest-final-types" "-Wsuggest-final-methods" "-Wsuggest-override")
#   list(APPEND CXX_FLAGS_RELEASE "-O3" "-Wno-unused")
# endif()
# if(CMAKE_CXX_COMPILER_ID MATCHES Clang)
#   list(APPEND CXX_FLAGS "-fno-rtti" "-fno-exceptions" "-Qunused-arguments" "-fcolor-diagnostics")
#   list(APPEND CXX_FLAGS_DEBUG "-Wdocumentation")
#   list(APPEND CXX_FLAGS_RELEASE "-O3" "-Wno-unused")
# endif()


# target_compile_option(compute-areas
#   PRIVATE
#     ${CXX_FLAGS}
#     "$<$<CONFIG:Debug>:${CXX_FLAGS_DEBUG}>"
#     "$<$<CONFIG:Release>:${CXX_FLAGS_RELEASE}>"
#   )