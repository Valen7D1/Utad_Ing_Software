#include "global.h"
#include "Entity.h"

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
std::vector<Entity*> Manager::getEntities() {
    return entities;
}

// update for all game objects
void Manager::update() const
{   
    Manager* manager = Manager::getInstance();
    std::vector<Entity*> entities = manager->getEntities();

    for (Entity* entity : entities) {
        entity->Slot();
    }
}

// getter for timer
Timer* Manager::getTimer() {
    return &timer;
}