
set(SOURCES
        WindowTests.cpp
        )
add_executable(GraphicsTests AllTests.cpp ${SOURCES})
target_link_libraries(GraphicsTests PUBLIC
        Catch2::Catch2
        Graphics
        ${OPENGL_LIBRARIES}
        )