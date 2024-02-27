#pragma once
#include "component.h"


class PlayerProjectileComponent : public ProjectileComponent
{
private:
	std::vector<Entity*> m_projectiles;

	double timeLimit = 0.f;

	GLuint m_gfx;
	GLuint m_trace;

	float m_radius;
	vec2 m_velocity;

	unsigned int m_maxBullets = 1;
	unsigned int m_typeOfProjectile = 0;

	vec2 m_playerPosition;

	void CreateProjectile(); // selects projectile to be created
	void BasicThreat(); // one projectile
	void TrippleThreat(); // 3 projectiles no trace

public:
	void Slot();
	void ReceiveMessage(Message* msg);

	//setters
	void SetVelocity(vec2 newVelocity) { m_velocity = newVelocity; }
	void SetGfx(GLuint newGfx) { m_gfx = newGfx; }
	void SetTraceSprite(GLuint newGfx) { m_trace = newGfx; }
	void SetRadius(float newRadius) { m_radius = newRadius; }
	void SetPlayerPosition(vec2 newPlayerPosition) { m_playerPosition = newPlayerPosition; }
	void SetNumberOfProjectiles() { m_maxBullets += 1; }
	void SetTypeOfProjectile(unsigned int newType) { m_typeOfProjectile = newType; }

	//getters
	vec2 GetVelocity() { return m_velocity; }
	vec2 GetPlayerPosition() { return m_playerPosition; }
	GLuint GetId() { return m_gfx; }
	GLuint GetTraceSprite() { return m_trace; }
	float GetRadius() { return m_radius; }
	unsigned int GetTypeOfProjectile() { return m_typeOfProjectile; }

	std::vector<Entity*> getProjectiles() { return m_projectiles; }



	virtual ~PlayerProjectileComponent() 
	{ 
		GLuint temp[2] = { m_gfx, m_gfx };
		glDeleteTextures(2, temp);
	}
};