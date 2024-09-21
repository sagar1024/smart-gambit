# Minimum CMake version required
cmake_minimum_required(VERSION 3.30.3)

# Project name and version
project(ChessEngine VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Path to SFML library
set(SFML_DIR "${PROJECT_SOURCE_DIR}/lib/cmake/SFML")

# Find and link SFML components
find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

# Check if SFML was found successfully
if(SFML_FOUND)
    message(STATUS "SFML found in ${SFML_DIR}")
else()
    message(FATAL_ERROR "SFML not found. Make sure the SFML_DIR is set correctly.")
endif()

# Source files
set(SOURCES
    src/main.cpp
    src/gui.cpp
    src/board.cpp
    src/movegen.cpp
    src/evaluation.cpp
    src/search.cpp
)

# Add executable target for the project
add_executable(ChessEngine ${SOURCES})

# Link SFML libraries to the ChessEngine executable
target_link_libraries(ChessEngine sfml-graphics sfml-window sfml-system)

# Set output directories for the built executable and DLLs
set_target_properties(ChessEngine PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)

# Copy DLLs after the build (Windows specific)
if(WIN32)
    add_custom_command(TARGET ChessEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SFML_DIR}/../../../bin/sfml-graphics-2.dll"
        "${SFML_DIR}/../../../bin/sfml-window-2.dll"
        "${SFML_DIR}/../../../bin/sfml-system-2.dll"
        $<TARGET_FILE_DIR:ChessEngine>
    )
endif()

# Post-build success message
message(STATUS "ChessEngine project built successfully.")

