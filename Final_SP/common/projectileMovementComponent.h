#pragma once
#include "component.h"


class ProjectileMovementComponent : public MovementComponent
{
private:
	vec2 m_position;
	float m_velocity;

public:
	// update position based on velocity
	virtual void Slot() override;
	virtual void  ReceiveMessage(Message* msg) override; 

	void SetVelocity(float newVelocity) { m_velocity = newVelocity; }
	void SetPosition(vec2 m_newPosition) { m_position = m_newPosition; }

	float GetVelocity() { return m_velocity; }
	vec2 GetPosition() { return m_position; }
};