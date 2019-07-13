cmake_minimum_required(VERSION 3.10)

# Project Name
project(ezsrv_log)

# Files
set(SOURCE_FILES src/logger.cpp)

# Targets
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ezsrv_config spdlog)
target_include_directories(${PROJECT_NAME} PUBLIC include)

# Install destination
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
