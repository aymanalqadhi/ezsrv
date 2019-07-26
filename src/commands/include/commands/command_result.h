#ifndef EZSRV_COMMANDS_COMMAND_RESULT_H
#define EZSRV_COMMANDS_COMMAND_RESULT_H

#include <cstdint>
#include <string>

namespace ezsrv::commands {
    enum class result_code : std::uint16_t {
        success           = 0,
        unknown_error     = 1,
        permission_denied = 2
    };

    struct command_result {
        result_code code;
        std::string message;
    };
} // namespace ezsrv::commands

#endif /* EZSRV_COMMANDS_COMMAND_RESULT_H */
