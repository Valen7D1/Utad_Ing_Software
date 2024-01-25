#include "factory.h"


// breakable wall factory
Room* factoryDestroy::CreateRoom(unsigned int id) const
{
	return new Room(id);
}


Wall* factoryDestroy::CreateWall() const
{
	return new DestructibleWall();
}


Door* factoryDestroy::CreateDoor(Room* room) const
{
	return new Door(room);
}


// explosive room factory
Room* factoryExplode::CreateRoom(unsigned int id) const
{
	return new ExplosiveRoom(id);
}


Wall* factoryExplode::CreateWall() const
{
	return new Wall();
}


Door* factoryExplode::CreateDoor(Room* room) const
{
	return new Door(room);
}
