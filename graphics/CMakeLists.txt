cmake_minimum_required(VERSION 3.10)

set(SOURCES
        src/Texture.cpp src/Texture.h
        src/Shader.cpp src/Shader.h src/Model.h)

add_library(Graphics STATIC ${SOURCES})
add_library(Glitter::Graphics ALIAS Graphics)
target_link_libraries(Graphics
        PUBLIC glfw glew_s
        Glitter::Math
        Glitter::Screen
        Glitter::Engine
        glm::glm
        )
target_include_directories(Graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../third-party/glew-2.1.0/include)
target_include_directories(Graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

