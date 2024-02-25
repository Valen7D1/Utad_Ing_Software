#include "projectileMovementComponent.h"
#include "projectileColisionComponent.h"
#include "ballRenderComponent.h"
#include "entity.h"
#include "manager.h"
#include "message.h"
#include <Windows.h>


void ProjectileMovementComponent::Slot()
{ 
	Manager* manager = Manager::getInstance();

	if (m_typeOfProjectile != 0)
	{
		m_position.x += m_velocity.x * manager->getTimer()->GetFrameTime();
	}

	m_position.y += m_velocity.y* manager->getTimer()->GetFrameTime();

	NewPositionMessage* newPositionMessage = new NewPositionMessage(m_position);
	entityOwner->SendMsg(new NewPositionMessage(m_position));
	delete newPositionMessage;
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