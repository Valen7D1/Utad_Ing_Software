#include "renderComponent.h"
#include "entity.h"
#include "core.h"


void RenderComponent::Slot() 
{
	CORE_RenderCenteredSprite(pos, vec2(radius * 2.f, radius * 2.f), gfx);
}