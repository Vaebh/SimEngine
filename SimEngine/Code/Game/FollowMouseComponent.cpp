#include "../Game/FollowMouseComponent.h"
#include "../Rendering/RenderSystem.h"

FollowMouseComponent::FollowMouseComponent(AXIS inAxis) :
IComponent(),
mAxis(inAxis)
{

}

void FollowMouseComponent::Update(float inDT)
{
	double mouseX, mouseY;

	glfwGetCursorPos(RenderSystem::mWindow, &mouseX, &mouseY);

	int width, height;
	glfwGetFramebufferSize(RenderSystem::mWindow, &width, &height);

	float xPos = mOwner->GetPosition().x;
	float yPos = mOwner->GetPosition().y;

	if(mAxis == X_AXIS || mAxis == BOTH_AXIS)
	{
		xPos = ((mouseX * 2) / width) - 1;
	}

	if(mAxis == Y_AXIS || mAxis == BOTH_AXIS)
	{
		yPos = -(((mouseY * 2) / height) - 1);
	}

	mOwner->SetPosition(Vector3(xPos, yPos, mOwner->GetPosition().z));
}