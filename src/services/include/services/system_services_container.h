#ifndef EZSRV_SERVICES_SYSTEM_SERVICES_CONTAINER_H
#define EZSRV_SERVICES_SYSTEM_SERVICES_CONTAINER_H

#include "log/logger.h"

#include "services/echo_service.h"
#include "services/service.h"

#include <atomic>

namespace ezsrv::services {
    namespace detail {
        namespace svcs = ezsrv::services;
        class system_services_container {
          public:
            system_services_container(ezsrv::log::logger &logger,
                                      svcs::echo_service  echo_service)
                : logger_ {logger}, echo_service_ {std::move(echo_service)} {}

            bool initialize();

            inline svcs::echo_service &echo_service() noexcept {
                return echo_service_;
            }

          private:
            ezsrv::log::logger &logger_;
            svcs::echo_service  echo_service_;

            std::atomic_bool inited_ {false};
        };
    } // namespace detail
    using detail::system_services_container;
} // namespace ezsrv::services

#endif /* EZSRV_SERVICES_SYSTEM_SERVICES_CONTAINER_H */
