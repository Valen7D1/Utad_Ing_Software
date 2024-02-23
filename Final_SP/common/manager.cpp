#include "manager.h"
#include "Entity.h"
#include "core.h"
#include "sys.h"
#include "manager.h"
#include "renderEngine.h"
#include "ballMovementComponent.h"
#include "ballColisionComponent.h"
#include "playerMovementComponent.h"
#include "playerColisionComponent.h"
#include "playerProjectileComponent.h"
#include "playerRenderComponent.h"
#include "ballRenderComponent.h"
#include "sceneComponent.h"
#include <iostream>
#include <vector>
#include "message.h"
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
std::vector<Entity*> Manager::getEntities() { return entities; }

void Manager::addEntity(Entity* entity) { entities.push_back(entity); }

std::vector<Entity*> Manager::getPlatforms() { return platforms; }
std::vector<Entity*> Manager::getLadders() { return ladders; }

Entity* Manager::getPlayer() { return player; }

void Manager::ResetLevel()
{
	//for (int i = entities.size(); i <= 0; --i)
	if (player)
	{
		delete player;
		player = nullptr;
	}
	while(entities.size() > 0)
	{
		delete entities[entities.size()-1];
		entities.pop_back();
	}

	while (platforms.size() > 0)
	{
		delete platforms[platforms.size() - 1];
		platforms.pop_back();
	}
	m_CurrentLevel->CreateLevel();
}

// update for all game objects
void Manager::update()
{   
	// reset level
	if (reset == 1)
	{
		unsigned int hp = player->FindComponent<PlayerColisionComponent>()->GetHitPoints();
		ResetLevel();
		NewHitPointsMessage* newHitPointsMessage = new NewHitPointsMessage(hp);
		player->SendMsg(newHitPointsMessage);
		delete newHitPointsMessage;
		reset = 0;
	}
	// player update
	if (player)
	{
		if (player->toBeDeleted)
		{
			delete m_CurrentLevel;
			m_CurrentLevel = new DeathMenu();
			ResetLevel();
		}
		else
		{
			player->Slot();
		}
	}

	// entities update
	std::vector<Entity*> tempEntities;

	if (entities.size() <= 0)
	{
		m_CurrentLevel = m_CurrentLevel->NextLevel();
		ResetLevel();
	}

	for (auto it = entities.begin(); it != entities.end(); )
	{
		Entity* entity = *it;

		if (entity->toBeDeleted)
		{	
			// if its scene type means its time for level change
			if (entity->FindComponent<SceneLogicComponent>())
			{
				m_CurrentLevel = m_CurrentLevel->NextLevel();
				ResetLevel();
				break;
			}
			else // collided balls
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
		entity->Destroy();
		it = tempEntities.erase(it);
		delete entity;
	}
}


// getter for timer
Timer* Manager::getTimer() 
{
    return &timer;
}

void Manager::SetReset(int value)
{
	reset = value;
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