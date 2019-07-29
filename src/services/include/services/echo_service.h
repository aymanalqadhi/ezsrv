#ifndef EZSRV_SERVICES_ECHO_SERVICE_H
#define EZSRV_SERVICES_ECHO_SERVICE_H

#include "services/service.h"

#include <chrono>
#include <string_view>
#include <thread>

namespace ezsrv::services {
    class echo_service final : public service_base {
        static constexpr bool required {true};
        static constexpr auto name {"Echo Service"};

      public:
        echo_service() : service_base(required, name) {}

        void initialize() override final {
            // Simulate initialization
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }

        inline const std::string &echo(const std::string &str) { return str; }
    };
} // namespace ezsrv::services

#endif /* EZSRV_SERVICES_ECHO_SERVICE_H */
