#include "../Game/StateDefault.h"

#include "../Application/Application.h"

#include "../Structure/GameObjectFactory.h"

#include "../Game/PlayerController.h"

StateDefault::StateDefault()
{
	m_player.reset(Application::GetApplication()->GetGameObjectFactory()->CreateSpriteGameObject("testAnim1"));
	m_player->Attach(new PlayerController());
	m_player->SetPosition(Vector3(640.f, 360.f, 0.f));

	std::unique_ptr<GameObject> redBlock(Application::GetApplication()->GetGameObjectFactory()->CreateSpriteGameObject("red"));
	redBlock->SetPosition(Vector3(320.f, 660.f, 0.1f));
	m_blocks.push_back(std::move(redBlock));
	
}

StateDefault::~StateDefault()
{

}

#include "../Debug/Log.h"

void StateDefault::Update(float in_dt)
{
	static float grav = 0.f;

	m_player->Update(in_dt);

	if (m_player->GetPosition().y < 542.f)
	{
		grav += 0.5 * in_dt;
	}
	else
	{
		grav = 0.f;
	}

	Log().Get() << m_player->GetPosition().y;

	m_player->MovePosition(Vector3(0.f, grav, 0.f));
}