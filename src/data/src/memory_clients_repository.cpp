#include "data/repos/memory_clients_repository.h"

#include "data/models/client.h"

#include <vector>

using ezsrv::data::models::client;
using ezsrv::data::repos::memory_clients_repository;

bool memory_clients_repository::add(const client &item) {
    clients_.push_back(item);
    return true;
}

bool memory_clients_repository::add(const std::vector<client> &items) {
    clients_.insert(clients_.end(), items.begin(), items.end());
    return true;
}

bool memory_clients_repository::get(std::uint32_t id, client &out) {
    auto client = std::find_if(clients_.begin(), clients_.end(),
        [id](const auto &c) -> bool { return c.id() == id; });

    if (client == clients_.end()) {
        return false;
    }

    out = *client;
    return true;
}

std::vector<client> memory_clients_repository::get(
    std::function<bool(const client &)> pred) {
    std::vector<client> ret;
    for (const auto &client : clients_) {
        if (pred(client)) {
            ret.push_back(client);
        }
    }
    return ret;
}

std::vector<client> memory_clients_repository::get_all() {
    return clients_;
}

bool memory_clients_repository::update(const client &item) {
    auto client = std::find_if(clients_.begin(), clients_.end(),
        [id = item.id()](const auto &c) { return c.id() == id; });

    if (client == clients_.end()) {
        return false;
    }

    client->type(item.type());
    client->name(item.name());
    client->permissions(item.permissions());

    return true;
}

bool memory_clients_repository::remove(std::uint32_t id) {
    auto client = std::find_if(clients_.begin(), clients_.end(),
        [id](const auto &c) { return c.id() == id; });

    if (client == clients_.end()) {
        return false;
    }

    clients_.erase(client);
    return true;
}

bool memory_clients_repository::remove(
    std::function<bool(const client &)> pred) {
    for (auto itr = clients_.begin(); itr != clients_.end(); ++itr) {
        if (pred(*itr)) {
            clients_.erase(itr);
        }
    }
    return true;
}

std::uint64_t memory_clients_repository::count() {
    return clients_.size();
}
