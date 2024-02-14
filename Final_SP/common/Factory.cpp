#include "Factory.h"
#include "manager.h"
#include "renderEngine.h"

#include "movementComponent.h"
#include "colisionComponent.h"
#include "playerMovementComponent.h"
#include "playerColisionComponent.h"
#include "playerProjectileComponent.h"
#include "playerRenderComponent.h"
#include "renderComponent.h"
#include "entity.h"


void BaseLevel::CreatePlayer()
{
	Manager* manager = Manager::getInstance();
	RenderEngine* renderEngine = RenderEngine::getInstance();
	const rapidjson::Value& playerData = manager->doc["Player"];

	manager->player = new Entity();
	float playerRadius = playerData["radius"].GetFloat();
	vec2 playerPosition = vec2(playerData["position"].GetFloat(), FLOOR + playerRadius);
	float playerVelocity = playerData["speed"].GetFloat();
	unsigned int playerHP = playerData["hitPoints"].GetUint();

	PlayerColisionComponent* playerColision = new PlayerColisionComponent();
	playerColision->SetPosition(playerPosition);
	playerColision->SetRadius(playerRadius);
	playerColision->SetHitPoints(playerHP);
	playerColision->entityOwner = manager->player;

	PlayerMovementComponent* playerMovement = new PlayerMovementComponent();
	playerMovement->SetPosition(playerPosition);
	playerMovement->SetVelocity(playerVelocity);
	playerMovement->SetRadius(playerRadius);
	playerMovement->entityOwner = manager->player;

	PlayerRenderComponent* playerRender = new PlayerRenderComponent();
	playerRender->SetGfx(
		CORE_LoadPNG(playerData["spriteI"].GetString(), false),
		CORE_LoadPNG(playerData["spriteD"].GetString(), false));
	playerRender->SetHpGfx(CORE_LoadPNG("data/heart.png", false));
	playerRender->SetPosition(playerPosition);
	playerRender->SetRadius(playerRadius);
	playerRender->SetHitPoint(playerHP);
	playerRender->entityOwner = manager->player;

	PlayerProjectileComponent* playerProjectileComponent = new PlayerProjectileComponent();
	playerProjectileComponent->SetGfx(CORE_LoadPNG("data/arrow.png", false));
	playerProjectileComponent->SetVelocity(300);
	playerProjectileComponent->SetRadius(playerRadius);
	playerProjectileComponent->SetPlayerPosition(playerPosition);
	playerProjectileComponent->entityOwner = manager->player;

	manager->player->AddComponent(playerColision);
	manager->player->AddComponent(playerMovement);
	manager->player->AddComponent(playerRender);
	manager->player->AddComponent(playerProjectileComponent);
}


void Level1::CreateLevel()
{
	Manager* manager = Manager::getInstance();
	RenderEngine* renderEngine = RenderEngine::getInstance();

	const rapidjson::Value& ballData = manager->doc["Ball"];

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
		vec2 Velocity = vec2(CORE_FRand(-ballSpeed, ballSpeed), 0);
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

		manager->entities.push_back(ballEntity);
	}
}

void Level2::CreateLevel()
{
	Manager* manager = Manager::getInstance();
	RenderEngine* renderEngine = RenderEngine::getInstance();
}