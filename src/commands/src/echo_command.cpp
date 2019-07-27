#include "commands/detail/echo_command.h"

#include <string>
#include <string_view>

using ezsrv::commands::system_command_error;
using ezsrv::commands::system_command_result;
using ezsrv::commands::detail::echo_command;

system_command_result echo_command::operator()(std::string_view msg) {
    return {system_command_error::success, std::string {msg}};
}
