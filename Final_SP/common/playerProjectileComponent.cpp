#include "playerProjectileComponent.h"
#include "projectileColisionComponent.h"
#include "projectileMovementComponent.h"
#include "projectileRenderComponent.h"
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
		//if (timeLimit <= 0)
		if(m_projectiles.size()<=0)
		{
			CreateProjectile();
			timeLimit = 0.1;
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

	vec2 startingPosition = vec2(m_playerPosition.x, m_playerPosition.y + m_radius);

	ProjectileColisionComponent* projectileColision = new ProjectileColisionComponent();
	projectileColision->SetPosition(startingPosition);
	projectileColision->SetStartingPosition(startingPosition);
	projectileColision->SetRadius(m_radius/2);
	projectileColision->entityOwner = bulletEntity;

	ProjectileMovementComponent* projectileMovement = new ProjectileMovementComponent();
	projectileMovement->SetPosition(startingPosition);
	projectileMovement->SetVelocity(m_velocity);
	projectileMovement->entityOwner = bulletEntity;

	ProjectileRenderComponent* renderComponent = new ProjectileRenderComponent();
	renderComponent->SetGfx(m_gfx);
	renderComponent->SetTraceSprite(m_trace);
	renderComponent->SetPosition(startingPosition);
	renderComponent->SetRadius(m_radius/2);
	renderComponent->SetStartingPosition(startingPosition);
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