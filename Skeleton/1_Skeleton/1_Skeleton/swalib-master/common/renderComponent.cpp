#include "renderComponent.h"
#include "core.h"
#include "message.h"


void RenderComponent::Slot() 
{
	CORE_RenderCenteredSprite(pos, vec2(radius * 2.f, radius * 2.f), gfx);
}

void RenderComponent::ReceiveMessage(Message* msg) 
{
	//if new position
	NewPositionMessage* newPositionMessage = dynamic_cast<NewPositionMessage*>(msg);
	if (newPositionMessage)
	{
		pos = newPositionMessage->newPos;
	}

	// current position != new position from colision component
	// we cast to father so we only get the position (we dont care for velocity)
	CollisionMessage* collisionMessage = dynamic_cast<CollisionMessage*>(msg);
	if (collisionMessage)
	{
		pos = collisionMessage->newPos;
	}
}