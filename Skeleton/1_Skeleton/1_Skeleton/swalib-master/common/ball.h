#pragma once
#include "stdafx.h"
#include "vector2d.h"


class Ball
{
public:       
	vec2 getPosition();
	vec2 getVelocity();
	float getRadius();

	void setPosition(vec2 position);
	void setVelocity(vec2 velocity);
	void setRadius(float radius);

	void update();

	GLuint gfx;
	Ball();

	// currently unused but might want it later
	bool operator==(const Ball& other) const {
		return this == &other;  // Compare memory addresses
	}

private:
	vec2 pos;
	vec2 vel;
	float radius;
};
