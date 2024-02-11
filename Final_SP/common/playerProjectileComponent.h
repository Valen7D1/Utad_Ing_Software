#pragma once
#include "component.h"


class PlayerProjectileComponent : public Component
{
private:
	std::vector<Entity*> m_projectiles;

	double timeLimit = 0.f;

	GLuint m_gfx;
	float m_radius;
	float m_velocity;
	vec2 m_playerPosition;
	unsigned int m_clipSize;

	void CreateProjectile();

public:
	void Slot();
	void ReceiveMessage(Message* msg);

	//setters
	void SetVelocity(float newVelocity) { m_velocity = newVelocity; }
	void SetGfx(GLuint newGfx) { m_gfx = newGfx; }
	void SetRadius(float newRadius) { m_radius = newRadius; }
	void SetClipSize(unsigned int newClipSize) { m_clipSize = newClipSize; }
	void SetPlayerPosition(vec2 newPlayerPosition) { m_playerPosition = newPlayerPosition; };


	//getters
	vec2 GetVelocity() { return m_velocity; };

	vec2 GetPlayerPosition() { return m_playerPosition; };
	GLuint GetId() { return m_gfx; };

	float GetRadius() { return m_radius; };
	unsigned int GetClipSize() { return m_clipSize; };

	std::vector<Entity*> getProjectiles() { return m_projectiles; }
};