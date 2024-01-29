#pragma once
#include "component.h"


class ColisionComponent : public Component
{
private:
	vec2 currentPos;
	vec2 newPos;
	vec2 vel;
	float radius;
public:
	virtual void Slot() override;
	void SetPosition(vec2 newPosition);
	void SetVelocity(vec2 newVelocity);
	void SetRadius(float newRadius);

	vec2 GetPosition() { return currentPos; };
	vec2 GetVelocity() { return vel; };
	float GetRadius() { return radius; };

};