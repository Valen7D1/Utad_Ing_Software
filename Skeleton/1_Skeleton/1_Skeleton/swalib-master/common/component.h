#pragma once
#include <vector>
#include "stdafx.h"
#include "vector2d.h"

class Entity;

class Component
{
public:
	//update method to be implemented in children classes
	virtual void Slot() = 0;
	Entity* entityOwner; 
};
