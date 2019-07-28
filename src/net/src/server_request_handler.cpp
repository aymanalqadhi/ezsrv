#include "net/server.h"

using ezsrv::commands::system_command_error;
using ezsrv::commands::system_command_result;
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
        system_command_result cmd_ret {std::invoke(*cmd, req.body)};
        auto                  response =
            std::make_shared<response_message>(std::move(cmd_ret.message));

        response->type(message_type::system_command);
        response->code(
            static_cast<std::underlying_type_t<system_command_error>>(
                cmd_ret.code));
        response->sequence_no(req.header.seq_no);
        response->flags(0);

        client->enqueue_send(std::move(response));
    } else {
        auto response = std::make_shared<response_message>();

        response->type(message_type::system_command);
        response->code(
            static_cast<std::underlying_type_t<system_command_error>>(
                system_command_error::unknown_command));
        response->sequence_no(req.header.seq_no);
        response->flags(0);

        client->enqueue_send(std::move(response));
    }

    client->send_enqueued();
}
