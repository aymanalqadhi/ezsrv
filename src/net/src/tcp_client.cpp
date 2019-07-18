#include "net/buffer.h"
#include "net/tcp_client.h"

#include "boost/asio/buffer.hpp"
#include "boost/asio/placeholders.hpp"
#include "boost/asio/read.hpp"

using ezsrv::net::tcp_client;
using ezsrv::net::header_size;

using boost::asio::placeholders::bytes_transferred;
using boost::asio::placeholders::error;

void tcp_client::start() {
    using namespace std::placeholders;

    if (state() == client_state::idle) {
        state(client_state::reading_header);
        tmp_buffer_.reserve(header_size);

        boost::asio::async_read(
            sock_, boost::asio::buffer(tmp_buffer_),
            boost::asio::transfer_exactly(header_size),
            std::bind(&tcp_client::handle_read, shared_from_this(), _1,
                      tmp_buffer_, _2));
    } else {
        throw std::runtime_error {"Client was already started!"};
    }
}

void tcp_client::on_reading_header(std::string_view msg) {
}

void tcp_client::on_reading_body(std::string_view msg) {
}

void tcp_client::on_error(const error_code &err) {
}
