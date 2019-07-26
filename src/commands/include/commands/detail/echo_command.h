#ifndef EZSRV_COMMANDS_DETAIL_ECHO_COMMAND_H
#define EZSRV_COMMANDS_DETAIL_ECHO_COMMAND_H

#include "commands/system_commands.h"

namespace ezsrv::commands::detail {
    class echo_command final : public ezsrv::commands::system_command {
        ezsrv::commands::command_result
        operator()(std::string_view msg) override final;
    };
} // namespace ezsrv::commands::detail

#endif /* end of include guard: EZSRV_COMMANDS_DETAIL_ECHO_COMMAND_H */
