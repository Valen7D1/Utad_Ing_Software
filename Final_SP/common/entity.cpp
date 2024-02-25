#include "renderEngine.h"
#include "entity.h"
#include "message.h"
#include "manager.h"
#include "component.h"


#include "ballRenderComponent.h"
#include "ballColisionComponent.h"
#include "ballMovementComponent.h"

#include "powerUpMovementComponent.h"
#include "powerUpColisionComponent.h"
#include "powerUpRenderComponent.h"



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

	// if big enough to split
	if (radius > 8.f)
	{
		// split in two
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

	// get powerUp data
	/*const rapidjson::Value& powerUpData = manager->doc["Ball"];

	float powerUpRadius = powerUpData["radius"].GetArray()[0].GetFloat();
	float speed = powerUpData["speed"].GetArray()[0].GetFloat();
	const rapidjson::Value& powerUpSprites = powerUpData["sprite"];*/


	float powerUpRadius = 16.f;
	float speed = -100.f;

	// booster spawn chance depend on the size of the ball destroyed
	float probability;
	if (radius >= 32) { probability = 1.f; }
	else if (radius >= 16) { probability = 1.f; }
	else { probability = 1.f; }

	if (CORE_FRand(0.f, 1.f) <= probability)
	{
		int whichOne = rand() % (2 + 1);
		GLuint powerUpSprite;

		Entity* powerUpEntity = new HealthBoostPowerUp();

		switch (whichOne) {
		case 0:
			powerUpEntity = new HealthBoostPowerUp();
			powerUpSprite = CORE_LoadPNG("data/ball.png", true);
			break;
		case 1:
			powerUpEntity = new MagazineBoostPowerUp();
			powerUpSprite = CORE_LoadPNG("data/trace.png", true);
			break;
		case 2:
			powerUpEntity = new TrippleThreatPowerUp();
			powerUpSprite = CORE_LoadPNG("data/ball128.png", true);
			break;
		default:
			powerUpEntity = new HealthBoostPowerUp();
			powerUpSprite = CORE_LoadPNG("data/ball.png", true);
			break;
		}


		PowerUpMovementComponent* movementComponent = new PowerUpMovementComponent();
		movementComponent->SetPosition(position);
		movementComponent->SetVelocity(vec2(0, speed));
		movementComponent->entityOwner = powerUpEntity;

		PowerUpColisionComponent* collisionComponent = new PowerUpColisionComponent();
		collisionComponent->SetPosition(position);
		collisionComponent->SetRadius(powerUpRadius);
		collisionComponent->entityOwner = powerUpEntity;

		PowerUpRenderComponent* renderComponent = new PowerUpRenderComponent();
		renderComponent->SetGfx(powerUpSprite);
		renderComponent->SetPosition(position);
		renderComponent->SetRadius(powerUpRadius);
		renderComponent->entityOwner = powerUpEntity;

		powerUpEntity->AddComponent(movementComponent);
		powerUpEntity->AddComponent(collisionComponent);
		powerUpEntity->AddComponent(renderComponent);

		manager->addPowerUp(powerUpEntity);
	}
}


// only apply boost if collided with player
void TrippleThreatPowerUp::Destroy()
{
	PowerUpColisionComponent* powerUp = FindComponent<PowerUpColisionComponent>();

	if (FindComponent<PowerUpColisionComponent>()->GetCollision())
	{

	}

}

void HealthBoostPowerUp::Destroy()
{
	PowerUpColisionComponent* powerUp = FindComponent<PowerUpColisionComponent>();
	if (FindComponent<PowerUpColisionComponent>()->GetCollision())
	{

	}

}

void MagazineBoostPowerUp::Destroy()
{
	PowerUpColisionComponent* powerUp = FindComponent<PowerUpColisionComponent>();
	if (FindComponent<PowerUpColisionComponent>()->GetCollision())
	{

	}

}
