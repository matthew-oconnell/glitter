cmake_minimum_required(VERSION 3.10)

set(SOURCES src/Screen.h src/Screen.cpp)

add_library(Screen STATIC ${SOURCES})
add_library(Glitter::Screen ALIAS Screen)
target_include_directories(Screen PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(Screen PUBLIC Glitter::Math)


add_subdirectory(test)
