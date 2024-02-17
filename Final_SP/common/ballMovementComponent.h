#pragma once
#include "component.h"


class BallMovementComponent : public MovementComponent
{
private:
	vec2 m_position;
	vec2 m_velocity;

public:
	// update position based on velocity
	virtual void Slot() override;
	virtual void  ReceiveMessage(Message* msg) override; //msg system for component comunication

	//setters
	void SetPosition(vec2 newPos) { m_position = newPos; }
	void SetVelocity(vec2 newVel) { m_velocity = newVel; }
	//getters
	vec2 GetVelocity() { return m_velocity; }
	vec2 GetPosition() { return m_position; }
};