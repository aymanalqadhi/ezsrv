#include "net/buffer.h"
#include "net/tcp_client.h"

#include "boost/asio/buffer.hpp"
#include "boost/asio/placeholders.hpp"
#include "boost/asio/read.hpp"

using ezsrv::net::auth_message_length;
using ezsrv::net::tcp_client;

using boost::asio::placeholders::bytes_transferred;
using boost::asio::placeholders::error;

void tcp_client::start() {
}

void tcp_client::on_authing(std::string_view msg) {
}

void tcp_client::on_reading_header(std::string_view msg) {
}

void tcp_client::on_reading_body(std::string_view msg) {
}

void tcp_client::on_error(const error_code &err) {
}
