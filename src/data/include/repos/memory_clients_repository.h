#ifndef EZSRV_DATA_REPOS_MEMORY_CLIENTS_REPOSITORY_H
#define EZSRV_DATA_REPOS_MEMORY_CLIENTS_REPOSITORY_H

#include "models/client.h"
#include "repos/repository.h"

#include <vector>

namespace ezsrv::data::repos {
    class memory_clients_repository
        : public repository_base<ezsrv::data::models::client> {
        using client = ezsrv::data::models::client;

      public:
        bool add(const client &item) override;
        bool add(const std::vector<client> &items) override;

        bool get(std::uint32_t id, client& out) override;
        std::vector<client> get(
            std::function<bool(const client &)> pred) override;
        std::vector<client> get_all() override;

        bool update(const client &item) override;

        bool remove(std::uint32_t id) override;
        bool remove(std::function<bool(const client &)> pred) override;

        std::uint64_t count() override;

      private:
        std::vector<client> clients_;
    };
} // namespace ezsrv::data::repos

#endif /* EZSRV_DATA_REPOS_MEMORY_CLIENTS_REPOSITORY_H */
