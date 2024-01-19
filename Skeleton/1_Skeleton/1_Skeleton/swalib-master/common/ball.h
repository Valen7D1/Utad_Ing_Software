#pragma once
#include "stdafx.h"
#include "vector2d.h"

const unsigned int NUM_BALLS = 10;  // Max. num balls.
const float MAX_BALL_SPEED = 480.0f;   // Max vel. of ball (pixels/?).


//struct Ball	// Info Ball
//{
//	vec2   pos;	// Position.
//	vec2   vel;	// Velocity.
//	GLuint gfx;	// OpenGL for id. for visualization purposes. 
//	float  radius;	// Radius.
//
//	Ball();
//};


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

private:
	vec2 pos;
	vec2 vel;
	float radius;
};
