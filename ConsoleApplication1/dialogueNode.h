#pragma once
#include <string>
#include <vector>
#include "json.hpp"
using json = nlohmann::ordered_json;

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
inline void to_json(json& j, const dialogueNode& n) {
    j = json{
        {"id", n.id},
        {"speakerId", n.speakerId},
        {"textId", n.textId},
        {"bubbleTextureKey", n.bubbleTextureKey},
        {"nextId", n.nextId},
        {"choices", n.choices},
        {"speakerFontId", n.speakerFontId},
        {"textFontId", n.textFontId}
    };
}

inline void from_json(const json& j, dialogueNode& n) {
    j.at("id").get_to(n.id);
    j.at("speakerId").get_to(n.speakerId);
    j.at("textId").get_to(n.textId);
    j.at("bubbleTextureKey").get_to(n.bubbleTextureKey);
     
    n.nextId = j.value("nextId", -1);
    n.choices = j.value("choices", std::vector<int>{});
    n.speakerFontId = j.value("speakerFontId", std::string("Sagewold-Regular"));
    n.textFontId = j.value("textFontId", std::string("Sagewold-Regular"));
}