#ifndef EZSRV_APP_IAPPLICATION_H
#define EZSRV_APP_IAPPLICATION_H

#include "config/app_config.h"

namespace ezsrv::app {
    class iapplication {
      public:
        virtual void configure(const ezsrv::config::app_config& config) = 0;
        virtual void run() = 0;
    };
} // namespace ezsrv::app

#endif /* end of include guard: EZSRV_APP_IAPPLICATION_H */
