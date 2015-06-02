#include "../Game/StateBattle.h"

#include "../Application/Application.h"

#include "../Structure/GameObject.h"
#include "../Structure/GameObjectFactory.h"

#include "../Rendering/SpriteComponent.h"

StateBattle::StateBattle()
{
	m_battleGrid = Application::GetApplication()->GetGameObjectFactory()->CreateGameObject();
	SpriteComponent* battleGridSprite = new SpriteComponent("testAnim1");
	m_battleGrid->Attach(battleGridSprite);

	battleGridSprite->AddAnimation("default", 6.0f, true, 6, "testAnim1", "testAnim2", "testAnim3", "testAnim4", "testAnim5", "testAnim6");
	battleGridSprite->SetDefaultAnimationClip("default");

	m_gameObjects.push_back(m_battleGrid);
}

StateBattle::~StateBattle()
{

}

void StateBattle::Update(float in_dt)
{
	for (std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
	{
		if ((*it) != NULL)
		{
			(*it)->Update(in_dt);
		}
	}
}