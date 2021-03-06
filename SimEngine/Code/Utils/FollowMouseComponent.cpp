#include "../Utils/FollowMouseComponent.h"
#include "../Rendering/RenderSystem.h"
#include "../Structure/GameObject.h"

FollowMouseComponent::FollowMouseComponent(AXIS inAxis) :
IComponent(),
mAxis(inAxis)
{

}

void FollowMouseComponent::Update(float in_dt)
{
	double mouseX, mouseY;

	//glfwGetCursorPos(RenderSystem::mWindow, &mouseX, &mouseY);

	int width, height;
	//glfwGetFramebufferSize(RenderSystem::mWindow, &width, &height);

	float xPos = m_owner->GetPosition().x;
	float yPos = m_owner->GetPosition().y;

	if(mAxis == X_AXIS || mAxis == BOTH_AXIS)
	{
		xPos = ((mouseX * 2) / width) - 1;
	}

	if(mAxis == Y_AXIS || mAxis == BOTH_AXIS)
	{
		yPos = -(((mouseY * 2) / height) - 1);
	}

	m_owner->SetPosition(Vector3(xPos, yPos, m_owner->GetPosition().z));
}