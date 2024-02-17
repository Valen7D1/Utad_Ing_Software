#include "Factory.h"
#include "manager.h"
#include "renderEngine.h"

#include "ballMovementComponent.h"
#include "ballColisionComponent.h"
#include "playerMovementComponent.h"
#include "playerColisionComponent.h"
#include "playerProjectileComponent.h"
#include "playerRenderComponent.h"
#include "ballRenderComponent.h"
#include "entity.h"
#include "sceneComponent.h"
#include "platformRenderComponent.h"

//cosos mios
//[150, 200],
//[250, 350],
//[350, 250],
//[420, 150],
//[450, 350]

void BaseLevel::CreatePlayer()
{
	Manager* manager = Manager::getInstance();
	RenderEngine* renderEngine = RenderEngine::getInstance();
	const rapidjson::Value& playerData = manager->doc["Player"];

	manager->player = new PlayerEntity();
	float playerRadius = playerData["radius"].GetFloat();
	vec2 playerPosition = vec2(playerData["position"].GetFloat(), FLOOR + playerRadius);
	float playerVelocity = playerData["speed"].GetFloat();
	unsigned int playerHP = playerData["hitPoints"].GetUint();

	PlayerMovementComponent* playerMovement = new PlayerMovementComponent();
	playerMovement->SetPosition(playerPosition);
	playerMovement->SetVelocity(playerVelocity);
	playerMovement->SetRadius(playerRadius);
	playerMovement->entityOwner = manager->player;

	PlayerColisionComponent* playerColision = new PlayerColisionComponent();
	playerColision->SetPosition(playerPosition);
	playerColision->SetRadius(playerRadius);
	playerColision->SetHitPoints(playerHP);
	playerColision->entityOwner = manager->player;

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
	playerProjectileComponent->SetGfx(CORE_LoadPNG(playerData["arrow"].GetString(), false));
	playerProjectileComponent->SetTraceSprite(CORE_LoadPNG(playerData["trace"].GetString(), false));
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
	CreatePlayer();

	Manager* manager = Manager::getInstance();
	RenderEngine* renderEngine = RenderEngine::getInstance();

	// get balls data
	const rapidjson::Value& ballData = manager->doc["Ball"];

	float minHeight = ballData["height"].GetArray()[0].GetFloat();
	float maxHeight = ballData["height"].GetArray()[1].GetFloat();

	float minWidth = ballData["width"].GetArray()[0].GetFloat();
	float maxWidth = ballData["width"].GetArray()[1].GetFloat();

	float ballSpeed = ballData["speed"].GetFloat();
	float radius = ballData["radius"].GetFloat();

	// create balls
	for (int i = 0; i < 1; i++) {
		Entity* ballEntity = new BallEntity();

		vec2 Velocity = vec2(CORE_FRand(-ballSpeed, ballSpeed), 0);
		vec2 Position = vec2(CORE_FRand(maxWidth, minWidth), CORE_FRand(maxHeight, minHeight));

		BallMovementComponent* movementComponent = new BallMovementComponent();
		movementComponent->SetPosition(Position);
		movementComponent->SetVelocity(Velocity);
		movementComponent->entityOwner = ballEntity;

		BallColisionComponent* colisionComponent = new BallColisionComponent();
		colisionComponent->SetPosition(Position);
		colisionComponent->SetVelocity(Velocity);
		colisionComponent->SetRadius(radius);
		colisionComponent->entityOwner = ballEntity;

		BallRenderComponent* renderComponent = new BallRenderComponent();
		renderComponent->SetGfx(CORE_LoadPNG(ballData["sprite"].GetString(), false));
		renderComponent->SetPosition(Position);
		renderComponent->SetRadius(radius);
		renderComponent->entityOwner = ballEntity;

		ballEntity->AddComponent(movementComponent);
		ballEntity->AddComponent(colisionComponent);
		ballEntity->AddComponent(renderComponent);

		manager->entities.push_back(ballEntity);
	}


	// get platforms data

	const rapidjson::Value& platformData = manager->doc["Platform"];

	// all platforms to be created
	std::vector<vec2> platforms;
	const rapidjson::Value& platformPositions = platformData["position"];
	for (unsigned int i = 0; i < platformPositions.Size(); i++) {
		platforms.push_back(vec2(
			platformPositions.GetArray()[i][0].GetFloat(),
			platformPositions.GetArray()[i][1].GetFloat()));
	}

	float platformWidth = platformData["width"].GetFloat();
	float platformHeight = platformData["height"].GetFloat();
	vec2 proportions = vec2(
		platformData["size"].GetArray()[0].GetFloat(),
		platformData["size"].GetArray()[1].GetFloat()
	);

	// create platforms
	// loop using position array as control

	for (auto item = platforms.begin(); item != platforms.end(); )
	{
		vec2 position = *item;
		Entity* platformEntity = new PlatformEntity();

		PLatformRenderComponent* pLatformRenderComponent = new PLatformRenderComponent();
		pLatformRenderComponent->SetPosition(position);
		pLatformRenderComponent->SetSize(vec2(platformWidth, platformHeight));
		pLatformRenderComponent->SetProportions(proportions);
		pLatformRenderComponent->SetSprite(CORE_LoadPNG(platformData["sprite"].GetString(), false));

		platformEntity->AddComponent(pLatformRenderComponent);

		manager->platforms.push_back(platformEntity);
		++item;
	}
}


