#include "movementEvents.h"
#include "dialogueEvents.h"
#include "movementManager.h"
#include "entityManager.h"
#include "dialogueManager.h"
#include "renderCacheManager.h"

void movementProposedEvent::dispatch(movementManager& m, entityManager& entity, dialogueManager& d, renderCacheManager& r, turnContext& ctx)
{ 
    m.processMovementProposedEvent(ctx, *this, phase); 
}

void finishedMovementEvent::dispatch(movementManager& m, entityManager& entity, dialogueManager& d, renderCacheManager& r, turnContext& ctx)
{
    m.processFinishedMovementEvent(ctx, *this, phase);
}

void finishedPathEvent::dispatch(movementManager& m, entityManager& entity, dialogueManager& d, renderCacheManager& r, turnContext& ctx)
{
    m.processFinishedPathEvent(ctx, *this, phase);
}

void movedThisFrameEvent::dispatch(movementManager& m, entityManager& entity, dialogueManager& d, renderCacheManager& r, turnContext& ctx)
{
    m.processMovedThisFrameEvent(ctx, *this, phase);
}