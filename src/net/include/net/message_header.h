#ifndef EZSRV_NET_MESSAGE_HEADER
#define EZSRV_NET_MESSAGE_HEADER

#include <cstddef>
#include <cstdint>

#include <array>

namespace ezsrv::net {
    enum class message_type : std::uint16_t {
        ping           = 0,
        system_command = 1,
        custom_command = 2,
    };

    struct request_message_header {
        static constexpr auto size {16};

        using header_buffer = std::array<std::uint8_t, size>;

        message_type  type;
        std::uint16_t extra;
        std::uint32_t seq_no;
        std::uint32_t flags;
        std::uint32_t body_size;

        static void encode(const request_message_header &header,
                           header_buffer &               out);
        static void decode(const header_buffer &   arr,
                           request_message_header &out);
    };

    struct response_message_header {
        static constexpr auto size {16};

        using header_buffer = std::array<std::uint8_t, size>;

        message_type  type;
        std::uint16_t code;
        std::uint32_t seq_no;
        std::uint32_t flags;
        std::uint32_t body_size;

        static void encode(const response_message_header &header,
                           header_buffer &                out);
        static void decode(const header_buffer &    arr,
                           response_message_header &out);
    };

    static_assert(sizeof(request_message_header) ==
                  request_message_header::size);

    static_assert(sizeof(response_message_header) ==
                  response_message_header::size);
} // namespace ezsrv::net

#endif /* EZSRV_NET_MESSAGE_HEADER */
