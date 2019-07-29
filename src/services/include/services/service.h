#ifndef EZSRV_SERVICES_SERVICE_H
#define EZSRV_SERVICES_SERVICE_H

#include <string_view>

namespace ezsrv::services {
    class service_base {
      public:
        service_base(bool required, const char *name)
            : required_ {required}, name_ {name} {}

        inline std::string_view display_name() const noexcept { return name_; }
        inline bool is_required() const noexcept { return required_; }

        virtual void initialize() = 0;

      private:
        bool        required_;
        const char *name_;
    };
} // namespace ezsrv::services

#endif /* EZSRV_SERVICES_SERVICE_H */
