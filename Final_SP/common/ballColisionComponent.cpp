#include "ballColisionComponent.h"
#include "ballMovementComponent.h"
#include "ballRenderComponent.h"
#include "platformRenderComponent.h"
#include "entity.h"
#include "manager.h"
#include "message.h"
#include <math.h>
#include "sys.h"

void BallColisionComponent::Slot()
{
	//control vars for collision checking
	bool colliding = false;
	Entity* entityColliding = nullptr;
	BallColisionComponent* otherEntityCollision = nullptr;

	// call to entity vector for collision checking
	Manager* manager = manager->getInstance();
	std::vector<Entity*> entities = manager->getEntities();
	std::vector<Entity*> platforms = manager->getPlatforms();

	//platforms colision
	vec2 newVel = m_velocity; // if collided we need new vel
	for (Entity* platform: platforms)
	{
		PLatformRenderComponent* pData = platform->FindComponent<PLatformRenderComponent>();
		vec2 pPos = pData->GetPosition(); // platform position
		vec2 cornerPos = vec2(pPos.x + pData->GetSize().x/2, pPos.y + pData->GetSize().y / 2);

		// get angle from center to top right corner of platform
		float angle = static_cast<float>(atan2(cornerPos.y - pPos.y, cornerPos.x - pPos.x) * 180 / 3.14);
		float colisionAngle = static_cast<float>(atan2(m_newPos.y - pPos.y, m_newPos.x - pPos.x) * 180 / 3.14);

		// change angle from -180:180 format to 0-360 format
		if (colisionAngle < 0) { colisionAngle += 360; }

		vec2 position = pData->GetPosition();
		vec2 size = pData->GetSize();

		// distance from platform
		float distanceX = abs(pPos.x - m_newPos.x);
		float distanceY = abs(pPos.y - m_newPos.y);
		// max distance for collision to be true
		float maxDistanceX = abs(pData->GetSize().x/2 + m_radius);
		float maxDistanceY = abs(pData->GetSize().y/2 + m_radius);

		if (distanceX < maxDistanceX && distanceY < maxDistanceY) 
		{
			colliding = true;
			// up collision
			if (colisionAngle >= angle && colisionAngle <= 180 - angle)
			{
				if (newVel.y < 0) { newVel.y *= -1; } 
			}
			// down collision
			if (colisionAngle >= 180 + angle && colisionAngle <= 360 - angle)
			{
				if (newVel.y > 0) { newVel.y *= -1; }
			}
			// left collision
			if (colisionAngle >= 180 - angle && colisionAngle <= 180 + angle)
			{
				if (newVel.x > 0) { newVel.x *= -1; }
			}
			// right collision
			if (colisionAngle >= 360 - angle || colisionAngle <= 0 + angle)
			{
				if (newVel.x < 0) { newVel.x *= -1; }
			}
			break;
		}
	}

	// if not collided update position definitely
	if (!colliding) {
		m_currentPos = m_newPos;
	}
	// if collision ocurred
	else {
		m_currentPos += m_velocity *manager->getTimer()->GetFrameTime();
		NewPositionMessage* newPositionMessage = new NewPositionMessage(m_currentPos);
		NewVelocityMessage* newVelocityMessage = new NewVelocityMessage(newVel);

		entityOwner->SendMsg(newPositionMessage);
		entityOwner->SendMsg(newVelocityMessage);

		delete newVelocityMessage;
		delete newPositionMessage;
	}

	// collisions with margins
	bool marginCollided = false;
	// side margins
	if ((m_currentPos.x > (SCR_WIDTH- m_radius /2)) || (m_currentPos.x < m_radius / 2)) {

		LimitWorldCollMessage* limitWorldCollMessage = new LimitWorldCollMessage(vec2(-1, 1), m_currentPos);
		entityOwner->SendMsg(limitWorldCollMessage);
		delete limitWorldCollMessage;
		marginCollided = true;
	}
	// up / down margins
	if ((m_currentPos.y > SCR_HEIGHT) || (m_currentPos.y < FLOOR+ m_radius)) {
		LimitWorldCollMessage* limitWorldCollMessage = new LimitWorldCollMessage(vec2(1, -1), m_currentPos);
		entityOwner->SendMsg(limitWorldCollMessage);
		delete limitWorldCollMessage;
		marginCollided = true;
	}

	// apply gravity if not collided
	if (!marginCollided && !colliding)
	{
		float addedVel = GRAVITY* manager->getTimer()->GetFrameTime();
		NewVelocityMessage* newVelocityMessage = new NewVelocityMessage(vec2(m_velocity.x, m_velocity.y + addedVel));
		entityOwner->SendMsg(newVelocityMessage);
		delete newVelocityMessage;
	}
}


void BallColisionComponent::Divide()
{
	// get manager for entities list
	Manager* manager = Manager::getInstance();
	if (m_radius > 8.f)
	{
		// split ball into two with +/- X velocity and radius/2
		for (int i = 0; i < 2; i++) {
			Entity* ballEntity = new BallEntity();
			m_velocity.x *= -1;
			BallColisionComponent* colisionComponent = new BallColisionComponent();
			colisionComponent->SetPosition(m_currentPos);
			colisionComponent->SetVelocity(vec2(m_velocity.x, 170));
			colisionComponent->SetRadius(m_radius / 2);
			colisionComponent->entityOwner = ballEntity;

			BallMovementComponent* movementComponent = new BallMovementComponent();
			movementComponent->SetPosition(m_currentPos);
			movementComponent->SetVelocity(vec2(m_velocity.x, 170));
			movementComponent->entityOwner = ballEntity;

			BallRenderComponent* renderComponent = new BallRenderComponent();
			renderComponent->SetGfx(entityOwner->FindComponent<BallRenderComponent>()->GetId());
			renderComponent->SetPosition(m_currentPos);
			renderComponent->SetRadius(m_radius / 2);
			renderComponent->entityOwner = ballEntity;

			ballEntity->AddComponent(movementComponent);
			ballEntity->AddComponent(colisionComponent);
			ballEntity->AddComponent(renderComponent);

			manager->addEntity(ballEntity);
		}

	}
}


void BallColisionComponent::ReceiveMessage(Message* msg)
{
	// if collision with entity
	EntCollisionMessage* entCollisionMessage = dynamic_cast<EntCollisionMessage*>(msg);
	if (entCollisionMessage)
	{
		m_currentPos = entCollisionMessage->newPos;
		m_velocity = m_velocity * (-1);
	}

	// if collision with world limits
	LimitWorldCollMessage* limitWorldCollMessage = dynamic_cast<LimitWorldCollMessage*>(msg);
	if (limitWorldCollMessage)
	{
		m_currentPos = limitWorldCollMessage->newPos;
		m_velocity = m_velocity * limitWorldCollMessage->entityDirection;
	}

	//if new position
	NewPositionMessage* newPositionMessage = dynamic_cast<NewPositionMessage*>(msg);
	if (newPositionMessage)
	{
		m_newPos = newPositionMessage->newPos;
	}

	// new velocity
	NewVelocityMessage* newVelocityMessage = dynamic_cast<NewVelocityMessage*>(msg);
	if (newVelocityMessage)
	{
		m_velocity = newVelocityMessage->newVel;
	}
}