cmake_minimum_required(VERSION 3.10)

set(SOURCES src/Window.h src/Window.cpp)

add_library(Graphics STATIC ${SOURCES})
add_library(Glitter::Graphics ALIAS Graphics)
target_link_libraries(Graphics PUBLIC glfw)
target_include_directories(Graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(test)
