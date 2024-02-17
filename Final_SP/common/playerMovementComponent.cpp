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
	if (GetKeyState('A') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
	{
		m_position.x -= m_velocity * manager->getTimer()->GetFrameTime();
		NewPositionMessage* newPositionMessage = new NewPositionMessage(m_position);
		NewDirectionMessage* newDirectionMessage = new NewDirectionMessage(1);

		entityOwner->SendMsg(newPositionMessage);
		entityOwner->SendMsg(newDirectionMessage);

		delete newPositionMessage;
		delete newDirectionMessage;
	}
	if (GetKeyState('D') & 0x8000)
	{
		m_position.x += m_velocity * manager->getTimer()->GetFrameTime();
		NewPositionMessage* newPositionMessage = new NewPositionMessage(m_position);
		NewDirectionMessage* newDirectionMessage = new NewDirectionMessage(0);

		entityOwner->SendMsg(newPositionMessage);
		entityOwner->SendMsg(newDirectionMessage);

		delete newDirectionMessage;
		delete newPositionMessage;
	}
	if (GetKeyState('W') & 0x8000)
	{
		//TODO
	}
	if (GetKeyState('S') & 0x8000)
	{
		//TODO
	}

}

void PlayerMovementComponent::ReceiveMessage(Message* msg) 
{ 
	//if new position
	NewPositionMessage* newPositionMessage = dynamic_cast<NewPositionMessage*>(msg);
	if (newPositionMessage)
	{
		m_position = newPositionMessage->newPos;
	}
}