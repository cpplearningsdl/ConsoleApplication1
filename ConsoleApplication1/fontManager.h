#pragma once
#include <unordered_map>
#include <string>
#include <SDL3_ttf/SDL_ttf.h>

class fontManager {
public:
    static fontManager& getInstance() {
        static fontManager instance;
        return instance;
    }

    bool loadFont(const std::string& key, const std::string& path, int size);
    TTF_Font* getFont(const std::string& key);

    void clear();

private:
    fontManager() = default;
    ~fontManager();

    fontManager(const fontManager&) = delete;
    fontManager& operator=(const fontManager&) = delete;

    std::unordered_map<std::string, TTF_Font*> fonts;
};
