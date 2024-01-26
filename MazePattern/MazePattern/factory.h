#pragma once
#include "room.h"
#include "wall.h"
#include "door.h"

class factoryBase {
public:
	// defines virtual methods for the sub factories
	virtual Room* CreateRoom(unsigned int id) const = 0;
	virtual Wall* CreateWall() const = 0;
	virtual Door* CreateDoor(Room* room) const = 0;

};


class factoryDestroy : public factoryBase 
{
public:
	Room* CreateRoom(unsigned int id) const override; // new Room()
	Wall* CreateWall() const override; // new DestructibleWall()
	Door* CreateDoor(Room* room) const override; // new Door()
};


class factoryExplode : public factoryBase 
{
public:
	Room* CreateRoom(unsigned int id) const override; // new ExplosiveRoom()
	Wall* CreateWall() const override; // new Wall()
	Door* CreateDoor(Room* room) const override; // new Door()
};