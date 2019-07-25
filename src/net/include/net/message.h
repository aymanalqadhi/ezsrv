#ifndef EZSRV_NET_MESSAGE_H
#define EZSRV_NET_MESSAGE_H

#include "net/message_header.h"

#include <string_view>

namespace ezsrv::net {
    struct request_message {
        request_message_header header;
        std::string_view       body;
    };
} // namespace ezsrv::net

#endif /* EZSRV_NET_MESSAGE_H */
