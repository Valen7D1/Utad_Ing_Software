#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "../../../common/vector2d.h"
#include "../../../common/sys.h"

const unsigned int WORLD_WIDTH = 10;
const unsigned int WORLD_HEIGHT = 10;
const float TILE_WIDTH = SCR_WIDTH / WORLD_WIDTH;
const float TILE_HEIGHT = SCR_HEIGHT / WORLD_HEIGHT;


/** 
*	Class to represent the game playable world
*	It's composed by a matrix of terrains
*/

class Factory;
class TerrainFactory;
class Terrain;
class NewTerrain;

//deprecated class
class World
{
public:
	// Singleton accessor
	static World* Get();

	/** Method that generate the terrain randomly*/
	void GenerateTerrain();

	/** Delete terrain tiles and free the terrain textures*/
	void DestroyTerrain();
	std::vector<std::vector<Terrain*>> map;

private:
	World() { }

private:

	static World* m_WorldInstance;
};


// new class for world sim
class NewWorld
{
public:
	// Singleton accessor
	static NewWorld* Get();
	// call to generate and set tiles
	void Initialize();
	// create all the factory values for tiles vector
	void SetTileTypes();
	/** Method that generate the terrain randomly*/
	void GenerateTerrain();

	/** Delete terrain tiles and free the terrain textures*/
	void DestroyTerrain();
	std::vector<std::vector<NewTerrain*>> map;

	TerrainFactory* GetTile(int index) { return tiles[index]; }

private:
	NewWorld() { }

private:
	std::vector<TerrainFactory*> tiles;
	static NewWorld* m_WorldInstance;
};

// Initialization global data.
void InitGlobalData();
// Shutdown global data.
void ShutDownGlobalData();

#endif // !_GLOBAL_H_