#include "ezsrv_app.h"

#include "config/app_config.h"
#include "log/logger.h"

using ezsrv::app::ezsrv_app;

void ezsrv_app::configure() {
    logger_.info("Configuring application {}", config_.executable);

    logger_.info("Initializng system services");
    if (!system_services_.initialize()) {
        throw std::runtime_error {"Could not initialize system services"};
    }
}

void ezsrv_app::run() {
    logger_.info("Running application");
    server_.run();
}
