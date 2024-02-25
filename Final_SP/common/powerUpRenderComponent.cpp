#include "powerUpRenderComponent.h"
#include "message.h"
#include "core.h"



void PowerUpRenderComponent::Slot()
{
	CORE_RenderCenteredSprite(m_position, vec2(m_radius * 2.f, m_radius * 2.f), m_sprite);
}




void PowerUpRenderComponent::ReceiveMessage(Message* msg)
{
	NewPositionMessage* newPositionMessage = dynamic_cast<NewPositionMessage*>(msg);
	if (newPositionMessage)
	{
		m_position = newPositionMessage->newPos;
	}
}