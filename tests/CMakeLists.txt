find_package(Catch2 REQUIRED)
include(CTest)
include(Catch)

add_executable(cpp_test test.cpp)
target_link_libraries(cpp_test sum_integers)
target_link_libraries(cpp_test sum_integers Catch2::Catch2WithMain)

macro(add_catch_test _name _cost)
  math(EXPR num_macro_calls "${num_macro_calls} + 1")
  message(STATUS "FF, add_catch_test called with ${ARGC} arguments: ${ARGV}")

  set(_argn "${ARGN}")
  message(STATUS "FF, add_catch_test received extra arguments: ${_argn}")
  if(_argn)
    message(STATUS "FF, oops - macro received argument(s) we did not expect: ${ARGN}")
  endif()

  add_test(
    NAME
      ${_name}
    COMMAND
      $<TARGET_FILE:cpp_test>
      [${_name}] --success --out
      ${PROJECT_BINARY_DIR}/tests/${_name}.log --durations yes
    WORKING_DIRECTORY
      ${CMAKE_CURRENT_BINARY_DIR}
    )

  set_tests_properties(
    ${_name}
    PROPERTIES
      COST ${_cost}
    )
endmacro()

set(num_macro_calls 0)

add_catch_test(short 1.5)
add_catch_test(long 2.5 extra_argument)

message(STATUS "FF, in total there were ${num_macro_calls} calls to add_catch_test")
