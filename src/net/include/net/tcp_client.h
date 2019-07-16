#ifndef EZSRV_NET_TCP_CLIENT_H
#define EZSRV_NET_TCP_CLIENT_H

#include "data/models/client.h"
#include "net/client_state_machine.h"
#include "net/reading_context.h"

#include "boost/asio/ip/tcp.hpp"
#include "boost/asio/streambuf.hpp"
#include "boost/system/error_code.hpp"

namespace ezsrv::net {
    constexpr auto auth_message_length = 0x40;
    namespace details {
        using boost::asio::ip::tcp;
        using boost::system::error_code;
        using ezsrv::net::reading_context;

        class tcp_client final
            : public ezsrv::data::models::client,
              public ezsrv::net::client_state_machine,
              public std::enable_shared_from_this<tcp_client> {
          public:
            tcp_client(tcp::socket &&sock)
                : sock_ {std::forward<tcp::socket>(sock)} {}

            void start();

            void on_authing(std::string_view msg) final override;
            void on_reading_header(std::string_view msg) final override;
            void on_reading_body(std::string_view msg) final override;
            void on_error(const error_code &err) final override;

            tcp::socket &socket() { return sock_; }

          private:
            std::string     tmp_buffer_;
            tcp::socket     sock_;
            reading_context reading_ctx_;
        };
    } // namespace details
    using details::tcp_client;
} // namespace ezsrv::net

#endif /* EZSRV_NET_TCP_CLIENT_H */
