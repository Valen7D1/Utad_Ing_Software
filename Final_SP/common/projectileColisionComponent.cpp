#include "projectileMovementComponent.h"
#include "projectileColisionComponent.h"
#include "renderComponent.h"
#include "entity.h"
#include "manager.h"
#include "message.h"
#include "sys.h"

void ProjectileColisionComponent::Slot() 
{ 
	if ((m_position.y > SCR_HEIGHT) || (m_position.y < FLOOR)) {
		entityOwner->toBeDeleted = true;
	}
}

void ProjectileColisionComponent::ReceiveMessage(Message* msg) 
{
	//if new position
	NewPositionMessage* newPositionMessage = dynamic_cast<NewPositionMessage*>(msg);
	if (newPositionMessage)
	{
		m_position = newPositionMessage->newPos;
	}
}