cmake_minimum_required(VERSION 3.10)

set(SOURCES src/Vector2d.cpp src/Vector2d.h src/Vec3d.cpp src/Vec3d.h src/AABB.cpp src/AABB.h)

add_library(Math STATIC ${SOURCES})
add_library(Glitter::Math ALIAS Math)
target_include_directories(Math PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


add_subdirectory(test)

