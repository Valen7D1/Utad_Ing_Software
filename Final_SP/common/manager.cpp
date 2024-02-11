#include "manager.h"
#include "Entity.h"
#include "core.h"
#include "sys.h"
#include "manager.h"
#include "renderEngine.h"
#include "movementComponent.h"
#include "colisionComponent.h"
#include "playerMovementComponent.h"
#include "playerColisionComponent.h"
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

std::vector<Entity*> Manager::getPlayers() {
	return players;
}

// update for all game objects
void Manager::update() const
{   
    Manager* manager = Manager::getInstance();
    std::vector<Entity*> entities = manager->getEntities();

    for (Entity* entity : entities) {
        entity->Slot();
    }

	for (Entity* player : players) {
		player->Slot();
	}
}

// getter for timer
Timer* Manager::getTimer() 
{
    return &timer;
}


void Manager::CreateGame() 
{
	CreatePlayers();
	CreateEntities();
}


void Manager::CreatePlayers()
{
	Entity* playerEntity = new Entity();

	vec2 playerPosition = vec2(320, 100);
	float playerRadius = 16;
	float playerVelocity = 200;

	PlayerColisionComponent* playerColision = new PlayerColisionComponent();
	playerColision->SetPosition(playerPosition);
	playerColision->SetRadius(playerRadius);
	playerColision->entityOwner = playerEntity;

	PlayerMovementComponent* playerMovement = new PlayerMovementComponent();
	playerMovement->SetPosition(playerPosition);
	playerMovement->SetVelocity(playerVelocity);
	playerMovement->SetRadius(playerRadius);
	playerMovement->entityOwner = playerEntity;

	RenderComponent* renderComponent = new RenderComponent();
	renderComponent->SetGfx(CORE_LoadPNG("data/tyrian_ball.png", false));
	renderComponent->SetPosition(playerPosition);
	renderComponent->SetRadius(playerRadius);
	renderComponent->entityOwner = playerEntity;

	playerEntity->AddComponent(playerColision);
	playerEntity->AddComponent(playerMovement);
	playerEntity->AddComponent(renderComponent);

	players.push_back(playerEntity);

}


void Manager::CreateEntities() 
{


	char readBuffer[1024];
	FILE* fp;
	fopen_s(&fp, entitiesFile, "rb");
	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	rapidjson::Document doc;
	doc.ParseStream(is);
	const rapidjson::Value& ballData = doc["BALL"];


	Manager* manager = Manager::getInstance();
	RenderEngine* renderEngine = RenderEngine::getInstance();

	float maxWidth = ballData["MAX_BALL_POSITION"].GetArray()[0].GetFloat();
	float maxHeight = ballData["MAX_BALL_POSITION"].GetArray()[1].GetFloat();
	float ballSpeed = ballData["MAX_BALL_SPEED"].GetFloat();

	for (int i = 0; i < NUM_BALLS; i++) {
		Entity* ballEntity = new Entity();

		//vec2 Position = vec2(CORE_FRand(0.0, maxWidth), CORE_FRand(0.0, maxHeight));
		//vec2 Velocity = vec2(CORE_FRand(-ballSpeed, +ballSpeed), CORE_FRand(-ballSpeed, +ballSpeed));
		vec2 Velocity = vec2(-100,0);
		vec2 Position = vec2(250, 350);

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