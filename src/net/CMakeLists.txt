cmake_minimum_required(VERSION 3.10)

# Project Name
project(ezsrv_net)

# Files
set(SOURCE_FILES src/server.cpp src/tcp_listener.cpp src/tcp_client.cpp
                 src/client_state_machine.cpp src/message_header.cpp)

# Targets
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} ezsrv_config ezsrv_log)

# Install destination
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
