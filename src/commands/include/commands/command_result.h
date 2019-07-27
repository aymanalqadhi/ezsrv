#ifndef EZSRV_COMMANDS_COMMAND_RESULT_H
#define EZSRV_COMMANDS_COMMAND_RESULT_H

#include <cstdint>
#include <string>

namespace ezsrv::commands {
    enum class system_command_error : std::uint16_t {
        success         = 0,
        unknown_command = 1,
        unknown_error   = 2
    };

    struct system_command_result {
        system_command_error code;
        std::string          message;
    };
} // namespace ezsrv::commands

#endif /* EZSRV_COMMANDS_COMMAND_RESULT_H */
