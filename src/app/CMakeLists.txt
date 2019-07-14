cmake_minimum_required(VERSION 3.10)

# Project Name
project(ezsrv_app)

# Files
set(SOURCE_FILES)

# Targets
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

# Install destination
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
