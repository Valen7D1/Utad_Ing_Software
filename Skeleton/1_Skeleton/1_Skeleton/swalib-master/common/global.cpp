#include "global.h"

GLuint texbkg;
GLuint texsmallball;

// instantiate manager to nullptr
Manager* Manager::instance = nullptr;

Manager* Manager::getInstance() 
{   
    // if not created already then create it
    if (instance == nullptr)
    {
        instance = new Manager();
    }
    return instance;
}

// getter for balls vector
std::vector<Ball>* Manager::getBalls() {
    return &balls;
}

// update for all game objects
void Manager::update() const
{   
    Manager* manager = Manager::getInstance();
    std::vector<Ball>* balls = manager->getBalls();

    for (Ball& ball : *balls) {
        ball.update();
    }
}

// getter for timer
Timer* Manager::getTimer() {
    return &timer;
}