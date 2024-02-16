#include "projectileMovementComponent.h"
#include "projectileColisionComponent.h"
#include "platformRenderComponent.h"
#include "renderComponent.h"
#include "colisionComponent.h"
#include "entity.h"
#include "manager.h"
#include "message.h"
#include "sys.h"

void ProjectileColisionComponent::Slot() 
{ 
	Manager* manager = manager->getInstance();
	std::vector<Entity*> entities = manager->getEntities();
	std::vector<Entity*> platforms = manager->getPlatforms();


	ColisionComponent* otherEntityCollision = nullptr;
	bool colliding = false;
	// collision with balls
	for (Entity* otherEntity : entities)
	{
		if (entityOwner != otherEntity)
		{
			otherEntityCollision = otherEntity->FindComponent<ColisionComponent>();
			float limit2 = (m_radius + otherEntityCollision->GetRadius()) * (m_radius + otherEntityCollision->GetRadius());

			if (vlen2(m_position - otherEntityCollision->GetPosition()) <= limit2) {
				colliding = true;
				otherEntityCollision->entityOwner->toBeDeleted = true;
				break;
			}
		}
	}

	// collision with platforms

	for (Entity* platform : platforms)
	{
		PLatformRenderComponent* pData = platform->FindComponent<PLatformRenderComponent>();
		vec2 pPos = pData->GetPosition(); // platform position
		vec2 cornerPos = vec2(pPos.x + pData->GetSize().x / 2, pPos.y + pData->GetSize().y / 2);

		// get angle from center to top right corner of platform
		float angle = static_cast<float>(atan2(cornerPos.y - pPos.y, cornerPos.x - pPos.x) * 180 / 3.14);
		float colisionAngle = static_cast<float>(atan2(m_position.y - pPos.y, m_position.x - pPos.x) * 180 / 3.14);

		if (colisionAngle < 0) { colisionAngle += 360; }

		vec2 position = pData->GetPosition();
		vec2 size = pData->GetSize();

		float distanceX = abs(pPos.x - m_position.x);
		float distanceY = abs(pPos.y - m_position.y);

		float maxDistanceX = abs(pData->GetSize().x / 2 + m_radius);
		float maxDistanceY = abs(pData->GetSize().y / 2 + m_radius);

		if (distanceX < maxDistanceX && distanceY < maxDistanceY)
		{
			colliding = true;
			break;
		}
	}

	if ((m_position.y > SCR_HEIGHT) || (m_position.y < FLOOR) || colliding) {
		entityOwner->toBeDeleted = true;
	}
}

void ProjectileColisionComponent::ReceiveMessage(Message* msg) 
{
	//if new position
	NewPositionMessage* newPositionMessage = dynamic_cast<NewPositionMessage*>(msg);
	if (newPositionMessage)
	{
		m_position = newPositionMessage->newPos;
	}
}