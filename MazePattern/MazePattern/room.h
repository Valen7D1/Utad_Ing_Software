#pragma once
#include "mapSite.h"


class Room : public mapSite {
public:
    Room(unsigned int id) : roomId(id) {}

    void enter() const override;
    void print() const;
    mapSite* getRoom(Direction dir);
    void setRoom(Direction dir, mapSite* site);

private:
    //mapSite* room[4];
    unsigned int roomId;

    std::vector<mapSite*> room[4];
};
