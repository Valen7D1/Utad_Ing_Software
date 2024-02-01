#include "manager.h"
#include "Entity.h"
#include "core.h"
#include "sys.h"
#include "manager.h"
#include "renderEngine.h"
#include "movementComponent.h"
#include "colisionComponent.h"
#include "renderComponent.h"

// instantiate manager to nullptr
Manager* Manager::instance = nullptr;

Manager* Manager::getInstance() 
{   
    // if not created already then create it
    if (instance == nullptr)
    {
        instance = new Manager();
    }
    return instance;
}

// getter for balls vector
std::vector<Entity*> Manager::getEntities() {
    return entities;
}

// update for all game objects
void Manager::update() const
{   
    Manager* manager = Manager::getInstance();
    std::vector<Entity*> entities = manager->getEntities();

    for (Entity* entity : entities) {
        entity->Slot();
    }
}

// getter for timer
Timer* Manager::getTimer() {
    return &timer;
}

void Manager::CreateEntities() {
	Manager* manager = Manager::getInstance();
	RenderEngine* renderEngine = RenderEngine::getInstance();

	for (int i = 0; i < NUM_BALLS; i++) {
		Entity* ballEntity = new Entity();

		vec2 Position = vec2(CORE_FRand(0.0, SCR_WIDTH), CORE_FRand(0.0, SCR_HEIGHT));
		vec2 Velocity = vec2(CORE_FRand(
			-MAX_BALL_SPEED, 
			+MAX_BALL_SPEED),
			CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED));

		float radius = 16.f;

		ColisionComponent* colisionComponent = new ColisionComponent();
		colisionComponent->SetPosition(Position);
		colisionComponent->SetVelocity(Velocity);
		colisionComponent->SetRadius(radius);
		colisionComponent->entityOwner = ballEntity;

		MovementComponent* movementComponent = new MovementComponent();
		movementComponent->SetPosition(Position);
		movementComponent->SetVelocity(Velocity);
		movementComponent->entityOwner = ballEntity;

		RenderComponent* renderComponent = new RenderComponent();
		renderComponent->SetGfx(renderEngine->GetSprite()->getTexsmallball());
		renderComponent->SetPosition(Position);
		renderComponent->SetRadius(radius);
		renderComponent->entityOwner = ballEntity;

		ballEntity->AddComponent(colisionComponent);
		ballEntity->AddComponent(movementComponent);
		ballEntity->AddComponent(renderComponent);

		entities.push_back(ballEntity);
	}
}