#include "colisionComponent.h"
#include "movementComponent.h"
#include "renderComponent.h"
#include "entity.h"
#include "global.h"
#include "sys.h"

void ColisionComponent::Slot() 
{
	//control vars for collision checking
	bool colliding = false;
	Entity* entityColliding = nullptr;
	ColisionComponent* otherEntityCollision = nullptr;

	Manager* manager = manager->getInstance();
	std::vector<Entity*> entities = manager->getEntities();

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
	else {

		entityOwner->FindComponent<RenderComponent>()->SetPosition(currentPos);
		entityOwner->FindComponent<MovementComponent>()->SetPosition(currentPos);


		vel = vel * -1.f;

		movementComponent->SetVelocity(movementComponent->GetVelocity() * -1.f);

		otherEntityCollision->SetVelocity(otherEntityCollision->GetVelocity()* - 1.f);

		MovementComponent* otherEntityMovement = entityColliding->FindComponent<MovementComponent>();
		otherEntityMovement->SetVelocity(otherEntityMovement->GetVelocity() * -1.f);
	}

	if ((currentPos.x > SCR_WIDTH) || (currentPos.x < 0)) {
		vel = vec2(vel.x * -1, vel.y);
		movementComponent->SetVelocity(vec2(movementComponent->GetVelocity().x * -1.f, movementComponent->GetVelocity().y));
	}
	if ((currentPos.y > SCR_HEIGHT) || (currentPos.y < 0)) {
		vel = vec2(vel.x, vel.y * -1);
		movementComponent->SetVelocity(vec2(movementComponent->GetVelocity().x, movementComponent->GetVelocity().y * -1.f));
	}
}