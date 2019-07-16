#include "ezsrv_app.h"

#include "config/app_config.h"
#include "log/logger.h"

using ezsrv::app::ezsrv_app;

void ezsrv_app::configure() {
    logger_.info("Configuring application {}", config_.executable);
}

void ezsrv_app::run() {
    logger_.info("Running application");
    server_.run();
}
