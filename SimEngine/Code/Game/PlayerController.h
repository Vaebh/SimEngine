#ifndef PLAYER_CONTROLLER_SIMENGINE
#define PLAYER_CONTROLLER_SIMENGINE

#include "../Structure/Component.h"
#include <vector>
class PlayerController : public IComponent
{
public:
	PlayerController();
	~PlayerController();

	virtual void Update(float in_dt);

private:
	GameObject* m_bullet;
	bool m_fired;

	Vector3 m_bulletDir;

	float m_fireTimer;
	float m_fireInterval;

	std::vector<GameObject*> m_bullets;
};

#endif