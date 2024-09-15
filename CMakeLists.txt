# Minimum CMake version required
cmake_minimum_required(VERSION 3.30)

# Project name and version
project(ChessEngine VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Find and link SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Source files
set(SOURCES
    src/main.cpp
    src/board.cpp
    src/movegen.cpp
    src/gui.cpp
    src/search.cpp
)

# Add executable
add_executable(ChessEngine ${SOURCES})

# Link SFML libraries to the executable
target_link_libraries(ChessEngine sfml-graphics sfml-window sfml-system)
