cmake_minimum_required(VERSION 3.10)

# Project Name
project(ezsrv_commands)

# Files
set(SOURCE_FILES src/echo_command.cpp src/system_commands.cpp)

# Targets
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME})

# Install destination
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
