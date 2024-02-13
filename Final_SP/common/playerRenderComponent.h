#pragma once
#include "component.h"

class PlayerRenderComponent : public Component
{
private:
	vec2 m_position;
	float m_radius;
	GLuint m_gfx[2];	// OpenGL for id. for visualization purposes. 
	GLuint m_HpGfx;
	unsigned int m_hitPoints;
	unsigned int m_direction = 0;

public:
	virtual void Slot() override; // call render sprite
	virtual void  ReceiveMessage(Message* msg) override; //msg system for component comunication

	//setters
	void SetGfx(GLuint newGfx1, GLuint newGfx2) { m_gfx[0] = newGfx1; m_gfx[1] = newGfx2;}
	void SetHpGfx(GLuint newHpGfx) { m_HpGfx = newHpGfx; }
	void SetPosition(vec2 m_newPosition) { m_position = m_newPosition; }
	void SetRadius(float newRadius) { m_radius = newRadius; }
	void SetHitPoint(unsigned int newHitPoints) { m_hitPoints = newHitPoints; }

	//getters
	GLuint GetId(unsigned int id) { return m_gfx[id]; };
	GLuint GetHpId() { return m_HpGfx; };
	vec2 GetPosition() { return m_position; };
	float GetRadius() { return m_radius; };
	unsigned int GetHitPoint() { return m_hitPoints; }

};