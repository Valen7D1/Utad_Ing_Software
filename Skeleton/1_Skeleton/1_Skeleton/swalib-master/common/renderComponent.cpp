#include "renderComponent.h"
#include "core.h"
#include "message.h"


void RenderComponent::Slot() 
{
	CORE_RenderCenteredSprite(pos, vec2(radius * 2.f, radius * 2.f), gfx);
}

void RenderComponent::ReceiveMessage(Message* msg) {

}