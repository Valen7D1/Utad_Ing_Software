#pragma once
#include "component.h"

class SceneLogicComponent : public Component
{
public:
	virtual void Slot() override; // call render sprite
	virtual void  ReceiveMessage(Message* msg){}
};



class SceneRenderComponent : public Component
{
private:
	GLuint m_sceneSprite;

public:
	virtual void Slot() override; // call render sprite

	void SetSprite(GLuint newGfx) { m_sceneSprite = newGfx; }
	GLuint GetId() { return m_sceneSprite; }
	virtual void  ReceiveMessage(Message* msg) {}
};