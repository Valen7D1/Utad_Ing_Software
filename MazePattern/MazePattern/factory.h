#pragma once
#include "room.h"
#include "wall.h"
#include "door.h"

class factoryBase {
public:
	virtual Room* CreateRoom(unsigned int id) const = 0;
	virtual Wall* CreateWall() const = 0;
	virtual Door* CreateDoor(Room* room) const = 0;

};


class factoryDestroy : public factoryBase 
{
public:
	Room* CreateRoom(unsigned int id) const override;
	Wall* CreateWall() const override;
	Door* CreateDoor(Room* room) const override;
};


class factoryExplode : public factoryBase 
{
public:
	Room* CreateRoom(unsigned int id) const override;
	Wall* CreateWall() const override;
	Door* CreateDoor(Room* room) const override;
};