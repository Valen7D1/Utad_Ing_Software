#include "room.h"


//Room::Room(mapSite* rooms[4], unsigned int id) : roomId(id) {
//	for (int i = 0; i < 4; ++i) {
//		room[i] = rooms[i];
//	}
//}


void Room::printRoom() 
{
	for (int i = 0; i < 4; i++)
	{
		roomObjects[i]->print();
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


mapSite* Room::getRoom(Direction dir) 
{
	return roomObjects[static_cast<int>(dir)];
	//return room[dir];
}


void Room::print() const 
{	
	printf("   Room %d\n", roomId);
}


void ExplosiveRoom::print() const 
{
	printf("   Explosive Room %d\n", roomId);
}

void ExplosiveRoom::enter() const
{
	printf("You Exploded");
}