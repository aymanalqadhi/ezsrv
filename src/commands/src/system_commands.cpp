#include "commands/detail/echo_command.h"
#include "commands/system_commands.h"

#include "services/system_services_container.h"

using ezsrv::commands::system_command;
using ezsrv::commands::system_commands;
using ezsrv::commands::system_commands_container;
using ezsrv::commands::detail::echo_command;

using system_command_ptr = std::shared_ptr<system_command>;

using ezsrv::services::system_services_container;

system_commands_container::system_commands_container(
    system_services_container &system_services)
    : system_services_ {system_services} {
    commands_.emplace(std::make_pair(system_commands::echo_command,
                                     std::make_shared<echo_command>()));
}

const system_command_ptr &
system_commands_container::get_command(system_commands cmd) {
    static system_command_ptr null_cmd {nullptr};
    auto                      cmd_itr = commands_.find(cmd);

    return cmd_itr != commands_.end() ? cmd_itr->second : null_cmd;
}
