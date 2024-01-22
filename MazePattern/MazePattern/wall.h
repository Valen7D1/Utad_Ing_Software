#pragma once
#include "mapSite.h"

class Wall : public mapSite {
public:
    void enter() const override;
    void print() const { printf("X"); }
};