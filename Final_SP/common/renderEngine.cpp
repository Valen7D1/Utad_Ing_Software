#include "renderEngine.h"
#include "manager.h"
#include "entity.h"
#include "renderComponent.h"
#include "playerRenderComponent.h"
#include "PlayerColisionComponent.h"
#include "playerProjectileComponent.h"
#include "platformRenderComponent.h"
#include "sceneComponent.h"
#include <math.h>


RenderEngine* RenderEngine::instance = nullptr;


RenderEngine* RenderEngine::getInstance()
{
	// if not created already then create it
	if (instance == nullptr) {instance = new RenderEngine();}
	return instance;
}


void RenderEngine::RenderSetUp() {
	// Set up rendering.
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); // Sets up clipping.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// Specifies clear values for the color buffers.
	glMatrixMode(GL_PROJECTION);	// Specifies projection matrix is the current matrix.
	glLoadIdentity();	// Replaces the current matrix with the identity matrix.
	glOrtho(0.0, SCR_WIDTH, 0.0, SCR_HEIGHT, 0.0, 1.0);	// Multiplies the current matrix by an orthographic matrix.
	glEnable(GL_TEXTURE_2D);	// Enabling two-dimensional texturing.
	glEnable(GL_BLEND);	// Blend the incoming RGBA color values with the values in the color buffers.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Blend func. for alpha color.
}


void RenderEngine::TexturesSetting() {
	// Load textures
	GetSprite()->setBackgroundSprite(CORE_LoadPNG("data/back.png", true));
}


void RenderEngine::RenderObjects(){

	// render background
	CORE_RenderCenteredSprite(vec2(SCR_WIDTH/2, SCR_HEIGHT/2), vec2(SCR_WIDTH, SCR_HEIGHT), GetSprite()->getBackgroundSprite());


	float distance = FLOOR/2;
	for (int i = 0; i<10; ++i)
	{
		CORE_RenderCenteredSprite(vec2(distance, FLOOR/2), vec2(FLOOR, FLOOR), CORE_LoadPNG("data/tile.png", true));
		distance += FLOOR;
	}

	// get manager for balls render and timer data getters
	Manager* manager = Manager::getInstance();

	std::vector<Entity*> entities = manager->getEntities();
	std::vector<Entity*> platforms = manager->getPlatforms();
	Entity* player = manager->getPlayer();

	// for every object render it using its location and radius values
	// maybe get a get all objects?
	for (Entity* entity : entities) 
	{
		RenderComponent * renderComponent = entity->FindComponent<RenderComponent>();
		if (renderComponent){ renderComponent->Slot(); }

		SceneRenderComponent* sceneRenderComponent = entity->FindComponent<SceneRenderComponent>();
		if (sceneRenderComponent) { sceneRenderComponent->Slot(); }
	}

	if (player)
	{
		PlayerRenderComponent* playerRenderComponent = player->FindComponent<PlayerRenderComponent>();
		playerRenderComponent->Slot();

		PlayerProjectileComponent* playerProjectileComponent = player->FindComponent<PlayerProjectileComponent>();
		std::vector<Entity*> projectiles = playerProjectileComponent->getProjectiles();
		for (Entity* projectile : projectiles)
		{
			RenderComponent* renderComponent = projectile->FindComponent<RenderComponent>();
			renderComponent->Slot();
		}
	}
	//if (manager->platforms != nullptr){}
	//for (auto item = manager->platforms.begin(); item != manager->platforms.end(); )
	for (Entity* platform : platforms)

	{
		//Entity* platform = *item;
		PLatformRenderComponent* platformRender = platform->FindComponent<PLatformRenderComponent>();
		platformRender->Slot();
	}
}


void RenderEngine::RenderText() 
{
	Manager* manager = Manager::getInstance();
	Entity* player = manager->getPlayer();
	if (manager->getPlatforms().size() > 0 &&
		manager->getEntities().size() > 0)
	{
		Entity* platform = manager->getPlatforms()[0];
		Entity* ball = manager->getEntities()[0];

		RenderComponent* renderBall = ball->FindComponent<RenderComponent>();
		PLatformRenderComponent* renderPlatform = platform->FindComponent<PLatformRenderComponent>();

		if (player) {
			PlayerRenderComponent* renderPlayer = player->FindComponent<PlayerRenderComponent>();

			vec2 platlPos = renderPlatform->GetPosition();
			vec2 ballPos = renderBall->GetPosition();
			vec2 playerPos = renderPlayer->GetPosition();


			float angle = atan2(ballPos.y - platlPos.y, ballPos.x - platlPos.x) * 180 / 3.14;;

			if (angle < 0) { angle += 360; }
			//float angle = atan2(0 - -1, 0 - 0) * 180 / 3.14;;

			// Frames per second
			char fpsString[50] = { 0 };
			snprintf(fpsString, 50, "ANGLE:%f", angle);
			FONT_DrawString(vec2(0, SCR_HEIGHT - 16), fpsString);
		}
	}
}