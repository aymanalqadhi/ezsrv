#ifndef EZSRV_NET_BUFFER_H
#define EZSRV_NET_BUFFER_H

#include <cstddef>
#include <cstring>

#include <string>
#include <string_view>

namespace ezsrv::net {
    class basic_buffer {
      public:
        inline void allocate(std::size_t len) {
            if (data_ != nullptr) {
                delete[] data_;
            }
            data_ = new char[len_ = len];
        }

        inline void clean() {
            if (data_ != nullptr) {
                delete[] data_;
                data_ = nullptr;
            }
            len_ = 0;
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
            buffer_.reserve(length);
        }
        buffer() : buffer(0) {};

        inline std::size_t current() const noexcept { return current_; }
        inline std::size_t total() const noexcept { return total_; }
        inline std::size_t available() const noexcept {
            return total_ - current_;
        }
        inline std::string_view data() { return {buffer_.c_str(), current_}; }

        inline bool add(std::string_view str) {
            if (available() < str.length()) {
                return false;
            }

            buffer_.append(str);
            current_ += str.length();

            return true;
        }

        inline void reset(std::size_t len = 0) noexcept {
            if (len > 0) {
                buffer_.resize(len);
                total_   = len;
                current_ = 0;
            } else {
                buffer_.resize(0);
                total_ = current_ = 0;
            }
        }

      private:
        std::size_t total_, current_;
        std::string buffer_;
    };
} // namespace ezsrv::net

#endif /*  EZSRV_NET_BUFFER_H */
