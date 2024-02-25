#pragma once
#include "component.h"

class PowerUpRenderComponent : public RenderComponent
{
private:
	vec2 m_position;
	GLuint m_sprite;
	float m_radius;

public:
	virtual void Slot() override; // call render sprite
	virtual void  ReceiveMessage(Message* msg) override; //msg system for component comunication

	//setters
	void SetPosition(vec2 newPos) { m_position = newPos; }
	void SetGfx(GLuint newGfx) { m_sprite = newGfx; }
	void SetRadius(float newRadius) { m_radius = newRadius; }

	//getters
	vec2 GetPosition() { return m_position; }
	GLuint GetId() { return m_sprite; }
	float GetRadius() { return m_radius; }
};