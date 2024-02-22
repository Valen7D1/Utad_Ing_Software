#include "playerColisionComponent.h"
#include "playerMovementComponent.h"
#include "ballRenderComponent.h"
#include "ballColisionComponent.h"
#include "ladderRenderComponent.h"
#include "entity.h"
#include "manager.h"
#include "message.h"
#include "sys.h"

void PlayerColisionComponent::Slot() 
{ 

	Manager* manager = manager->getInstance();
	std::vector<Entity*> entities = manager->getEntities();
	std::vector<Entity*> platforms = manager->getPlatforms();

	BallColisionComponent* otherEntityCollision = nullptr;

	for (Entity* otherEntity : entities)
	{
		otherEntityCollision = otherEntity->FindComponent<BallColisionComponent>();
		float limit2 = (m_radius + otherEntityCollision->GetRadius()) * (m_radius + otherEntityCollision->GetRadius());

		if (vlen2(m_position - otherEntityCollision->GetPosition()) <= limit2) {
			//otherEntity->toBeDeleted = true;
			HitControl();
			break;
		}
	}


	LadderRenderComponent* platformData = nullptr;
	for (Entity* platform : platforms)
	{
		platformData = platform->FindComponent<LadderRenderComponent>();

		vec2 pos = platformData->GetPosition();
		float rad = platformData->GetRadius();

		float distanceX = abs(pos.x - m_position.x);
		float distanceY = abs(pos.y - m_position.y);

		if (distanceX <= rad && distanceY <= rad)
		{
			NewOnLadderMessage* newOnLadderMessage = new NewOnLadderMessage(true);
			entityOwner->SendMsg(newOnLadderMessage);
			delete newOnLadderMessage;
		}
	}
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
		NewHitPointsMessage* newHitPointsMessage = new NewHitPointsMessage(m_hitPoints);
		entityOwner->SendMsg(newHitPointsMessage);
		Manager::getInstance()->SetReset(1);
		delete newHitPointsMessage;
	}
}


void PlayerColisionComponent::ReceiveMessage(Message* msg) 
{ 
	//if new position
	NewPositionMessage* newPositionMessage = dynamic_cast<NewPositionMessage*>(msg);
	if (newPositionMessage)
	{
		m_newPos = newPositionMessage->newPos;
	}

	NewHitPointsMessage* newHitPointsMessage = dynamic_cast<NewHitPointsMessage*>(msg);
	if (newHitPointsMessage)
	{
		m_hitPoints = newHitPointsMessage->newHP;
	}
}