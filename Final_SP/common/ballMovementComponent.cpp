#include "ballMovementComponent.h"
#include "ballColisionComponent.h"
#include "ballRenderComponent.h"
#include "entity.h"
#include "manager.h"
#include "message.h"

// we need to apply mrua

void BallMovementComponent::Slot()
{
	Manager* manager = Manager::getInstance();
	m_position = m_position + m_velocity * manager->getTimer()->GetFrameTime();
	// its redundant because msg will call to movement position but doesnt matter
	NewPositionMessage* msg = new NewPositionMessage(m_position);
	entityOwner->SendMsg(msg);
	delete msg;
}

void BallMovementComponent::ReceiveMessage(Message* msg)
{
	// if collision with entity
	EntCollisionMessage* entCollisionMessage = dynamic_cast<EntCollisionMessage*>(msg);
	if (entCollisionMessage)
	{
		m_position = entCollisionMessage->newPos;
		m_velocity = m_velocity * (-1);
	}

	// if collision with world limits
	LimitWorldCollMessage* limitWorldCollMessage = dynamic_cast<LimitWorldCollMessage*>(msg);
	if (limitWorldCollMessage)
	{
		m_position = limitWorldCollMessage->newPos;
		m_velocity = m_velocity * limitWorldCollMessage->entityDirection;
	}

	//if new position
	NewPositionMessage* newPositionMessage = dynamic_cast<NewPositionMessage*>(msg);
	if (newPositionMessage)
	{
		m_position = newPositionMessage->newPos;
	}

	// new velocity
	NewVelocityMessage* newVelocityMessage = dynamic_cast<NewVelocityMessage*>(msg);
	if (newVelocityMessage)
	{
		m_velocity = newVelocityMessage->newVel;
	}

}