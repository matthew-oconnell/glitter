cmake_minimum_required(VERSION 3.10)

set(SOURCES Text.h Text.cpp)

add_library(Text STATIC ${SOURCES})
add_library(Glitter::Text ALIAS Text)
target_include_directories(Text PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Text PUBLIC freetype::freetype Glitter::Graphics)
target_include_directories(Text PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../third-party/glew-2.1.0/include)

