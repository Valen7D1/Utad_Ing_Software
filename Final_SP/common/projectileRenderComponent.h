#pragma once
#include "component.h"

class ProjectileRenderComponent : public RenderComponent
{
private:
	vec2 m_position;
	vec2 m_startingPosition;
	GLuint m_sprite;
	GLuint m_trace;
	float m_radius;
	unsigned int m_typeOfProjectile;

public:
	virtual void Slot() override; // call render sprite
	virtual void  ReceiveMessage(Message* msg) override; //msg system for component comunication
	virtual void RenderTrace();

	//setters
	void SetPosition(vec2 newPos) { m_position = newPos; }
	void SetStartingPosition(vec2 newStartingPosition) { m_startingPosition = newStartingPosition; }
	void SetGfx(GLuint newGfx) { m_sprite = newGfx; }
	void SetTraceSprite(GLuint newGfx) { m_trace = newGfx; }
	void SetRadius(float newRadius) { m_radius = newRadius; }
	void SetTypeOfProjectile(unsigned int newType) { m_typeOfProjectile = newType; }

	//getters
	vec2 GetPosition() { return m_position; }
	GLuint GetId() { return m_sprite; }
	GLuint GetTraceSprite() { return m_trace; }
	float GetRadius() { return m_radius; }
	vec2 GetStartingPosition() { return m_startingPosition; }
	unsigned int GetTypeOfProjectile() { return m_typeOfProjectile; }
};