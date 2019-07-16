#include "net/server.h"

using ezsrv::net::server;

void server::run() {
    logger_.info("Starting Listener");
    listener_.start();
    logger_.info("Listener started on {}:{}",
                 listener_.acceptor().local_endpoint().address().to_string(),
                 config_.listen_port);

    logger_.debug("Starting event loop");
    io_ctx_.run();
}
