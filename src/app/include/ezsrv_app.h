#ifndef EZSRV_APP_EZSRV_APP_H
#define EZSRV_APP_EZSRV_APP_H

#include "iapplication.h"

#include "config/app_config.h"
#include "log/logger.h"

namespace ezsrv::app {
    namespace details {
        using ezsrv::config::app_config;
        using ezsrv::log::logger;

        class ezsrv_app final : public iapplication {
          public:
            explicit ezsrv_app(app_config &config, logger &logger)
                : config_(config), logger_(logger) {}

            void configure() override final;
            void run() override final;

          private:
            const app_config &config_;
            logger &          logger_;
        };
    } // namespace details

    using details::ezsrv_app;
} // namespace ezsrv::app

#endif /* EZSRV_APP_EZSRV_APP_H */
