#pragma once
#include "component.h"

class LadderRenderComponent : public RenderComponent
{
private:
	GLuint m_sprite;
	vec2 m_position;
	float m_radius;

public:
	virtual void Slot() override;
	virtual void  ReceiveMessage(Message* msg) override; 

	void SetPosition(vec2 newPosition) { m_position = newPosition; }
	void SetRadius(float newRadius) { m_radius = newRadius; }
	void SetSprite(GLuint newSprite) { m_sprite = newSprite; }

	vec2 GetPosition() { return m_position; }
	float GetRadius() { return m_radius; }
	GLuint GetSprite() { return m_sprite; }
};