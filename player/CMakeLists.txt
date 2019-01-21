cmake_minimum_required(VERSION 3.10)

set(SOURCES src/Ally.cpp src/Ally.h
        src/Bullet.h src/Bullet.cpp
        src/Input.h src/Player.h src/Enemy.cpp src/Enemy.h
        src/PowerUp.h
        src/Weapon.h)

add_library(Player STATIC ${SOURCES})
add_library(Glitter::Player ALIAS Player)
target_include_directories(Player PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(Player PUBLIC Glitter::Math Glitter::Graphics Glitter::Utilities)


add_subdirectory(test)
