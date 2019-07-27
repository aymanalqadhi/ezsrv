#include "commands/system_commands.h"

#include "net/message.h"
#include "net/server.h"
#include "net/tcp_client.h"

#include "boost/asio/io_context.hpp"
#include "boost/system/error_code.hpp"

#include <type_traits>

using ezsrv::commands::system_command_error;
using ezsrv::commands::system_commands;

using ezsrv::net::response_message;
using ezsrv::net::server;

using boost::asio::io_context;
using boost::system::error_code;

using tcp_client_ptr = std::shared_ptr<ezsrv::net::tcp_client>;

void server::run() {
    logger_.info("Starting Listener");
    listener_.start();
    logger_.info("Listener started on {}", listener_.endpoint_string());

    logger_.debug("Starting event loop");
    boost::asio::io_context::work work {io_ctx_};
    io_ctx_.run();
}

void server::on_client_accepted(tcp_client_ptr client) {
    logger_.info("Got a connection from {}:{}, and was given id #{}",
                 client->address(), client->port(), client->id());

    client->start();
    clients_.emplace(std::make_pair(client->id(), std::move(client)));
}

void server::on_request(const tcp_client_ptr &client, request_message req) {
    // TODO:
    // - Handle the rest of request types
    switch (req.header.type) {
    case message_type::system_command:
        handle_system_command(client, req);
        break;
    default:
        logger_.info("Got message from client #{}: {}", client->id(), req.body);
    }
}

void server::on_error(const tcp_client_ptr &client, const error_code &err) {
    logger_.info("Got an error from client #{} : {}", client->id(),
                 err.message());
    on_close(client);
}

void server::on_close(const tcp_client_ptr &client) {
    if (client->is_connected()) {
        client->close();
    }

    logger_.info("Connection to client #{} was closed", client->id());
    clients_.erase(client->id());
}
