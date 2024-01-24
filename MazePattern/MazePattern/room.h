#pragma once
#include "mapSite.h"
#include<map>


class Room : public mapSite {
public:
    //Room() {}
    Room(unsigned int id) : roomId(id), roomObjects() {}

    unsigned int roomId;
    mapSite* getRoom(Direction dir);

    virtual void enter() const override;
    void setRoom(Direction dir, mapSite* site);

    virtual void print() const;
    void printRoom();

    ~Room() {
        for (int i = 0; i < 4; ++i) {
            if (roomObjects[i]) {
                if (roomObjects[i] != nullptr) {
                    if (typeid(*roomObjects[i]) != typeid(Room)) {
                        delete roomObjects[i];
                        roomObjects[i] = nullptr;
                    }
                }
            }
        }
    }

private:
    mapSite* roomObjects[4];
};


class ExplosiveRoom : public Room {
public:
    ExplosiveRoom(unsigned int id) : Room(id) {}

    void enter() const override;
    void print() const override;
};
