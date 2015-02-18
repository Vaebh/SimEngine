#include "../Structure/System.h"

#include "../Structure/Component.h"

ISystem::ISystem()
{

}

void ISystem::AddComponent(IComponent* in_component)
{
	m_components.push_back(in_component);
	in_component->SetSystem(this);
}

void ISystem::RemoveComponent(IComponent* in_component)
{
	m_components.remove(in_component);
}