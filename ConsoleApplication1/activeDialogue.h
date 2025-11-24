#pragma once
#include "label.h"
#include "DialogueNode.h"
#include <SDL3/SDL.h>
#include "dimensions.h"

struct activeDialogue {
    int nodeId = -1;
    label speakerLabel;
    label textLabel;
    SDL_Texture* bubbleTexture = nullptr;
    position textBubblePos = { 0.0f, 0.0f };
    dimensions textBubbleSize = { 0.0f, 0.0f };
    bool visible = true;
};
