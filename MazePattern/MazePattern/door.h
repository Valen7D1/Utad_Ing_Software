#pragma once
#include "mapSite.h"
#include "room.h"

class Door : public mapSite {

public:

    Door(Room* room) : OtherSide(room) {}

    Room* OtherSide = nullptr;

    void enter() const override { printf("Opening Door\n"); }

    void print() const { printf("   Door to: Room %i\n", OtherSide->roomId); }
};
