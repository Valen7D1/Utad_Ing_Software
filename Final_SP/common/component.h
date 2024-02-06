#pragma once
#include <vector>
#include "stdafx.h"
#include "vector2d.h"

class Entity;
class Message;

class Component
{
public:
	//update method to be implemented in children classes
	virtual void Slot() = 0;
	virtual void ReceiveMessage(Message* msg) = 0;
	Entity* entityOwner; 
};
