#pragma once  
#include <variant>
#include <string>
#include <cstdint> 

struct turnContext;
class entity; 
class movementManager;
class dialogueManager;
class renderCacheManager;
class entityManager;

enum class eventPhase {
    PROCESS,
    EXECUTE
};

struct baseEvent {
    eventPhase phase = eventPhase::PROCESS;
    bool convertToExecuteAfterProcessing = true;
    std::string eventName = "";

    virtual ~baseEvent() = default;

    // Every event type will override this
    virtual void dispatch(class movementManager&, class entityManager&, class dialogueManager&, class renderCacheManager&, turnContext&) = 0;

    std::string eventPhaseToString() {
        if (phase == eventPhase::PROCESS) {
            return "PROCESS";
        }
        return "EXECUTE";
    }
};

