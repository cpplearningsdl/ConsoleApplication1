 
#include "dialogueEvents.h"
#include "movementManager.h"
#include "entityManager.h"
#include "dialogueManager.h"
#include "renderCacheManager.h"

void startDialogueEvent::dispatch(movementManager& m, entityManager& entity, dialogueManager& d, renderCacheManager& r, turnContext& ctx)
{
    d.processStartDialogueEvent(ctx, *this, phase);
    entity.processStartDialogueEvent(ctx, *this, phase);
    // others if required
}

void dialogueProposalEvent::dispatch(movementManager& m, entityManager& entity, dialogueManager& d, renderCacheManager& r, turnContext& ctx)
{
    d.processDialogueProposalEvent(ctx, *this, phase); 
}

void setUpDialogueBubbleEvent::dispatch(movementManager& m, entityManager& entity, dialogueManager& d, renderCacheManager& r, turnContext& ctx)
{
    d.processSetUpDialogueBubbleEvent(ctx, *this, phase);
}