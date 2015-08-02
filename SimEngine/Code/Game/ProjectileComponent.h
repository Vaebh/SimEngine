#ifndef PROJECTILE_COMPONENT
#define PROJECTILE_COMPONENT

#include "../Structure/Component.h"

#include "../Structure/Vectors.h"

class ProjectileComponent : public IComponent
{
public:
	ProjectileComponent(float in_speed, Vector3 in_direction);

	virtual void Update(float in_dt);

private:
	float m_speed;
	Vector3 m_direction;
};

#endif