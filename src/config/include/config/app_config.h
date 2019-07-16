#ifndef EZSRV_CONFIG_APP_CONFIG_H
#define EZSRV_CONFIG_APP_CONFIG_H

#include <string>

namespace ezsrv::config {
    namespace info {
        constexpr char app_name[] {"ezsrv"};
        constexpr char app_description[] {
            "A high performance realtime communication server"};
        constexpr char app_version[] {"v0.1 ALPHA"};
    } // namespace info

    namespace defaults {
        constexpr std::uint16_t listen_port {3434};
        constexpr bool          ipv6_only {false};
        constexpr std::uint16_t verbosity {3};
    } // namespace defaults

    struct app_config {
        const std::string   executable;
        const std::uint16_t listen_port;
        const bool          ipv6_only;
        const std::uint16_t verbosity;

        static app_config from_command_line(int argc, const char *argv[]);
        static app_config from_config_file(const std::string &path);
    };
} // namespace ezsrv::config

#endif /* EZSRV_CONFIG_APP_CONFIG_H */
