#pragma once
#include <vector>
#include "stdafx.h"
#include "vector2d.h"

class Entity;

class Component
{
public:
	virtual void Slot() = 0;
	Entity* entityOwner;
};
