#include "config/app_config.h"

#include "ezsrv_app.h"
#include "iapplication.h"

#include "data/sources/ezsrv_data_source.h"
#include "data/sources/memory_ezsrv_data_source.h"

#include "boost/di.hpp"

#include <iostream>

namespace di = boost::di;

using ezsrv::app::ezsrv_app;
using ezsrv::app::iapplication;
using ezsrv::config::app_config;
using ezsrv::data::sources::ezsrv_data_source_base;
using ezsrv::data::sources::memory_ezsrv_data_source;
using ezsrv::log::logger;

int main(int argc, const char *argv[]) {
    try {
        auto opts {app_config::from_command_line(argc, argv)};

        const auto injector = di::make_injector(
            di::bind<app_config>().to(opts),
            di::bind<ezsrv_data_source_base>().to<memory_ezsrv_data_source>(),
            di::bind<iapplication>().to<ezsrv_app>());
        auto app = injector.create<iapplication *>();

        app->configure();
        app->run();
    } catch (const std::exception &ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
