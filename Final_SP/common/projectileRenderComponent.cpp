#include "projectileRenderComponent.h"
#include "core.h"
#include "message.h"


void ProjectileRenderComponent::Slot()
{
	CORE_RenderCenteredSprite(m_position, vec2(m_radius * 2.f, m_radius * 2.f), m_sprite);
	CORE_RenderCenteredSprite(m_startingPosition, vec2(m_radius, m_radius), m_trace);

}

void ProjectileRenderComponent::ReceiveMessage(Message* msg)
{
	//if new position
	NewPositionMessage* newPositionMessage = dynamic_cast<NewPositionMessage*>(msg);
	if (newPositionMessage)
	{
		m_position = newPositionMessage->newPos;
	}

	// current position != new position from colision component
	// we cast to father so we only get the position (we dont care for velocity)
	CollisionMessage* collisionMessage = dynamic_cast<CollisionMessage*>(msg);
	if (collisionMessage)
	{
		m_position = collisionMessage->newPos;
	}
}