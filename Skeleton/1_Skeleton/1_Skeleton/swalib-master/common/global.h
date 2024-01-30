#pragma once
#include "ball.h"
#include "logicSlot.h"
#include <vector>

const unsigned int NUM_BALLS = 10;  // Max. num balls.
const float MAX_BALL_SPEED = 480.0f;   // Max vel. of ball (pixels/?).

class Entity;

class Manager {
private:
    static Manager* instance;
    Timer timer;

public:
    //singleton
    static Manager* getInstance();

    // set balls
    std::vector<Entity*> entities = std::vector<Entity*>(NUM_BALLS);

    //getters
    std::vector<Entity*> Manager::getEntities();
    Timer* getTimer();

    void update() const;
};
