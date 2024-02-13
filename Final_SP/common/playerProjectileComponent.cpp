#include "playerProjectileComponent.h"
#include "projectileColisionComponent.h"
#include "projectileMovementComponent.h"
#include "renderComponent.h"
#include "entity.h"
#include "manager.h"
#include "message.h"
#include <Windows.h>


void PlayerProjectileComponent::Slot()
{ 
	Manager* manager = Manager::getInstance();
	double elapsed = manager->getTimer()->GetElapsed();


	if (GetKeyState('X') & 0x8000)
	{
		if (m_clipSize > 0 && timeLimit <= 0)
		{
			CreateProjectile();
			timeLimit = 1;
		}
	}

	if (timeLimit>0)
	{
		timeLimit -= elapsed;
	}


	for (auto it = m_projectiles.begin(); it != m_projectiles.end(); )
	{ 
		Entity* entity = *it;

		entity->Slot();

		if (entity->toBeDeleted)
		{ 
			it = m_projectiles.erase(it);
			delete entity;
		} 
		else
		{
			++it;
		}
	}
	
}

void PlayerProjectileComponent::CreateProjectile() 
{
	Entity* bulletEntity = new Entity();

	ProjectileColisionComponent* projectileColision = new ProjectileColisionComponent();
	projectileColision->SetPosition(m_playerPosition);
	projectileColision->SetRadius(m_radius);
	projectileColision->entityOwner = bulletEntity;

	ProjectileMovementComponent* projectileMovement = new ProjectileMovementComponent();
	projectileMovement->SetPosition(m_playerPosition);
	projectileMovement->SetVelocity(m_velocity);
	projectileMovement->entityOwner = bulletEntity;

	RenderComponent* renderComponent = new RenderComponent();
	renderComponent->SetGfx(m_gfx);
	renderComponent->SetPosition(m_playerPosition);
	renderComponent->SetRadius(m_radius);
	renderComponent->entityOwner = bulletEntity;

	bulletEntity->AddComponent(projectileColision);
	bulletEntity->AddComponent(projectileMovement);
	bulletEntity->AddComponent(renderComponent);

	m_projectiles.push_back(bulletEntity);
}


void PlayerProjectileComponent::ReceiveMessage(Message* msg)
{ 
	//if new position
	NewPositionMessage* newPositionMessage = dynamic_cast<NewPositionMessage*>(msg);
	if (newPositionMessage)
	{
		m_playerPosition = newPositionMessage->newPos;
	}
}