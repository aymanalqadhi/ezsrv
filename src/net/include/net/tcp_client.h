#ifndef EZSRV_NET_TCP_CLIENT_H
#define EZSRV_NET_TCP_CLIENT_H

#include "net/client_state_machine.h"
#include "net/reading_context.h"
#include "net/message.h"

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
        class tcp_client;

        using ezsrv::net::basic_buffer;
        using ezsrv::net::reading_context;
        using tcp_client_ptr = std::shared_ptr<tcp_client>;

        using boost::asio::ip::tcp;
        using boost::system::error_code;

        struct client_callbacks {
            std::function<void(const tcp_client_ptr &, request_message)>
                request_cb;
            std::function<void(const tcp_client_ptr &, const error_code &)>
                error_cb;

            std::function<void(const tcp_client_ptr &)> close_cb;
        };

        class tcp_client final
            : public ezsrv::net::client_state_machine,
              public std::enable_shared_from_this<tcp_client> {
          public:
            tcp_client(tcp::socket &&sock, const client_callbacks &callbacks)
                : sock_ {std::move(sock)}, callbacks_ {callbacks} {
                static std::atomic_uint32_t next_id = 0;

                id_ = next_id++;
            }

            void start();
            void close();

            void enqueue_send(std::shared_ptr<std::string> msg);
            void send_enqueued();

            inline std::uint32_t id() const noexcept { return id_; }
            inline tcp::socket & socket() { return sock_; }
            inline bool          is_connected() const noexcept {
                return sock_.is_open();
            }

            inline std::string address() const {
                return sock_.remote_endpoint().address().to_string();
            }
            inline std::uint16_t port() const {
                return sock_.remote_endpoint().port();
            }

          private:
            void on_reading_header(std::string_view msg) final override;
            void on_reading_body(std::string_view msg) final override;
            void on_error(const error_code &err) final override;

            void handle_send(std::size_t sent, const error_code &err);
            void read_next(std::size_t bytes);

          private:
            basic_buffer    tmp_buffer_;
            reading_context reading_ctx_;
            tcp::socket     sock_;

            std::vector<std::shared_ptr<std::string>> send_queue_;
            const client_callbacks &                  callbacks_;

            std::uint32_t id_;
        };
    } // namespace details
    using details::tcp_client;
} // namespace ezsrv::net

#endif /* EZSRV_NET_TCP_CLIENT_H */
