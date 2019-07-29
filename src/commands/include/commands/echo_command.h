#ifndef EZSRV_COMMANDS_DETAIL_ECHO_COMMAND_H
#define EZSRV_COMMANDS_DETAIL_ECHO_COMMAND_H

#include "commands/system_commands.h"

#include "services/echo_service.h"

namespace ezsrv::commands {
    class echo_command final : public ezsrv::commands::system_command {
      public:
        echo_command(ezsrv::services::echo_service &echo_service)
            : echo_service_ {echo_service} {}

        ezsrv::commands::system_command_result
        operator()(std::string_view msg) override final;

      private:
        ezsrv::services::echo_service echo_service_;
    };
} // namespace ezsrv::commands

#endif /* EZSRV_COMMANDS_DETAIL_ECHO_COMMAND_H */
