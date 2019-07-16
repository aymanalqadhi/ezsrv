#ifndef EZSRV_NET_SERVER_H
#define EZSRV_NET_SERVER_H

#include "config/app_config.h"
#include "log/logger.h"
#include "net/tcp_listener.h"

#include "boost/asio/io_context.hpp"

#include <atomic>

namespace ezsrv::net {
    namespace details {
        using ezsrv::config::app_config;
        using ezsrv::log::logger;
        using ezsrv::net::tcp_listener;

        using boost::asio::io_context;

        class server {
          public:
            server(const app_config &config, logger &logger)
                : listener_ {io_ctx_, config, logger},
                  config_ {config},
                  logger_ {logger},
                  is_running_ {false} {}

            void run();

          private:
            io_context io_ctx_;

            tcp_listener      listener_;
            const app_config &config_;
            logger &          logger_;
            std::atomic_bool  is_running_;
        };
    } // namespace details

    using details::server;
} // namespace ezsrv::net

#endif /* EZSRV_NET_SERVER_H */
