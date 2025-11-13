#include "dialogueManager.h"
#include "textureManager.h"

dialogueManager& dialogueManager::getInstance() {
    static dialogueManager instance;
    return instance;
}

void dialogueManager::loadDialogue(const std::vector<dialogueNode>& nodes) {
    for (auto& n : nodes)
        dialogueNodes[n.id] = n;
}

void dialogueManager::setStringDatabase(textDatabase* db) {
    textDB = db;
}

activeDialogue* dialogueManager::startDialogue(int id) {
    auto it = dialogueNodes.find(id);
    if (it == dialogueNodes.end() || !textDB)
        return nullptr;

    const auto& node = it->second;
    activeDialogue dlg;
    dlg.nodeId = id;
    dlg.bubbleTexture = textureManager::getInstance().getFrame(node.bubbleTextureKey);
    dlg.bubbleRect = { 100, 100, 300, 150 }; // example layout
     
    dlg.speakerLabel.color = { 255, 255, 0, 255 };
    dlg.speakerLabel.pos = { dlg.bubbleRect.x + 10, dlg.bubbleRect.y + 10 };
    dlg.speakerLabel.text = textDB->get(node.speakerId); 
    dlg.speakerLabel.updateTexture(dlg.speakerLabel.text);

    dlg.textLabel.color = { 255, 255, 255, 255 };
    dlg.textLabel.pos = { dlg.bubbleRect.x + 10, dlg.bubbleRect.y + 40, };
    dlg.textLabel.text = textDB->get(node.textId);
    dlg.speakerLabel.updateTexture(dlg.textLabel.text);

    activeDialogues.push_back(dlg);
    return &activeDialogues.back();
}

void dialogueManager::advanceDialogue(activeDialogue& dlg) {
    auto it = dialogueNodes.find(dlg.nodeId);
    if (it == dialogueNodes.end()) return;

    int nextId = it->second.nextId;
    if (nextId == -1) {
        dlg.visible = false;
        return;
    }

    dlg = *startDialogue(nextId);
}
