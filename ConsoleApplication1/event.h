#pragma once  
#include <variant>
#include <string>
#include <cstdint> 

struct turnContext;
class entity; 
class movementManager;
class dialogueManager;
class renderCacheManager;

enum class eventPhase {
    PROCESS,
    EXECUTE
};

struct baseEvent {
    eventPhase phase = eventPhase::PROCESS;
    bool convertToExecuteAfterProcessing = true;
    virtual ~baseEvent() = default;

    // Every event type will override this
    virtual void dispatch(class movementManager&, class dialogueManager&, class renderCacheManager&, turnContext&) = 0;
};
