#pragma once
#include "component.h"


class BallColisionComponent : public CollisionComponent
{
private:
	vec2 m_currentPos;
	vec2 m_newPos; // temporary position for collision control
	vec2 m_velocity;
	float m_radius;
public:
	virtual void Slot() override; // checks collisions and acts acordingly
	void Divide(); // when collided with projectile split in two
	virtual void  ReceiveMessage(Message* msg) override; //msg system for component comunication

	// setters
	void SetPosition(vec2 newPosition) { m_newPos = newPosition; }
	void SetVelocity(vec2 newVelocity) { m_velocity = newVelocity; }
	void SetRadius(float newRadius) { m_radius = newRadius; }
	// getters
	vec2 GetPosition() { return m_currentPos; }
	vec2 GetVelocity() { return m_velocity; }
	float GetRadius() { return m_radius; }

};