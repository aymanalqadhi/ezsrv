#ifndef EZSRV_NET_SERVER_H
#define EZSRV_NET_SERVER_H

#include "config/app_config.h"
#include "log/logger.h"

#include "net/tcp_client.h"
#include "net/tcp_listener.h"

#include "boost/asio/io_context.hpp"
#include "boost/system/error_code.hpp"

#include <atomic>
#include <string_view>
#include <vector>

namespace ezsrv::net {
    namespace details {
        using namespace std::placeholders;

        using ezsrv::config::app_config;
        using ezsrv::log::logger;
        using ezsrv::net::tcp_listener;
        using tcp_client_ptr = std::shared_ptr<tcp_client>;

        using boost::asio::io_context;
        using boost::system::error_code;

        class server {
          public:
            server(const app_config &config, logger &logger)
                : callbacks_ {std::bind(&server::on_message_read, this, _1, _2),
                              std::bind(&server::on_error, this, _1, _2),
                              std::bind(&server::on_close, this, _1)},
                  listener_ {io_ctx_, callbacks_, config, logger},
                  config_ {config},
                  logger_ {logger},
                  is_running_ {false} {
                listener_.set_accept_cb(
                    std::bind(&server::on_client_accepted, this, _1));
            }

            void run();

          private:
            void on_client_accepted(tcp_client_ptr client);
            void on_message_read(const tcp_client_ptr &client,
                                 std::string_view      msg);
            void on_error(const tcp_client_ptr &client, const error_code &err);
            void on_close(const tcp_client_ptr &client);

          private:
            io_context io_ctx_;

            client_callbacks  callbacks_;
            tcp_listener      listener_;
            const app_config &config_;
            logger &          logger_;

            std::atomic_bool            is_running_;

            // TODO:
            // Use hashtables instead of vector
            std::vector<tcp_client_ptr> clients_;
        };
    } // namespace details

    using details::server;
} // namespace ezsrv::net

#endif /* EZSRV_NET_SERVER_H */
