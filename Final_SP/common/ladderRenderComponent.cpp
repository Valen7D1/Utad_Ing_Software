#include "ladderRenderComponent.h"
#include "message.h"
#include "core.h"


void LadderRenderComponent::Slot()
{
	// simplified version of render for ladders
	CORE_RenderCenteredSprite(m_position, m_radius, m_sprite);
}

// ladders dont really comunicate do them? xd
void LadderRenderComponent::ReceiveMessage(Message* msg)
{
}