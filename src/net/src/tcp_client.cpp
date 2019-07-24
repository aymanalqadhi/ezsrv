#include "net/buffer.h"
#include "net/message_header.h"
#include "net/tcp_client.h"

#include "boost/asio/buffer.hpp"
#include "boost/asio/placeholders.hpp"
#include "boost/asio/read.hpp"

#include "boost/bind.hpp"
#include "boost/system/error_code.hpp"

#include <array>
#include <cstdio>
#include <cstring>

using ezsrv::net::header_size;
using ezsrv::net::request_message_header;
using ezsrv::net::tcp_client;

using boost::asio::transfer_exactly;
using boost::asio::placeholders::bytes_transferred;
using boost::asio::placeholders::error;
using boost::system::error_code;

void tcp_client::read_next(std::size_t bytes) {
    if (tmp_buffer_.length() != bytes) {
        tmp_buffer_.allocate(bytes);
    }

    boost::asio::async_read(
        sock_, boost::asio::buffer(tmp_buffer_.data(), bytes),
        transfer_exactly(bytes),
        boost::bind(&tcp_client::handle_read, shared_from_this(),
                    bytes_transferred,
                    std::string_view {tmp_buffer_.data(), bytes}, error));
}

void tcp_client::start() {
    if (state() == client_state::idle) {
        state(client_state::reading_header);
        read_next(header_size);
    } else {
        throw std::runtime_error {"Client was already started!"};
    }
}

void tcp_client::close() {
    state(client_state::closing);
    sock_.close();
}

void tcp_client::on_reading_header(std::string_view msg) {
    if (msg.length() != ezsrv::net::header_size) {
        throw std::runtime_error {"Got invalid header length!"};
    }

    std::array<std::uint8_t, ezsrv::net::header_size> buff {};
    std::memcpy(buff.data(), tmp_buffer_.data(), ezsrv::net::header_size);

    request_message_header header {};
    request_message_header::decode(buff, header);
    reading_ctx_.set_header(std::move(header));

    state(client_state::reading_body);
    read_next(reading_ctx_.next_chunk_size());
}

void tcp_client::on_reading_body(std::string_view msg) {
    reading_ctx_.add_body_data(msg);

    if (reading_ctx_.is_full()) {
        callbacks_.message_read_cb(shared_from_this(), reading_ctx_.body());
        state(client_state::reading_header);
        read_next(header_size);
    } else {
        read_next(reading_ctx_.next_chunk_size());
    }
}

inline void tcp_client::on_error(const error_code &err) {
    if (err == boost::asio::error::eof) {
        callbacks_.close_cb(shared_from_this());
    } else {
        callbacks_.error_cb(shared_from_this(), err);
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

void tcp_client::handle_send([[maybe_unused]] std::size_t sent,
                             const error_code &           err) {
    if (err) {
        callbacks_.error_cb(shared_from_this(), err);
    }
}
