#ifndef SYSTEM_SIMENGINE
#define SYSTEM_SIMENGINE

#include <list>

class IComponent;

class ISystem
{
public:
	ISystem();

	virtual void AddComponent(IComponent* in_component);
	void RemoveComponent(IComponent* in_component);

protected:
	std::list<IComponent*> m_components;
};

#endif