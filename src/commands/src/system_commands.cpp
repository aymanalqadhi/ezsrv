#include "commands/system_commands.h"

#include "commands/detail/echo_command.h"

using ezsrv::commands::system_command;
using ezsrv::commands::system_commands;
using ezsrv::commands::system_commands_container;

using ezsrv::commands::detail::echo_command;

using system_command_ptr = std::shared_ptr<system_command>;

system_commands_container::system_commands_container() {
    commands_.emplace(std::make_pair(system_commands::echo_command,
                                     std::make_shared<echo_command>()));
}

const system_command_ptr &
system_commands_container::get_command(system_commands cmd) {
    return commands_[cmd];
}
