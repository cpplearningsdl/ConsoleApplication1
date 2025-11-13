#pragma once
#include "fontManager.h"
#include <SDL3/SDL_log.h>
#include "logManager.h"

bool fontManager::loadFont(const std::string& key, const std::string& path, int size) {
    TTF_Font* font = TTF_OpenFont(path.c_str(), size);
    if (!font) {
        SDL_Log("Failed to load font %s: %s", path.c_str(), SDL_GetError());
        logManager::logThis("Failed to open font: " + key + " \n path: ");
        return false;
    }
    fonts[key] = font;
    return true;
}

TTF_Font* fontManager::getFont(const std::string& key) {
    auto it = fonts.find(key);
    return it != fonts.end() ? it->second : nullptr;
}

void fontManager::clear() {
    for (auto& f : fonts)
        TTF_CloseFont(f.second);
    fonts.clear();
}

fontManager::~fontManager() {
    clear();
}
