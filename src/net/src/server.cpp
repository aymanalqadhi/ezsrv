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
    // 1. Validate the command existance - Done
    // 2. Send real flags
    // 2. Handle the rest of request types

    switch (req.header.type) {
    case message_type::system_command: {
        auto cmd {system_commands_.get_command(
            static_cast<system_commands>(req.header.extra))};

        if (cmd == nullptr) {
            response_message_header header {
                req.header.type,
                static_cast<std::underlying_type_t<system_command_error>>(
                    system_command_error::unknown_command),
                req.header.seq_no, 0, 0};

            client->enqueue_send(std::shared_ptr<response_message>(
                new response_message {std::move(header)}));
        } else {
            auto cmd_ret {std::invoke(*cmd, req.body)};

            response_message_header header {
                req.header.type,
                static_cast<std::underlying_type_t<system_command_error>>(
                    cmd_ret.code),
                req.header.seq_no, 0,
                static_cast<std::uint32_t>(cmd_ret.message.size())};

            client->enqueue_send(
                std::shared_ptr<response_message>(new response_message {
                    std::move(header), std::move(cmd_ret.message)}));
        }

        client->send_enqueued();

        break;
    }
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
