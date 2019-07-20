#include "net/buffer.h"
#include "net/tcp_client.h"

#include "boost/asio/buffer.hpp"
#include "boost/asio/placeholders.hpp"
#include "boost/asio/read.hpp"

#include "boost/bind.hpp"
#include "boost/system/error_code.hpp"

using ezsrv::net::header_size;
using ezsrv::net::tcp_client;

using boost::asio::placeholders::bytes_transferred;
using boost::asio::placeholders::error;
using boost::system::error_code;

void tcp_client::start() {
    using namespace std::placeholders;

    if (state() == client_state::idle) {
        state(client_state::reading_header);
        tmp_buffer_.reserve(header_size);

        boost::asio::async_read(
            sock_, boost::asio::buffer(tmp_buffer_),
            boost::asio::transfer_exactly(header_size),
            boost::bind(&tcp_client::handle_read, shared_from_this(),
                        bytes_transferred, tmp_buffer_, error));
    } else {
        throw std::runtime_error {"Client was already started!"};
    }
}

void tcp_client::on_reading_header(std::string_view msg) {
}

void tcp_client::on_reading_body(std::string_view msg) {
}

inline void tcp_client::on_error(const error_code &err) {
    if (err == boost::asio::error::eof) {
        callbacks_.close_cb(shared_from_this(), err);
    }
}

void tcp_client::enqueue_send(std::shared_ptr<std::string> msg) {
    send_queue_.emplace_back(std::move(msg));
}

void tcp_client::send_enqueued() {
    for (const auto &msg_ptr : send_queue_) {
        sock_.async_send(boost::asio::buffer(*msg_ptr),
                         boost::bind(&tcp_client::handle_send,
                                     shared_from_this(), bytes_transferred,
                                     error));
    }

    send_queue_.clear();
}

void tcp_client::handle_send(std::size_t sent, const error_code &err) {
    if (err) {
        callbacks_.error_cb(shared_from_this(), err);
    }
}
