#pragma once
#include "component.h"


class PlayerProjectileComponent : public Component
{
private:
	std::vector<Entity*> m_projectiles;

	double timeLimit = 0.f;

	GLuint m_gfx;
	GLuint m_trace;
	float m_radius;
	float m_velocity;
	vec2 m_playerPosition;

	void CreateProjectile();

public:
	void Slot();
	void ReceiveMessage(Message* msg);

	//setters
	void SetVelocity(float newVelocity) { m_velocity = newVelocity; }
	void SetGfx(GLuint newGfx) { m_gfx = newGfx; }
	void SetTraceSprite(GLuint newGfx) { m_trace = newGfx; }
	void SetRadius(float newRadius) { m_radius = newRadius; }
	void SetPlayerPosition(vec2 newPlayerPosition) { m_playerPosition = newPlayerPosition; }

	//getters
	vec2 GetVelocity() { return m_velocity; }
	vec2 GetPlayerPosition() { return m_playerPosition; }
	GLuint GetId() { return m_gfx; }
	GLuint GetTraceSprite() { return m_trace; }
	float GetRadius() { return m_radius; }

	std::vector<Entity*> getProjectiles() { return m_projectiles; }

	virtual ~PlayerProjectileComponent() 
	{ 
		GLuint temp[2] = { m_gfx, m_gfx };
		glDeleteTextures(2, temp);
	}
};