#include "room.h"

void Room::enter() const
{ 
	std::cout << "Opening Door" << std::endl; 
}


mapSite* Room::getRoom(Direction dir) 
{
	return room[static_cast<int>(dir)];
	//return room[dir];
}

void Room::print() const 
{	
	printf("#Room %d:", roomId);
	for (mapSite* site : room) {

		site->print();
	}
	printf("#End of Room %d", roomId);
}