#pragma once
#include "mapSite.h"
#include<map>

class Room : public mapSite {
public:
    Room(unsigned int id) : roomId(id), roomObjects() {}

    unsigned int roomId;

    void enter() const override;
    void print() const;
    mapSite* getRoom(Direction dir);
    void setRoom(Direction dir, mapSite* site);

    void printRoom();

private:
    mapSite* roomObjects[4];
    //std::vector<mapSite*> room;  
};
