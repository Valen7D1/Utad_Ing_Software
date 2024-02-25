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
	double elapsed = manager->getTimer()->GetFrameTime();


	if (GetKeyState('X') & 0x8000)
	{
		// if you want to test anything disable this If 
		// and then you can fire infite bullets
		if(m_projectiles.size() < m_maxBullets && timeLimit <= 0)
		{
			CreateProjectile();
			timeLimit = 0.3;
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
	switch (m_typeOfProjectile) {
	case 0:
		BasicThreat();
		break;
	case 1:
		TrippleThreat();
		break;
	default:
		BasicThreat();
	} 
}

void PlayerProjectileComponent::BasicThreat()
{
	Entity* bulletEntity = new BulletEntity();

	vec2 startingPosition = vec2(m_playerPosition.x, m_playerPosition.y + m_radius);

	ProjectileColisionComponent* projectileColision = new ProjectileColisionComponent();
	projectileColision->SetPosition(startingPosition);
	projectileColision->SetStartingPosition(startingPosition);
	projectileColision->SetRadius(m_radius / 2);
	projectileColision->entityOwner = bulletEntity;

	ProjectileMovementComponent* projectileMovement = new ProjectileMovementComponent();
	projectileMovement->SetPosition(startingPosition);
	projectileMovement->SetVelocity(m_velocity);
	projectileMovement->entityOwner = bulletEntity;

	ProjectileRenderComponent* renderComponent = new ProjectileRenderComponent();
	renderComponent->SetGfx(m_gfx);
	renderComponent->SetTraceSprite(m_trace);
	renderComponent->SetPosition(startingPosition);
	renderComponent->SetRadius(m_radius / 2);
	renderComponent->SetStartingPosition(startingPosition);
	renderComponent->entityOwner = bulletEntity;

	bulletEntity->AddComponent(projectileColision);
	bulletEntity->AddComponent(projectileMovement);
	bulletEntity->AddComponent(renderComponent);

	m_projectiles.push_back(bulletEntity);
}

void PlayerProjectileComponent::TrippleThreat()
{
	vec2 tempVelocity = m_velocity;
	for (unsigned int i = 0; i<3; ++i)
	{
		Entity* bulletEntity = new BulletEntity();

		vec2 startingPosition = vec2(m_playerPosition.x, m_playerPosition.y + m_radius);

		ProjectileColisionComponent* projectileColision = new ProjectileColisionComponent();
		projectileColision->SetPosition(startingPosition);
		projectileColision->SetStartingPosition(startingPosition);
		projectileColision->SetRadius(m_radius / 2);
		projectileColision->entityOwner = bulletEntity;
		projectileColision->SetTypeOfProjectile(m_typeOfProjectile);


		ProjectileMovementComponent* projectileMovement = new ProjectileMovementComponent();
		projectileMovement->SetPosition(startingPosition);
		projectileMovement->SetVelocity(tempVelocity);
		projectileMovement->entityOwner = bulletEntity;
		projectileMovement->SetTypeOfProjectile(m_typeOfProjectile);


		ProjectileRenderComponent* renderComponent = new ProjectileRenderComponent();
		renderComponent->SetGfx(m_gfx);
		renderComponent->SetTraceSprite(m_trace);
		renderComponent->SetPosition(startingPosition);
		renderComponent->SetRadius(m_radius / 2);
		renderComponent->SetStartingPosition(startingPosition);
		renderComponent->entityOwner = bulletEntity;
		renderComponent->SetTypeOfProjectile(m_typeOfProjectile);

		bulletEntity->AddComponent(projectileColision);
		bulletEntity->AddComponent(projectileMovement);
		bulletEntity->AddComponent(renderComponent);

		m_projectiles.push_back(bulletEntity);

		tempVelocity.x -= m_velocity.x;
	}
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