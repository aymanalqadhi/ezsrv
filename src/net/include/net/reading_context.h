#ifndef EZSRV_NET_READING_CONTEXT_H
#define EZSRV_NET_READING_CONTEXT_H

#include "net/buffer.h"
#include "net/message_header.h"

#include <cstddef>
#include <cstring>

namespace ezsrv::net {
    class reading_context {
      public:
        const request_message_header &header() const noexcept {
            return header_;
        }

        void reset() { body_buffer_.reset(0); }

        void set_header(request_message_header header) {
            body_buffer_.reset(header.body_size);
            header_ = std::move(header);
        }

        bool add_body_data(std::string_view str) {
            return body_buffer_.add(str);
        }

      private:
        buffer                 body_buffer_;
        request_message_header header_;
    };
} // namespace ezsrv::net

#endif /* EZSRV_NET_READING_CONTEXT_H */
