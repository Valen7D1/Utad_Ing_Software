#pragma once
#include <vector>
#include "component.h"
#include "stdafx.h"
#include "vector2d.h"



class Entity
{
public:
	std::vector<Component*> components;

	template <class T>
	void AddComponent(T* newComponent);

	template <class T>
	T* FindComponent(); // finds comp in components

	virtual ~Entity();

	void Slot(); // for each components call slot method
};

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


class MovementComponent : public Component
{
private:
	vec2 pos;
	vec2 vel;

public:
	virtual void Slot() override;

	void SetPosition(vec2 newPosition);
	void SetVelocity(vec2 newVelocity);

	vec2 GetVelocity() { return vel; };
};

class RenderComponent : public Component
{
private:
	vec2 pos;
	GLuint gfx;	// OpenGL for id. for visualization purposes. 
	float radius;

public:
	virtual void Slot() override;

	void SetPosition(vec2 newPosition) {}
	void SetGfx(GLuint newGLuint) {}
	void SetRadius(float newRadius) {}

	vec2 GetPosition() { return pos; };
	GLuint GetId() { return gfx; };
	float GetRadius() { return radius; };

};