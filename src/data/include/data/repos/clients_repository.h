#ifndef EZSRV_DATA_REPOS_CLIENTS_REPOSITORY_H
#define EZSRV_DATA_REPOS_CLIENTS_REPOSITORY_H

#include "data/models/client.h"
#include "data/repos/repository.h"

#include <memory>
#include <string_view>

namespace ezsrv::data::repos {
    class clients_repository
        : public repository_base<ezsrv::data::models::client> {
        using client = ezsrv::data::models::client;

      public:
        bool add(const client &item) override;
        bool add(const std::vector<client> &items) override;

        bool                get(std::uint32_t id, client &out) override;
        std::vector<client> get(std::function<bool(const client &)> p) override;
        std::vector<client> get_all() override;

        bool update(const client &item) override;

        bool remove(std::uint32_t id) override;
        bool remove(std::function<bool(const client &)> pred) override;

        bool authenticate(std::string_view        username,
                          std::string_view        password,
                          std::shared_ptr<client> out);
    };
} // namespace ezsrv::data::repos

#endif /* EZSRV_DATA_REPOS_CLIENTS_REPOSITORY_H */
