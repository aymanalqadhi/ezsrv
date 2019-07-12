#ifndef EZSRV_DATA_REPOS_REPOSITORY_H
#define EZSRV_DATA_REPOS_REPOSITORY_H

#include <functional>
#include <vector>

namespace ezsrv::data::repos {
    template <typename TModel>
    class repository_base {
      public:
        virtual bool add(const TModel &item) = 0;
        virtual bool add(const std::vector<TModel> &items) = 0;

        virtual bool get(std::uint32_t id, TModel& out) = 0;
        virtual std::vector<TModel> get(
            std::function<bool(const TModel &)> pred) = 0;
        virtual std::vector<TModel> get_all() = 0;

        virtual bool update(const TModel &item) = 0;

        virtual bool remove(std::uint32_t id) = 0;
        virtual bool remove(std::function<bool(const TModel &)> pred) = 0;

        virtual std::uint64_t count() = 0;
    };
} // namespace ezsrv::data

#endif /* end of include guard: EZSRV_DATA_REPOS_REPOSITORY_H */
