cmake_minimum_required(VERSION 3.10)
project(glitter)
set(CMAKE_CXX_STANDARD 17)
find_package(OpenGL REQUIRED)
#set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")


add_subdirectory(third-party/catch)
add_subdirectory(third-party/glfw-3.2.1)
add_subdirectory(third-party/glew-2.1.0/build/cmake)
add_subdirectory(third-party/LodePNG)
add_subdirectory(third-party/freetype-2.9.1)
add_subdirectory(third-party/glm/glm)
add_subdirectory(third-party/soloud)

add_executable(UnitTests AllTests.cpp)
target_link_libraries(UnitTests PRIVATE Catch2::Catch2)

add_subdirectory(player)
add_subdirectory(math)
add_subdirectory(camera)
add_subdirectory(graphics)
add_subdirectory(text)
add_subdirectory(audio)
add_subdirectory(core)

add_executable(Game game.cpp)
target_include_directories(Game PRIVATE ${GLEW_INCLUDE_DIRS} )
target_link_libraries(Game PRIVATE
        Glitter::Engine
        Glitter::Graphics
        Glitter::Text
        ${OPENGL_LIBRARIES})


