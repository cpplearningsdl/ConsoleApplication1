#pragma once
#include "label.h"
#include "dialogueNode.h"
#include <SDL3/SDL.h>
#include <string>
#include "dimensions.h"

struct activeDialogue {
    int nodeId = -1;
    int entityId = -1;
    label speakerLabel;
    label textLabel;
    std::string bubbleTextureKey = "";
    std::string bubbleTextureKeyBase = "";
    SDL_Texture* bubbleTexture = nullptr;
    position textBubblePos = { 0.0f, 0.0f };
    dimensions textBubbleSize = { 0.0f, 0.0f };
    bool visible = true;
};
