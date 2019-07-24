#ifndef EZSRV_NET_BUFFER_H
#define EZSRV_NET_BUFFER_H

#include <cstddef>
#include <cstring>

#include <cstring>
#include <string_view>

namespace ezsrv::net {
    class basic_buffer {
      public:
        ~basic_buffer() {
            if (data_ != nullptr) {
                delete[] data_;
            }
        }

        inline void allocate(std::size_t len) {
            if (data_ != nullptr) {
                delete[] data_;
            }
            data_ = new char[len_ = len];
        }

        inline char *      data() const noexcept { return data_; }
        inline std::size_t length() const noexcept { return len_; }

      private:
        std::size_t len_ {0};
        char *      data_ {nullptr};
    };

    class buffer {
      public:
        buffer(std::size_t length) : total_ {length}, current_ {0} {
            if (length > 0) {
                buffer_ = new std::uint8_t[length];
            } else {
                buffer_ = nullptr;
            }
        }

        buffer() : buffer {0} {};
        ~buffer() {
            if (buffer_ != nullptr) {
                delete[] buffer_;
            }
        }

        inline std::size_t current() const noexcept { return current_; }
        inline std::size_t total() const noexcept { return total_; }
        inline std::size_t available() const noexcept {
            return total_ - current_;
        }
        inline std::string_view data() const {
            return {reinterpret_cast<char *>(buffer_), total_};
        }

        inline bool add(std::string_view str) {
            if (buffer_ == nullptr || available() < str.length()) {
                return false;
            }

            std::memcpy(buffer_ + current_, str.data(), str.length());
            current_ += str.length();

            return true;
        }

        inline void reset(std::size_t len = 0) {
            if (len == total_) {
                current_ = 0;
                return;
            }

            if (buffer_ != nullptr) {
                delete[] buffer_;
            }

            current_ = 0;
            total_   = len;
            buffer_  = len != 0 ? new std::uint8_t[len] : nullptr;
        }

      private:
        std::size_t   total_, current_;
        std::uint8_t *buffer_;
    };
} // namespace ezsrv::net

#endif /*  EZSRV_NET_BUFFER_H */
