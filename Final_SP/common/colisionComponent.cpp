#include "colisionComponent.h"
#include "movementComponent.h"
#include "renderComponent.h"
#include "platformRenderComponent.h"
#include "entity.h"
#include "manager.h"
#include "message.h"
#include <math.h>
#include "sys.h"

void ColisionComponent::Slot() 
{
	//control vars for collision checking
	bool colliding = false;
	Entity* entityColliding = nullptr;
	ColisionComponent* otherEntityCollision = nullptr;

	// call to entity vector for collision checking
	Manager* manager = manager->getInstance();
	std::vector<Entity*> entities = manager->getEntities();
	std::vector<Entity*> platforms = manager->getPlatforms();

	//platforms colision
	vec2 newVel; // if collided we need new vel
	for (Entity* platform: platforms)
	{
		PLatformRenderComponent* pData = platform->FindComponent<PLatformRenderComponent>();
		vec2 pPos = pData->GetPosition(); // platform position
		vec2 cornerPos = vec2(pPos.x + pData->GetSize().x/2, pPos.y + pData->GetSize().y / 2);

		// get angle from center to top right corner of platform
		float angle = atan2(cornerPos.y - pPos.y, cornerPos.x - pPos.x) * 180 / 3.14;
		float colisionAngle = atan2(newPos.y - pPos.y, newPos.x - pPos.x) * 180 / 3.14;;

		if (colisionAngle < 0) { colisionAngle += 360; }

		vec2 position = pData->GetPosition();
		vec2 size = pData->GetSize();

		float distanceX = abs(pPos.x - newPos.x);
		float distanceY = abs(pPos.y - newPos.y);

		float maxDistanceX = abs(pData->GetSize().x/2 + radius);
		float maxDistanceY = abs(pData->GetSize().y/2 + radius);

		if (distanceX < maxDistanceX && distanceY < maxDistanceY) 
		{
			colliding = true;
			// up collision
			if (colisionAngle > angle && colisionAngle < 180 - angle)
			{
				newVel = vec2(vel.x, -vel.y);
			}
			// down collision
			else if (colisionAngle > 180 + angle && colisionAngle < 360 + angle)
			{
				newVel = vec2(vel.x, -vel.y);
			}
			// left collision
			else if (colisionAngle >= 180 - angle && colisionAngle <= 180 + angle)
			{
				newVel = vec2(-vel.x, vel.y);
			}
			// right collision
			else if (colisionAngle >= 360 - angle || colisionAngle <= 0 + angle)
			{
				newVel = vec2(-vel.x, vel.y);
			}
			break;
		}
	}


	if (!colliding) {
		currentPos = newPos;
	}
	// if collision ocurred
	else {
		// current poss sent to entity
		//vel = newVel;
		entityOwner->SendMsg(new NewPositionMessage(currentPos));
		entityOwner->SendMsg(new NewVelocityMessage(newVel));
	}

	bool marginCollided = false;
	// if x2 collided with margins
	if ((currentPos.x > (SCR_WIDTH-radius/2)) || (currentPos.x < radius / 2)) {
		entityOwner->SendMsg(new LimitWorldCollMessage(vec2( -1, 1), currentPos));
		marginCollided = true;
	}
	if ((currentPos.y > SCR_HEIGHT) || (currentPos.y < FLOOR+radius)) {
		entityOwner->SendMsg(new LimitWorldCollMessage(vec2( 1, -1), currentPos));
		marginCollided = true;
	}
	if (!marginCollided && !colliding)
	{
		float addedVel = GRAVITY* manager->getTimer()->GetFrameTime();
		entityOwner->SendMsg(new NewVelocityMessage(vec2(vel.x, vel.y+addedVel)));
	}
}


void ColisionComponent::ReceiveMessage(Message* msg) 
{
	// if collision with entity
	EntCollisionMessage* entCollisionMessage = dynamic_cast<EntCollisionMessage*>(msg);
	if (entCollisionMessage)
	{
		currentPos = entCollisionMessage->newPos;
		vel = vel * (-1);
	}

	// if collision with world limits
	LimitWorldCollMessage* limitWorldCollMessage = dynamic_cast<LimitWorldCollMessage*>(msg);
	if (limitWorldCollMessage)
	{
		currentPos = limitWorldCollMessage->newPos;
		vel = vel * limitWorldCollMessage->entityDirection;
	}

	//if new position
	NewPositionMessage* newPositionMessage = dynamic_cast<NewPositionMessage*>(msg);
	if (newPositionMessage)
	{
		newPos = newPositionMessage->newPos;
	}

	// new velocity
	NewVelocityMessage* newVelocityMessage = dynamic_cast<NewVelocityMessage*>(msg);
	if (newVelocityMessage)
	{
		vel = newVelocityMessage->newVel;
	}
}