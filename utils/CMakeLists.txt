cmake_minimum_required(VERSION 3.10)

set(SOURCES src/glDebug.h)

add_library(Utilities INTERFACE)
add_library(Glitter::Utilities ALIAS Utilities)
target_include_directories(Utilities INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src)

