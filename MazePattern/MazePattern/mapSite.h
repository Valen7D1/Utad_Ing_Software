#pragma once
#include <iostream>
#include <typeinfo>
#include <vector>


enum class Direction {
    NORTH = 0,
    SOUTH,
    EAST,
    WEST
};

enum class Type {
    Room,
    Door,
    Wall,
};



class mapSite {
public:

    mapSite(Type _tipo) : tipo(_tipo) {}

    virtual void enter() const {}
    virtual void print() const {}
    virtual ~mapSite() {} //virtual destructor

    Type getTipo() const { return tipo; }

protected:
    Type tipo;
};