#include "net/tcp_listener.h"

#include "boost/asio/ip/tcp.hpp"
#include "boost/system/error_code.hpp"

using ezsrv::net::tcp_listener;

using boost::asio::ip::tcp;
using boost::system::error_code;

void tcp_listener::start() {
    if (is_running_) {
        throw std::runtime_error {"Listener is already started"};
    }

    is_running_.store(true);
    accept_next();
}

void tcp_listener::stop() {
    if (!is_running_) {
        throw std::runtime_error {"Listener is not started"};
    }

    is_running_.store(false);
}

void tcp_listener::accept_next() {
    if (!is_running_) {
        return;
    }

    auto client_ptr = std::make_shared<tcp::socket>(acceptor_.get_io_context());
    acceptor_.async_accept(*client_ptr,
                           std::bind(&tcp_listener::handle_accept, this,
                                     client_ptr, std::placeholders::_1));
}

void tcp_listener::handle_accept(std::shared_ptr<tcp::socket> client,
                                 const error_code &           err) {
    if (err) {
        logger_.error("{}", err.message());
    }

    auto endpoint {client->remote_endpoint()};
    logger_.info("Got connection from {}:{}", endpoint.address().to_string(),
                 endpoint.port());

    client->send(boost::asio::buffer("Test message"));

    accept_next();
}
