#ifndef EZSRV_DATA_SOURCES_MEMORY_EZSRV_DATA_SOURCE_H
#define EZSRV_DATA_SOURCES_MEMORY_EZSRV_DATA_SOURCE_H

#include "data/repos/memory_clients_repository.h"
#include "data/sources/ezsrv_data_source.h"

namespace ezsrv::data::sources {
    class memory_ezsrv_data_source : public ezsrv_data_source_base {
        using client           = ezsrv::data::models::client;
        using clients_repo     = ezsrv::data::repos::memory_clients_repository;
        using permission_group = ezsrv::data::models::client_permission_group;
        using client_type      = ezsrv::data::models::client_type;

        template <typename TModel>
        using repository = ezsrv::data::repos::repository_base<TModel>;

      public:
        memory_ezsrv_data_source()
            : clients_repo_ {std::make_shared<clients_repo>()} {
            client root {0};
            root.set_permission_group(permission_group::root);
            root.name("root");
            root.type(client_type::root);
            clients_repo_->add(std::move(root));
        }

        std::shared_ptr<repository<client>> clients_repository() override {
            return clients_repo_;
        }

      private:
        std::shared_ptr<repository<client>> clients_repo_;
    };
} // namespace ezsrv::data::sources

#endif /* end of include guard: EZSRV_DATA_SOURCES_MEMORY_EZSRV_DATA_SOURCE_H  \
        */
