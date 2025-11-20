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
void fontManager::loadDefaultFonts() {
    std::string path = "C:\\Users\\spyse\\source\\repos\\cpplearningsdl\\ConsoleApplication1\\ConsoleApplication1\\fonts\\Sagewold_Font_1_0\\TrueType (.ttf)\\Sagewold-Regular.ttf";
    std::string fontName = "Sagewold-Regular";
    int size = 30;

    loadFont(fontName, path, size);
    loadFont(fontName + "_small", path, size / 2);
    loadFont(fontName + "_large", path, size * 2);
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
