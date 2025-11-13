#pragma once
#include <string>
#include <vector>

struct dialogueNode {
    int id;
    std::string speakerId; 
    std::string textId; 
    std::string bubbleTextureKey; 
    int nextId = -1;
    std::vector<int> choices; 

    std::string speakerFontId = "Sagewold-Regular";
    std::string textFontId = "Sagewold-Regular";
};
