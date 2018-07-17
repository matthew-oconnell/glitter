cmake_minimum_required(VERSION 3.10)

set(SOURCES src/Map.h src/Map.cpp)

add_library(World STATIC ${SOURCES})
add_library(Glitter::World ALIAS World)
target_include_directories(World PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(World PUBLIC Glitter::Math Glitter::Graphics)
