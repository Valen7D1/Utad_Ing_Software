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
#include "sceneComponent.h"
#include <iostream>
#include <vector>

#include "Factory.h"

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
	m_CurrentLevel->CreateLevel();
}

// update for all game objects
void Manager::update()
{   
	if (player)
	{
		if (player->toBeDeleted)
		{
			ResetLevel();
		}
		else
		{
			player->Slot();
		}
	}

	std::vector<Entity*> tempEntities;

	for (auto it = entities.begin(); it != entities.end(); )
	{
		Entity* entity = *it;

		if (entity->toBeDeleted)
		{	
			// if its scene type means its time for level change
			if (entity->FindComponent<SceneLogicComponent>())
			{

			}
			else
			{
				it = entities.erase(it);
				tempEntities.push_back(entity);
			}
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

	m_CurrentLevel = new MainMenu();
	m_CurrentLevel->CreateLevel();
}