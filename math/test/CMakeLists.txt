cmake_minimum_required(VERSION 3.10)

set(SOURCES Vector2dTests.cpp AllTests.cpp Vector3dTests.cpp AABBTests.cpp)

add_executable(MathTests ${SOURCES})
target_link_libraries(MathTests PRIVATE Glitter::Math Catch2::Catch2)


