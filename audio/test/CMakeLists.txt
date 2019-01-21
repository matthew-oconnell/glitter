cmake_minimum_required(VERSION 3.10)

set(SOURCES AllTests.cpp AudioTests.cpp)

add_executable(AudioTests ${SOURCES})
target_link_libraries(AudioTests PRIVATE Glitter::Audio Catch2::Catch2)
