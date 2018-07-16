cmake_minimum_required(VERSION 3.10)

set(SOURCES src/Engine.h src/Engine.cpp src/Input.cpp src/Input.h)

add_library(Core STATIC ${SOURCES})
add_library(Glitter::Core ALIAS Core)
target_link_libraries(Core PUBLIC glfw glew_s)
target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../third-party/glew-2.1.0/include)
target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

