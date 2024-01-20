#pragma once
#include "stdafx.h"
#include "vector2d.h"


class Ball
{
public:
	Ball(); //constructor

	//getters
	vec2 getPosition();
	vec2 getVelocity();
	float getRadius();

	// setters
	void setPosition(vec2 position);
	void setVelocity(vec2 velocity);
	void setRadius(float radius);

	//update for ball collisions and location
	void update();

	GLuint gfx;

	// currently unused but might want it later
	bool operator==(const Ball& other) const {
		return this == &other;  // Compare memory addresses
	}

private:
	//world values
	vec2 pos; //position
	vec2 vel; //velocity
	float radius;
};
