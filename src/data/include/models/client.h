#ifndef EZSRV_DATA_MODELS_CLIENT_H
#define EZSRV_DATA_MODELS_CLIENT_H

#include <cstdint>
#include <string>

namespace ezsrv::data::models {
    enum class client_type : std::uint8_t { root, admin, user };

    class client {
      public:
        inline const std::uint32_t id() const noexcept { return id_; }
        inline const client_type   type() const noexcept { return type_; }
        inline const std::string & name() const noexcept { return name_; }
        inline const std::uint32_t permissions() const noexcept {
            return permissions_;
        }

      private:
        std::uint32_t id_;
        client_type   type_;
        std::string   name_;
        std::uint32_t permissions_;
    };
} // namespace ezsrv::data::models

#endif /* end of include guard: EZSRV_DATA_MODELS_CLIENT_H */
