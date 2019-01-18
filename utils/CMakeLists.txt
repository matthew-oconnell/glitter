cmake_minimum_required(VERSION 3.10)

set(SOURCES src/glDebug.h src/FPSCounter.h src/ResourceManager.h src/ResourceManager.cpp)

add_library(Utilities ${SOURCES})
add_library(Glitter::Utilities ALIAS Utilities)
target_include_directories(Utilities PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(Utilities PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../third-party/glew-2.1.0/include)
target_link_libraries(Utilities PUBLIC
        glew_s
        LodePNG::LodePNG
        )

