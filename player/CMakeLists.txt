cmake_minimum_required(VERSION 3.10)

set(SOURCES src/First.cpp src/First.h src/Input.h)

add_library(Player STATIC ${SOURCES})
add_library(Glitter::Player ALIAS Player)
target_include_directories(Player PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(Player PUBLIC Glitter::Math)


add_subdirectory(test)
