#ifndef EZSRV_DATA_REPOS_CLIENTS_REPOSITORY_H
#define EZSRV_DATA_REPOS_CLIENTS_REPOSITORY_H

#include "models/client.h"
#include "repos/repository.h"

namespace ezsrv::data::repos {
    class clients_repository
        : public repository_base<ezsrv::data::models::client> {
        using client = ezsrv::data::models::client;

        bool add(const client &item) override;
        bool add(const std::vector<client> &items) override;

        std::vector<client> get_all() override;
        std::vector<client> get(std::uint32_t id) override;
        std::vector<client> get(
            std::function<bool(const client &)> pred) override;

        bool update(const client &item) override;

        bool remove(std::uint32_t id) override;
        bool remove(std::function<bool(const client &)> pred) override;
    };
} // namespace ezsrv::data::repos

#endif /* end of include guard: EZSRV_DATA_REPOS_CLIENTS_REPOSITORY_H */
