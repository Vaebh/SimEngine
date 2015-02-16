#ifndef SYSTEM_SIMENGINE
#define SYSTEM_SIMENGINE

#include "../Structure/Component.h"

#include <string>
#include <vector>

class ISystem
{
public:
	ISystem();

protected:
	std::vector<IComponent*> m_components;
};

#endif