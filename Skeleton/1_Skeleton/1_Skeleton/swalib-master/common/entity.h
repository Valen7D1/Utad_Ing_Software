#pragma once
#include <vector>
#include "component.h"
#include "stdafx.h"
#include "vector2d.h"


class Message;

class Entity
{
public:
	std::vector<Component*> components;

	template <class T>
	T* FindComponent(); // iterates through component vector

	void AddComponent(Component* newComponent){ components.push_back(newComponent); }

	virtual ~Entity(); // for each component delete

	void Slot(); // for each component call slot method
	void SendMsg(Message* msg); //for each component call to receive msg

};


template<class T>
T* Entity::FindComponent()
{	
	//for (Component* component : components)
	for (auto component = components.begin(); component != components.end(); ++component)
	{
		T* comp = dynamic_cast<T*>(*component);
		if (comp) { return comp; }
	}
	return NULL;
}