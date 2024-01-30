#include "movementComponent.h"
#include "colisionComponent.h"
#include "renderComponent.h"
#include "entity.h"


void MovementComponent::Slot() 
{
	pos = pos + vel;
	// check for collisions and then render
	entityOwner->FindComponent<ColisionComponent>()->SetPosition(pos);
	entityOwner->FindComponent<RenderComponent>()->SetPosition(pos);
}