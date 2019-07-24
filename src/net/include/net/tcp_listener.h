#ifndef EZSRV_NET_TCP_LISTENER_H
#define EZSRV_NET_TCP_LISTENER_H

#include "config/app_config.h"
#include "log/logger.h"
#include "net/tcp_client.h"

#include "boost/asio/io_context.hpp"
#include "boost/asio/ip/tcp.hpp"
#include "boost/system/error_code.hpp"

#include "spdlog/fmt/fmt.h"

#include <atomic>

namespace ezsrv::net {
    namespace details {
        using ezsrv::config::app_config;
        using ezsrv::log::logger;

        using boost::asio::io_context;
        using boost::asio::ip::tcp;
        using boost::system::error_code;

        using tcp_client_ptr     = std::shared_ptr<tcp_client>;
        using client_accepted_cb = std::function<void(tcp_client_ptr)>;

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

            inline void set_accept_cb(client_accepted_cb callback) {
                accept_cb_ = std::move(callback);
            }

            inline tcp::acceptor &acceptor() noexcept { return acceptor_; }
            inline bool is_running() const noexcept { return is_running_; }

            inline std::string listen_address() const {
                return acceptor_.local_endpoint().address().to_string();
            }
            inline std::uint16_t listen_port() const {
                return acceptor_.local_endpoint().port();
            }
            inline std::string endpoint_string() const {
                return fmt::format("{}:{}", listen_address(), listen_port());
            }

          private:
            void accept_next();
            void handle_accept(tcp_client_ptr client, const error_code &err);

            const client_callbacks &callbacks_;
            const app_config &      config_;
            logger &                logger_;

            tcp::acceptor    acceptor_;
            std::atomic_bool is_running_;

            client_accepted_cb accept_cb_ {[]([[maybe_unused]] auto client) {}};
        };
    } // namespace details

    using details::tcp_listener;
} // namespace ezsrv::net

#endif /* end of include guard: EZSRV_NET_TCP_LISTENER_H */
