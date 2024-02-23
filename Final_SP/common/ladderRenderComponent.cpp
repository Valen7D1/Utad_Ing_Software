#include "ladderRenderComponent.h"
#include "message.h"
#include "core.h"


void LadderRenderComponent::Slot()
{
	CORE_RenderCenteredSprite(m_position, m_radius, m_sprite);
}

void LadderRenderComponent::ReceiveMessage(Message* msg)
{
}