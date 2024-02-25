#pragma once
#include "component.h"


class PowerUpMovementComponent : public MovementComponent
{
private:
	vec2 m_position;
	vec2 m_velocity;

public:
	// update position based on velocity
	virtual void Slot() override;
	virtual void  ReceiveMessage(Message* msg) override; 

	void SetVelocity(vec2 newVelocity) { m_velocity = newVelocity; }
	void SetPosition(vec2 m_newPosition) { m_position = m_newPosition; }

	vec2 GetVelocity() { return m_velocity; }
	vec2 GetPosition() { return m_position; }
};