cmake_minimum_required(VERSION 3.10)

set(SOURCES src/File.h src/File.cpp)

add_library(Utilities STATIC ${SOURCES})
add_library(Glitter::Utilities ALIAS Utilities)
target_include_directories(Utilities PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

