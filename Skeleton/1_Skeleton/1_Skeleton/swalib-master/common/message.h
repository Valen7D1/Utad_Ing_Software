#pragma once
#include "vector2d.h"


class Message 
{ 
public:
    virtual ~Message(){}
};


class CollisionMessage : public Message
{
public:
    CollisionMessage(vec2 _newPos) : newPos(_newPos) {}
    vec2 newPos;
};


class EntCollisionMessage : public CollisionMessage
{
public:
    EntCollisionMessage(vec2 _newPos) : CollisionMessage(_newPos) {}
};


class LimitWorldCollMessage : public CollisionMessage
{
public:
    LimitWorldCollMessage(vec2 _newDirection, vec2 _newPos) : 
        CollisionMessage(_newPos), entityDirection(_newDirection) {}

    vec2 entityDirection; //{ Horizontal, Vertical }
};


class NewPositionMessage : public Message
{
public:
    NewPositionMessage(vec2 _newPos) : newPos(_newPos) {}
    vec2 newPos;
};
