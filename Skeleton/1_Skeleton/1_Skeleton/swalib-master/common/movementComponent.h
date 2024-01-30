#pragma once
#include "component.h"


class MovementComponent : public Component
{
private:
	vec2 pos;
	vec2 vel;

public:
	// update position based on velocity
	virtual void Slot() override;
	virtual void  ReceiveMessage(Message* msg) override; //msg system for component comunication

	//setters
	void SetPosition(vec2 newPos) { pos = newPos; }
	void SetVelocity(vec2 newVel) { vel = newVel; }
	//getters
	vec2 GetVelocity() { return vel; }
	vec2 GetPosition() { return pos; }
};