#ifndef EZSRV_NET_MESSAGE_HEADER
#define EZSRV_NET_MESSAGE_HEADER

#include <cstddef>
#include <cstdint>

#include <array>

namespace ezsrv::net {
    constexpr auto header_size {16};

    struct request_message_header {
        using header_buffer = std::array<std::uint8_t, header_size>;

        std::uint16_t type;
        std::uint16_t extra;
        std::uint32_t seq_no;
        std::uint32_t flags;
        std::uint32_t body_size;

        static void encode(const request_message_header &header,
                           header_buffer &               out);
        static void decode(const header_buffer &   arr,
                           request_message_header &out);
    };

    static_assert(sizeof(request_message_header) == header_size);
} // namespace ezsrv::net

#endif /* EZSRV_NET_MESSAGE_HEADER */
