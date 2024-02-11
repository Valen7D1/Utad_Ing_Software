#pragma once
#include "timer.h"
#include <vector>

const unsigned int NUM_BALLS = 1;  // Max. num balls.
const float MAX_BALL_SPEED = 480.0f;   // Max vel. of ball (pixels/?).
const float GRAVITY = -150.f;
const float FLOOR = 100.f;

class Entity;
class vec2;
//class GLuint;

class Manager {
private:
    static Manager* instance;
    Timer timer;
    std::vector<Entity*> entities;    
    std::vector<Entity*> players;

public:
    //singleton
    static Manager* getInstance();
    //getters
    std::vector<Entity*> Manager::getEntities();
    std::vector<Entity*> Manager::getPlayers();
    Timer* getTimer();

    void CreateEntities();
    //void CreateBall(vec2 Velocity, vec2 Position, float radius, GLuint gfx);

    void CreatePlayers();
    void CreateGame();

    void update();

public:
    const char* entitiesFile = "data/Entities.json";
};
