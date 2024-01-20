#pragma once
#include "stdafx.h"
#include "vector2d.h"
#include <iostream>
#include "ball.h"
#include <vector>

const unsigned int NUM_BALLS = 10;  // Max. num balls.
const float MAX_BALL_SPEED = 480.0f;   // Max vel. of ball (pixels/?).


class Manager {
private:
    static Manager* instance;

public:
    static Manager* getInstance();
    std::vector<Ball> balls = std::vector<Ball>(NUM_BALLS);
    void update() const;
    std::vector<Ball>* Manager::getBalls();
};
