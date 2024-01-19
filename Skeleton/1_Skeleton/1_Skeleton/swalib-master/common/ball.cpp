#include "ball.h"
#include "global.h"
#include "sys.h"




// setting values of member variables.

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

void Ball::update()
{	
	// Run balls
	for (int i = 0; i < NUM_BALLS; i++) {
		// New Pos.
		vec2 newpos =  Manager::balls[i].getPosition() + Manager::balls[i].getVelocity();

		// Collision detection.
		bool collision = false;
		int colliding_ball = -1;
		for (int j = 0; j < NUM_BALLS; j++) {
			if (i != j) {
				float limit2 = (Manager::balls[i].getRadius() + Manager::balls[j].getRadius()) * (Manager::balls[i].getRadius() + Manager::balls[j].getRadius());
				if (vlen2(newpos - Manager::balls[j].getPosition()) <= limit2) {
					collision = true;
					colliding_ball = j;
					break;
				}
			}
		}

		if (!collision) {
			Manager::balls[i].setPosition(newpos);
		}
		else {
			// Rebound!
			Manager::balls[i].setVelocity(Manager::balls[i].getVelocity() * -1.f);
			Manager::balls[colliding_ball].setVelocity(Manager::balls[colliding_ball].getVelocity() * -1.f);
		}

		// Rebound on margins.
		if ((Manager::balls[i].getPosition().x > SCR_WIDTH) || (Manager::balls[i].getPosition().x < 0)) {
			Manager::balls[i].setVelocity(vec2(Manager::balls[i].getVelocity().x * -1.0, Manager::balls[i].getVelocity().y));
		}
		if ((Manager::balls[i].getPosition().y > SCR_HEIGHT) || (Manager::balls[i].getPosition().y < 0)) {
			Manager::balls[i].setVelocity(vec2(Manager::balls[i].getVelocity().x, Manager::balls[i].getVelocity().y * -1.0));
		}
	}
}