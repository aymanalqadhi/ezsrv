#include "config/app_config.h"

#include "boost/program_options/options_description.hpp"
#include "boost/program_options/variables_map.hpp"
#include "boost/program_options/parsers.hpp"

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

namespace po       = boost::program_options;
namespace defaults = ezsrv::config::defaults;
namespace info     = ezsrv::config::info;

using ezsrv::config::app_config;

namespace {
    po::options_description get_options_aggregator();
    po::options_description get_global_options();
    po::options_description get_network_options();
} // namespace

app_config app_config::from_command_line(int argc, const char *argv[]) {
    auto              options {get_options_aggregator()};
    po::variables_map var_map;

    po::store(po::parse_command_line(argc, argv, options), var_map);
    po::notify(var_map);

    if (var_map.count("help")) {
        std::cout << options << std::endl;
        std::exit(EXIT_SUCCESS);
    } else if (var_map.count("version")) {
        std::cout << info::app_name << ": " << info::app_version << std::endl;
        std::exit(EXIT_SUCCESS);
    } else if (var_map.count("verbose")) {
        auto log_level = var_map["verbose"].as<std::uint16_t>();
        if (log_level > 6) {
            throw po::invalid_option_value(std::to_string(log_level));
        }
    }

    return {
        // Executable Name
        argv[0],

        // Listen Port
        var_map.count("port") ? var_map["port"].as<std::uint16_t>()
                              : defaults::listen_port,

        // IPv6 Only
        var_map.count("ipv6") > 0,

        // Verbosity
        var_map.count("verbose")
            ? static_cast<std::uint16_t>(
                6 - var_map["verbose"].as<std::uint16_t>())
            : defaults::verbosity,
    };
}

namespace {
po::options_description get_options_aggregator() {
    po::options_description aggregator {std::string {info::app_description} +
                                        "\n\nusage: ezsrv [ options... ]"};
    aggregator.add(get_network_options()).add(get_global_options());
    return aggregator;
}

    po::options_description get_global_options() {
        po::options_description global {"Global Options"};
        global.add_options()
            (
                "verbose,v",
                po::value<std::uint16_t>()->default_value(3),
                "Increase the logging verbosity level"
            )
            ("version,V", "Show the app version")
            ("help,h", "Show this help message");
        return global;
    }

    po::options_description get_network_options() {
        po::options_description global {"Network Options"};
        global.add_options()
            (
              "port,p",
              po::value<std::uint16_t>()->default_value(defaults::listen_port),
              "Set the listening TCP port"
            )
            (
              "ipv6,6",
              "Accept IPv6 connections only"
            );
        return global;
    }
} // namespace
