#include "sum_integers.hpp"
// this tells catch to provide a main()
// only do this in one cpp file
#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <vector>
#include "sum_integers.hpp"

#include <iostream>
#include <string>
#include <vector>

// we assume all arguments are integers and we sum them up
// for simplicity we do not verify the type of arguments
int main(int argc, char *argv[]) {

  std::vector<int> integers = {1, 2, 3, 4, 5};
  auto sum = sum_integers(integers);

  std::cout << sum << std::endl;
}

TEST_CASE("Sum of integers for a short vector", "[short]")
{
  auto integers = {1, 2, 3, 4, 5};
  REQUIRE(sum_integers(integers) == 15);
}
TEST_CASE("Sum of integers for a longer vector", "[long]")
{
  std::vector<int> integers;
  for (int i = 1; i < 1001; ++i)
  {
    integers.push_back(i);
  }
  REQUIRE(sum_integers(integers) == 500500);
}