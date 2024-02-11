#include "colisionComponent.h"
#include "movementComponent.h"
#include "renderComponent.h"
#include "entity.h"
#include "manager.h"
#include "message.h"
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
	// get movement component from owner for movement if collided
	MovementComponent* movementComponent = entityOwner->FindComponent<MovementComponent>();

	/*for (Entity* otherEntity : entities)
	{
		if (entityOwner != otherEntity)
		{
			otherEntityCollision = otherEntity->FindComponent<ColisionComponent>();
			float limit2 = (radius + otherEntityCollision->GetRadius()) * (radius + otherEntityCollision->GetRadius());

			if (vlen2(newPos - otherEntityCollision->GetPosition()) <= limit2) {
				colliding = true;
				entityColliding = otherEntity;
				break;
			}
		}
	}*/

	if (!colliding) {
		currentPos = newPos;
	}
	// if collision ocurred
	else {
		// current poss sent to entity
		entityOwner->SendMsg(new EntCollisionMessage(currentPos));
		// same but only so that it changes direction
		entityColliding->SendMsg(new EntCollisionMessage(otherEntityCollision->GetPosition()));
	}

	bool marginCollided = false;
	// if x2 collided with margins
	if ((currentPos.x > (SCR_WIDTH-radius/2)) || (currentPos.x < radius / 2)) {
		entityOwner->SendMsg(new LimitWorldCollMessage(vec2( -1, 1), currentPos));
		marginCollided = true;
	}
	if ((currentPos.y > SCR_HEIGHT) || (currentPos.y < FLOOR)) {
		entityOwner->SendMsg(new LimitWorldCollMessage(vec2( 1, -1), currentPos));
		marginCollided = true;
	}
	if (!marginCollided)
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