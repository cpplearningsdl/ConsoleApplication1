#pragma once
#include <string>
#include <vector>
#include <SDL3/SDL.h>
#include "SDL_Color_Json.h"
#include "json.hpp"
using json = nlohmann::ordered_json;
 
struct dialogueNode {
    int id = -1;
    int entityId = -1;
    std::string speakerId; 
    std::string textId; 
    std::string bubbleTextureKeyBase = "textBubble";
    int nextId = -1;
    bool advanceOnClick = true;
    int tickCount = 6000;
    std::vector<int> choices; 

    std::string speakerFontId = "Sagewold-Regular";
    SDL_Color speakerFontColor = { 255, 255, 255, 255 };
    std::string textFontId = "Sagewold-Regular";
    SDL_Color textFontColor = { 255, 255, 255, 255 };
};
//inline void to_json(json& j, const SDL_Color& c) {
//    j = json{
//        {"r", c.r},
//        {"g", c.g},
//        {"b", c.b},
//        {"a", c.a}
//    };
//}
//
//inline void from_json(const json& j, SDL_Color& c) {
//    c.r = j.value("r", 0);
//    c.g = j.value("g", 0);
//    c.b = j.value("b", 0);
//    c.a = j.value("a", 255);
//}

inline void to_json(json& j, const dialogueNode& n) {
    j = json{
        {"id", n.id},
        {"entityId", n.entityId},
        {"speakerId", n.speakerId},
        {"textId", n.textId},
        {"bubbleTextureKeyBase", n.bubbleTextureKeyBase},
        {"nextId", n.nextId},
        {"advanceOnClick", n.advanceOnClick},
        {"tickCount", n.tickCount},
        {"choices", n.choices},
        {"speakerFontId", n.speakerFontId},
        {"textFontId", n.textFontId},
        {"speakerFontColor", json{
            {"r", n.speakerFontColor.r},
            {"g", n.speakerFontColor.g},
            {"b", n.speakerFontColor.b},
            {"a", n.speakerFontColor.a}
        }},
        {"textFontColor", json{
            {"r", n.textFontColor.r},
            {"g", n.textFontColor.g},
            {"b", n.textFontColor.b},
            {"a", n.textFontColor.a}
        }}
    };
}
inline void from_json(const json& j, dialogueNode& n) {
    n.id = j.value("id", -1);
    n.entityId = j.value("entityId", -1);
    n.speakerId = j.value("speakerId", std::string(""));
    n.textId = j.value("textId", std::string(""));
    n.bubbleTextureKeyBase = j.value("bubbleTextureKeyBase", std::string("textBubble"));
    n.nextId = j.value("nextId", -1);
    n.advanceOnClick = j.value("advanceOnClick", false);
    n.tickCount = j.value("tickCount", -1);

    if (j.contains("choices") && j["choices"].is_array())
        n.choices = j["choices"].get<std::vector<int>>();
    else {
        n.choices.clear();
    }
    n.speakerFontId = j.value("speakerFontId", std::string("Sagewold-Regular"));
    n.textFontId = j.value("textFontId", std::string("Sagewold-Regular"));

    if (j.contains("speakerFontColor") && j["speakerFontColor"].is_object()) {
        n.speakerFontColor.r = j["speakerFontColor"].value("r", 0);
        n.speakerFontColor.g = j["speakerFontColor"].value("g", 0);
        n.speakerFontColor.b = j["speakerFontColor"].value("b", 0);
        n.speakerFontColor.a = j["speakerFontColor"].value("a", 255);
    }
    else {
        n.speakerFontColor = { 0, 0, 0, 255 };
    }

    if (j.contains("textFontColor") && j["textFontColor"].is_object()) {
        n.textFontColor.r = j["textFontColor"].value("r", 0);
        n.textFontColor.g = j["textFontColor"].value("g", 0);
        n.textFontColor.b = j["textFontColor"].value("b", 0);
        n.textFontColor.a = j["textFontColor"].value("a", 255);
    }
    else {
        n.textFontColor = { 0, 0, 0, 255 };
    }
}