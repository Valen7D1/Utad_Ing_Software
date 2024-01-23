#pragma once
#include "mapSite.h"

class Wall : public mapSite {
public:

    void enter() const override { printf("Hitting Wall\n"); }

    void print() const { printf("   Wall\n"); }
};