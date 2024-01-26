#pragma once
#include "mapSite.h"

class Wall : public mapSite {
public:

    Wall() : mapSite(Type::Wall){} // constructor

    virtual void enter() const override { printf("Hitting Wall\n"); }

    virtual void print() const override { printf("   Wall\n"); }
};


class DestructibleWall : public Wall {
public:
    // constructor + father constructor for type
    DestructibleWall() : Wall() {}

    void enter() const override { printf("Breaking Wall\n"); }

    void print() const override { printf("   Breakable Wall\n"); }
};