void Level2::CreateLevel()
{
	CreatePlayer();

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
		Entity* ballEntity = new BallEntity();

		vec2 Velocity = vec2(CORE_FRand(-ballSpeed, ballSpeed), 0);
		vec2 Position = vec2(CORE_FRand(maxWidth, minWidth), CORE_FRand(maxHeight, minHeight));

		BallColisionComponent* colisionComponent = new BallColisionComponent();
		colisionComponent->SetPosition(Position);
		colisionComponent->SetVelocity(Velocity);
		colisionComponent->SetRadius(radius);
		colisionComponent->entityOwner = ballEntity;

		BallMovementComponent* movementComponent = new BallMovementComponent();
		movementComponent->SetPosition(Position);
		movementComponent->SetVelocity(Velocity);
		movementComponent->entityOwner = ballEntity;

		BallRenderComponent* renderComponent = new BallRenderComponent();
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


void DeathMenu::CreateLevel()
{
	Manager* manager = Manager::getInstance();
	RenderEngine* renderEngine = RenderEngine::getInstance();

	const rapidjson::Value& deathData = manager->doc["DeathMenu"];

	Entity* DeathScene = new SceneEntity();

	SceneLogicComponent* sceneLogicComponent = new SceneLogicComponent();
	sceneLogicComponent->entityOwner = DeathScene;

	SceneRenderComponent* sceneRenderComponent = new SceneRenderComponent();
	sceneRenderComponent->SetSprite(CORE_LoadPNG(deathData["sprite"].GetString(), false));
	sceneRenderComponent->entityOwner = DeathScene;

	DeathScene->AddComponent(sceneLogicComponent);
	DeathScene->AddComponent(sceneRenderComponent);

	manager->entities.push_back(DeathScene);
}


void MainMenu::CreateLevel()
{
	Manager* manager = Manager::getInstance();
	RenderEngine* renderEngine = RenderEngine::getInstance();

	const rapidjson::Value& mainMenuData = manager->doc["MainMenu"];

	Entity* MainMenuScene = new SceneEntity();

	SceneLogicComponent* sceneLogicComponent = new SceneLogicComponent();
	sceneLogicComponent->entityOwner = MainMenuScene;

	SceneRenderComponent* sceneRenderComponent = new SceneRenderComponent();
	sceneRenderComponent->SetSprite(CORE_LoadPNG(mainMenuData["sprite"].GetString(), false));
	sceneRenderComponent->entityOwner = MainMenuScene;

	MainMenuScene->AddComponent(sceneLogicComponent);
	MainMenuScene->AddComponent(sceneRenderComponent);

	manager->entities.push_back(MainMenuScene);
}

void WinMenu::CreateLevel()
{
	Manager* manager = Manager::getInstance();
	RenderEngine* renderEngine = RenderEngine::getInstance();

	const rapidjson::Value& winData = manager->doc["WinScene"];

	Entity* WinScene = new SceneEntity();

	SceneLogicComponent* sceneLogicComponent = new SceneLogicComponent();
	sceneLogicComponent->entityOwner = WinScene;

	SceneRenderComponent* sceneRenderComponent = new SceneRenderComponent();
	sceneRenderComponent->SetSprite(CORE_LoadPNG(winData["sprite"].GetString(), false));
	sceneRenderComponent->entityOwner = WinScene;


	WinScene->AddComponent(sceneLogicComponent);
	WinScene->AddComponent(sceneRenderComponent);

	manager->entities.push_back(WinScene);
}

BaseLevel* MainMenu::NextLevel() { return new Level1(); }
BaseLevel* Level1::NextLevel() { return new Level2(); }
BaseLevel* Level2::NextLevel() { return new Level1(); }
BaseLevel* DeathMenu::NextLevel() { return new WinMenu(); }
BaseLevel* WinMenu::NextLevel() { return new Level1(); }