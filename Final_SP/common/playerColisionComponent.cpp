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
	std::vector<Entity*> entities = manager->getEntities();
	std::vector<Entity*> platforms = manager->getPlatforms();
	std::vector<Entity*> ladders = manager->getLadders();

	bool collided = false;
	// collision with lateral walls
	if ((m_newPos.x > (SCR_WIDTH - m_radius / 2)) || (m_newPos.x < m_radius / 2)) {

		NewPositionMessage* newPositionMessage = new NewPositionMessage(m_position);
		entityOwner->SendMsg(newPositionMessage);
		delete newPositionMessage;
		collided = true;
	}

	// collision with floor
	if (m_newPos.y < (FLOOR + m_radius)) {
		m_position.y = FLOOR + m_radius;
		m_position.x = m_newPos.x;
		NewPositionMessage* newPositionMessage = new NewPositionMessage(m_position);
		entityOwner->SendMsg(newPositionMessage);
		delete newPositionMessage;

		NewOnSurfaceMessage* newOnSurfaceMessage = new NewOnSurfaceMessage(true);
		entityOwner->SendMsg(newOnSurfaceMessage);
		delete newOnSurfaceMessage;
		collided = true;
		collidedSurface = true;
	}

	// collision with other balls
	BallColisionComponent* otherEntityCollision = nullptr;
	for (Entity* otherEntity : entities)
	{
		otherEntityCollision = otherEntity->FindComponent<BallColisionComponent>();
		float maxDistance = (m_radius + otherEntityCollision->GetRadius());

		float distanceX = abs(m_position.x - otherEntityCollision->GetPosition().x);
		float distanceY = abs(m_position.y - otherEntityCollision->GetPosition().y);


		if (distanceX < maxDistance && distanceY < maxDistance)
		{
			HitControl();
			break;
		}
	}


	// collision with ladders
	LadderRenderComponent* platformData = nullptr;

	PlayerMovementComponent* pmov = entityOwner->FindComponent<PlayerMovementComponent>();

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
			NewOnLadderMessage* newOnLadderMessage = new NewOnLadderMessage(true);
			entityOwner->SendMsg(newOnLadderMessage);
			delete newOnLadderMessage;
			collidedLadder = true;
			if (pmov->m_onLadder){ m_position.y = m_newPos.y; }
			m_position.x = m_newPos.x;

			NewPositionMessage* newPositionMessage = new NewPositionMessage(m_position);
			entityOwner->SendMsg(newPositionMessage);
			delete newPositionMessage;

			collided = true;
		}
	}

	if (!collidedLadder)
	{
		for (Entity* platform : platforms)
		{
			PLatformRenderComponent* pData = platform->FindComponent<PLatformRenderComponent>();
			vec2 pPos = pData->GetPosition(); // platform position

			vec2 position = pData->GetPosition();
			vec2 size = pData->GetSize();

			float distanceX = abs(pPos.x - m_newPos.x);
			float distanceY = abs(pPos.y - m_newPos.y);

			float lastDistanceY = m_position.y - pPos.y;

			float maxDistanceX = abs(pData->GetSize().x / 2 + m_radius);
			float maxDistanceY = abs(pData->GetSize().y / 2 + m_radius);


			if (distanceX < maxDistanceX && distanceY <= maxDistanceY && lastDistanceY >= maxDistanceY)
			{

				m_position.y = pPos.y + pData->GetSize().y / 2 + m_radius;
				m_position.x = m_newPos.x;
				NewPositionMessage* newPositionMessage = new NewPositionMessage(m_position);
				entityOwner->SendMsg(newPositionMessage);
				delete newPositionMessage;

				NewOnSurfaceMessage* newOnSurfaceMessage = new NewOnSurfaceMessage(true);
				entityOwner->SendMsg(newOnSurfaceMessage);
				delete newOnSurfaceMessage;

				collided = true;
				collidedSurface = true;
			}
		}
	}


	if (!collidedLadder)
	{
		NewOnLadderMessage* newOnLadderMessage = new NewOnLadderMessage(false);
		entityOwner->SendMsg(newOnLadderMessage);
		delete newOnLadderMessage;
	}

	if (!collidedSurface)
	{
		NewOnSurfaceMessage* newOnSurfaceMessage = new NewOnSurfaceMessage(false);
		entityOwner->SendMsg(newOnSurfaceMessage);
		delete newOnSurfaceMessage;
	}


	if(!collided)
	{
		m_position = m_newPos;
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