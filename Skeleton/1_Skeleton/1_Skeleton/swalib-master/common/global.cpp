#include "global.h"

GLuint texbkg;
GLuint texsmallball;

Manager* Manager::instance = nullptr;

Manager* Manager::getInstance() 
{
    if (instance == NULL) 
    {
        instance = new Manager();
    }
    return instance;
}

std::vector<Ball>* Manager::getBalls() {
    return &balls;
}

void Manager::update() const
{   
    Manager* manager = Manager::getInstance();
    std::vector<Ball>* balls = manager->getBalls();

    for (Ball& ball : *balls) {
        ball.update();
    }
}