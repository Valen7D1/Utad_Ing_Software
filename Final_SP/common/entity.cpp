#include "entity.h"
#include "message.h"
#include "manager.h"
#include "component.h"

#include "ballRenderComponent.h"
#include "ballColisionComponent.h"
#include "ballMovementComponent.h"



void Entity::Slot()
{
	for (Component* component : components)
	{
		if (components.size() <= 0 && !component) { break; }

		if (!dynamic_cast<RenderComponent*>(component))
		{
			component->Slot();
		}
	}

}

//name sendMsg because internally SendMessage is already in use
void Entity::SendMsg(Message* msg)
{
	for (Component* component : components) 
	{
		component->ReceiveMessage(msg);
	}
}


Entity::~Entity()
{
	while (components.size() > 0)
	{
		delete components[components.size() - 1];
		components.pop_back();
	}
}


void BallEntity::Destroy()
{
	Manager* manager = Manager::getInstance();
	BallColisionComponent* component = FindComponent<BallColisionComponent>();
	
	float radius = component->GetRadius();
	vec2 velocity = component->GetVelocity();
	vec2 position = component->GetPosition();

	if (radius > 8.f)
	{

		for (int i = 0; i < 2; i++) {
			Entity* ballEntity = new BallEntity();
			velocity.x *= -1;
			BallColisionComponent* colisionComponent = new BallColisionComponent();
			colisionComponent->SetPosition(position);
			colisionComponent->SetVelocity(vec2(velocity.x, 170));
			colisionComponent->SetRadius(radius / 2);
			colisionComponent->entityOwner = ballEntity;

			BallMovementComponent* movementComponent = new BallMovementComponent();
			movementComponent->SetPosition(position);
			movementComponent->SetVelocity(vec2(velocity.x, 170));
			movementComponent->entityOwner = ballEntity;

			BallRenderComponent* renderComponent = new BallRenderComponent();
			renderComponent->SetGfx(FindComponent<BallRenderComponent>()->GetId());
			renderComponent->SetPosition(position);
			renderComponent->SetRadius(radius / 2);
			renderComponent->entityOwner = ballEntity;

			ballEntity->AddComponent(movementComponent);
			ballEntity->AddComponent(colisionComponent);
			ballEntity->AddComponent(renderComponent);

			manager->addEntity(ballEntity);
		}

	}
}


// i was gonna use this but I didnt have time at the end 
// so... yeah xd

void PlayerEntity::Destroy()
{

}


void PlatformEntity::Destroy()
{

}


void SceneEntity::Destroy()
{

}


void BulletEntity::Destroy()
{

}


void LadderEntity::Destroy()
{
}
