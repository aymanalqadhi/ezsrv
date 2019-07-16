#ifndef EZSRV_NET_MESSAGE_HEADER
#define EZSRV_NET_MESSAGE_HEADER

#include <cstddef>
#include <cstdint>

namespace ezsrv::net {
    constexpr auto header_size {12};
    struct request_message_header {
        std::uint32_t flags;
        std::uint64_t body_size;
    };
} // namespace ezsrv::net

#endif /* EZSRV_NET_MESSAGE_HEADER */
