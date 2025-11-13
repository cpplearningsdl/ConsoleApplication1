#pragma once
#include <unordered_map>
#include "dialogueNode.h"
#include "activeDialogue.h"
#include "textDB.h"
#include "renderer.h" 

class dialogueManager {
public:
    static dialogueManager& getInstance();

    void loadDialogue(const std::vector<dialogueNode>& nodes);
    void setStringDatabase(textDatabase* db);
    activeDialogue* startDialogue(int id);
    void advanceDialogue(activeDialogue& dlg);

    const std::vector<activeDialogue>& getActiveDialogues() const { return activeDialogues; }

private:
    dialogueManager() = default;
    std::unordered_map<int, dialogueNode> dialogueNodes;
    std::vector<activeDialogue> activeDialogues;
    textDatabase* textDB = nullptr;
};
