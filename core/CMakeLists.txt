cmake_minimum_required(VERSION 3.10)

set(SOURCES
        src/Engine.cpp
        src/Engine.h
        src/File.h
        src/FPSCounter.h
        src/Game.h
        src/Game.cpp
        src/GLFWInput.cpp
        src/GLFWInput.h
        src/GlewContext.cpp src/GlewContext.h
        src/ModelDatabase.cpp src/ModelDatabase.cpp
        src/Window.cpp src/Window.h
        )

add_library(Engine STATIC ${SOURCES})
add_library(Glitter::Engine ALIAS Engine)
target_link_libraries(Engine PUBLIC glfw glew_s
        glm::glm
        Glitter::Player
        Glitter::Screen
        Glitter::Audio
        Glitter::Text
        LodePNG::LodePNG
        )
target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../third-party/glew-2.1.0/include)
target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

