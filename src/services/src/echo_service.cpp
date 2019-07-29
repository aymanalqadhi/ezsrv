#include "services/echo_service.h"

#include <chrono>
#include <string>
#include <string_view>
#include <thread>

using ezsrv::services::echo_service;

bool echo_service::initialize() {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return true;
}

std::string echo_service::echo(const std::string_view &str) {
    return std::string {str};
}
