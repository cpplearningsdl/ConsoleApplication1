#pragma once  
#include <variant>
#include <string>
#include <cstdint>

class entity;

enum class eventType {
	//
	dialogueProposal,
	startDialogue,

	//movement
	movementProposed,
	finishedMovement,
	finishedPath
};


struct baseEvent {
	eventType type;

	baseEvent(eventType t) : type(t) {}
	virtual ~baseEvent() = default;
};


