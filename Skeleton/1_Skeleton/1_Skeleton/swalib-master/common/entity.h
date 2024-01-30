#pragma once
#include <vector>
#include "component.h"
#include "stdafx.h"
#include "vector2d.h"



class Entity
{
public:
	std::vector<Component*> components;

	template <class T>
	void AddComponent(T* newComponent);

	template <class T>
	T* FindComponent(); // finds comp in components

	virtual ~Entity();

	void Slot(); // for each components call slot method
};

template<class T>
void Entity::AddComponent(T* newComponent)
{
	components.push_back(newComponent);
}


template<class T>
T* Entity::FindComponent()
{
	//for (Component* component : components) {
	for (auto component = components.begin();
		component != components.end();
			++component){
		T* comp = dynamic_cast<T*>(*component);
		if (comp) { return comp; }
	}
	return NULL;
}