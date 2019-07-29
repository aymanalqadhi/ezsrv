#ifndef EZSRV_COMMANDS_SYSTEM_COMMANDS_H
#define EZSRV_COMMANDS_SYSTEM_COMMANDS_H

#include "commands/command_result.h"

#include "services/system_services_container.h"

#include <cstring>

#include <map>
#include <memory>
#include <string_view>

namespace ezsrv::commands {
    namespace details {
        using ezsrv::services::system_services_container;

        enum class system_commands : std::uint16_t { echo_command = 0 };

        class system_command {
          public:
            virtual system_command_result operator()(std::string_view msg) = 0;
        };

        class system_commands_container {
          public:
            explicit system_commands_container(
                system_services_container &system_services);

            system_commands_container(const system_commands_container &) =
                delete;

            const std::shared_ptr<system_command> &
            get_command(system_commands command);

          private:
            std::map<system_commands, std::shared_ptr<system_command>>
                                                        commands_;
            ezsrv::services::system_services_container &system_services_;
        };
    } // namespace details

    using details::system_command;
    using details::system_commands;
    using details::system_commands_container;
} // namespace ezsrv::commands

#endif /* EZSRV_COMMANDS_SYSTEM_COMMANDS_H */
