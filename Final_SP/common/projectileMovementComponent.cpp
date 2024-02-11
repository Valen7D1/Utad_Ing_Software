#include "projectileMovementComponent.h"
#include "projectileColisionComponent.h"
#include "renderComponent.h"
#include "entity.h"
#include "manager.h"
#include "message.h"
#include <Windows.h>


void ProjectileMovementComponent::Slot()
{ 
	Manager* manager = Manager::getInstance();
	m_position.y += m_velocity* manager->getTimer()->GetFrameTime();
	entityOwner->SendMsg(new NewPositionMessage(m_position));
}

void ProjectileMovementComponent::ReceiveMessage(Message* msg)
{ 
	//if new position
	NewPositionMessage* newPositionMessage = dynamic_cast<NewPositionMessage*>(msg);
	if (newPositionMessage)
	{
		m_position = newPositionMessage->newPos;
	}
}