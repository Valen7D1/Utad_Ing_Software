#include "manager.h"
#include "Entity.h"
#include "core.h"
#include "sys.h"
#include "manager.h"
#include "renderEngine.h"
#include "movementComponent.h"
#include "colisionComponent.h"
#include "renderComponent.h"
#include <iostream>
#include "../swalib_example/rapidjson/document.h"
#include "../swalib_example/rapidjson/filereadstream.h"

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


	char readBuffer[1024];
	FILE* fp;
	fopen_s(&fp, entitiesFile, "rb");
	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	rapidjson::Document doc;
	doc.ParseStream(is);
	const rapidjson::Value& ballData = doc["BALL"];
	fclose(fp);

	Manager* manager = Manager::getInstance();
	RenderEngine* renderEngine = RenderEngine::getInstance();

	float maxWidth = ballData["MAX_BALL_POSITION"].GetArray()[0].GetFloat();
	float maxHeight = ballData["MAX_BALL_POSITION"].GetArray()[1].GetFloat();
	float ballSpeed = ballData["MAX_BALL_SPEED"].GetFloat();

	for (int i = 0; i < NUM_BALLS; i++) {
		Entity* ballEntity = new Entity();

		vec2 Position = vec2(CORE_FRand(0.0, maxWidth), CORE_FRand(0.0, maxHeight));
		vec2 Velocity = vec2(CORE_FRand(-ballSpeed, +ballSpeed), CORE_FRand(-ballSpeed, +ballSpeed));

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
		renderComponent->SetGfx(CORE_LoadPNG(ballData["SPRITE"].GetString(), false));
		renderComponent->SetPosition(Position);
		renderComponent->SetRadius(radius);
		renderComponent->entityOwner = ballEntity;

		ballEntity->AddComponent(movementComponent);
		ballEntity->AddComponent(colisionComponent);
		ballEntity->AddComponent(renderComponent);

		entities.push_back(ballEntity);
	}
}