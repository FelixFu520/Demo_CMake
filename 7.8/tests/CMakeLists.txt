find_package(Catch2 REQUIRED)
include(CTest)
include(Catch)

add_executable(cpp_test test.cpp)
target_link_libraries(cpp_test evolution Catch2::Catch2WithMain)


# 测试
add_test(
  NAME
    test_evolution
  COMMAND
    $<TARGET_FILE:cpp_test>
)

