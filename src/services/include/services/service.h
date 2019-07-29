#ifndef EZSRV_SERVICES_SERVICE_H
#define EZSRV_SERVICES_SERVICE_H

#include <string_view>

namespace ezsrv::services {
    class service_base {
      public:
        virtual std::string_view display_name() const noexcept = 0;
        virtual bool             is_required() const noexcept  = 0;

        virtual void initialize() = 0;
    };
} // namespace ezsrv::services

#endif /* EZSRV_SERVICES_SERVICE_H */
