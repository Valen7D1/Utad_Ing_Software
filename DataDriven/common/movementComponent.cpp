#include "movementComponent.h"
#include "colisionComponent.h"
#include "renderComponent.h"
#include "entity.h"
#include "manager.h"
#include "message.h"


void MovementComponent::Slot() 
{
	Manager* manager = Manager::getInstance();
	pos = pos + vel * manager->getTimer()->GetFrameTime();
	// its redundant because msg will call to movement position but doesnt matter
	entityOwner->SendMsg(new NewPositionMessage(pos));

	//entityOwner->FindComponent<ColisionComponent>()->SetPosition(pos);
	//entityOwner->FindComponent<RenderComponent>()->SetPosition(pos);
}

void MovementComponent::ReceiveMessage(Message* msg) 
{
	// if collision with entity
	EntCollisionMessage* entCollisionMessage = dynamic_cast<EntCollisionMessage*>(msg);
	if (entCollisionMessage)
	{
		pos = entCollisionMessage->newPos;
		vel = vel * (-1);
	}

	// if collision with world limits
	LimitWorldCollMessage* limitWorldCollMessage = dynamic_cast<LimitWorldCollMessage*>(msg);
	if (limitWorldCollMessage)
	{
		pos = limitWorldCollMessage->newPos;
		vel = vel * limitWorldCollMessage->entityDirection;
	}

	//if new position
	NewPositionMessage* newPositionMessage = dynamic_cast<NewPositionMessage*>(msg);
	if (newPositionMessage)
	{
		pos = newPositionMessage->newPos;
	}
}