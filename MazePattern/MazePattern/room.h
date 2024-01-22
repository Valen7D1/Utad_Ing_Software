#pragma once
#include "mapSite.h"


class Room : public mapSite {
public:
    void enter() const override;
    void print() const;
    mapSite* getRoom(Direction dir);
private:
    mapSite* room[4];
    unsigned int roomId;
};
