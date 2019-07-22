#ifndef EZSRV_NET_TCP_LISTENER_H
#define EZSRV_NET_TCP_LISTENER_H

#include "config/app_config.h"
#include "log/logger.h"
#include "net/tcp_client.h"

#include "boost/asio/io_context.hpp"
#include "boost/asio/ip/tcp.hpp"
#include "boost/system/error_code.hpp"

#include <atomic>

namespace ezsrv::net {
    namespace details {
        using ezsrv::config::app_config;
        using ezsrv::log::logger;

        using boost::asio::io_context;
        using boost::asio::ip::tcp;
        using boost::system::error_code;

        using tcp_client_ptr = std::shared_ptr<tcp_client>;

        inline auto get_endpoint(const app_config &conf) {
            return tcp::endpoint {conf.ipv6_only ? tcp::v6() : tcp::v4(),
                                  conf.listen_port};
        }

        class tcp_listener {
          public:
            tcp_listener(io_context &            io_ctx,
                         const client_callbacks &callbacks,
                         const app_config &      config,
                         logger &                logger)
                : callbacks_ {callbacks},
                  config_ {config},
                  logger_ {logger},
                  acceptor_ {io_ctx, get_endpoint(config)},
                  is_running_ {false} {}

            void start();
            void stop();

            inline tcp::acceptor &acceptor() noexcept { return acceptor_; }

          private:
            void accept_next();
            void handle_accept(tcp_client_ptr client, const error_code &err);

            const client_callbacks &callbacks_;
            const app_config &      config_;
            logger &                logger_;

            tcp::acceptor    acceptor_;
            std::atomic_bool is_running_;
        };
    } // namespace details

    using details::tcp_listener;
} // namespace ezsrv::net

#endif /* end of include guard: EZSRV_NET_TCP_LISTENER_H */
