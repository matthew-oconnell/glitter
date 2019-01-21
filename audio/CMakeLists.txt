cmake_minimum_required(VERSION 3.10)

set(SOURCES
        src/Audio.h
        src/SoLoudEngine.h
        src/SoLoudEngine.cpp
        )

add_library(Audio STATIC ${SOURCES})
add_library(Glitter::Audio ALIAS Audio)
target_include_directories(Audio PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(Audio PUBLIC soloud::soloud)


add_subdirectory(test)

