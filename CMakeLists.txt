# # Minimum CMake version required
# cmake_minimum_required(VERSION 3.30.3)

# # Project name and version
# project(ChessEngine VERSION 1.0)

# # Set the C++ standard
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED True)

# # Include directories
# include_directories(${PROJECT_SOURCE_DIR}/include)

# # Path to SFML library
# set(SFML_DIR "${PROJECT_SOURCE_DIR}/lib/cmake/SFML")

# # Find and link SFML components
# find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

# # Check if SFML was found successfully
# if(SFML_FOUND)
#     message(STATUS "SFML found in ${SFML_DIR}")
# else()
#     message(FATAL_ERROR "SFML not found. Make sure the SFML_DIR is set correctly.")
# endif()

# # Source files
# set(SOURCES
#     src/main.cpp
#     src/gui.cpp
#     src/board.cpp
#     src/movegen.cpp
#     src/evaluation.cpp
#     src/search.cpp
# )

# # Add executable target for the project
# add_executable(ChessEngine ${SOURCES})

# # Link SFML libraries to the ChessEngine executable
# target_link_libraries(ChessEngine sfml-graphics sfml-window sfml-system)

# # Set output directories for the built executable and DLLs
# set_target_properties(ChessEngine PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
#     LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
#     ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
# )

# # Copy DLLs after the build (Windows specific)
# if(WIN32)
#     add_custom_command(TARGET ChessEngine POST_BUILD
#         COMMAND ${CMAKE_COMMAND} -E copy_if_different
#         "${SFML_DIR}/../../../bin/sfml-graphics-2.dll"
#         "${SFML_DIR}/../../../bin/sfml-window-2.dll"
#         "${SFML_DIR}/../../../bin/sfml-system-2.dll"
#         $<TARGET_FILE_DIR:ChessEngine>
#     )
# endif()

# # Post-build success message
# message(STATUS "ChessEngine project built successfully.")

#Alternate code -

cmake_minimum_required(VERSION 3.28)

# Project name and language
project(SmartGambitChessEngine LANGUAGES CXX)

# Set output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Option to build shared libraries
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Fetch SFML library using FetchContent
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Add the executable target
add_executable(ChessEngine
    src/main.cpp
    src/gui.cpp
    src/board.cpp
    src/movegen.cpp
    src/evaluation.cpp
    src/search.cpp
)

# Link SFML libraries to the executable
target_link_libraries(ChessEngine PRIVATE sfml-graphics sfml-window sfml-system)

# Set C++ standard
target_compile_features(ChessEngine PRIVATE cxx_std_17)

# Copy DLLs for Windows
if(WIN32)
    add_custom_command(
        TARGET ChessEngine
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:ChessEngine>
        VERBATIM)
endif()
