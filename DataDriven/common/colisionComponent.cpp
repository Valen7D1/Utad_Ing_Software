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

	for (Entity* otherEntity : entities)
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
	}

	if (!colliding) {
		currentPos = newPos;
	}
	// if collision ocurred
	else {
		// current poss sent to entity
		entityOwner->SendMsg(new EntCollisionMessage(currentPos));
		// same but only so that it changes direction
		entityColliding->SendMsg(new EntCollisionMessage(otherEntityCollision->GetPosition()));

		// call to render / movement to set the correct position (current instead of new)
		//entityOwner->FindComponent<RenderComponent>()->SetPosition(currentPos);
		//entityOwner->FindComponent<MovementComponent>()->SetPosition(currentPos);

		// reverse velocity for rebound
		//vel = vel * -1.f;

		//movementComponent->SetVelocity(movementComponent->GetVelocity() * -1.f);

		// same for collided entity in collision and movement
		//otherEntityCollision->SetVelocity(otherEntityCollision->GetVelocity()* - 1.f);

		//MovementComponent* otherEntityMovement = entityColliding->FindComponent<MovementComponent>();
		//otherEntityMovement->SetVelocity(otherEntityMovement->GetVelocity() * -1.f);
	}

	// if x2 collided with margins
	if ((currentPos.x > SCR_WIDTH) || (currentPos.x < 0)) {
		entityOwner->SendMsg(new LimitWorldCollMessage(vec2( -1, 1), currentPos));
		//vel = vec2(vel.x * -1, vel.y);
		//movementComponent->SetVelocity(vec2(movementComponent->GetVelocity().x * -1.f, movementComponent->GetVelocity().y));
	}
	if ((currentPos.y > SCR_HEIGHT) || (currentPos.y < 0)) {
		entityOwner->SendMsg(new LimitWorldCollMessage(vec2( 1, -1), currentPos));
		//vel = vec2(vel.x, vel.y * -1);
		//movementComponent->SetVelocity(vec2(movementComponent->GetVelocity().x, movementComponent->GetVelocity().y * -1.f));
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
}