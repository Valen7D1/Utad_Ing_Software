#pragma once
#include "component.h"

class RenderComponent : public Component
{
private:
	vec2 pos;
	GLuint gfx;	// OpenGL for id. for visualization purposes. 
	float radius;

public:
	virtual void Slot() override; // call render sprite

	void SetPosition(vec2 newPos) { pos = newPos; }
	void SetGfx(GLuint newGfx) { gfx = newGfx; }
	void SetRadius(float newRadius) { radius = newRadius; }

	vec2 GetPosition() { return pos; };
	GLuint GetId() { return gfx; };
	float GetRadius() { return radius; };

};