#pragma once
#include "maze.h"


class builderBase {
public:

};


class builder1 : public builderBase
{
public:
	Room* CreateRoom(unsigned int id) const override;
	Wall* CreateWall() const override;
	Door* CreateDoor(Room* room) const override;
};

class builder2 : public builderBase
{
public:
	Room* CreateRoom(unsigned int id) const override;
	Wall* CreateWall() const override;
	Door* CreateDoor(Room* room) const override;
};