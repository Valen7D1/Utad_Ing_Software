#include "room.h"


//room methods
void Room::printRoom() const
{
	for (int i = 0; i < 4; i++)
	{
		roomObjects[i]->print();
	}
}


void Room::cleanUp() {
	for (int i = 0; i < 4; ++i) {
		if (roomObjects[i]) {
			if (roomObjects[i]->getTipo() != Type::Room) {
				delete roomObjects[i];
				roomObjects[i] = nullptr;
			}
		}
	}
}


void Room::setRoom(Direction dir, mapSite* site) 
{
	roomObjects[static_cast<int>(dir)] = site;
}


void Room::enter() const
{ 
	printf("Opening Door");
}


mapSite* Room::getRoomObject(Direction dir)
{
	return roomObjects[static_cast<int>(dir)];
	//return room[dir];
}

void Room::print() const 
{	
	printf("   Room %d\n", roomId);
}



//explosive room methods
void ExplosiveRoom::print() const 
{
	printf("   Explosive Room %d\n", roomId);
}

void ExplosiveRoom::enter() const
{
	printf("You Exploded");
}