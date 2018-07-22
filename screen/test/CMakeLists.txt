cmake_minimum_required(VERSION 3.10)

set(SOURCES AllTests.cpp ScreenTests.cpp)

add_library(ScreenTests ${SOURCES})
target_link_libraries(ScreenTests PRIVATE Glitter::Screen Catch2::Catch2)


