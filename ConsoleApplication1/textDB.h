#pragma once
#include "json.hpp"
#include <unordered_map>
#include <string>
using json = nlohmann::ordered_json;

struct textDatabase {
    std::unordered_map<std::string, std::string> entries;

    void addEntry(const std::string& id, const std::string& text) {
        entries[id] = text;
    }

    const std::string& get(const std::string& id) const {
        static std::string empty = "";
        auto it = entries.find(id);
        return it != entries.end() ? it->second : empty;
    }
};
inline void to_json(json& j, const textDatabase& db) {
    j = db.entries;  
}

inline void from_json(const json& j, textDatabase& db) {
    db.entries = j.get<std::unordered_map<std::string, std::string>>();
}