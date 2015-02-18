#include "../Structure/Component.h"

#include "../Structure/System.h"

IComponent::IComponent() : 
m_owner(NULL),
m_system(NULL)
{

}

IComponent::~IComponent()
{
	RemoveCompFromSystem();
}

void IComponent::OnAttached(GameObject* in_gameObject)
{
	m_owner = in_gameObject;
}

void IComponent::OnDetached(GameObject* in_gameObject)
{
	m_owner = NULL;

	RemoveCompFromSystem();
}

void IComponent::RemoveCompFromSystem()
{
	if(m_system != NULL)
	{
		m_system->RemoveComponent(this);
	}
}