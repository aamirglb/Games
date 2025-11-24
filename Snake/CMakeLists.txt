# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

project(SnakeGame VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

# Specify the raylib installation directory
set(RAYLIB_DIR "C:/sw/raylib/build-msvc/raylib")

# Include raylib headers
include_directories("${RAYLIB_DIR}/include")

# Link raylib libraries
link_directories("${RAYLIB_DIR}/Debug")

set(SOURCES
    main.cpp
    # Add all your .cpp files here
)

set(HEADERS
    board.h
    fixq.h
    food.h
    snake.h
    vec.h
)

# Add the executable
add_executable(snake ${SOURCES} ${HEADERS})

# create Visual Studio filter folders
source_group("include" FILES ${HEADERS})
source_group("source" FILES ${SOURCES})

# Link raylib and Windows Multimedia API library
target_link_libraries(snake raylib winmm.lib)

