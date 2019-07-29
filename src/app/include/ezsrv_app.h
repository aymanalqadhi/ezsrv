#ifndef EZSRV_APP_EZSRV_APP_H
#define EZSRV_APP_EZSRV_APP_H

#include "iapplication.h"

#include "config/app_config.h"
#include "log/logger.h"

#include "services/system_services_container.h"
#include "commands/system_commands.h"

#include "net/server.h"

namespace ezsrv::app {
    namespace details {
        using ezsrv::config::app_config;
        using ezsrv::log::logger;
        using ezsrv::net::server;

        using ezsrv::commands::system_commands_container;
        using ezsrv::services::system_services_container;

        class ezsrv_app final : public iapplication {
          public:
            ezsrv_app(app_config &               config,
                      logger &                   logger,
                      system_commands_container &system_commands,
                      system_services_container &system_services)
                : config_ {config},
                  logger_ {logger},
                  server_ {config, logger, system_commands},
                  system_services_ {system_services} {}

            void configure() override final;
            void run() override final;

          private:
            const app_config &config_;
            logger &          logger_;
            server            server_;

            system_services_container &system_services_;
        };
    } // namespace details

    using details::ezsrv_app;
} // namespace ezsrv::app

#endif /* EZSRV_APP_EZSRV_APP_H */
