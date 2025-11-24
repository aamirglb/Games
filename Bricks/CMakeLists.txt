# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

project(BricksGame VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

# Specify the SFML installation directory
set(SFML_DIR "C:/sw/SFML-3.0.2-vc17-x64")

# Include SFML headers
include_directories("${SFML_DIR}/include")

# Link SFML libraries
# link_directories("${SFML_DIR}/lib/release")
link_directories("${SFML_DIR}/lib")

set(SOURCES
    main.cpp
    # Add all your .cpp files here
)

# set(HEADERS
#     board.h
#     fixq.h
#     food.h
#     snake.h
#     vec.h
# )

# set(SFML_STATIC_LIBRARIES TRUE)

# Add the executable
add_executable(brick ${SOURCES} )

# create Visual Studio filter folders
# source_group("include" FILES ${HEADERS})
source_group("source" FILES ${SOURCES})

# target_compile_definitions(brick PRIVATE
#     SFML_STATIC
# )

# Link 
# target_link_libraries(brick PRIVATE 
#     sfml-system-s.lib
#     sfml-graphics-s.lib
#     sfml-window-s.lib
#     )
target_link_libraries(brick PRIVATE 
    sfml-system.lib
    sfml-window.lib
    sfml-graphics.lib
    )

if(MSVC)
    target_link_libraries(brick PRIVATE
        opengl32
        winmm
        )
endif()
