cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(recipe-03 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(UseBreathe)

add_subdirectory(src)

add_breathe_doc(
  SOURCE_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/docs
  BUILD_DIR
    ${CMAKE_CURRENT_BINARY_DIR}/_build
  CACHE_DIR
    ${CMAKE_CURRENT_BINARY_DIR}/_doctrees
  HTML_DIR
    ${CMAKE_CURRENT_BINARY_DIR}/html
  DOXY_FILE
    ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in
  CONF_FILE
    ${CMAKE_CURRENT_SOURCE_DIR}/docs/conf.py.in
  TARGET_NAME
    docs
  COMMENT
    "HTML documentation"
  )

# sudo apt install python3-breathe
# pip install breathe
# cmake ..
# make
# cmake --build . --target docs