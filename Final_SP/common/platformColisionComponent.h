#pragma once
#include "component.h"


class PlatformColisionComponent : public Component
{
private:
	vec2 m_height;
	vec2 m_width;
public:
	virtual void Slot() override;
	virtual void  ReceiveMessage(Message* msg) override;

	void SetHeight(vec2 newHeight) { m_height = newHeight; }
	void SetWidth(vec2 newWidth) { m_width = newWidth; }
	vec2 GetHeight() { return m_height; };
	vec2 GetWidth() { return m_width; };

};