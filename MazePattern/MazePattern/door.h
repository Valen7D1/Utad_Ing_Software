#pragma once
#include "mapSite.h"

class Door : public mapSite {
public:
    void enter() const override {
        std::cout << "Opening Door" << std::endl;
    }

    void print() const { printf(" "); }
};
