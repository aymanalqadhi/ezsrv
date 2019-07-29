#ifndef EZSRV_SERVICES_ECHO_SERVICE_H
#define EZSRV_SERVICES_ECHO_SERVICE_H

#include "services/service.h"

#include <chrono>
#include <string_view>
#include <thread>

namespace ezsrv::services {
    class echo_service final : public service_base {
        static constexpr auto name {"Echo Service"};

      public:
        std::string_view display_name() const noexcept override final {
            return name;
        }
        bool is_required() const noexcept override final { return true; }
        void initialize() override final {
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    };
} // namespace ezsrv::services

#endif /* EZSRV_SERVICES_ECHO_SERVICE_H */
