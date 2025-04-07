cmake_minimum_required(VERSION 3.15)
project(JustRight C)

# Set C standard and enable debug symbols
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

# Find SDL2 (adjust paths if needed)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Add executable
add_executable(Just-Right
    src/main.c
)

# Link SDL2
target_link_libraries(Just-Right ${SDL2_LIBRARIES})
