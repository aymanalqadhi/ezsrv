#ifndef EZSRV_COMMANDS_SYSTEM_COMMANDS_H
#define EZSRV_COMMANDS_SYSTEM_COMMANDS_H

#include "commands/command_result.h"

#include <cstring>

#include <map>
#include <string_view>

namespace ezsrv::commands {
    enum class system_commands : std::uint16_t { echo_command = 0 };

    class system_command {
      public:
        virtual command_result operator()(std::string_view msg) = 0;
    };

    class system_commands_container {
      public:
        system_command &get_command(system_commands command);

      private:
        std::map<system_commands, system_command> commands_;
    };
} // namespace ezsrv::commands

#endif /* EZSRV_COMMANDS_SYSTEM_COMMANDS_H */
