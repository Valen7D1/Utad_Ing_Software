#include "powerUpColisionComponent.h"
#include "PlayerColisionComponent.h"
#include "message.h"
#include "entity.h"
#include "manager.h"



void PowerUpColisionComponent::Slot()
{
	Manager* manager = Manager::getInstance();

	PlayerColisionComponent* player = manager->getPlayer()->FindComponent<PlayerColisionComponent>();

	float maxDistance = (m_radius + player->GetRadius());

	float distanceX = abs(m_position.x - player->GetPosition().x);
	float distanceY = abs(m_position.y - player->GetPosition().y);

	// collision with player
	if (distanceX < maxDistance && distanceY < maxDistance)
	{
		m_collidedWithPlayer = true;
		entityOwner->toBeDeleted = true;
	}

	// collision with floor
	if (m_position.y <= (FLOOR + m_radius))
	{
		entityOwner->toBeDeleted = true;
	}
}

void PowerUpColisionComponent::ReceiveMessage(Message* msg)
{
	NewPositionMessage* newPositionMessage = dynamic_cast<NewPositionMessage*>(msg);
	if (newPositionMessage)
	{
		m_position = newPositionMessage->newPos;
	}
}