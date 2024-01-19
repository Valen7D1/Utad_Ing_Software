#include "ball.h"

Ball::Ball() : pos(0.0f), vel(0.0f), gfx(0), radius(0.0f)
{}

//getters
vec2 Ball::getPosition() {return pos;}
vec2 Ball::getVelocity() {return vel;}
float Ball::getRadius() {return radius;}

//setters
void Ball::setPosition(vec2 position) { pos = position; }
void Ball::setVelocity(vec2 velocity) { vel = velocity; }
void Ball::setRadius(float rad) { radius = rad; }