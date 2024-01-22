#pragma once
#include <iostream>
#include <typeinfo>


enum class Direction {
    NORTH = 0,
    SOUTH,
    EAST,
    WEST
};


class mapSite {
public:
    virtual void enter() const {}
    virtual void print() const {}
    virtual ~mapSite() {} //virtual destructor
};