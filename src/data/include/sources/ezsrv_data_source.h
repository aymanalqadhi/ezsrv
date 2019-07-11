#ifndef EZSEV_DATA_SOURCES_EZSRV_DATA_SOURCE_H
#define EZSEV_DATA_SOURCES_EZSRV_DATA_SOURCE_H

#include "models/client.h"
#include "repos/repository.h"

#include <memory>

namespace ezsrv::data::sources {
    class ezsrv_data_source_base {
        using client = ezsrv::data::models::client;

        template <typename TModel>
        using repository = ezsrv::data::repos::repository_base<TModel>;

      public:
        virtual std::shared_ptr<repository<client>> clients_repository();
    };
} // namespace ezsrv::data::sources

#endif /* end of include guard: EZSEV_DATA_SOURCES_EZSRV_DATA_SOURCE_H */
