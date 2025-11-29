#pragma once  
#include <variant>
#include <string>
#include <cstdint> 

struct turnContext;
class entity; 
class movementManager;
class dialogueManager;
class renderCacheManager;

struct baseEvent {
    virtual ~baseEvent() = default;

    // Each system gets process/execute hooks. Events override what they need.
    virtual void process(turnContext& ctx, movementManager& move) {}
    virtual void execute(turnContext& ctx, movementManager& move) {}

    virtual void process(turnContext& ctx, dialogueManager& dialogue) {}
    virtual void execute(turnContext& ctx, dialogueManager& dialogue) {}

    virtual void process(turnContext&, renderCacheManager&) {}
    virtual void execute(turnContext&, renderCacheManager&) {}
};