#pragma once
#include "component.h"


class ColisionComponent : public Component
{
private:
	vec2 currentPos;
	vec2 newPos; // temporary position for collision control
	vec2 vel;
	float radius;
public:
	virtual void Slot() override; // checks collisions and acts acordingly

	// setters
	void SetPosition(vec2 newPosition) { newPos = newPosition; }
	void SetVelocity(vec2 newVelocity) { vel = newVelocity; }
	void SetRadius(float newRadius) { radius = newRadius; }
	// getters
	vec2 GetPosition() { return currentPos; };
	vec2 GetVelocity() { return vel; };
	float GetRadius() { return radius; };

};