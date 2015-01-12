#include "../Game/ComponentBallModel.h"

ComponentBallModel::ComponentBallModel() : 
IComponent()
,mMovementEnabled(false)
{

}

void ComponentBallModel::OnAttached(GameObject* inGameObject)
{
	IComponent::OnAttached(inGameObject);

	mInitialPosition = inGameObject->GetPosition();
}

void ComponentBallModel::Update(float inDT)
{

}