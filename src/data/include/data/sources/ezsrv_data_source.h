#ifndef EZSRV_DATA_SOURCES_EZSRV_DATA_SOURCE_H
#define EZSRV_DATA_SOURCES_EZSRV_DATA_SOURCE_H

#include "data/models/client.h"
#include "data/repos/repository.h"

#include <memory>

namespace ezsrv::data::sources {
    class ezsrv_data_source_base {
        using client = ezsrv::data::models::client;

        template <typename TModel>
        using repository = ezsrv::data::repos::repository_base<TModel>;

      public:
        virtual std::shared_ptr<repository<client>> clients_repository() = 0;
    };
} // namespace ezsrv::data::sources

#endif /* EZSRV_DATA_SOURCES_EZSRV_DATA_SOURCE_H */
