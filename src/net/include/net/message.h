#ifndef EZSRV_NET_MESSAGE_H
#define EZSRV_NET_MESSAGE_H

#include "net/message_header.h"

#include <string>
#include <string_view>

namespace ezsrv::net {
    struct request_message {
        request_message_header header;
        std::string_view       body;
    };

    class response_message {
      public:
        response_message(const std::string &body) : body_ {body} {
            header_.body_size = static_cast<std::uint32_t>(body_.size());
        }

        response_message(std::string &&body) {
            body_             = std::move(body);
            header_.body_size = static_cast<std::uint32_t>(body_.size());
        }

        response_message() : body_ {} {
            header_.body_size = 0;
        };

        inline message_type  type() const noexcept { return header_.type; }
        inline std::uint32_t code() const noexcept { return header_.code; }
        inline std::uint32_t flags() const noexcept { return header_.flags; }
        inline std::uint32_t sequence_no() const noexcept {
            return header_.seq_no;
        }
        inline std::uint32_t body_size() const noexcept {
            return header_.body_size;
        }
        inline const response_message_header &header() const noexcept {
            return header_;
        }
        inline const std::string_view body() const noexcept { return body_; }

        inline void type(message_type type) noexcept { header_.type = type; }
        inline void code(std::uint16_t code) noexcept { header_.code = code; }
        inline void flags(std::uint32_t flags) noexcept {
            header_.flags = flags;
        }
        inline void sequence_no(std::uint32_t seq_no) noexcept {
            header_.seq_no = seq_no;
        }

        inline void body(const std::string &body) {
            body_             = body;
            header_.body_size = static_cast<std::uint32_t>(body_.size());
        }
        inline void body(std::string &&body) {
            body_             = std::move(body);
            header_.body_size = static_cast<std::uint32_t>(body_.size());
        }

      private:
        response_message_header header_;
        std::string             body_;
    };
} // namespace ezsrv::net

#endif /* EZSRV_NET_MESSAGE_H */
