#pragma once
#include "event.h"
#include "path.h"


class entity;
 

struct dialogueProposalEvent : baseEvent {
	int  dialogueNode; 

	bool accepted = true;
	dialogueProposalEvent(
		int dlgNode) 
		: dialogueNode(dlgNode){
	};

};

struct startDialogueEvent : baseEvent {
	int dialogueNode;
	startDialogueEvent(int dlgNode) : dialogueNode(dlgNode) {};
};
