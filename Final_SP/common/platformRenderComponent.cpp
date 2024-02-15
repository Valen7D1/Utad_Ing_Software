#include "platformRenderComponent.h"
#include "core.h"
#include "message.h"


void PLatformRenderComponent::Slot()
{
	float sizeX = m_size.x / m_proportions.x;
	float sizeY = m_size.y / m_proportions.y;

	vec2 initialPosition = vec2(m_position-m_size/2);

	//platforms render
	vec2 position;
	position.x = initialPosition.x + m_proportions.x / 2;
	position.y = initialPosition.y + m_proportions.y / 2;

	for (int i = 0; i < sizeY; ++i) {
		for (int j = 0; j < sizeX; j++) {
			CORE_RenderCenteredSprite(position, m_proportions, m_sprite);
			position.x += m_proportions.x;
		}
		position.x = initialPosition.x + m_proportions.x / 2;
		position.y += m_proportions.y;
	}
}

void PLatformRenderComponent::ReceiveMessage(Message* msg)
{
}