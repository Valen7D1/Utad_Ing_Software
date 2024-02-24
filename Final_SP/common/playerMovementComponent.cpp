#include "playerMovementComponent.h"
#include "playerColisionComponent.h"
#include "ballRenderComponent.h"
#include "entity.h"
#include "manager.h"
#include "message.h"
#include <Windows.h>


void PlayerMovementComponent::Slot() 
{ 
	Manager* manager = Manager::getInstance();


	/////////////////////////////////////////////////////////////////////////////
	// X axis movement
	if (GetKeyState('A') & 0x8000)
	{
		m_position.x -= m_velocity * manager->getTimer()->GetFrameTime();

		NewDirectionMessage* newDirectionMessage = new NewDirectionMessage(1);
		entityOwner->SendMsg(newDirectionMessage);
		delete newDirectionMessage;
	}

	if (GetKeyState('D') & 0x8000)
	{
		m_position.x += m_velocity * manager->getTimer()->GetFrameTime();

		NewDirectionMessage* newDirectionMessage = new NewDirectionMessage(0);
		entityOwner->SendMsg(newDirectionMessage);
		delete newDirectionMessage;
	}

	/////////////////////////////////////////////////////////////////////////////
	// ladder movements ( Y axis )
	if (GetKeyState('W') & 0x8000 && m_onLadder)
	{
		m_position.y += m_velocity * manager->getTimer()->GetFrameTime();
	}

	if (GetKeyState('S') & 0x8000 && m_onLadder)
	{
		m_position.y -= m_velocity * manager->getTimer()->GetFrameTime();
	}

	/////////////////////////////////////////////////////////////////////////////
	if (!m_onLadder && !m_onSurface) // apply gravity if not in surface or ladder
	{
		m_position.y += GRAVITY * manager->getTimer()->GetFrameTime();
	}

	// update position on all components
	NewPositionMessage* newPositionMessage = new NewPositionMessage(m_position);
	entityOwner->SendMsg(newPositionMessage);
	delete newPositionMessage;
}

void PlayerMovementComponent::ReceiveMessage(Message* msg) 
{ 
	//if new position
	NewPositionMessage* newPositionMessage = dynamic_cast<NewPositionMessage*>(msg);
	if (newPositionMessage)
	{
		m_position = newPositionMessage->newPos;
	}
	// if on ladder detected in collision component
	NewOnLadderMessage * newOnLadderMessage = dynamic_cast<NewOnLadderMessage*>(msg);
	if (newOnLadderMessage)
	{
		m_onLadder = newOnLadderMessage->onLadder;
	}
	// if on surface detected in collision component
	NewOnSurfaceMessage* newOnSurfaceMessage = dynamic_cast<NewOnSurfaceMessage*>(msg);
	if (newOnSurfaceMessage)
	{
		m_onSurface = newOnSurfaceMessage->onSurface;
	}
}