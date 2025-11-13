#pragma once
#include <unordered_map>
#include <string>

class stringDatabase {
public:
    stringDatabase() = default;

    void add(const std::string& id, const std::string& value) {
        strings[id] = value;
    }

    const std::string& get(const std::string& id) const {
        static std::string empty = "";
        auto it = strings.find(id);
        return it != strings.end() ? it->second : empty;
    }

private:
    std::unordered_map<std::string, std::string> strings; 
};
