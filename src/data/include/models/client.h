#ifndef EZSRV_DATA_MODELS_CLIENT_H
#define EZSRV_DATA_MODELS_CLIENT_H

#include <cstdint>
#include <string>

namespace ezsrv::data::models {
    enum class client_type : std::uint8_t { root, admin, user };
    enum class client_permission : std::uint32_t {
        none               = 0,
        send_messages      = 1,
        query_client       = 2,
        broadcast_messages = 4,
        add_users          = 8,
        remove_users       = 16,
        add_admins         = 32,
        remove_admins      = 64,
    };
    enum class client_permission_group : std::uint32_t {
        root  = 0xFFFFFFFF,
        admin = 0x0000001F,
        user  = 0x00000001
    };

    class client {
      public:
        client() = default;
        client(const std::uint32_t id) : id_(id) {}

        inline const std::uint32_t id() const noexcept { return id_; }
        inline const client_type   type() const noexcept { return type_; }
        inline const std::string & name() const noexcept { return name_; }
        inline const std::uint32_t permissions() const noexcept {
            return permissions_;
        }
        inline const bool has_permission(client_permission perm) const
            noexcept {
            return permissions_ & static_cast<std::uint32_t>(perm);
        }

        inline void type(const client_type type) noexcept { type_ = type; }
        inline void name(const std::string &name) noexcept { name_ = name; }
        inline void permissions(const std::uint32_t permissions) noexcept {
            permissions_ = permissions;
        }
        inline void set_permission_group(
            const client_permission_group pgrp) noexcept {
            permissions_ = static_cast<std::uint32_t>(pgrp);
        }
        inline void set_permission(client_permission perm) noexcept {
            permissions_ |= static_cast<std::uint32_t>(perm);
        }

      private:
        std::uint32_t id_;
        client_type   type_;
        std::string   name_;
        std::uint32_t permissions_;
    };
} // namespace ezsrv::data::models

#endif /* end of include guard: EZSRV_DATA_MODELS_CLIENT_H */
