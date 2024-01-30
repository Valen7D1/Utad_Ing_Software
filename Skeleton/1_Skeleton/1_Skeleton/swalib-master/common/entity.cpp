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