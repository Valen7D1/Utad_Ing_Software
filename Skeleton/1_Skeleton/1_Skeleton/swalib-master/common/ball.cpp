#include "ball.h"
#include "global.h"
#include "sys.h"


Ball::Ball() : pos(0.0f), vel(0.0f), gfx(0), radius(0.0f)
{}

//getters
vec2 Ball::getPosition() { return pos; }
vec2 Ball::getVelocity() { return vel; }
float Ball::getRadius() { return radius; }

//setters
void Ball::setPosition(vec2 position) { pos = position; }
void Ball::setVelocity(vec2 velocity) { vel = velocity; }
void Ball::setRadius(float rad) { radius = rad; }

void Ball::update()
{
	Manager* manager = manager->getInstance();
	std::vector<Ball>* balls = manager->getBalls();
	// Run balls

	// New Pos.
	vec2 newpos = this->getPosition() + this->getVelocity();

	// Collision detection.
	bool collision = false;
	Ball* colliding_ball = nullptr;
	for (Ball& otherBall : *balls) {
		if (!(this == &otherBall)) {
			float limit2 = (this->getRadius() + otherBall.getRadius()) * (this->getRadius() + otherBall.getRadius());
			if (vlen2(newpos - otherBall.getPosition()) <= limit2) {
				collision = true;
				colliding_ball = &otherBall;
				break;
			}
		}
	}

	if (!collision) {
		this->setPosition(newpos);
	}
	else {
		// Rebound!
		this->setVelocity(this->getVelocity() * -1.f);
		colliding_ball->setVelocity(colliding_ball->getVelocity() * -1.f);
	}

	// Rebound on margins.
	if ((this->getPosition().x > SCR_WIDTH) || (this->getPosition().x < 0)) {
		this->setVelocity(vec2(this->getVelocity().x * -1.0, this->getVelocity().y));
	}
	if ((this->getPosition().y > SCR_HEIGHT) || (this->getPosition().y < 0)) {
		this->setVelocity(vec2(this->getVelocity().x, this->getVelocity().y * -1.0));
	}
}