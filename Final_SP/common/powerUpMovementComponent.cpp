#include "powerUpMovementComponent.h"
#include "message.h"
#include "manager.h"
#include "entity.h"



void PowerUpMovementComponent::Slot()
{ 
	Manager* manager = Manager::getInstance();

	m_position = m_position + m_velocity * manager->getTimer()->GetFrameTime();

	NewPositionMessage* msg = new NewPositionMessage(m_position);
	entityOwner->SendMsg(msg);
	delete msg;
}

void PowerUpMovementComponent::ReceiveMessage(Message* msg)
{ 
	NewPositionMessage* newPositionMessage = dynamic_cast<NewPositionMessage*>(msg);
	if (newPositionMessage)
	{
		m_position = newPositionMessage->newPos;
	}
}