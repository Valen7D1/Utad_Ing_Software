#pragma once
#include "component.h"


class PlayerColisionComponent : public Component
{
private:
	vec2 m_position;
	float m_radius;
	unsigned int m_hitPoints;
public:
	virtual void Slot() override; 
	virtual void  ReceiveMessage(Message* msg) override;

	void SetPosition(vec2 newPosition) { m_position = newPosition; }
	void SetRadius(float newRadius) { m_radius = newRadius; }
	void SetHitPoints(unsigned int newHitPoints) { m_hitPoints = newHitPoints; }

	vec2 GetPosition() { return m_position; };
	float GetRadius() { return m_radius; };
	unsigned int GetHitPoints() { return m_hitPoints; };

};