#pragma once
#include <string>
#include <SDL3/SDL.h> 
#include "renderer.h"
#include "position.h"
#include "dimensions.h"


struct label {
    std::string id; 
    std::string text = "How did you get me\n to say this?";
    std::string fontName = "Sagewold-Regular";
    SDL_Color color = { 255, 255, 255, 255 };
    position pos = { 0.0f, 0.0f };
    float scale = 1.0f;
    SDL_Texture* texture = nullptr;
    float w = 0, h = 0;

    void updateTexture(const std::string& newText) {
        if (text != newText || texture == nullptr) {
            text = newText;
            if (texture) SDL_DestroyTexture(texture);
            texture = renderer::getInstance().createTextTexture(text, fontName, color); 
            SDL_GetTextureSize(texture, &w, &h);
        }
    } 
};
 
