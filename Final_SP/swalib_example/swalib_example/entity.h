#pragma once
#include <vector>
#include "component.h"
//#include "stdafx.h"
//#include "vector2d.h"



class CEntity
{
public:
	std::vector<Component*> componentList;

	template <class T>
	void AddComponent(T* newComponent);
	template <class T>
	T* FindComponent();

	//virtual ~CEntity();

	void Slot();
};