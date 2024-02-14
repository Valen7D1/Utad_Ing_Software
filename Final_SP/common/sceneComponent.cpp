#include "sceneComponent.h"
#include "core.h"
#include "sys.h"
#include "entity.h"


void SceneLogicComponent::Slot()
{
	if (GetKeyState(VK_RETURN) & 0x8000)
	{
		entityOwner->toBeDeleted = true;
	}
}

void SceneRenderComponent::Slot()
{
	CORE_RenderCenteredSprite(vec2(SCR_WIDTH / 2, SCR_HEIGHT / 2), vec2(SCR_WIDTH, SCR_HEIGHT), m_sceneSprite);
}