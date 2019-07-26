#include "commands/detail/echo_command.h"

#include <string>
#include <string_view>

using ezsrv::commands::command_result;
using ezsrv::commands::result_code;
using ezsrv::commands::detail::echo_command;

command_result echo_command::operator()(std::string_view msg) {
    return {result_code::success, std::string {msg}};
}
