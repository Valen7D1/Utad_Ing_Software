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
#include "playerProjectileComponent.h"
#include "playerRenderComponent.h"
#include "renderComponent.h"
#include <iostream>
#include <vector>

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

Entity* Manager::getPlayer() {
	return player;
}

void Manager::ResetLevel()
{
	//for (int i = entities.size(); i <= 0; --i)
	while(entities.size() > 0)
	{
		delete entities[entities.size()-1];
		entities.pop_back();
	}
	CreateEntities();
}

// update for all game objects
void Manager::update()
{   
	if (player->toBeDeleted)
	{
		ResetLevel();
		CreatePlayers();
	}
	else
	{
		player->Slot();
	}

	std::vector<Entity*> tempEntities;

	for (auto it = entities.begin(); it != entities.end(); )
	{
		Entity* entity = *it;

		if (entity->toBeDeleted)
		{	
			it = entities.erase(it);
			tempEntities.push_back(entity);
		}
		else
		{
			entity->Slot();
			++it;
		}
	}


	for (auto it = tempEntities.begin(); it != tempEntities.end(); )
	{
		Entity* entity = *it;
		ColisionComponent* colisionComponent = entity->FindComponent<ColisionComponent>();

			vec2 Velocity = vec2(colisionComponent->GetVelocity().x, 170);

			vec2 Position = colisionComponent->GetPosition();
			float radius = colisionComponent->GetRadius();

			if (colisionComponent->GetRadius() > 8.f)
			{

				for (int i = 0; i < 2; i++) {
					Entity* ballEntity = new Entity();
					Velocity.x *= -1;
					ColisionComponent* colisionComponent = new ColisionComponent();
					colisionComponent->SetPosition(Position);
					colisionComponent->SetVelocity(Velocity);
					colisionComponent->SetRadius(radius / 2);
					colisionComponent->entityOwner = ballEntity;

					MovementComponent* movementComponent = new MovementComponent();
					movementComponent->SetPosition(Position);
					movementComponent->SetVelocity(Velocity);
					movementComponent->entityOwner = ballEntity;

					RenderComponent* renderComponent = new RenderComponent();
					renderComponent->SetGfx(entity->FindComponent<RenderComponent>()->GetId());
					renderComponent->SetPosition(Position);
					renderComponent->SetRadius(radius/2);
					renderComponent->entityOwner = ballEntity;

					ballEntity->AddComponent(movementComponent);
					ballEntity->AddComponent(colisionComponent);
					ballEntity->AddComponent(renderComponent);

					entities.push_back(ballEntity);
				}

			}
			it = tempEntities.erase(it);
			delete entity;

	}
}


// getter for timer
Timer* Manager::getTimer() 
{
    return &timer;
}


void Manager::CreateGame() 
{
	char readBuffer[1024];
	FILE* fp;
	fopen_s(&fp, entitiesFile, "rb");
	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	doc.ParseStream(is);
	CreatePlayers();
	CreateEntities();
}


void Manager::CreatePlayers()
{
	const rapidjson::Value& playerData = doc["Player"];

	player = new Entity();
	float playerRadius = playerData["radius"].GetFloat();
	vec2 playerPosition = vec2(playerData["position"].GetFloat(), FLOOR + playerRadius);
	float playerVelocity = playerData["speed"].GetFloat();
	unsigned int playerHP = playerData["hitPoints"].GetUint();

	PlayerColisionComponent* playerColision = new PlayerColisionComponent();
	playerColision->SetPosition(playerPosition);
	playerColision->SetRadius(playerRadius);
	playerColision->SetHitPoints(playerHP);
	playerColision->entityOwner = player;

	PlayerMovementComponent* playerMovement = new PlayerMovementComponent();
	playerMovement->SetPosition(playerPosition);
	playerMovement->SetVelocity(playerVelocity);
	playerMovement->SetRadius(playerRadius);
	playerMovement->entityOwner = player;

	PlayerRenderComponent* playerRender = new PlayerRenderComponent();
	playerRender->SetGfx(
		CORE_LoadPNG(playerData["spriteI"].GetString(), false),
		CORE_LoadPNG(playerData["spriteD"].GetString(), false));
	playerRender->SetHpGfx(CORE_LoadPNG("data/heart.png", false));
	playerRender->SetPosition(playerPosition);
	playerRender->SetRadius(playerRadius);
	playerRender->SetHitPoint(playerHP);
	playerRender->entityOwner = player;

	PlayerProjectileComponent* playerProjectileComponent = new PlayerProjectileComponent();
	playerProjectileComponent->SetGfx(CORE_LoadPNG("data/arrow.png", false));
	playerProjectileComponent->SetVelocity(300);
	playerProjectileComponent->SetRadius(playerRadius);
	playerProjectileComponent->SetPlayerPosition(playerPosition);
	playerProjectileComponent->entityOwner = player;

	player->AddComponent(playerColision);
	player->AddComponent(playerMovement);
	player->AddComponent(playerRender);
	player->AddComponent(playerProjectileComponent);
}


void Manager::CreateEntities() 
{
	const rapidjson::Value& ballData = doc["Ball"];


	Manager* manager = Manager::getInstance();
	RenderEngine* renderEngine = RenderEngine::getInstance();

	float minHeight = ballData["height"].GetArray()[0].GetFloat();
	float maxHeight = ballData["height"].GetArray()[1].GetFloat();

	float minWidth = ballData["width"].GetArray()[0].GetFloat();
	float maxWidth = ballData["width"].GetArray()[1].GetFloat();

	float ballSpeed = ballData["speed"].GetFloat();
	float radius = ballData["radius"].GetFloat();

	for (int i = 0; i < NUM_BALLS; i++) {
		Entity* ballEntity = new Entity();

		//vec2 Position = vec2(CORE_FRand(0.0, maxWidth), CORE_FRand(0.0, maxHeight));
		//vec2 Velocity = vec2(CORE_FRand(-ballSpeed, +ballSpeed), CORE_FRand(-ballSpeed, +ballSpeed));
		vec2 Velocity = vec2(CORE_FRand(-ballSpeed, ballSpeed),0);
		vec2 Position = vec2(CORE_FRand(maxWidth, minWidth), CORE_FRand(maxHeight, minHeight));

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
		renderComponent->SetGfx(CORE_LoadPNG(ballData["sprite"].GetString(), false));
		renderComponent->SetPosition(Position);
		renderComponent->SetRadius(radius);
		renderComponent->entityOwner = ballEntity;

		ballEntity->AddComponent(movementComponent);
		ballEntity->AddComponent(colisionComponent);
		ballEntity->AddComponent(renderComponent);

		entities.push_back(ballEntity);
	}
}