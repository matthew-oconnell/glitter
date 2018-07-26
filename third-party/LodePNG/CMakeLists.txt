add_library(LodePNG lodepng.cpp)
add_library(LodePNG::LodePNG ALIAS LodePNG)
target_include_directories(LodePNG INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})