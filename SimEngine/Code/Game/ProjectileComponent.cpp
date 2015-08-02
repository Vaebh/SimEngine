#include "../Game/ProjectileComponent.h"

#include "../Structure/GameObject.h"

ProjectileComponent::ProjectileComponent(float in_speed, Vector3 in_direction) :
m_speed(in_speed),
m_direction(in_direction)
{

}

void ProjectileComponent::Update(float in_dt)
{
	GetOwner()->MovePosition(m_direction * m_speed * in_dt);
}