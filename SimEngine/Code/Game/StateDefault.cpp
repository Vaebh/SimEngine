#include "../Game/StateDefault.h"

#include "../Application/Application.h"

#include "../Structure/GameObjectFactory.h"

#include "../Game/PlayerController.h"

StateDefault::StateDefault()
{
	m_player.reset(Application::GetApplication()->GetGameObjectFactory()->CreateSpriteGameObject("testAnim1"));
	m_player->Attach(new PlayerController());
}

StateDefault::~StateDefault()
{

}

void StateDefault::Update(float in_dt)
{
	m_player->Update(in_dt);
}