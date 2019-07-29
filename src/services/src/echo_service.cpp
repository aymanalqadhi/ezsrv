#include "services/echo_service.h"

#include <chrono>
#include <thread>

using ezsrv::services::echo_service;

bool echo_service::initialize() {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return true;
}

const std::string &echo_service::echo(const std::string &str) {
    return str;
}
