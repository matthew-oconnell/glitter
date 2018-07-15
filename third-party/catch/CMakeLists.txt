add_library(Catch2 INTERFACE)
add_library(Catch2::Catch2 ALIAS Catch2)
target_include_directories(Catch2 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})