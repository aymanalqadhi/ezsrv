#ifndef EZSRV_APP_EZSRV_APP_H
#define EZSRV_APP_EZSRV_APP_H

#include "iapplication.h"

#include "commands/system_commands.h"
#include "config/app_config.h"
#include "log/logger.h"
#include "net/server.h"

namespace ezsrv::app {
    namespace details {
        using ezsrv::commands::system_commands_container;
        using ezsrv::config::app_config;
        using ezsrv::log::logger;
        using ezsrv::net::server;

        class ezsrv_app final : public iapplication {
          public:
            ezsrv_app(app_config &               config,
                      logger &                   logger,
                      system_commands_container &system_commands)
                : config_ {config},
                  logger_ {logger},
                  server_ {config, logger, system_commands} {}

            void configure() override final;
            void run() override final;

          private:
            const app_config &config_;
            logger &          logger_;
            server            server_;
        };
    } // namespace details

    using details::ezsrv_app;
} // namespace ezsrv::app

#endif /* EZSRV_APP_EZSRV_APP_H */
