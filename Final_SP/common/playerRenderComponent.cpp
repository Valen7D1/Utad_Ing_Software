#include "playerRenderComponent.h"
#include "playerProjectileComponent.h"
#include "projectileRenderComponent.h"
#include "entity.h"
#include "core.h"
#include "message.h"
#include "sys.h"


void PlayerRenderComponent::Slot()
{
	// render player
	CORE_RenderCenteredSprite(m_position, vec2(m_radius * 2.f, m_radius * 2.f), m_gfx[m_direction]);

	float heartLocation = m_radius+16;

	// render hearts
	for (unsigned int i = 0; i<m_hitPoints; ++i)
	{
		CORE_RenderCenteredSprite(vec2(heartLocation, SCR_HEIGHT - m_radius-16), vec2(m_radius * 1.5f, m_radius * 1.5f), m_HpGfx);
		heartLocation += m_radius * 2;
	}

	std::vector<Entity*> projectiles = entityOwner->FindComponent<PlayerProjectileComponent>()->getProjectiles();

	for (Entity* projectil : projectiles)
	{
		projectil->FindComponent<ProjectileRenderComponent>()->Slot();
	}
	
}

void PlayerRenderComponent::ReceiveMessage(Message* msg)
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

	NewHitPointsMessage* newHitPointsMessage = dynamic_cast<NewHitPointsMessage*>(msg);
	if (newHitPointsMessage)
	{
		m_hitPoints = newHitPointsMessage->newHP;
	}

	NewDirectionMessage* newDirectionMessage = dynamic_cast<NewDirectionMessage*>(msg);
	if (newDirectionMessage)
	{
		m_direction = newDirectionMessage->newDir;
	}

}