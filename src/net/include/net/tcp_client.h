#ifndef EZSRV_NET_TCP_CLIENT_H
#define EZSRV_NET_TCP_CLIENT_H

#include "data/models/client.h"
#include "net/client_state_machine.h"
#include "net/reading_context.h"

#include "boost/asio/ip/tcp.hpp"
#include "boost/asio/streambuf.hpp"
#include "boost/system/error_code.hpp"

#include <functional>
#include <memory>
#include <string_view>
#include <vector>

namespace ezsrv::net {
    constexpr auto auth_message_length = 0x40;
    namespace details {
        using boost::asio::ip::tcp;
        using boost::system::error_code;
        using ezsrv::net::reading_context;

        class tcp_client;

        struct client_callbacks {
            std::function<bool(std::shared_ptr<tcp_client>,
                               std::string_view,
                               std::string_view)>
                auth_cb;
            std::function<void(std::shared_ptr<tcp_client>, std::string_view)>
                message_read_cb;
            std::function<void(std::shared_ptr<tcp_client>, const error_code &)>
                error_cb;
            std::function<void(std::shared_ptr<tcp_client>, const error_code &)>
                close_cb;
        };

        class tcp_client final
            : public ezsrv::data::models::client,
              public ezsrv::net::client_state_machine,
              public std::enable_shared_from_this<tcp_client> {
          public:
            tcp_client(tcp::socket &&sock, const client_callbacks &callbacks)
                : sock_ {std::move(sock)},
                  callbacks_ {callbacks} {}

            void start();

            void on_reading_header(std::string_view msg) final override;
            void on_reading_body(std::string_view msg) final override;
            void on_error(const error_code &err) final override;

            void enqueue_send(std::shared_ptr<std::string> msg);
            void send_enqueued();

            void handle_send(std::size_t sent, const error_code& err);

            tcp::socket &socket() { return sock_; }

          private:
            std::string             tmp_buffer_;
            tcp::socket             sock_;
            reading_context         reading_ctx_;

            std::vector<std::shared_ptr<std::string>> send_queue_;
            const client_callbacks &callbacks_;
        };
    } // namespace details
    using details::tcp_client;
} // namespace ezsrv::net

#endif /* EZSRV_NET_TCP_CLIENT_H */
