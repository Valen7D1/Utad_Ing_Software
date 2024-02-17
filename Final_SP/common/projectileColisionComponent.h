#pragma once
#include "component.h"


class ProjectileColisionComponent : public Component
{
private:
	vec2 m_position;
	vec2 m_startingPosition;
	float m_radius = 0;
public:
	virtual void Slot() override; 
	virtual void  ReceiveMessage(Message* msg) override;

	void SetPosition(vec2 newPosition) { m_position = newPosition; }
	void SetStartingPosition(vec2 newStartingPosition) { m_startingPosition = newStartingPosition; }
	void SetRadius(float newRadius) { m_radius = newRadius; }

	vec2 GetStartingPosition() { return m_startingPosition; }
	vec2 GetPosition() { return m_position; }
	float GetRadius() { return m_radius; }
};