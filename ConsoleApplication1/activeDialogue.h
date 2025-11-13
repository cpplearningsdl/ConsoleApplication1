#pragma once
#include "label.h"
#include "DialogueNode.h"
#include <SDL3/SDL.h>

struct activeDialogue {
    int nodeId = -1;
    label speakerLabel;
    label textLabel;
    SDL_Texture* bubbleTexture = nullptr;
    SDL_FRect bubbleRect{};
    bool visible = true;
};
