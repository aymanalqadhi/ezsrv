cmake_minimum_required(VERSION 3.10)

# Project Name
project(ezsrv_data)

# Files
set(SOURCE_FILES src/memory_clients_repository.cpp)

# Targets
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC include)

# Install destination
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
