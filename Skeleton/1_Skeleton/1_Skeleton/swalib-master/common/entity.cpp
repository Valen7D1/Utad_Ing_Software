#include "entity.h"
#include "message.h"


void Entity::Slot()
{
	for (Component* component : components)
	{
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
	for (Component* component : components)
	{
		delete component;
	}
}