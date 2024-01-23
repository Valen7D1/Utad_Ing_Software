#include "room.h"


//Room::Room(mapSite* rooms[4], unsigned int id) : roomId(id) {
//	for (int i = 0; i < 4; ++i) {
//		room[i] = rooms[i];
//	}
//}


void Room::setRoom(Direction dir, mapSite* site) {

	room->at(static_cast<int>(dir)) = site;
}


void Room::enter() const
{ 
	std::cout << "Opening Door" << std::endl; 
}


mapSite* Room::getRoom(Direction dir) 
{
	return room->at(static_cast<int>(dir));
	//return room[dir];
}


void Room::print() const 
{	
	printf("Room %d:\n", roomId);
}