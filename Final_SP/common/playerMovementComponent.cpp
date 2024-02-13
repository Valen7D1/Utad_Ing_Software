#include "playerMovementComponent.h"
#include "playerColisionComponent.h"
#include "renderComponent.h"
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
		entityOwner->SendMsg(new NewPositionMessage(m_position));
		entityOwner->SendMsg(new NewDirectionMessage(1));
	}
	if (GetKeyState('D') & 0x8000)
	{
		m_position.x += m_velocity * manager->getTimer()->GetFrameTime();
		entityOwner->SendMsg(new NewPositionMessage(m_position));
		entityOwner->SendMsg(new NewDirectionMessage(0));
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