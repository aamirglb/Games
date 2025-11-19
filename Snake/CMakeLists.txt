# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

project(BouncingBall VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

# Specify the GDAL installation directory
set(RAYLIB_DIR "C:/sw/raylib/build-msvc/raylib")

# Include GDAL headers
include_directories("${RAYLIB_DIR}/include")

# Link GDAL libraries
link_directories("${RAYLIB_DIR}/Debug")

set(SOURCES
    main.cpp
    # Add all your .cpp files here
)

# Add the executable
add_executable(snake ${SOURCES})

# Link GDAL library
target_link_libraries(snake raylib winmm.lib)

