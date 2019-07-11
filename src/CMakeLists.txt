cmake_minimum_required(VERSION 3.10)

# Project name
project(ezsrv)

# Paths
set(EXECUTABLE_OUTPUT_PATH bin)
set(LIBRARY_OUTPUT_PATH lib)

# Include libraries
include_directories(lib)

# Sub directories inclusion
add_subdirectory(main)

# Final executable
add_executable(${PROJECT_NAME} $<TARGET_OBJECTS:ezsrv_main>)

# Install
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
