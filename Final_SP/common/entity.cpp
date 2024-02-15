#include "entity.h"
#include "message.h"


void Entity::Slot()
{
	for (Component* component : components)
	{
		if (components.size() <= 0 && !component) { break; }
		component->Slot(); 
	}

}

//name sendMsg because internally SendMessage is already in use
void Entity::SendMsg(Message* msg)
{
	for (Component* component : components) 
	{
		component->ReceiveMessage(msg);
	}
}


Entity::~Entity()
{
	while (components.size() > 0)
	{
		delete components[components.size() - 1];
		components.pop_back();
	}
}

