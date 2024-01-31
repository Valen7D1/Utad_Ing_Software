#pragma once
#include "../../../common/vector2d.h"
#include "../../../common/stdafx.h"
#include "../../../common/core.h"

class TerrainFactory {

public:
	TerrainFactory(int navCost, GLuint gfx) :
		m_navCost(navCost), 
		m_gfx(gfx){}

	// getters
	int GetNavCost() const { return m_navCost; }
	GLuint GetSprite() const { return m_gfx; };

private:
	int m_navCost;
	GLuint m_gfx;
};


class SandFactory : public TerrainFactory {
public:
	SandFactory() :
		TerrainFactory(1, CORE_LoadPNG("data/Sand.png", true)) {}
};


class WaterFactory : public TerrainFactory {
public:
	WaterFactory() :
		TerrainFactory(2, CORE_LoadPNG("data/Water.png", true)) {}
};


class AcidFactory: public TerrainFactory{
public:
	AcidFactory() : 
		TerrainFactory(3, CORE_LoadPNG("data/Acid.png", true)){}
};
