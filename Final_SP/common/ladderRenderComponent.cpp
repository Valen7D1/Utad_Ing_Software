#include "ladderRenderComponent.h"
#include "core.h"
#include "message.h"


void LadderRenderComponent::Slot()
{
	CORE_RenderCenteredSprite(m_position, m_radius, m_sprite);
}

void LadderRenderComponent::ReceiveMessage(Message* msg)
{
}