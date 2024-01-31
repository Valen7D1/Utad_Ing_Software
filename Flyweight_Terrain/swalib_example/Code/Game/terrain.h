#pragma once
#include "../../../common/vector2d.h"
#include "../../../common/stdafx.h"

// deprecated class terrain
class Terrain {

public:
	Terrain(int navCost, vec2 position, GLuint gfx) :
		m_navCost(navCost), 
		m_position(position), 
		m_gfx(gfx){}

	// getters
	int GetNavCost() { return m_navCost; }
	vec2 GetPosition() { return m_position; }
	GLuint GetSprite() { return m_gfx; };

private:
	int m_navCost;
	vec2 m_position;
	GLuint m_gfx;

};

class TerrainFactory;

class NewTerrain {

public:
	NewTerrain(vec2 position, TerrainFactory* terrainType) :
		m_position(position), 
		m_terrainType(terrainType){}

	// getters
	vec2 GetPosition() { return m_position; }
	TerrainFactory* GetTerrrain() { return m_terrainType; }

private:
	vec2 m_position;
	TerrainFactory* m_terrainType;

};
