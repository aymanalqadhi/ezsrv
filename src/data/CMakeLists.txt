cmake_minimum_required(VERSION 3.10)

# Project Name
project(ezsrv_data)

# Files
set(SOURCE_FILES)
set(HEADER_FILES)

# Targets
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})

# Install destination
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
