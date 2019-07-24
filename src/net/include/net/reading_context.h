#ifndef EZSRV_NET_READING_CONTEXT_H
#define EZSRV_NET_READING_CONTEXT_H

#include "net/buffer.h"
#include "net/message_header.h"

#include <cstddef>
#include <cstring>

namespace ezsrv::net {
    class reading_context {
      public:
        static constexpr std::size_t recommended_chunk_size = 0x400;

        inline const request_message_header &header() const noexcept {
            return header_;
        }

        inline void set_header(request_message_header header) {
            body_buffer_.reset(header.body_size);
            header_ = std::move(header);
        }

        inline bool add_body_data(std::string_view str) {
            return body_buffer_.add(std::move(str));
        }

        inline bool available() const noexcept {
            return body_buffer_.available();
        }

        inline bool is_full() const noexcept {
            return body_buffer_.current() == body_buffer_.total();
        }

        inline std::string_view body() const noexcept {
            return body_buffer_.data();
        }

        inline std::size_t next_chunk_size() const noexcept {
            return body_buffer_.available() >= recommended_chunk_size
                       ? recommended_chunk_size
                       : body_buffer_.available();
        }

      private:
        buffer                 body_buffer_;
        request_message_header header_;
    };
} // namespace ezsrv::net

#endif /* EZSRV_NET_READING_CONTEXT_H */
