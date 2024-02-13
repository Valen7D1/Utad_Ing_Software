#pragma once
#include "vector2d.h"

// base class for messages
class Message 
{ 
public:
    virtual ~Message(){}
};

// base class for collision messages
class CollisionMessage : public Message
{
public:
    CollisionMessage(vec2 _newPos) : newPos(_newPos) {}
    vec2 newPos;
};

// collision with entity
class EntCollisionMessage : public CollisionMessage
{
public:
    EntCollisionMessage(vec2 _newPos) : CollisionMessage(_newPos) {}
};

// collision with world limits
class LimitWorldCollMessage : public CollisionMessage
{
public:
    LimitWorldCollMessage(vec2 _newDirection, vec2 _newPos) : 
        CollisionMessage(_newPos), entityDirection(_newDirection) {}

    vec2 entityDirection; //{ Horizontal, Vertical }
};

// new position message
class NewPositionMessage : public Message
{
public:
    NewPositionMessage(vec2 _newPos) : newPos(_newPos) {}
    vec2 newPos;
};

// new position message
class NewVelocityMessage : public Message
{
public:
    NewVelocityMessage(vec2 _newVel) : newVel(_newVel) {}
    vec2 newVel;
};

// new position message
class NewHitPointsMessage : public Message
{
public:
    NewHitPointsMessage(unsigned int _newHP) : newHP(_newHP) {}
    unsigned int newHP;
};

class NewDirectionMessage : public Message
{
public:
    NewDirectionMessage(unsigned int _newDir) : newDir(_newDir) {}
    unsigned int newDir;
};

