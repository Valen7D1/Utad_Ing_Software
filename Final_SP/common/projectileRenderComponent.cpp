#include "projectileRenderComponent.h"
#include "core.h"
#include "message.h"


void ProjectileRenderComponent::Slot()
{
	if (m_typeOfProjectile == 0) { RenderTrace(); }
	// render for main projectile
	CORE_RenderCenteredSprite(m_position, vec2(m_radius * 2.f, m_radius * 2.f), m_sprite);
}


void ProjectileRenderComponent::RenderTrace()
{
	int traceSize = static_cast<int>(round((m_position.y - m_startingPosition.y) / m_radius));
	vec2 currentPosition = m_startingPosition;
	for (int i = 0; i < traceSize; i++)
	{
		CORE_RenderCenteredSprite(currentPosition, vec2(m_radius, m_radius), m_trace);
		currentPosition.y += m_radius;
	}
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