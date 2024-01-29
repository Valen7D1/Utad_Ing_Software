#include "entity.h"


void Entity::Slot()
{
	for (Component* component : components)
	{
		component->Slot();
	}

}


Entity::~Entity()
{
	for (Component* component : components)
	{
		delete component;
	}
}


template<class T>
void Entity::AddComponent(T* newComponent)
{
	componentList.push_back(newComponent);
}


template<class T>
T* Entity::FindComponent()
{
	for (Component* component : components) {
	/*for (auto compIt = componentList.begin();
		compIt != componentList.end();
		++compIt)*/
		T* comp = dynamic_cast<T*>(*component);
		if (comp){ return comp; }
	}
	return NULL;
}