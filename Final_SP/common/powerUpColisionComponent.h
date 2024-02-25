#pragma once
#include "component.h"


class PowerUpColisionComponent : public CollisionComponent
{
private:
	vec2 m_position;
	float m_radius;
	bool m_collidedWithPlayer = false;

public:
	virtual void Slot() override; 
	virtual void  ReceiveMessage(Message* msg) override;

	void SetPosition(vec2 newPosition) { m_position = newPosition; }
	void SetRadius(float newRadius) { m_radius = newRadius; }

	vec2 GetPosition() { return m_position; }
	float GetRadius() { return m_radius; }
	bool GetCollision() { return m_collidedWithPlayer; }
};