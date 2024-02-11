#include "projectileMovementComponent.h"
#include "projectileColisionComponent.h"
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

	ColisionComponent* otherEntityCollision = nullptr;


	for (Entity* otherEntity : entities)
	{
		if (entityOwner != otherEntity)
		{
			otherEntityCollision = otherEntity->FindComponent<ColisionComponent>();
			float limit2 = (m_radius + otherEntityCollision->GetRadius()) * (m_radius + otherEntityCollision->GetRadius());

			if (vlen2(m_position - otherEntityCollision->GetPosition()) <= limit2) {
				entityOwner->toBeDeleted = true;
				otherEntityCollision->entityOwner->toBeDeleted = true;
				break;
			}
		}
	}

	if ((m_position.y > SCR_HEIGHT) || (m_position.y < FLOOR)) {
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