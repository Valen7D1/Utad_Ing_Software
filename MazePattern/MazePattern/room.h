#pragma once
#include "mapSite.h"
#include<map>


class Room : public mapSite {
public:
    //Room() {}
    Room(unsigned int id) : 
        mapSite(Type::Room), roomId(id), roomObjects() {}

    mapSite* getRoomObject(Direction dir);
    unsigned int roomId;

    virtual void enter() const override;

    void setRoom(Direction dir, mapSite* site);
    // prints room id
    virtual void print() const;
    // calls to print from all objects in roomObjects
    void printRoom() const;

    // iterates through the roomObjects and delete
    // all except room type objects
    void cleanUp();

    ~Room() {}

protected:
    mapSite* roomObjects[4];
};


class ExplosiveRoom : public Room {
public:
    ExplosiveRoom(unsigned int id) : Room(id) {}

    void enter() const override;
    void print() const override;
};
