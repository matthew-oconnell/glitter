cmake_minimum_required(VERSION 3.10)

set(SOURCES src/Sound.h src/Sound.cpp)

add_library(Sound STATIC ${SOURCES})
add_library(Glitter::Sound ALIAS Utilities)
target_include_directories(Sound PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

