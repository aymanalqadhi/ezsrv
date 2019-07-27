#include "net/server.h"

using ezsrv::commands::system_command_error;
using ezsrv::commands::system_commands;

using ezsrv::net::message_type;
using ezsrv::net::response_message;
using ezsrv::net::server;

void server::handle_system_command(const tcp_client_ptr & client,
                                   const request_message &req) {
    // TODO:
    // - Send real flags
    auto cmd {system_commands_.get_command(
        static_cast<system_commands>(req.header.extra))};

    if (cmd != nullptr) {
        auto cmd_ret {std::invoke(*cmd, req.body)};

        response_message_header header {
            message_type::system_command,
            static_cast<std::underlying_type_t<system_command_error>>(
                cmd_ret.code),
            req.header.seq_no, 0,
            static_cast<std::uint32_t>(cmd_ret.message.size())};

        client->enqueue_send(
            std::shared_ptr<response_message>(new response_message {
                std::move(header), std::move(cmd_ret.message)}));
    } else {
        response_message_header header {
            message_type::system_command,
            static_cast<std::underlying_type_t<system_command_error>>(
                system_command_error::unknown_command),
            req.header.seq_no, 0, 0};

        client->enqueue_send(std::shared_ptr<response_message>(
            new response_message {std::move(header)}));
    }

    client->send_enqueued();
}
