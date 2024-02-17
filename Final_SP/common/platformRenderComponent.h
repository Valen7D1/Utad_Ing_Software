#pragma once
#include "component.h"

class PLatformRenderComponent : public Component
{
private:
	GLuint m_sprite;
	vec2 m_position;
	vec2 m_size;
	vec2 m_proportions;

public:
	virtual void Slot() override;
	virtual void  ReceiveMessage(Message* msg) override; 

	void SetPosition(vec2 newPosition) { m_position = newPosition; }
	void SetSize(vec2 newSize) { m_size = newSize; }
	void SetProportions(vec2 newProportions) { m_proportions = newProportions; }
	void SetSprite(GLuint newSprite) { m_sprite = newSprite; }

	vec2 GetPosition() { return m_position; }
	vec2 GetSize() { return m_size; }
	vec2 GetProportions() { return m_proportions; }
	GLuint GetSprite() { return m_sprite; }

};