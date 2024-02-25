#pragma once
#include <vector>
#include "component.h"
#include "stdafx.h"
#include "vector2d.h"



class Message;

class Entity
{
public:
	std::vector<Component*> components;

	template <class T>
	T* FindComponent(); // iterates through component vector

	void AddComponent(Component* newComponent){ components.push_back(newComponent); }

	virtual ~Entity(); // for each component delete

	void Slot(); // for each component call slot method
	virtual void Destroy() = 0;
	void SendMsg(Message* msg); //for each component call to receive msg

	bool toBeDeleted = false;

};

class PlayerEntity : public Entity
{
public:
	virtual void Destroy() override {}
};


class BallEntity : public Entity
{
public:
	virtual void Destroy() override;
};


class PlatformEntity : public Entity
{
public:
	virtual void Destroy() override {}
};


class LadderEntity : public Entity
{
public:
	virtual void Destroy() override {}
};


class SceneEntity : public Entity
{
public:
	virtual void Destroy() override {}
};


class BulletEntity : public Entity
{
public:
	virtual void Destroy() override {}
};


class TrippleThreatPowerUp : public Entity
{
public:
	virtual void Destroy() override;
};


class HealthBoostPowerUp : public Entity
{
public:
	virtual void Destroy() override;
};


class MagazineBoostPowerUp : public Entity
{
public:
	virtual void Destroy() override;
};





template<class T>
T* Entity::FindComponent()
{	
	//for (Component* component : components)
	for (auto component = components.begin(); component != components.end(); ++component)
	{
		T* comp = dynamic_cast<T*>(*component);
		if (comp) { return comp; }
	}
	return NULL;
}