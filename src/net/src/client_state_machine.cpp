#include "net/client_state_machine.h"

using ezsrv::net::client_state_machine;

void client_state_machine::handle_read(std::size_t       nread,
                                       std::string_view  msg,
                                       const error_code &err) {
    if (state() == client_state::closing) {
        return;
    }

    if (err) {
        on_error(err);
        return;
    } else if (nread == 0) {
        on_error(boost::asio::error::eof);
    }

    switch (current_state_) {
    case client_state::reading_header:
        on_reading_header(msg);
        break;

    case client_state::reading_body:
        on_reading_body(msg);
        break;

    default:
        break;
    }
}
