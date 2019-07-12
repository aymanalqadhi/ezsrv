#ifndef EZSRV_DATA_REPOS_REPOSITORY_H
#define EZSRV_DATA_REPOS_REPOSITORY_H

#include <functional>
#include <vector>

namespace ezsrv::data::repos {
    template <typename TModel>
    class repository_base {
      public:
        virtual bool add(const TModel &item);
        virtual bool add(const std::vector<TModel> &items);

        virtual bool get(std::uint32_t id, TModel& out);
        virtual std::vector<TModel> get(
            std::function<bool(const TModel &)> pred);
        virtual std::vector<TModel> get_all();

        virtual bool update(const TModel &item);

        virtual bool remove(std::uint32_t id);
        virtual bool remove(std::function<bool(const TModel &)> pred);

        virtual std::uint64_t count();
    };
} // namespace ezsrv::data

#endif /* end of include guard: EZSRV_DATA_REPOS_REPOSITORY_H */
