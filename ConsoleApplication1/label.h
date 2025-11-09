#pragma once
#include <string>
#include <SDL3/SDL.h> 
#include "renderer.h"
#include "position.h"
#include "dimensions.h"


struct label {
    std::string id;              // Optional link to TextDatabase
    std::string text;            // Current text
    SDL_Color color = { 255,255,255,255 };
    position pos = { 0.0f, 0.0f };
    float scale = 1.0f;
    std::string fontId = "default";
    SDL_Texture* texture = nullptr;
    dimensions size;
    float w = 0, h = 0;

    void setText(const std::string& newText) {
        if (text != newText) {
            text = newText;
            if (texture) SDL_DestroyTexture(texture);
            texture = renderer::getInstance().createTextTexture(text, fontId, color); 
            SDL_GetTextureSize(texture,  &w, &h);
        }
    } 
};
