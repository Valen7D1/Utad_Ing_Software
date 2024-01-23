#pragma once
#include "mapSite.h"

class Door : public mapSite {

public:

    Door(Room* room) : OtherSide(room) {}

    Room* OtherSide;

    void enter() const override { printf("Opening Door\n"); }

    void print() const { printf("Door\n"); }
};
