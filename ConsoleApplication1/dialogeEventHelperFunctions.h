#pragma once
#include <string>
#include "logManager.h"
#include "turnContext.h"
#include "event.h"
#include "dialogueEvents.h"
#include "activeDialogue.h"
#include "windowSettings.h" 
#include "textureManager.h" 


enum class screenQuadrant {
	TOP_LEFT,
	TOP_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_RIGHT
};


screenQuadrant getScreenQuadrant(const position& worldPos, const position& cameraPos, int screenWidth, int screenHeight) {
    float screenX = worldPos.getX() - cameraPos.getX();
    float screenY = worldPos.getY() - cameraPos.getY();

    bool left = (screenX < static_cast<float>(screenWidth) * 0.5f);
    bool top = (screenY < static_cast<float>(screenHeight) * 0.5f);

    if (left && top)     return screenQuadrant::TOP_LEFT;
    if (!left && top)    return screenQuadrant::TOP_RIGHT;
    if (left && !top)    return screenQuadrant::BOTTOM_LEFT;
    return screenQuadrant::BOTTOM_RIGHT;
}


std::string getOrientedBubblesTextureKeySuffix(screenQuadrant q) {
 
    switch (q)
    {
    case screenQuadrant::TOP_LEFT: 
        return "_fromLeft_0";
        break;

    case screenQuadrant::TOP_RIGHT: 
        return "_fromRight_0";
        break;

    case screenQuadrant::BOTTOM_LEFT: 
        return "_fromLeft_0";
        break;

    case screenQuadrant::BOTTOM_RIGHT: 
        return "_fromRight_0";
        break;  
    }
    return "_fromLeft_0"; 

}
 
position getTextBubbleScreenPos(const position& worldPos, const position& cameraPos, const float portraitSize, const float buffer, screenQuadrant quad, const dimensions& size) {
    float screenX = worldPos.getX() - cameraPos.getX();
    float screenY = worldPos.getY() - cameraPos.getY();

    float bubbleW = size.getW();
    float bubbleH = size.getH();

    position bubblePos = { screenX, screenY };

    switch (quad)
    {
    case screenQuadrant::TOP_LEFT:
        // Bubble RIGHT of portrait
        bubblePos.setX(screenX + portraitSize + buffer);
        break;

    case screenQuadrant::TOP_RIGHT:
        // Bubble LEFT of bubble width
        bubblePos.setX(screenX - bubbleW - buffer);
        break;

    case screenQuadrant::BOTTOM_LEFT:
        // Bubble RIGHT of portrait
        bubblePos.setX(screenX + portraitSize + buffer);
        break;

    case screenQuadrant::BOTTOM_RIGHT:
        // Bubble LEFT of bubble width
        bubblePos.setX(screenX - bubbleW - buffer);
        break;
    }

    return bubblePos;
} 


 void setUpDialogueBubble(position entityPos, position cameraPos, activeDialogue& d){
     float w, h;
     screenQuadrant quad = getScreenQuadrant(entityPos, cameraPos, logicalW, logicalH);
     d.bubbleTextureKey = d.bubbleTextureKeyBase + getOrientedBubblesTextureKeySuffix(quad);
     d.bubbleTexture = textureManager::getInstance().getFrame(d.bubbleTextureKey);
     SDL_GetTextureSize(d.bubbleTexture, &w, &h);
     d.textBubbleSize.setSize(w, h);
     dimensions size = dimensions(w, h);
     d.textBubblePos = getTextBubbleScreenPos(entityPos, cameraPos, 128, 5, quad, size);
     d.speakerLabel.updateTexture(d.speakerLabel.text);
     d.textLabel.updateTexture(d.textLabel.text);
}


void dialogueProposal(turnContext& ctx, dialogueProposalEvent& ev) {

}