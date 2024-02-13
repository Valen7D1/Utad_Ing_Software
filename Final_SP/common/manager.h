#pragma once
#include "timer.h"
#include <vector>
#include "../swalib_example/rapidjson/document.h"
#include "../swalib_example/rapidjson/filereadstream.h"

const unsigned int NUM_BALLS = 3;  // Max. num balls.
const float MAX_BALL_SPEED = 480.0f;   // Max vel. of ball (pixels/?).
const float GRAVITY = -150.f;
const float FLOOR = 64.f;

class Entity;
class vec2;
class Document;
//class GLuint;

class Manager {
private:
    static Manager* instance;
    Timer timer;
    std::vector<Entity*> entities;    
    Entity* player; // in case you want coop

    rapidjson::Document doc;

public:
    //singleton
    static Manager* getInstance();
    //getters
    std::vector<Entity*> getEntities();
    Entity* getPlayer();
    Timer* getTimer();

    void CreateEntities();
    //void CreateBall(vec2 Velocity, vec2 Position, float radius, GLuint gfx);

    void CreatePlayers();
    void CreateGame();
    void ResetLevel();

    void update();

public:
    const char* entitiesFile = "data/entities.json";
};
