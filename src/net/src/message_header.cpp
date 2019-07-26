#include "net/message_header.h"

#include "boost/endian/conversion.hpp"

#include <cstdlib>
#include <cstring>

#include <array>
#include <type_traits>

namespace nd = boost::endian;

using ezsrv::net::request_message_header;
using ezsrv::net::response_message_header;

using header_buffer = std::array<std::uint8_t, request_message_header::size>;

#include <iostream>
namespace {
    template <typename T>
    inline void append_number(char **buffer, T value) {
        std::memcpy(*buffer, &value, sizeof(T));
        *buffer += sizeof(T);
    }

    template <typename T>
    inline void extract_number(const char **buffer, T &out) {
        if constexpr (std::is_enum<T>()) {
            out = static_cast<T>(nd::big_to_native(
                *reinterpret_cast<const std::underlying_type_t<T> *>(*buffer)));
        } else {
            out = nd::big_to_native(*reinterpret_cast<const T *>(*buffer));
        }

        *buffer += sizeof(T);
    }

    template <typename T>
    constexpr auto to_underlying(T e) noexcept {
        return static_cast<std::underlying_type_t<T>>(e);
    }
} // namespace

void request_message_header::encode(const request_message_header &header,
                                    header_buffer &               out) {
    auto ptr = reinterpret_cast<char *>(out.data());

    append_number(&ptr, nd::native_to_big(to_underlying(header.type)));
    append_number(&ptr, nd::native_to_big(header.extra));
    append_number(&ptr, nd::native_to_big(header.seq_no));
    append_number(&ptr, nd::native_to_big(header.flags));
    append_number(&ptr, nd::native_to_big(header.body_size));
}

void request_message_header::decode(const header_buffer &   arr,
                                    request_message_header &out) {
    auto ptr = reinterpret_cast<const char *>(arr.data());

    extract_number(&ptr, out.type);
    extract_number(&ptr, out.extra);
    extract_number(&ptr, out.seq_no);
    extract_number(&ptr, out.flags);
    extract_number(&ptr, out.body_size);
}

void response_message_header::encode(const response_message_header &header,
                                    header_buffer &               out) {
    auto ptr = reinterpret_cast<char *>(out.data());

    append_number(&ptr, nd::native_to_big(to_underlying(header.type)));
    append_number(&ptr, nd::native_to_big(header.code));
    append_number(&ptr, nd::native_to_big(header.seq_no));
    append_number(&ptr, nd::native_to_big(header.flags));
    append_number(&ptr, nd::native_to_big(header.body_size));
}

void response_message_header::decode(const header_buffer &   arr,
                                    response_message_header &out) {
    auto ptr = reinterpret_cast<const char *>(arr.data());

    extract_number(&ptr, out.type);
    extract_number(&ptr, out.code);
    extract_number(&ptr, out.seq_no);
    extract_number(&ptr, out.flags);
    extract_number(&ptr, out.body_size);
}
