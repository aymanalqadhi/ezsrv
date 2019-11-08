#include "net/tcp_client.h"
#include "net/tcp_listener.h"

#include "boost/asio/ip/tcp.hpp"
#include "boost/asio/placeholders.hpp"
#include "boost/bind.hpp"
#include "boost/system/error_code.hpp"

using ezsrv::net::tcp_listener;

using boost::asio::ip::tcp;
using boost::asio::placeholders::error;
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

    auto client_ptr {std::make_shared<tcp_client>(
        tcp::socket {io_ctx_}, callbacks_)};

    acceptor_.async_accept(
        client_ptr->socket(),
        boost::bind(&tcp_listener::handle_accept, this, client_ptr, error));
}

void tcp_listener::handle_accept(std::shared_ptr<tcp_client> client,
                                 const error_code &          err) {
    if (err) {
        logger_.error("{}", err.message());
        accept_next();
        return;
    }

    accept_cb_(std::move(client));
    accept_next();
}
