#include "../Structure/GameObject.h"
#include "../Foundation/Foundation.h"
#include <algorithm>

unsigned int GameObject::m_numGameObjects = 0;

GameObject::GameObject() :
m_index(m_numGameObjects++),
m_position(0),
m_scale(1.0, 1.0, 1.0),
m_rotationQuat(glm::quat())
{

}

GameObject::~GameObject()
{
    for(uint32_t i = 0; i < m_components.size(); ++i)
    {
        SAFE_DELETE(m_components[i]);
    }

	m_components.clear();
}

void GameObject::Attach(IComponent* in_component)
{
	for(std::vector<IComponent*>::const_iterator it = m_components.begin(); it != m_components.end(); ++it)
	{
		// Check if we have this Component
		if((*it) == in_component)
		{
			return;
		}
	}

	in_component->SetOwner(this);
	in_component->OnAttached(this);
	m_components.push_back(in_component);
}

void GameObject::Detach(IComponent* in_component)
{
	if(in_component == NULL)
		return;

	for(std::vector<IComponent*>::const_iterator it = m_components.begin(); it != m_components.end(); ++it)
	{
		// Check if we have this Component
		if((*it) == in_component)
		{
			in_component->SetOwner(NULL);
			in_component->OnDetached(this);
			m_components.erase(std::remove(m_components.begin(), m_components.end(), in_component));
			break;
		}
	}
}

void GameObject::MovePosition(Vector3 in_position)
{
	in_position = GetPosition() + in_position;

	for(uint32_t i = 0; i < m_components.size(); ++i)
    {
		m_components[i]->PrePositionSet(in_position);
	}

	SetPosition(in_position);
}

void GameObject::Update(float in_dt)
{
	MovePosition(m_velocity * in_dt);

	for(std::vector<IComponent*>::const_iterator it = m_components.begin(); it != m_components.end(); ++it)
	{
		if(*it)
		{
			(*it)->Update(in_dt);
		}
	}
}