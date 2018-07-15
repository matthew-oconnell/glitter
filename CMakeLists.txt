cmake_minimum_required(VERSION 3.10)
project(glitter)
set(CMAKE_CXX_STANDARD 17)
find_package(OpenGL REQUIRED)

add_subdirectory(third-party/catch)
add_subdirectory(third-party/glfw-3.2.1)
add_subdirectory(third-party/glew-2.1.0/build/cmake)

add_subdirectory(graphics)



add_executable(Game game.cpp game.cpp)
target_include_directories(Game PRIVATE ${GLEW_INCLUDE_DIRS})
target_link_libraries(Game PRIVATE Glitter::Graphics ${OPENGL_LIBRARIES})
