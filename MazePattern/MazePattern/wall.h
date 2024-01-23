#pragma once
#include "mapSite.h"

class Wall : public mapSite {
public:

    virtual void enter() const override { printf("Hitting Wall\n"); }

    virtual void print() const override { printf("   Wall\n"); }
};


class DestructibleWall : public Wall {
public:

    DestructibleWall(Room* room) : OtherSide(room) {}

    Room* OtherSide = nullptr;

    void enter() const override { printf("Breaking Wall\n"); }

    void print() const override 
    { 
        printf("   Breakable Wall to Room %d\n", OtherSide->roomId); 
    }
};