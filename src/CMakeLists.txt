cmake_minimum_required(VERSION 3.10)

# Project name
project(ezsrv)

# Options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Paths
set(EXECUTABLE_OUTPUT_PATH bin)
set(LIBRARY_OUTPUT_PATH lib)

# Sub directories inclusion
add_subdirectory(config)
add_subdirectory(log)
add_subdirectory(data)
add_subdirectory(app)
add_subdirectory(main)
add_subdirectory(lib)

# Final executable
add_executable(${PROJECT_NAME} $<TARGET_OBJECTS:ezsrv_main>)
target_link_libraries(${PROJECT_NAME} ezsrv_config ezsrv_log ezsrv_data)

# Install
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
