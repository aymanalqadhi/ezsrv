#ifndef EZSRV_APP_IAPPLICATION_H
#define EZSRV_APP_IAPPLICATION_H

namespace ezsrv::app {
    class iapplication {
      public:
        virtual void configure() = 0;
        virtual void run() = 0;

        virtual ~iapplication() noexcept = default;
    };
} // namespace ezsrv::app

#endif /* end of include guard: EZSRV_APP_IAPPLICATION_H */
