#include "movementComponent.h"
#include "colisionComponent.h"
#include "renderComponent.h"
#include "entity.h"
#include "manager.h"
#include "message.h"


void MovementComponent::Slot() 
{
	Manager* manager = Manager::getInstance();
	pos = pos + vel * manager->getTimer()->GetFrameTime();
	// check for collisions and then render
	entityOwner->FindComponent<ColisionComponent>()->SetPosition(pos);
	entityOwner->FindComponent<RenderComponent>()->SetPosition(pos);
}

void MovementComponent::ReceiveMessage(Message* msg) {

}