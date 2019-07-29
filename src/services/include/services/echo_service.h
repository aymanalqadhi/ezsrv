#ifndef EZSRV_SERVICES_ECHO_SERVICE_H
#define EZSRV_SERVICES_ECHO_SERVICE_H

#include "services/service.h"

#include <string_view>

namespace ezsrv::services {
    class echo_service final : public service_base {
        static constexpr bool required {true};
        static constexpr auto name {"Echo Service"};

      public:
        echo_service() : service_base(required, name) {}
        bool initialize() override final;

        std::string echo(const std::string_view &str);
    };
} // namespace ezsrv::services

#endif /* EZSRV_SERVICES_ECHO_SERVICE_H */
