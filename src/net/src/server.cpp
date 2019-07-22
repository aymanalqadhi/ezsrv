#include "net/server.h"
#include "net/tcp_client.h"

#include "boost/asio/io_context.hpp"
#include "boost/system/error_code.hpp"

using tcp_client_ptr = std::shared_ptr<ezsrv::net::tcp_client>;
using ezsrv::net::server;

using boost::asio::io_context;
using boost::system::error_code;

void server::run() {
    logger_.info("Starting Listener");
    listener_.start();
    logger_.info("Listener started on {}:{}",
                 listener_.acceptor().local_endpoint().address().to_string(),
                 config_.listen_port);

    logger_.debug("Starting event loop");

    boost::asio::io_context::work work {io_ctx_};
    io_ctx_.run();
}

void server::on_message_read(const tcp_client_ptr &client,
                             std::string_view      msg) {
    logger_.info("Got message from {}: {}", client->address(), msg);
}

void server::on_error(const tcp_client_ptr &client, const error_code &err) {
    logger_.info("Got error from {}: {}", client->address(), err.message());
}

void server::on_close(const tcp_client_ptr &client) {
    logger_.info("Connection to {}:{} was closed", client->endpoint_string());
}
