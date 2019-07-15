#include "config/app_config.h"

#include "ezsrv_app.h"
#include "iapplication.h"

#include "boost/di.hpp"

#include <iostream>

using ezsrv::app::ezsrv_app;
using ezsrv::app::iapplication;

using ezsrv::config::app_config;
using ezsrv::log::logger;

int main(int argc, const char *argv[]) {
    try {
        auto opts {app_config::from_command_line(argc, argv)};

        const auto injector = boost::di::make_injector(
            boost::di::bind<app_config>().to(opts),
            boost::di::bind<iapplication>().to<ezsrv_app>());
        auto app = injector.create<ezsrv_app>();

        app.configure();
        app.run();
    } catch (const std::exception &ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
