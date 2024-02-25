#pragma once
#include "component.h"


class ProjectileMovementComponent : public MovementComponent
{
private:
	vec2 m_position;
	vec2 m_velocity;
	unsigned int m_typeOfProjectile;

public:
	// update position based on velocity
	virtual void Slot() override;
	virtual void  ReceiveMessage(Message* msg) override; 

	void SetVelocity(vec2 newVelocity) { m_velocity = newVelocity; }
	void SetPosition(vec2 m_newPosition) { m_position = m_newPosition; }
	void SetTypeOfProjectile(unsigned int newType) { m_typeOfProjectile = newType; }

	vec2 GetVelocity() { return m_velocity; }
	vec2 GetPosition() { return m_position; }
	unsigned int GetTypeOfProjectile() { return m_typeOfProjectile; }
};