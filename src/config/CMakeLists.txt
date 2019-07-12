cmake_minimum_required(VERSION 3.10)

# Project Name
project(ezsrv_config)

# Files
set(SOURCE_FILES src/app_config.cpp)

# Targets
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC include)

# Definitions
add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)

# Dependencies
find_package(Boost COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

# Install destination
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
