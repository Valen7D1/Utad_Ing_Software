#include "playerColisionComponent.h"
#include "playerMovementComponent.h"
#include "renderComponent.h"
#include "colisionComponent.h"
#include "entity.h"
#include "manager.h"
#include "message.h"
#include "sys.h"

void PlayerColisionComponent::Slot() 
{ 

	Manager* manager = manager->getInstance();
	std::vector<Entity*> entities = manager->getEntities();

	ColisionComponent* otherEntityCollision = nullptr;

	for (Entity* otherEntity : entities)
	{
		otherEntityCollision = otherEntity->FindComponent<ColisionComponent>();
		float limit2 = (m_radius + otherEntityCollision->GetRadius()) * (m_radius + otherEntityCollision->GetRadius());

		if (vlen2(m_position - otherEntityCollision->GetPosition()) <= limit2) {
			//otherEntity->toBeDeleted = true;
			HitControl();
			break;
		}
	}

	/*if ((currentPos.x > (SCR_WIDTH - radius / 2)) || (currentPos.x < radius / 2)) {
		entityOwner->SendMsg(new LimitWorldCollMessage(vec2(-1, 1), currentPos));
		marginCollided = true;
	}*/
}


void PlayerColisionComponent::HitControl()
{
	--m_hitPoints;
	if (m_hitPoints <= 0)
	{
		entityOwner->toBeDeleted = true;
	}
	else 
	{
		entityOwner->SendMsg(new NewHitPointsMessage(m_hitPoints));
		Manager::getInstance()->SetReset(1);
	}
}


void PlayerColisionComponent::ReceiveMessage(Message* msg) 
{ 
	//if new position
	NewPositionMessage* newPositionMessage = dynamic_cast<NewPositionMessage*>(msg);
	if (newPositionMessage)
	{
		m_position = newPositionMessage->newPos;
	}

	NewHitPointsMessage* newHitPointsMessage = dynamic_cast<NewHitPointsMessage*>(msg);
	if (newHitPointsMessage)
	{
		m_hitPoints = newHitPointsMessage->newHP;
	}
}