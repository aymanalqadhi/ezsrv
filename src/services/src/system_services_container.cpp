#include "services/system_services_container.h"

#include "services/echo_service.h"
#include "services/service.h"

#include <memory>
#include <stdexcept>
#include <vector>

using ezsrv::services::system_services_container;

bool system_services_container::initialize() {
    if (inited_) {
        throw std::runtime_error {"Services has been already initialized"};
    }

    std::vector<std::reference_wrapper<ezsrv::services::service_base>>
        services {echo_service_};

    for (const auto &svc : services) {
        logger_.debug("Initializing service `{}'", svc.get().display_name());
        if (!svc.get().initialize()) {
            if (svc.get().is_required()) {
                logger_.error("Could not initialize required service `{}'",
                              svc.get().display_name());
                return false;
            } else {
                logger_.warn("Could not initialize optional service `{}'",
                             svc.get().display_name());
            }
        }
    }

    inited_.store(true);
    return true;
}
