#include "ezsrv_app.h"

#include "config/app_config.h"
#include "log/logger.h"

using ezsrv::app::ezsrv_app;

void ezsrv_app::configure(const app_config &config) {
    logger_.info("Configuring application");
}

[[noreturn]]
void ezsrv_app::run() {
    logger_.info("Running application");
}
