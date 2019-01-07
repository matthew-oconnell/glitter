cmake_minimum_required(VERSION 3.10)

set(SOURCES AllTests.cpp MockInput.cpp MockInput.h)

add_executable(PlayerTests ${SOURCES})
target_link_libraries(PlayerTests PRIVATE Glitter::Player Catch2::Catch2)
