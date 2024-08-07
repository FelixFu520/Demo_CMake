cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(recipe-02 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(UseSphinxDoc)

add_subdirectory(src)

add_sphinx_doc(
  SOURCE_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/docs
  BUILD_DIR
    ${CMAKE_CURRENT_BINARY_DIR}/_build
  CACHE_DIR
    ${CMAKE_CURRENT_BINARY_DIR}/_doctrees
  HTML_DIR
    ${CMAKE_CURRENT_BINARY_DIR}/sphinx_html
  CONF_FILE
    ${CMAKE_CURRENT_SOURCE_DIR}/docs/conf.py.in
  TARGET_NAME
    docs
  COMMENT
    "HTML documentation"
  )
# sudo apt install sphinx
# mkdir -p build
# cd build
# cmake ..
# cmake --build . --target docs