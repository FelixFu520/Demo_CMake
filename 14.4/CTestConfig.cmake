set(CTEST_DROP_METHOD "http")
set(CTEST_DROP_SITE "my.cdash.org")
set(CTEST_DROP_LOCATION "/submit.php?project=cmake-cookbook")
set(CTEST_DROP_SITE_CDASH TRUE)

# # $ mkdir -p build
# $ cd build
# $ cmake -DENABLE_ASAN=ON ..
# $ cmake --build .
# $ cmake --build . --target test