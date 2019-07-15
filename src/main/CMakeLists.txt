cmake_minimum_required(VERSION 3.10)

# Project Name
project(ezsrv_main)

# Files
set(SOURCE_FILES src/main.cpp)
set(HEADER_FILE)

# Targets
add_library(${PROJECT_NAME} OBJECT ${SOURCE_FILES} ${HEADER_FILE})
target_link_libraries(${PROJECT_NAME} ezsrv_config ezsrv_app)

# Install destination
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
