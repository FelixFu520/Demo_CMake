#include "sum_integers.hpp"

#include <catch2/catch_test_macros.hpp>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>


TEST_CASE("Sum of integers for a short vector", "[short]") {
  auto integers = {1, 2, 3, 4, 5};
  REQUIRE(sum_integers(integers) == 15);
}

TEST_CASE("Sum of integers for a longer vector", "[long]") {
  std::vector<int> integers;
  for (int i = 1; i < 1001; ++i) {
    integers.push_back(i);
  }
  REQUIRE(sum_integers(integers) == 500500);
}
