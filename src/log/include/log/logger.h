#ifndef EZSRV_LOG_LOGGER_H
#define EZSRV_LOG_LOGGER_H

#include "config/app_config.h"

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

#include <iostream>

namespace ezsrv::log {
    class logger {
        using stdout_color_sink_mt = spdlog::sinks::stdout_color_sink_mt;
        using logger_ptr           = std::shared_ptr<spdlog::logger>;

      public:
        logger(const ezsrv::config::app_config &conf)
            : console_sink_(std::make_shared<stdout_color_sink_mt>()),
              logger_(std::make_shared<spdlog::logger>(conf.executable,
                                                       console_sink_)) {
            logger_->set_level(
                static_cast<spdlog::level::level_enum>(conf.verbosity));
        }

        template <typename... TArg>
        void trace(const char *fmt, TArg... args) {
            logger_->trace(fmt, args...);
        }

        template <typename... TArg>
        void debug(const char *fmt, TArg... args) {
            logger_->debug(fmt, args...);
        }

        template <typename... TArg>
        void info(const char *fmt, TArg... args) {
            logger_->info(fmt, args...);
        }

        template <typename... TArg>
        void warn(const char *fmt, TArg... args) {
            logger_->warn(fmt, args...);
        }

        template <typename... TArg>
        void error(const char *fmt, TArg... args) {
            logger_->error(fmt, args...);
        }

        template <typename... TArg>
        void fatal(const char *fmt, TArg... args) {
            logger_->critical(fmt, args...);
        }

      private:
        std::shared_ptr<stdout_color_sink_mt> console_sink_;
        logger_ptr                            logger_;
    };
} // namespace ezsrv::log

#endif /* EZSRV_LOG_LOGGER_H */
