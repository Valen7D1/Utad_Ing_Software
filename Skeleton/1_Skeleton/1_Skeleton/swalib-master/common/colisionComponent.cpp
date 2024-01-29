#include "colisionComponent.h"
#include "entity.h"
#include "global.h"
#include "sys.h"

void ColisionComponent::Slot() {
	//control vars for collision checking
	bool collision = false;
	Entity* entity = nullptr;
	ColisionComponent* otherEntity = nullptr;

	Manager* manager = manager->getInstance();
	std::vector<Ball*> balls = manager->getBalls();

	MovementComponent* movementComponent = entityOwner->FindComponent<MovementComponent>();

	for (Ball* otherBall : balls) {}
	for each (Entity * pBall in Manager::getInstance().GetEntityBallList())
	{
		//If not self
		if (entityOwner != pBall)
		{
			//Get values of other ball
			otherEntity = pBall->FindComponent<ColisionComponent>();
			float limit2 = (radius + otherEntity->GetRadius()) * (radius + otherEntity->GetRadius());
			//If hit
			if (vlen2(newPos - otherBallCollision->GetPosition()) <= limit2) {
				collision = true;
				entity = pBall;
				break;
			}
		}
	}


	//If not hit, you can move to the new position
	if (!collision) {
		m_currentPos = m_newPos;
	}
	//If hit
	else {


		//Restore previous movement
		//movementComponent->ReceiveMessage(new CEntCollisionMessage(m_currentPos));
		//entityOwner->FindComponent<CRenderComponent>()->SetPosition(m_currentPos);

		entityOwner->ReceiveMessage(new CEntCollisionMessage(m_currentPos));

		// Rebound!
		m_vel = m_vel * -1.f;

		//Change own component velocity
		//movementComponent->SetVelocity(movementComponent->GetVelocity() * -1.f);


		////Change other ball component velocity
		//otherBallCollision->SetVelocity(otherBallCollision->GetVelocity()* - 1.f);


		////Change other ball component movement
		//CMovementComponent* otherBallMovement = entityColliding->FindComponent<CMovementComponent>();
		//otherBallMovement->SetVelocity(otherBallMovement->GetVelocity() * -1.f);
	}

	// Rebound on margins.
	if ((m_currentPos.x > SCR_WIDTH) || (m_currentPos.x < 0)) {
		m_vel = vec2(m_vel.x * -1, m_vel.y);
		/*movementComponent->SetVelocity(vec2(movementComponent->GetVelocity().x * -1.f, movementComponent->GetVelocity().y));*/
		entityOwner->ReceiveMessage(new CLimitWorldCollMessage(1, m_currentPos));
	}
	if ((m_currentPos.y > SCR_HEIGHT) || (m_currentPos.y < 0)) {
		m_vel = vec2(m_vel.x, m_vel.y * -1);
		/*movementComponent->SetVelocity(vec2(movementComponent->GetVelocity().x, movementComponent->GetVelocity().y * -1.f));*/
		entityOwner->ReceiveMessage(new CLimitWorldCollMessage(0, m_currentPos));
	}
}