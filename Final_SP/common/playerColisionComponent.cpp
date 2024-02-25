#include "playerColisionComponent.h"
#include "playerMovementComponent.h"
#include "ballRenderComponent.h"
#include "ballColisionComponent.h"
#include "ladderRenderComponent.h"
#include "platformRenderComponent.h"
#include "entity.h"
#include "manager.h"
#include "message.h"
#include "sys.h"

void PlayerColisionComponent::Slot() 
{ 
	bool collidedSurface = false;
	bool collidedLadder = false;


	Manager* manager = manager->getInstance();

	// get all three entities for collision checking
	std::vector<Entity*> entities = manager->getEntities();
	std::vector<Entity*> platforms = manager->getPlatforms();
	std::vector<Entity*> ladders = manager->getLadders();

	// boolean for movement update
	bool collided = false;

	// collision with lateral walls
	if ((m_newPos.x >= (SCR_WIDTH - m_radius / 2)) || (m_newPos.x <= m_radius / 2)) 
	{
		m_position.y = m_newPos.y; // only need to update Y axis
		m_newPos.x = m_position.x; // fix X newPos for later checkings
		collided = true;
	}

	// collision with floor
	if (m_newPos.y <= (FLOOR + m_radius)) 
	{
		m_position.y = FLOOR + m_radius; // fix Y position and update X position
		m_position.x = m_newPos.x;
		m_newPos.y = m_position.y; // fix Y newPos for later checkings
		 
		collided = true;
		collidedSurface = true;
	}

	// collision with other balls
	BallColisionComponent* otherEntityCollision = nullptr;
	for (Entity* otherEntity : entities)
	{
		otherEntityCollision = otherEntity->FindComponent<BallColisionComponent>();
		if (otherEntityCollision)
		{
			float maxDistance = (m_radius + otherEntityCollision->GetRadius());

			float distanceX = abs(m_position.x - otherEntityCollision->GetPosition().x);
			float distanceY = abs(m_position.y - otherEntityCollision->GetPosition().y);


			if (distanceX < maxDistance && distanceY < maxDistance)
			{
				HitControl(); // level reset or death
				break;
			}
		}
	}


	// collision with ladders
	LadderRenderComponent* platformData = nullptr;
	
	bool WasOnLadder = entityOwner->FindComponent<PlayerMovementComponent>()->m_onLadder;

	for (Entity* ladder : ladders)
	{
		platformData = ladder->FindComponent<LadderRenderComponent>();

		vec2 pos = platformData->GetPosition();

		float radX = platformData->GetRadius()/2;
		float radY = platformData->GetRadius();

		float distanceX = abs(pos.x - m_position.x);
		float distanceY = abs(pos.y - m_position.y);

		if (distanceX <= radX && distanceY <= radY)
		{
			// only if was on ladder apply new Y move
			// else you would be applying gravity
			if (WasOnLadder)
			{ 
				m_position.y = m_newPos.y; 
			}
			m_position.x = m_newPos.x;

			collided = true;
			collidedLadder = true;
		}
	}

	if (!collidedLadder)
	{
		for (Entity* platform : platforms)
		{
			PLatformRenderComponent* pData = platform->FindComponent<PLatformRenderComponent>();
			vec2 pPos = pData->GetPosition();

			vec2 position = pData->GetPosition();
			vec2 size = pData->GetSize();

			float distanceX = abs(pPos.x - m_newPos.x);
			float distanceY = abs(pPos.y - m_newPos.y);

			float lastDistanceY = m_position.y - pPos.y;

			float maxDistanceX = abs(pData->GetSize().x / 2 + m_radius);
			float maxDistanceY = abs(pData->GetSize().y / 2 + m_radius);


			if (distanceX < maxDistanceX && distanceY <= maxDistanceY && lastDistanceY >= maxDistanceY)
			{
				// get Y position just above collision
				m_position.y = pPos.y + pData->GetSize().y / 2 + m_radius;
				m_position.x = m_newPos.x;

				collided = true;
				collidedSurface = true;
			}
		}
	}

	// update movement booleans
	NewOnLadderMessage* newOnLadderMessage = new NewOnLadderMessage(collidedLadder);
	entityOwner->SendMsg(newOnLadderMessage);
	delete newOnLadderMessage;

	NewOnSurfaceMessage* newOnSurfaceMessage = new NewOnSurfaceMessage(collidedSurface);
	entityOwner->SendMsg(newOnSurfaceMessage);
	delete newOnSurfaceMessage;

	// if not collided apply gravity and X movement
	if(!collided)
	{
		m_position = m_newPos;
	}
	else
	{
		// new position based on adjustments made by collisions
		NewPositionMessage* newPositionMessage = new NewPositionMessage(m_position);
		entityOwner->SendMsg(newPositionMessage);
		delete newPositionMessage;
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