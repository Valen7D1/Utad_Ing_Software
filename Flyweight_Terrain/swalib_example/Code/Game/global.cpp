#include "../../../common/stdafx.h"
#include "../../../common/core.h"
#include "global.h"
#include <stdlib.h>
#include "terrain.h"
#include "factory.h"
#include <random>


void InitGlobalData()
{
	//World::Get()->GenerateTerrain();
    NewWorld::Get()->Initialize();
}


void ShutDownGlobalData()
{
    //World::Get()->DestroyTerrain();
    NewWorld::Get()->DestroyTerrain();
}


//////////////////////////////////////////////////////////////////////////
/// WORLD
//////////////////////////////////////////////////////////////////////////


World* World::m_WorldInstance = nullptr;


World* World::Get()
{
	if (m_WorldInstance == nullptr)
	{
		m_WorldInstance = new World;
	}
	return m_WorldInstance;
}


void World::DestroyTerrain()
{
}


void World::GenerateTerrain()
{   
    
    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define the range
    std::uniform_int_distribution<int> distribution(1, 3);
    GLuint sprite;
    // Generate a random value between 1 and 3
    for (int i = 0; i < WORLD_WIDTH; ++i) {
        std::vector<Terrain*> row;
        for (int j = 0; j < WORLD_HEIGHT; ++j) {
            int randomValue = distribution(gen);

            if (randomValue == 1){ sprite = CORE_LoadPNG("data/Acid.png", true); }
            else if (randomValue == 2) { sprite = CORE_LoadPNG("data/Sand.png", true); }
            else { sprite = CORE_LoadPNG("data/Water.png", true); }

            Terrain* terrain = new Terrain(randomValue, vec2(i * 64.f + 32.f, j * 48.f + 24.f), sprite);
            row.push_back(terrain);
        }
        map.push_back(row);
    }
}



//////////////////////////////////////////////////////////////////////////
/// NEW WORLD
//////////////////////////////////////////////////////////////////////////



NewWorld* NewWorld::m_WorldInstance = nullptr;


NewWorld* NewWorld::Get()
{
    if (m_WorldInstance == nullptr)
    {
        m_WorldInstance = new NewWorld;
    }
    return m_WorldInstance;
}


void NewWorld::DestroyTerrain()
{
}


void NewWorld::GenerateTerrain()
{

    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define the range
    std::uniform_int_distribution<int> distribution(0, 2);
    TerrainFactory* terrainFactory;

    // Generate a random value between 1 and 3
    for (int i = 0; i < WORLD_WIDTH; ++i) {
        std::vector<NewTerrain*> row;
        for (int j = 0; j < WORLD_HEIGHT; ++j) {

            int randomValue = distribution(gen);

            terrainFactory = tiles[randomValue];

            NewTerrain* terrain = new NewTerrain(
                vec2(i * TILE_WIDTH + TILE_WIDTH/2, j * TILE_HEIGHT + TILE_HEIGHT/2),
                terrainFactory);
            row.push_back(terrain);
        }
        map.push_back(row);
    }
}



void NewWorld::Initialize()
{
    SetTileTypes();
    GenerateTerrain();
}


void NewWorld::SetTileTypes()
{
    tiles.push_back(new SandFactory());
    tiles.push_back(new WaterFactory());
    tiles.push_back(new AcidFactory());
}
